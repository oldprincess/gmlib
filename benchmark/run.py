#!/usr/bin/env python3
"""Collect CTest and speed-test output for the current checkout."""

import argparse
import hashlib
import json
import os
from pathlib import Path
import platform
import re
import shutil
import subprocess
import sys


def query(command, cwd=None):
    return subprocess.check_output(
        command,
        cwd=cwd,
        stderr=subprocess.DEVNULL,
        text=True,
        encoding="utf-8",
        errors="replace",
    ).strip()


def read_cache(build_dir):
    values = {}
    for line in (build_dir / "CMakeCache.txt").read_text(encoding="utf-8").splitlines():
        if line and not line.startswith(("#", "//")) and "=" in line:
            key, value = line.split("=", 1)
            values[key.split(":", 1)[0]] = value
    return values


def platform_info(build_dir, cache, config):
    cpu = platform.processor() or "unknown"
    memory = "unknown"
    if sys.platform.startswith("linux"):
        for line in Path("/proc/cpuinfo").read_text().splitlines():
            key, _, value = line.partition(":")
            if key.strip() in ("model name", "Hardware"):
                cpu = value.strip()
                break
        for line in Path("/proc/meminfo").read_text().splitlines():
            if line.startswith("MemTotal:"):
                memory = int(line.split()[1]) * 1024
                break
    elif os.name == "nt":
        powershell = shutil.which("powershell") or shutil.which("pwsh")
        if powershell:
            try:
                data = json.loads(
                    query(
                        [
                            powershell,
                            "-NoProfile",
                            "-NonInteractive",
                            "-Command",
                            "$cpu = @(Get-CimInstance Win32_Processor); "
                            "$os = Get-CimInstance Win32_OperatingSystem; "
                            "[pscustomobject]@{cpu = ($cpu.Name -join '; '); "
                            "memory = [long]$os.TotalVisibleMemorySize * 1024} | "
                            "ConvertTo-Json -Compress",
                        ]
                    )
                )
                cpu, memory = data["cpu"], data["memory"]
            except (subprocess.SubprocessError, ValueError, KeyError):
                pass

    compiler = {}
    cmake_version = ".".join(
        cache.get("CMAKE_CACHE_" + part + "_VERSION", "")
        for part in ("MAJOR", "MINOR", "PATCH")
    )
    compiler_file = build_dir / "CMakeFiles" / cmake_version / "CMakeCXXCompiler.cmake"
    if compiler_file.is_file():
        compiler = dict(
            re.findall(
                r'set\((CMAKE_CXX_COMPILER_(?:ID|VERSION)) "([^"]*)"\)',
                compiler_file.read_text(encoding="utf-8"),
            )
        )
    options = {
        key: value
        for key, value in sorted(cache.items())
        if key.startswith(("SUPPORT_", "CMAKE_CXX_FLAGS"))
    }
    return {
        "OS": platform.platform(),
        "Architecture": platform.machine(),
        "CPU": cpu,
        "Logical CPUs": os.cpu_count(),
        "Memory (bytes)": memory,
        "Compiler": compiler.get("CMAKE_CXX_COMPILER_ID", "unknown"),
        "Compiler version": compiler.get("CMAKE_CXX_COMPILER_VERSION", "unknown"),
        "Configuration": config or "unspecified",
        "CMake generator": cache.get("CMAKE_GENERATOR", "unknown"),
        "Build options": options,
    }


def remove_record(directory, benchmark_dir):
    # Only remove direct, marked children of this script's output directory.
    if directory.is_symlink() or directory.resolve().parent != benchmark_dir.resolve():
        raise ValueError(
            "Refusing to remove an unexpected record path: " + str(directory)
        )
    if not (directory / "_platform.txt").is_file():
        raise ValueError(
            "Record directory has no _platform.txt marker: " + str(directory)
        )
    shutil.rmtree(directory)


def run_logged(command, cwd, destination):
    with destination.open("wb") as output:
        try:
            return subprocess.run(
                command, cwd=cwd, stdout=output, stderr=subprocess.STDOUT, check=False
            ).returncode
        except OSError as error:
            output.write((str(error) + "\n").encode("utf-8"))
            return 127


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "test_directory", type=Path, help="Directory containing *_test executables"
    )
    parser.add_argument("--config", help="CMake configuration, e.g. Release")
    args = parser.parse_args()
    test_dir = args.test_directory.resolve()
    if not test_dir.is_dir():
        parser.error("Test directory does not exist: " + str(test_dir))

    suffix = "_test.exe" if os.name == "nt" else "_test"
    tests = [
        path
        for path in sorted(test_dir.iterdir(), key=lambda path: path.name.lower())
        if path.is_file()
        and path.name.lower().endswith(suffix)
        and (os.name == "nt" or os.access(path, os.X_OK))
    ]
    if not tests:
        parser.error("No *_test executables found in " + str(test_dir))
    build_dir = next(
        (
            path
            for path in (test_dir, *test_dir.parents)
            if (path / "CMakeCache.txt").is_file()
            and (path / "CTestTestfile.cmake").is_file()
        ),
        None,
    )
    if build_dir is None:
        parser.error(
            "Cannot find the CMake/CTest build directory; enable PROJECT_BUILD_TEST"
        )
    cache = read_cache(build_dir)
    configs = cache.get("CMAKE_CONFIGURATION_TYPES", "").split(";")
    config = args.config or next(
        (name for name in configs if name and name.lower() == test_dir.name.lower()), ""
    )
    config = config or cache.get("CMAKE_BUILD_TYPE", "")
    if cache.get("CMAKE_CONFIGURATION_TYPES") and not config:
        parser.error(
            "Cannot infer the build configuration; pass --config Release or Debug"
        )
    if args.config:
        actual_config = next(
            (
                name
                for name in configs
                if name and name.lower() == test_dir.name.lower()
            ),
            "",
        )
        actual_config = actual_config or cache.get("CMAKE_BUILD_TYPE", "")
        if actual_config and args.config.lower() != actual_config.lower():
            parser.error(
                "--config does not match the test directory's configuration: "
                + actual_config
            )
    ctest = shutil.which("ctest") or shutil.which(cache.get("CMAKE_CTEST_COMMAND", ""))
    if not ctest:
        parser.error("CTest was not found; add the CMake bin directory to PATH")

    benchmark_dir = Path(__file__).resolve().parent
    repo = benchmark_dir.parent
    commit = query(["git", "rev-parse", "HEAD"], repo)
    info = platform_info(build_dir, cache, config)
    fingerprint = hashlib.sha256(
        json.dumps(info, sort_keys=True).encode("utf-8")
    ).hexdigest()[:8]
    slug = re.sub(r"[^a-z0-9]+", "-", info["CPU"].lower()).strip("-")[:60]
    environment = "-".join(
        (platform.system().lower(), platform.machine().lower(), slug, fingerprint)
    )
    destination = benchmark_dir / environment

    commit_file = benchmark_dir / "_commit.txt"
    previous_commit = commit_file.read_text().strip() if commit_file.exists() else None
    if previous_commit != commit:
        for directory in benchmark_dir.iterdir():
            if directory.is_dir() and (directory / "_platform.txt").is_file():
                remove_record(directory, benchmark_dir)
    if destination.exists():
        remove_record(destination, benchmark_dir)
    destination.mkdir()
    commit_file.write_text(commit + "\n", encoding="utf-8")

    ctest_command = [
        ctest,
        "--test-dir",
        str(build_dir),
        "--output-on-failure",
        "--no-tests=error",
    ]
    if config:
        ctest_command.extend(["-C", config])
    with (destination / "_platform.txt").open("w", encoding="utf-8") as record:
        record.write("Git commit: " + commit + "\n")
        for key, value in info.items():
            record.write(
                key
                + ": "
                + (
                    json.dumps(value, sort_keys=True)
                    if isinstance(value, dict)
                    else str(value)
                )
                + "\n"
            )
        record.write(
            "Compiler path: " + cache.get("CMAKE_CXX_COMPILER", "unknown") + "\n"
        )
        record.write("Test arguments: speed\n\nExit codes:\n")
        record.flush()
        print("Results: " + str(destination), flush=True)
        print("[CTest] Running correctness tests...", flush=True)
        code = run_logged(ctest_command, build_dir, destination / "_ctest.txt")
        record.write("ctest: " + str(code) + "\n")
        record.flush()
        failed = code != 0
        print("[CTest] Exit code: " + str(code), flush=True)
        for index, executable in enumerate(tests, 1):
            name = executable.stem if os.name == "nt" else executable.name
            name = name[: -len("_test")]
            print(f"[{index}/{len(tests)}] {executable.name} speed", flush=True)
            code = run_logged(
                [str(executable), "speed"], test_dir, destination / (name + ".txt")
            )
            record.write(executable.name + ": " + str(code) + "\n")
            record.flush()
            failed = failed or code != 0
            print("Exit code: " + str(code), flush=True)
    print("Finished with failures." if failed else "Finished successfully.", flush=True)
    return 1 if failed else 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except (OSError, ValueError, subprocess.SubprocessError) as error:
        print("Error: " + str(error), file=sys.stderr)
        sys.exit(1)
