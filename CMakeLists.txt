cmake_minimum_required(VERSION 3.18)

project(gmlib CXX)

option(PROJECT_BUILD_TEST "Build GMLib tests" ON)

option(SUPPORT_AES_AESNI "Build the AES-NI implementation" ON)
option(SUPPORT_AES_ARM_AES "Build the ARMv8 Crypto Extensions AES implementation" ON)
option(SUPPORT_BASE64_AVX2 "Build the AVX2 Base64 implementation" ON)
option(SUPPORT_BASE64_CHROMIUM "Build the Chromium Base64 implementation" ON)
option(SUPPORT_GHASH_PCLMUL "Build the PCLMULQDQ GHASH implementation" ON)
option(SUPPORT_MEMXOR_AVX2 "Build the AVX2 memxor implementation" ON)
option(SUPPORT_MEMXOR_SSE2 "Build the SSE2 memxor implementation" ON)
option(SUPPORT_NUMBER_X64 "Build the BMI2/MOVBE number implementation" ON)
option(SUPPORT_SHA1_SHA "Build the Intel SHA Extensions SHA-1 implementation" ON)
option(SUPPORT_SHA2_SHA "Build the Intel SHA Extensions SHA-224/256 implementation" ON)
option(SUPPORT_SM3_YANG15 "Build the Yang15 SM3 implementation" ON)
option(SUPPORT_SM4_SM4NI "Build the AES-NI based SM4 implementation" ON)
option(SUPPORT_SM4_LANG18 "Build the AVX2 Lang18 SM4 implementation" ON)
option(SUPPORT_SM4_GONG23 "Build the AVX-512/GFNI Gong23 SM4 implementation" ON)
option(SUPPORT_UBLOCK_STANDARD "Build the SSSE3 uBlock implementation" ON)
option(SUPPORT_UBLOCK_GONG25 "Build the AVX2 Gong25 uBlock implementation" ON)
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

if(CMAKE_VS_PLATFORM_NAME STREQUAL "x64")
    set(ARCH_X86_64 TRUE)
    message(STATUS "Detected architecture: x86_64 (Visual Studio x64)")
elseif(CMAKE_VS_PLATFORM_NAME STREQUAL "Win32")
    set(ARCH_X86 TRUE)
    message(STATUS "Detected architecture: x86 (Visual Studio Win32)")
elseif(CMAKE_VS_PLATFORM_NAME STREQUAL "ARM")
    set(ARCH_ARM TRUE)
    message(STATUS "Detected architecture: ARM (Visual Studio ARM)")
elseif(CMAKE_VS_PLATFORM_NAME STREQUAL "ARM64")
    set(ARCH_AARCH64 TRUE)
    message(STATUS "Detected architecture: AArch64 (Visual Studio ARM64)")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|amd64|AMD64)$")
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

function(gmlib_enable_impl support_macro)
    target_compile_definitions(${PROJECT_NAME_}_static PRIVATE ${support_macro})
    message(STATUS "Enabled implementation: ${support_macro}")
endfunction()

function(gmlib_skip_impl option_name required_arch)
    if(${option_name})
        message(STATUS "${option_name} is ON, but requires ${required_arch}; implementation skipped")
    endif()
endfunction()

# Portable implementations selected at build time.
if(SUPPORT_BASE64_CHROMIUM)
    gmlib_enable_impl(SUPPORT_BASE64_CHROMIUM)
endif()
if(SUPPORT_SM3_YANG15)
    gmlib_enable_impl(SUPPORT_SM3_YANG15)
endif()

# Architecture-specific implementations. The support macro is target-wide
# and records that an implementation is present in the library. ISA compiler
# options are deliberately limited to the optimized kernel translation units.
if(SUPPORT_AES_ARM_AES)
    if(ARCH_ARM OR ARCH_AARCH64)
        gmlib_enable_impl(SUPPORT_AES_ARM_AES)
        if(NOT COMPILER_MSVC)
            if(ARCH_ARM)
                set(AES_ARM_AES_OPTIONS
                    -march=armv8-a
                    -mfpu=crypto-neon-fp-armv8)
            else()
                set(AES_ARM_AES_OPTIONS -march=armv8-a+crypto)
            endif()
            set_source_files_properties(
                ${BASE_LIB_SRC_DIRECTORY}/aes/aes_arm_aes.cpp
                PROPERTIES COMPILE_OPTIONS "${AES_ARM_AES_OPTIONS}")
        endif()
    else()
        gmlib_skip_impl(SUPPORT_AES_ARM_AES "ARM or AArch64")
    endif()
endif()

if(SUPPORT_AES_AESNI)
    if(ARCH_X86 OR ARCH_X86_64)
        gmlib_enable_impl(SUPPORT_AES_AESNI)
        if(NOT COMPILER_MSVC)
            set_source_files_properties(
                ${BASE_LIB_SRC_DIRECTORY}/aes/aes_aesni.cpp
                PROPERTIES COMPILE_OPTIONS "-maes;-msse2")
        endif()
    else()
        gmlib_skip_impl(SUPPORT_AES_AESNI "x86 or x86_64")
    endif()
endif()

if(SUPPORT_BASE64_AVX2)
    if(ARCH_X86 OR ARCH_X86_64)
        gmlib_enable_impl(SUPPORT_BASE64_AVX2)
        if(COMPILER_MSVC)
            set(BASE64_AVX2_OPTIONS /arch:AVX2)
        else()
            set(BASE64_AVX2_OPTIONS -mavx2)
        endif()
        set_source_files_properties(
            ${BASE_LIB_SRC_DIRECTORY}/base64/base64_avx2.cpp
            PROPERTIES COMPILE_OPTIONS "${BASE64_AVX2_OPTIONS}")
    else()
        gmlib_skip_impl(SUPPORT_BASE64_AVX2 "x86 or x86_64")
    endif()
endif()

if(SUPPORT_GHASH_PCLMUL)
    if(ARCH_X86 OR ARCH_X86_64)
        gmlib_enable_impl(SUPPORT_GHASH_PCLMUL)
        if(NOT COMPILER_MSVC)
            set_source_files_properties(
                ${BASE_LIB_SRC_DIRECTORY}/ghash/ghash_pclmul.cpp
                PROPERTIES COMPILE_OPTIONS "-mpclmul;-msse2;-mssse3")
        endif()
    else()
        gmlib_skip_impl(SUPPORT_GHASH_PCLMUL "x86 or x86_64")
    endif()
endif()

if(SUPPORT_MEMXOR_AVX2)
    if(ARCH_X86 OR ARCH_X86_64)
        gmlib_enable_impl(SUPPORT_MEMXOR_AVX2)
        if(COMPILER_MSVC)
            set(MEMXOR_AVX2_OPTIONS /arch:AVX2)
        else()
            set(MEMXOR_AVX2_OPTIONS -mavx2)
        endif()
        set_source_files_properties(
            ${BASE_LIB_SRC_DIRECTORY}/memory_utils/memxor_avx2.cpp
            PROPERTIES COMPILE_OPTIONS "${MEMXOR_AVX2_OPTIONS}")
    else()
        gmlib_skip_impl(SUPPORT_MEMXOR_AVX2 "x86 or x86_64")
    endif()
endif()

if(SUPPORT_MEMXOR_SSE2)
    if(ARCH_X86 OR ARCH_X86_64)
        gmlib_enable_impl(SUPPORT_MEMXOR_SSE2)
        if(NOT COMPILER_MSVC)
            set_source_files_properties(
                ${BASE_LIB_SRC_DIRECTORY}/memory_utils/memxor_sse2.cpp
                PROPERTIES COMPILE_OPTIONS "-msse2")
        endif()
    else()
        gmlib_skip_impl(SUPPORT_MEMXOR_SSE2 "x86 or x86_64")
    endif()
endif()

if(SUPPORT_NUMBER_X64)
    if(ARCH_X86_64)
        gmlib_enable_impl(SUPPORT_NUMBER_X64)
        if(NOT COMPILER_MSVC)
            set_source_files_properties(
                ${BASE_LIB_SRC_DIRECTORY}/number/mont256_x64.cpp
                ${BASE_LIB_SRC_DIRECTORY}/number/mpz_x64.cpp
                ${BASE_LIB_SRC_DIRECTORY}/number/uint256_x64.cpp
                PROPERTIES COMPILE_OPTIONS "-mmovbe;-mbmi2")
        endif()
    else()
        gmlib_skip_impl(SUPPORT_NUMBER_X64 "x86_64")
    endif()
endif()

if(SUPPORT_SHA1_SHA)
    if(ARCH_X86 OR ARCH_X86_64)
        gmlib_enable_impl(SUPPORT_SHA1_SHA)
        if(NOT COMPILER_MSVC)
            set_source_files_properties(
                ${BASE_LIB_SRC_DIRECTORY}/sha1/sha1_sha.cpp
                PROPERTIES COMPILE_OPTIONS "-msha;-msse4.1")
        endif()
    else()
        gmlib_skip_impl(SUPPORT_SHA1_SHA "x86 or x86_64")
    endif()
endif()

if(SUPPORT_SHA2_SHA)
    if(ARCH_X86 OR ARCH_X86_64)
        gmlib_enable_impl(SUPPORT_SHA2_SHA)
        if(NOT COMPILER_MSVC)
            set_source_files_properties(
                ${BASE_LIB_SRC_DIRECTORY}/sha2/sha224_256_sha.cpp
                PROPERTIES COMPILE_OPTIONS "-msha;-msse4.1")
        endif()
    else()
        gmlib_skip_impl(SUPPORT_SHA2_SHA "x86 or x86_64")
    endif()
endif()

if(SUPPORT_SM4_SM4NI)
    if(ARCH_X86 OR ARCH_X86_64)
        gmlib_enable_impl(SUPPORT_SM4_SM4NI)
        if(NOT COMPILER_MSVC)
            set_source_files_properties(
                ${BASE_LIB_SRC_DIRECTORY}/sm4/sm4_sm4ni.cpp
                PROPERTIES COMPILE_OPTIONS "-maes;-msse2;-mssse3")
        endif()
    else()
        gmlib_skip_impl(SUPPORT_SM4_SM4NI "x86 or x86_64")
    endif()
endif()

if(SUPPORT_SM4_LANG18)
    if(ARCH_X86 OR ARCH_X86_64)
        gmlib_enable_impl(SUPPORT_SM4_LANG18)
        if(COMPILER_MSVC)
            set(SM4_LANG18_OPTIONS /arch:AVX2)
        else()
            set(SM4_LANG18_OPTIONS -mavx2)
        endif()
        set_source_files_properties(
            ${BASE_LIB_SRC_DIRECTORY}/sm4/sm4_lang18.cpp
            PROPERTIES COMPILE_OPTIONS "${SM4_LANG18_OPTIONS}")
    else()
        gmlib_skip_impl(SUPPORT_SM4_LANG18 "x86 or x86_64")
    endif()
endif()

if(SUPPORT_SM4_GONG23)
    if(ARCH_X86 OR ARCH_X86_64)
        gmlib_enable_impl(SUPPORT_SM4_GONG23)
        if(COMPILER_MSVC)
            set(SM4_GONG23_OPTIONS /arch:AVX512)
        else()
            set(SM4_GONG23_OPTIONS -mavx512bw -mavx512vl -mavx512f -mgfni)
        endif()
        set_source_files_properties(
            ${BASE_LIB_SRC_DIRECTORY}/sm4/sm4_gong23.cpp
            PROPERTIES COMPILE_OPTIONS "${SM4_GONG23_OPTIONS}")
    else()
        gmlib_skip_impl(SUPPORT_SM4_GONG23 "x86 or x86_64")
    endif()
endif()

if(SUPPORT_UBLOCK_STANDARD)
    if(ARCH_X86 OR ARCH_X86_64)
        gmlib_enable_impl(SUPPORT_UBLOCK_STANDARD)
        if(NOT COMPILER_MSVC)
            set_source_files_properties(
                ${BASE_LIB_SRC_DIRECTORY}/ublock/ublock_standard.cpp
                PROPERTIES COMPILE_OPTIONS "-mssse3")
        endif()
    else()
        gmlib_skip_impl(SUPPORT_UBLOCK_STANDARD "x86 or x86_64")
    endif()
endif()

if(SUPPORT_UBLOCK_GONG25)
    if(ARCH_X86 OR ARCH_X86_64)
        gmlib_enable_impl(SUPPORT_UBLOCK_GONG25)
        if(COMPILER_MSVC)
            set(UBLOCK_GONG25_OPTIONS /arch:AVX2)
        else()
            set(UBLOCK_GONG25_OPTIONS -mavx2)
        endif()
        set_source_files_properties(
            ${BASE_LIB_SRC_DIRECTORY}/ublock/ublock_gong25.cpp
            PROPERTIES COMPILE_OPTIONS "${UBLOCK_GONG25_OPTIONS}")
    else()
        gmlib_skip_impl(SUPPORT_UBLOCK_GONG25 "x86 or x86_64")
    endif()
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
