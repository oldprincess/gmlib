cmake_minimum_required(VERSION 3.0)

# GMLib项目
project(GMLib LANGUAGES C)

# 设置GMLIB_DEBUG宏，开启错误提示
set(CMAKE_C_FLAGS -DGMLIB_DEBUG)

# 设置字符集
if(MSVC)
    # 在MSVC中添加编译参数，设置默认编码utf-8
    add_compile_options(/source-charset:utf-8)
endif()

# 设置可执行文件输出路径
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# 设置静态库文件输出路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# 设置全局Include目录
include_directories(include)

# 源文件列表
file(GLOB ALL_SOURCE
    "src/*.c"
    "src/bint/*.c"
    "src/cipher/mode/*.c"
    "src/cipher/mode/gcm/*.c"
    "src/cipher/*.c"
    "src/ec/*.c"
    "src/hash/sm3/*.c"
    "src/math/*.c"
    "src/publickey/sm2/*.c"
    "src/stream/zuc/*.c"
)

# 测试文件列表
file(GLOB ALL_TEST_SOURCE
    "test/bint/*.c"
    "test/cipher/*.c"
    "test/ec/*.c"
    "test/hash/sm3/*.c"
    "test/math/*.c"
    "test/publickey/sm2/*.c"
    "test/stream/zuc/*.c"
)

# 内部.h文件列表
file(GLOB LOCAL_INCLUDE
    "src/*.h"
    "src/bint/*.h"
    "src/cipher/mode/*.h"
    "src/cipher/mode/gcm/*.h"
    "src/cipher/sm4/*.h"
    "src/cipher/aes/*.h"
    "src/ec/*.h"
    "src/hash/sm3/*.h"
    "src/math/*.h"
    "src/publickey/sm2/*.h"
    "src/stream/zuc/*.h"
)

# 外部.h文件
file(GLOB GMLIB_INCLUDE
    "include/gmlib/*.h"
    "include/gmlib/cipher/*.h"
    "include/gmlib/hash/*.h"
    "include/gmlib/publickey/*.h"
    "include/gmlib/stream/*.h"
)

# 可执行文件 gmlib-test 项目
add_executable(gmlib-test
    ${ALL_SOURCE}
    ${LOCAL_INCLUDE}
    ${GMLIB_INCLUDE}
    # 测试文件
    test/main.c
    ${ALL_TEST_SOURCE}
)


# 设置 gmlib-test 项目 GMLIB_TEST 宏，用于限制随机数发生器的值，便于测试正确性
# 并开启 GMLIB_DEBUG
target_compile_definitions(gmlib-test PRIVATE GMLIB_TEST GMLIB_DEBUG)

# gmlib 库文件
add_library(gmlib STATIC
    ${ALL_SOURCE}
    ${LOCAL_INCLUDE}
    ${GMLIB_INCLUDE}
)

add_executable(gmlib-demo
    demo/demo_aesgcm.c
)

target_link_libraries(gmlib-demo gmlib)

