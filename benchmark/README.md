# 测试记录

这里保存最近一次测试版本的原始终端输出，不整理性能报告，也不按日期归档。

## 采集结果

需要 Python 3.9 或更新版本、Git 和 CTest。请先在当前源码版本下完成 Release 构建；脚本不会编译代码。

在项目根目录执行：

```sh
# Linux / 单配置生成器
python3 benchmark/run.py build
```

```powershell
# Windows / Visual Studio
python benchmark/run.py build/Release
```

也可以传入测试程序目录的绝对路径。脚本只查找该目录直接包含的 `*_test`（Linux）或 `*_test.exe`（Windows），不递归扫描。默认从该目录或其父目录定位 CTest 构建目录，并从 CMake 配置推断构建类型；必要时显式指定：

```sh
python3 benchmark/run.py /path/to/test-directory --config Release
```

执行顺序：

1. 收集 Git hash、平台和 CMake 构建信息。
2. 运行 `ctest --test-dir <build-directory> --output-on-failure --no-tests=error`，多配置构建会加上 `-C <config>`。
3. 按名称排序，逐个运行 `<name>_test speed`，合并保存标准输出和标准错误到 `<name>.txt`。

不支持 `speed` 参数的程序通常会忽略该参数，它们的文件仅包含原有测试输出。CTest 或某个程序失败时，脚本继续收集其它结果，最终返回非零退出码。每项的退出码记录在 `_platform.txt` 中；脚本本身不会在算法输出文件中添加表头或修改原始数据。

## 目录与覆盖规则

```text
benchmark/
├── README.md
├── run.py
├── _commit.txt
├── linux-x86_64-<cpu>-<environment-id>/
│   ├── _ctest.txt
│   ├── _platform.txt
│   ├── aes.txt
│   ├── sm3.txt
│   └── sm4.txt
└── windows-amd64-<cpu>-<environment-id>/
    ├── _ctest.txt
    ├── _platform.txt
    ├── aes.txt
    └── sm4.txt
```

- `_commit.txt` 保存本轮记录对应的完整 Git hash。
- Git hash 变化时，脚本删除旧版本的平台记录；同一 hash 下可以追加不同环境。
- 同一环境重新执行时，整个环境目录会被覆盖，避免保留本次没有运行的旧结果。
- 环境标识根据操作系统、CPU、核心数、内存、编译器、构建配置和编译选项生成，不要求租用同一台服务器。相同 CPU 但其它配置不同的机器也可以分别记录。
- `_ctest.txt` 和 `_platform.txt` 的下划线前缀便于与算法输出区分；其它文件按字母顺序浏览。

脚本仅清理 `benchmark/` 下包含 `_platform.txt` 标记的平台目录，不删除脚本或文档。不要把手工维护的内容放入这些自动生成的目录，也不要同时运行多个采集进程。

`_platform.txt` 记录系统、CPU、逻辑核心数、内存、编译器版本、构建配置、CMake 选项、Git 工作区状态和命令退出码。Git hash 表示采集时源码仓库的 HEAD，脚本无法证明现有二进制由该版本构建，请在切换源码后重新构建。未提交的源码修改会标记为 `dirty`；`benchmark/` 自身的记录变化不计入该标记。
