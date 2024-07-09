from pycpuid import InstructionSet


isa = InstructionSet()

pre_define_list = []
compile_option_list = []
if isa.AES():
    pre_define_list.append("CPU_FLAG_AES")
    compile_option_list.append("-maes")
if isa.AVX2():
    pre_define_list.append("CPU_FLAG_AVX2")
    compile_option_list.append("-mavx2")
if isa.BMI2():
    pre_define_list.append("CPU_FLAG_BMI2")
    compile_option_list.append("-mbmi2")
if isa.MOVBE():
    pre_define_list.append("CPU_FLAG_MOVBE")
    compile_option_list.append("-mmovbe")
if isa.PCLMULQDQ():
    pre_define_list.append("CPU_FLAG_PCLMUL")
    compile_option_list.append("-mpclmul")
if isa.RDRAND():
    pre_define_list.append("CPU_FLAG_RDRAND")
    compile_option_list.append("-mrdrnd")
if isa.RDSEED():
    pre_define_list.append("CPU_FLAG_RDSEED")
    compile_option_list.append("-mrdseed")
if isa.SHA():
    pre_define_list.append("CPU_FLAG_SHA")
    compile_option_list.append("-msha")
if isa.SSE2():
    pre_define_list.append("CPU_FLAG_SSE2")
    compile_option_list.append("-msse2")
if isa.SSE41():
    pre_define_list.append("CPU_FLAG_SSE4_1")
    compile_option_list.append("-msse4.1")
if isa.SSSE3():
    pre_define_list.append("CPU_FLAG_SSSE3")
    compile_option_list.append("-mssse3")

for item in pre_define_list:
    print("add_definitions(-D{})".format(item))
print("set(PROJECT_COMPILE_OPTIONS {})".format(" ".join(compile_option_list)))
