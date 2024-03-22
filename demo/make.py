import glob
import sys
import os
import cpuid


try:
    src, dst = sys.argv[1], sys.argv[2]

    source = " ".join(glob.glob("../src/**/*.cpp", recursive=True))
    define = " "
    option = " "

    try:
        flag_lst, option_lst = cpuid.support_flag()
        define = " ".join([f"-DCPU_FLAG_{flag}" for flag in flag_lst])
        option = " ".join(option_lst)
    except:
        pass

    code = f"g++ -o {dst} -I ../include {src} {source} {define} {option}"
    print(code)
    os.system(code)
except:
    print(": python make.py [source_path] [dist_path]")
    raise
