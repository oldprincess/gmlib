cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME_ gmlib)
set(THIRD_PARTY 
    aes
    block_cipher_mode
    ghash
    hash_lib
    memory_utils
    number
    rng
    sm2
    sm3
    sm4
    sm9
)

# *************************************
# ****** set definitions in here ******
# *************************************

# add_definitions(-DCPU_FLAG_SSE2)
# add_definitions(-DCPU_FLAG_AVX2)
# add_definitions(-DCPU_FLAG_AES)
# add_definitions(-DCPU_FLAG_MOVBE)
# add_definitions(-DCPU_FLAG_BMI2)
# add_definitions(-DCPU_FLAG_RDSEED)
# add_definitions(-DCPU_FLAG_RDRAND)
# add_definitions(-DCPU_FLAG_PCLMUL)
add_definitions(-DSUPPORT_SM3_YANG15)
add_definitions(-DSUPPORT_SM4_LANG18)

# set(PROJECT_COMPILE_OPTIONS -msse2 -mavx2 -maes -mmovbe -mbmi2 -mrdseed -mrdrnd -mpclmul)

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
endif()

set(BASE_INCLUDE_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(BASE_LIB_SRC_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BASE_TEST_SRC_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)

include_directories(${BASE_INCLUDE_DIRECTORY})
file(GLOB_RECURSE PROJECT_INCLUDE  ${BASE_INCLUDE_DIRECTORY}/*.h)
file(GLOB_RECURSE PROJECT_LIB_SRC  ${BASE_LIB_SRC_DIRECTORY}/*.cpp)

add_library(${PROJECT_NAME_} STATIC ${PROJECT_LIB_SRC} ${PROJECT_INCLUDE})

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
        ${PROJECT_NAME_}
    )
endforeach()