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

set(PROJECT_BUILD_TEST ON)

# add_definitions(-DSUPPORT_BASE64_CHROMIUM)
add_definitions(-DSUPPORT_SM3_YANG15)
add_definitions(-DSUPPORT_SM4_LANG18)

# *************************************
# ****** set definitions in here ******
# *************************************

# add_definitions(-DCPU_FLAG_AES)
# add_definitions(-DCPU_FLAG_AVX2)
# add_definitions(-DCPU_FLAG_BMI2)
# add_definitions(-DCPU_FLAG_MOVBE)
# add_definitions(-DCPU_FLAG_PCLMUL)
# add_definitions(-DCPU_FLAG_RDRAND)
# add_definitions(-DCPU_FLAG_RDSEED)
# add_definitions(-DCPU_FLAG_SHA)
# add_definitions(-DCPU_FLAG_SSE2)
# add_definitions(-DCPU_FLAG_SSE4_1)
# add_definitions(-DCPU_FLAG_SSSE3)
# set(PROJECT_COMPILE_OPTIONS -maes -mavx2 -mbmi2 -mmovbe -mpclmul -mrdrnd -mrdseed -msha -msse2 -msse4.1 -mssse3)

#######################################################
## ================================================= ##
## ================================================= ##
## ================================================= ##
#######################################################

project(${PROJECT_NAME_} CXX)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)

else()
    add_compile_options(${PROJECT_COMPILE_OPTIONS})
    add_compile_options(-std=c++17)
    add_compile_options(-fvisibility=hidden)
endif()

set(BASE_INCLUDE_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(BASE_LIB_SRC_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BASE_TEST_SRC_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)

include_directories(${BASE_INCLUDE_DIRECTORY})
file(GLOB_RECURSE PROJECT_INCLUDE  ${BASE_INCLUDE_DIRECTORY}/*.h)
file(GLOB_RECURSE PROJECT_LIB_SRC  ${BASE_LIB_SRC_DIRECTORY}/*.cpp)

add_library(${PROJECT_NAME_}_static STATIC ${PROJECT_LIB_SRC} ${PROJECT_INCLUDE})

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

add_library(${PROJECT_NAME_} SHARED ${PROJECT_LIB_SRC} ${PROJECT_INCLUDE})
target_compile_definitions(${PROJECT_NAME_} PUBLIC GMLIB_BUILD_DLL)
add_executable(
    ${PROJECT_NAME_}_test
    ${PROJECT_INCLUDE}
    ${BASE_TEST_SRC_DIRECTORY}/test.cpp
)
target_link_libraries(
    ${PROJECT_NAME_}_test
    PUBLIC
    ${PROJECT_NAME_}
)