cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME_ gmlib)
set(THIRD_PARTY 
    aes
    block_cipher_mode
    ballet
    base64
    des
    ghash
    hash_lib
    md5
    memory_utils
    number
    rng
    sha1
    sm2
    sm3
    sm4
    sm9
    ublock
)

set(PROJECT_BUILD_TEST OFF)

# add_definitions(-DSUPPORT_BASE64_CHROMIUM)
add_definitions(-DSUPPORT_SM3_YANG15)
add_definitions(-DSUPPORT_SM4_LANG18)

# *************************************
# ****** set definitions in here ******
# *************************************

add_definitions(-DCPU_FLAG_INTEL_AES)
add_definitions(-DCPU_FLAG_INTEL_AVX2)
add_definitions(-DCPU_FLAG_INTEL_BMI2)
add_definitions(-DCPU_FLAG_INTEL_MOVBE)
add_definitions(-DCPU_FLAG_INTEL_PCLMUL)
add_definitions(-DCPU_FLAG_INTEL_RDRAND)
add_definitions(-DCPU_FLAG_INTEL_RDSEED)
add_definitions(-DCPU_FLAG_INTEL_SHA)
add_definitions(-DCPU_FLAG_INTEL_SSE2)
add_definitions(-DCPU_FLAG_INTEL_SSE4_1)
add_definitions(-DCPU_FLAG_INTEL_SSSE3)
# set(PROJECT_COMPILE_OPTIONS -maes -mavx2 -mbmi2 -mmovbe -mpclmul -mrdrnd -mrdseed -msha -msse2 -msse4.1 -mssse3)

#######################################################
## ================================================= ##
## ================================================= ##
## ================================================= ##
#######################################################

project(${PROJECT_NAME_} CXX)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    message(STATUS "[GMLIB] Use Compiler MSVC")
    add_compile_options(/source-charset:utf-8)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "[GMLIB] Use Compiler GNU")
    add_compile_options(${PROJECT_COMPILE_OPTIONS})
    add_compile_options(-fvisibility=hidden)
endif()

set(BASE_INCLUDE_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(BASE_LIB_SRC_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BASE_TEST_SRC_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)

include_directories(${BASE_INCLUDE_DIRECTORY})
file(GLOB_RECURSE PROJECT_INCLUDE  ${BASE_INCLUDE_DIRECTORY}/*.h)
file(GLOB_RECURSE PROJECT_LIB_SRC  ${BASE_LIB_SRC_DIRECTORY}/*.cpp)

add_library(${PROJECT_NAME_}_static STATIC ${PROJECT_LIB_SRC} ${PROJECT_INCLUDE})
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME_}_static PRIVATE -fPIC)
endif()

if(${PROJECT_BUILD_TEST})
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
    endforeach()
endif()
