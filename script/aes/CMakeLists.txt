cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME_ aes)
set(THIRD_PARTY 
    block_cipher_mode
    ghash
    hash_lib
    memory_utils
)

add_definitions(-DCPU_FLAG_SSE2)
add_definitions(-DCPU_FLAG_AVX2)
add_definitions(-DCPU_FLAG_AES)
# add_compile_options(-O3 -msse2 -mavx2 -maes)

#######################################################
## ================================================= ##
## ================================================= ##
## ================================================= ##
#######################################################

project(${PROJECT_NAME_} CXX)

set(CMAKE_CXX_STANDARD 17)

set(BASE_INCLUDE_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
set(BASE_LIB_SRC_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/../../src)
set(BASE_TEST_SRC_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../test)

include_directories(${BASE_INCLUDE_DIRECTORY})
file(GLOB_RECURSE PROJECT_INCLUDE  ${BASE_INCLUDE_DIRECTORY}/${PROJECT_NAME_}/*.h)
file(GLOB_RECURSE PROJECT_LIB_SRC  ${BASE_LIB_SRC_DIRECTORY}/${PROJECT_NAME_}/*.cpp)
file(GLOB_RECURSE PROJECT_TEST_SRC ${BASE_TEST_SRC_DIRECTORY}/${PROJECT_NAME_}/*.cpp)

set(EXECUTABLE_NAME ${PROJECT_NAME_}_test)
add_executable(
    ${EXECUTABLE_NAME}
    ${PROJECT_INCLUDE} ${PROJECT_LIB_SRC} ${PROJECT_TEST_SRC}
)

foreach(THIRD_PARTY_NAME ${THIRD_PARTY})
    file(   
        GLOB_RECURSE
        THIRD_PARTY_LIB_SRC
        ${BASE_LIB_SRC_DIRECTORY}/${THIRD_PARTY_NAME}/*.cpp
    )
    target_include_directories(
        ${EXECUTABLE_NAME} 
        PRIVATE 
        ${BASE_INCLUDE_DIRECTORY}/${THIRD_PARTY_NAME}/include
    )
    target_sources(
        ${EXECUTABLE_NAME}
        PRIVATE
        ${THIRD_PARTY_LIB_SRC}
    )
endforeach()