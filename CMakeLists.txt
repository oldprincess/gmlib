cmake_minimum_required(VERSION 3.18)

project(gmlib CXX)

add_definitions(
    -DSUPPORT_BASE64_CHROMIUM
    -DSUPPORT_SM3_YANG15
    -DSUPPORT_SM4_LANG18
    -DSUPPORT_SM4_GONG23
    -DSUPPORT_UBLOCK_GONG25
)
set(PROJECT_BUILD_TEST ON)
set(THIRD_PARTY 
    aes
    asn1
    ballet
    base64
    block_cipher_mode
    cpuinfo
    des
    ghash
    # hash_lib
    md5
    memory_utils
    number
    # rng
    sha1
    sha2
    sm2
    sm3
    sm4
    sm9
    ublock
)

#######################################################
## ================================================= ##
## ================================================= ##
## ================================================= ##
#######################################################

if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|amd64|AMD64)$")
    set(ARCH_X86_64 TRUE)
    message(STATUS "Detected architecture: x86_64 (AMD64)")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(i386|i686|x86)$")
    set(ARCH_X86 TRUE)
    message(STATUS "Detected architecture: x86 (32-bit)")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm|armv7l|armv6l)$")
    set(ARCH_ARM TRUE)
    message(STATUS "Detected architecture: ARM (32-bit)")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(aarch64|arm64)$")
    set(ARCH_AARCH64 TRUE)
    message(STATUS "Detected architecture: AArch64 (ARM64)")
else()
    message(WARNING "Unrecognized architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER_GCC TRUE)
    message(STATUS "Detected compiler: GCC/GNU")
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(COMPILER_CLANG TRUE)
    message(STATUS "Detected compiler: Clang")
elseif(CMAKE_C_COMPILER_ID STREQUAL "AppleClang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    set(COMPILER_APPLE_CLANG TRUE)
    message(STATUS "Detected compiler: Apple Clang")
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC" OR CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(COMPILER_MSVC TRUE)
    message(STATUS "Detected compiler: MSVC (Visual Studio)")
elseif(CMAKE_C_COMPILER_ID MATCHES "Intel" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    set(COMPILER_INTEL TRUE)
    message(STATUS "Detected compiler: Intel C++")
else()
    message(WARNING "Unrecognized compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

#######################################################
## ================================================= ##
## ================================================= ##
## ================================================= ##
#######################################################

set(PROJECT_NAME_ gmlib)
set(CMAKE_CXX_STANDARD 17)

set(BASE_INCLUDE_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(BASE_LIB_SRC_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BASE_TEST_SRC_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)

file(GLOB_RECURSE PROJECT_INCLUDE  ${BASE_INCLUDE_DIRECTORY}/*.h)
file(GLOB_RECURSE PROJECT_LIB_SRC  ${BASE_LIB_SRC_DIRECTORY}/*.cpp)
file(GLOB_RECURSE PROJECT_TEST_SRC ${BASE_TEST_SRC_DIRECTORY}/*.cpp)

add_library(${PROJECT_NAME_}_static STATIC ${PROJECT_LIB_SRC} ${PROJECT_INCLUDE})
include_directories(${BASE_INCLUDE_DIRECTORY})
if(COMPILER_MSVC)
    target_compile_options(${PROJECT_NAME_}_static PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME_}_static PRIVATE -fPIC -Wall)
endif()

#######################################################
## ================================================= ##
## ================================================= ##
## ================================================= ##
#######################################################

# des
set_source_files_properties(
    ${BASE_LIB_SRC_DIRECTORY}/des/provider.cpp
    PROPERTIES
    COMPILE_FLAGS ""
)
# aes
if(ARCH_X86 OR ARCH_X86_64)
    if(COMPILER_MSVC)
        set(AES_AESNI_FLAGS "-D__AES__ -D__SSE2__")
    else()
        set(AES_AESNI_FLAGS "-maes -msse2")
    endif()
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/aes/aes_aesni.cpp
        ${BASE_LIB_SRC_DIRECTORY}/aes/provider_aes_aesni.cpp
        PROPERTIES
        COMPILE_FLAGS ${AES_AESNI_FLAGS}
    )
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/aes/provider.cpp
        PROPERTIES
        COMPILE_FLAGS "-DAES_IMPL_AESNI"
    )
elseif(ARCH_AARCH64)
    if(COMPILER_MSVC)
        set(AES_ARM_AES_FLAGS "-D__ARM_NEON -D__ARM_FEATURE_AES=1")
    else()
        set(AES_ARM_AES_FLAGS "-march=armv8-a+crypto")
    endif()
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/aes/aes_arm_aes.cpp
        ${BASE_LIB_SRC_DIRECTORY}/aes/provider_aes_arm_aes.cpp
        PROPERTIES
        COMPILE_FLAGS ${AES_ARM_AES_FLAGS}
    )
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/aes/provider.cpp
        PROPERTIES
        COMPILE_FLAGS "-DAES_IMPL_ARM_AES"
    )
endif()
# base64
if(ARCH_X86_64)
    if(COMPILER_MSVC)
        set(BASE64_AVX2_FLAGS "-D__AVX2__")
    else()
        set(BASE64_AVX2_FLAGS "-mavx2")
    endif()
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/base64/base64_avx2.cpp
        PROPERTIES
        COMPILE_FLAGS ${BASE64_AVX2_FLAGS}
    )
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/base64/provider.cpp
        PROPERTIES
        COMPILE_FLAGS "-DBASE64_IMPL_AVX2"
    )
endif()
# ghash
if(ARCH_X86_64)
    if(COMPILER_MSVC)
        set(GHASH_PCLMUL_FLAGS "-D__PCLMUL__ -D__SSE2__ -D__SSSE3__")
    else()
        set(GHASH_PCLMUL_FLAGS "-mpclmul -msse2 -mssse3")
    endif()
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/ghash/ghash_pclmul.cpp
        ${BASE_LIB_SRC_DIRECTORY}/ghash/provider_ghash_pclmul.cpp
        PROPERTIES
        COMPILE_FLAGS ${GHASH_PCLMUL_FLAGS}
    )
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/ghash/provider.cpp
        PROPERTIES
        COMPILE_FLAGS "-DGHASH_IMPL_PCLMUL"
    )
endif()
# memory_utils
if(ARCH_X86_64)
    if(COMPILER_MSVC)
        set(FLAGS "-D__AVX2__")
    else()
        set(FLAGS "-mavx2")
    endif()
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/memory_utils/memxor_avx2.cpp
        PROPERTIES
        COMPILE_FLAGS ${FLAGS}
    )
    if(COMPILER_MSVC)
        set(FLAGS "-D__SSE2__")
    else()
        set(FLAGS "-msse2")
    endif()
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/memory_utils/memxor_sse2.cpp
        PROPERTIES
        COMPILE_FLAGS ${FLAGS}
    )
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/memory_utils/memxor.cpp
        PROPERTIES
        COMPILE_FLAGS "-D__AVX2__ -D__SSE2__"
    )
endif()
# number
if(ARCH_X86_64)
    if(COMPILER_MSVC)
        set(NUMBER_X64_FLAGS "-D__MOVBE__ -D__BMI2__")
    else()
        set(NUMBER_X64_FLAGS "-mmovbe -mbmi2")
    endif()
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/number/mont256_x64.cpp
        ${BASE_LIB_SRC_DIRECTORY}/number/mpz_x64.cpp
        ${BASE_LIB_SRC_DIRECTORY}/number/uint256_x64.cpp
        PROPERTIES
        COMPILE_FLAGS ${NUMBER_X64_FLAGS}
    )
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/number/provider.cpp
        PROPERTIES
        COMPILE_FLAGS "-DNUMBER_IMPL_X64"
    )
endif()
# sha1
if(ARCH_X86_64)
    if(COMPILER_MSVC)
        set(SHA1_SHA_FLAGS "-D__SHA__ -D__SSE4_1__")
    else()
        set(SHA1_SHA_FLAGS "-msha -msse4.1")
    endif()
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/sha1/sha1_sha.cpp
        PROPERTIES
        COMPILE_FLAGS ${SHA1_SHA_FLAGS}
    )
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/sha1/provider_sha1_sha.cpp
        PROPERTIES
        COMPILE_FLAGS ${SHA1_SHA_FLAGS}
    )
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/sha1/provider.cpp
        PROPERTIES
        COMPILE_FLAGS "-DSHA1_IMPL_SHA"
    )
endif()
# sha2
if(ARCH_X86_64)
    if(COMPILER_MSVC)
        set(SHA2_SHA_FLAGS "-D__SHA__ -D__SSE4_1__")
    else()
        set(SHA2_SHA_FLAGS "-msha -msse4.1")
    endif()
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/sha2/sha224_256_sha.cpp
        PROPERTIES
        COMPILE_FLAGS ${SHA2_SHA_FLAGS}
    )
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/sha2/provider_sha2_sha.cpp
        PROPERTIES
        COMPILE_FLAGS ${SHA2_SHA_FLAGS}
    )
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/sha2/provider.cpp
        PROPERTIES
        COMPILE_FLAGS "-DSHA224_256_IMPL_SHA"
    )
endif()
# sm4
if(ARCH_X86_64)
    if(COMPILER_MSVC)
        set(SM4_LANG18_FLAGS "-D__AVX2__")
        set(SM4_GONG23_FLAGS "-D__AVX512BW__ -D__AVX512VL__ -D__AVX512F__ -D__GFNI__")
    else()
        set(SM4_LANG18_FLAGS "-mavx2")
        set(SM4_GONG23_FLAGS "-mavx512bw -mavx512vl -mavx512f -mgfni")
    endif()
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/sm4/sm4_lang18.cpp
        ${BASE_LIB_SRC_DIRECTORY}/sm4/provider_sm4_lang18.cpp
        PROPERTIES
        COMPILE_FLAGS ${SM4_LANG18_FLAGS}
    )
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/sm4/sm4_gong23.cpp
        ${BASE_LIB_SRC_DIRECTORY}/sm4/provider_sm4_gong23.cpp
        PROPERTIES
        COMPILE_FLAGS ${SM4_GONG23_FLAGS}
    )
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/sm4/provider.cpp
        PROPERTIES
        COMPILE_FLAGS "-DSM4_IMPL_LANG18 -DSM4_IMPL_GONG23"
    )
endif()
# ublock
if(ARCH_X86_64)
    if(COMPILER_MSVC)
        set(UBLOCK_STANDARD_FLAGS "-D__SSSE3__")
    else()
        set(UBLOCK_STANDARD_FLAGS "-mssse3")
    endif()
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/ublock/ublock_standard.cpp
        ${BASE_LIB_SRC_DIRECTORY}/ublock/provider_ublock_standard.cpp
        PROPERTIES
        COMPILE_FLAGS ${UBLOCK_STANDARD_FLAGS}
    )
    if(COMPILER_MSVC)
        set(UBLOCK_GONG25_FLAGS "-D__AVX2__")
    else()
        set(UBLOCK_GONG25_FLAGS "-mavx2")
    endif()
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/ublock/ublock_gong25.cpp
        ${BASE_LIB_SRC_DIRECTORY}/ublock/provider_ublock_gong25.cpp
        PROPERTIES
        COMPILE_FLAGS ${UBLOCK_GONG25_FLAGS}
    )
    set_source_files_properties(
        ${BASE_LIB_SRC_DIRECTORY}/ublock/provider.cpp
        PROPERTIES
        COMPILE_FLAGS "-DUBLOCK_IMPL_STANDARD -DUBLOCK_IMPL_GONG25"
    )
endif()

#######################################################
## ================================================= ##
## ================================================= ##
## ================================================= ##
#######################################################

if(${PROJECT_BUILD_TEST})
    enable_testing()
    foreach(THIRD_PARTY_NAME ${THIRD_PARTY})
        file(   
            GLOB_RECURSE
            MODULE_TEST_SRC
            ${BASE_TEST_SRC_DIRECTORY}/${THIRD_PARTY_NAME}/*.cpp
        )
        add_executable(
            ${THIRD_PARTY_NAME}_test
            ${PROJECT_INCLUDE}
            ${MODULE_TEST_SRC}
        )
        target_link_libraries(
            ${THIRD_PARTY_NAME}_test
            PUBLIC
            ${PROJECT_NAME_}_static
        )
        add_test(NAME ${THIRD_PARTY_NAME}_test COMMAND ${THIRD_PARTY_NAME}_test)
    endforeach()
endif()

