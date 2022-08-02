cmake_minimum_required(VERSION 3.0)

# GMLib项目
project(GMLib LANGUAGES C)

# 设置DEBUG模式时GMLIB_DEBUG宏，开启错误提示
set(CMAKE_C_FLAGS_DEBUG -DGMLIB_DEBUG)

# 设置RELEASE模式时GMLIB_DEBUG宏，开启错误提示
# set(CMAKE_C_FLAGS_RELEASE -DGMLIB_DEBUG)

# 设置字符集
if(MSVC)
    # 在MSVC中添加编译参数，设置默认编码utf-8
    add_compile_options(/source-charset:utf-8)
endif()

# 设置可执行文件输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ./output/exe/DEBUG)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ./output/exe/RELEASE)

# 设置静态库文件输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ./output/lib/DEBUG)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ./output/lib/RELEASE)

# 设置Include目录
include_directories(include)

# 可执行文件 gmlib-test 项目
add_executable(gmlib-test
    # bint 大整数
    src/bint/bint_add_sub.c
    src/bint/bint_cast.c
    src/bint/bint_cmp.c
    src/bint/bint_div.c
    src/bint/bint_mul.c
    src/bint/bint_pow.c
    src/bint/bint_shift.c
    src/bint/bint_utils.c
    # 对称密码工作模式
    src/cipher/cipher_mode/cbc.c
    src/cipher/cipher_mode/ctr.c
    src/cipher/cipher_mode/ecb.c
    src/cipher/cipher_mode/pad.c
    # SM4算法
    src/cipher/sm4/sm4.c
    src/cipher/sm4/sm4_common.c
    src/cipher/sm4/sm4_mode_cbc.c
    src/cipher/sm4/sm4_mode_ctr.c
    src/cipher/sm4/sm4_mode_ecb.c
    src/cipher/sm4/sm4_tbox.c
    # 椭圆曲线
    src/ec/ec_add.c
    src/ec/ec_cast.c
    src/ec/ec_const.c
    src/ec/ec_ctx.c
    src/ec/ec_jacobian.c
    src/ec/ec_mul.c
    src/ec/ec_utils.c
    # SM3算法
    src/hash/sm3/sm3.c
    src/hash/sm3/sm3_common.c
    # bint大整数数学运算
    src/math/bint_fp.c
    src/math/bint_gcd.c
    src/math/bint_prime.c
    src/math/bint_rand.c
    # SM2算法
    src/publickey/sm2/sm2_alg.c
    src/publickey/sm2/sm2_const.c
    src/publickey/sm2/sm2_sign.c
    src/publickey/sm2/sm2_verify.c
    # 功能函数
    src/utils.c
    # 测试文件
    test/main.c
    test/bint/test_bint.c
    test/bint/test_bint_alg.c
    test/bint/test_bint_cast.c
    test/bint/test_bint_utils.c
    test/cipher/sm4/test_sm4.c
    test/cipher/sm4/test_sm4_alg.c
    test/cipher/sm4/test_sm4_cbc.c
    test/cipher/sm4/test_sm4_ctr.c
    test/cipher/sm4/test_sm4_ecb.c
    test/ec/test_ec.c
    test/ec/test_ec_add.c
    test/ec/test_ec_mul.c
    test/ec/test_ec_utils.c
    test/hash/sm3/test_sm3.c
    test/math/test_bint_gcd.c
    test/math/test_math.c
    test/math/test_math_prime.c
    test/publickey/sm2/test_sm2.c
    test/publickey/sm2/test_sm2_sign_verify.c
)

# 设置 gmlib-test 项目 GMLIB_TEST 宏，用于限制随机数发生器的值
# 便于测试正确性
# 并开启 GMLIB_DEBUG
target_compile_definitions(gmlib-test PRIVATE GMLIB_TEST GMLIB_DEBUG)

# gmlib 库文件
add_library(gmlib STATIC
    src/bint/bint_add_sub.c
    src/bint/bint_cast.c
    src/bint/bint_cmp.c
    src/bint/bint_div.c
    src/bint/bint_mul.c
    src/bint/bint_pow.c
    src/bint/bint_shift.c
    src/bint/bint_utils.c
    src/cipher/cipher_mode/cbc.c
    src/cipher/cipher_mode/ctr.c
    src/cipher/cipher_mode/ecb.c
    src/cipher/cipher_mode/pad.c
    src/cipher/sm4/sm4.c
    src/cipher/sm4/sm4_common.c
    src/cipher/sm4/sm4_mode_cbc.c
    src/cipher/sm4/sm4_mode_ctr.c
    src/cipher/sm4/sm4_mode_ecb.c
    src/cipher/sm4/sm4_tbox.c
    src/ec/ec_add.c
    src/ec/ec_cast.c
    src/ec/ec_const.c
    src/ec/ec_ctx.c
    src/ec/ec_jacobian.c
    src/ec/ec_mul.c
    src/ec/ec_utils.c
    src/hash/sm3/sm3.c
    src/hash/sm3/sm3_common.c
    src/math/bint_fp.c
    src/math/bint_gcd.c
    src/math/bint_prime.c
    src/math/bint_rand.c
    src/publickey/sm2/sm2_alg.c
    src/publickey/sm2/sm2_const.c
    src/publickey/sm2/sm2_sign.c
    src/publickey/sm2/sm2_verify.c
    src/utils.c
)

