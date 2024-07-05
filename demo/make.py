import glob
import sys
import os


try:
    src, dst = sys.argv[1], sys.argv[2]

    source = " ".join(glob.glob("../src/**/*.cpp", recursive=True))
    define = " "
    option = " "

    code = f"g++ -o {dst} -I ../include {src} {source} {define} {option}"
    print(code)
    os.system(code)
except:
    print(": python make.py [source_path] [dist_path]")
    raise
