cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME_ sha1)
set(THIRD_PARTY 
    hash_lib
)

add_definitions(-DCPU_FLAG_SHA)
add_definitions(-DCPU_FLAG_SSE4_1)
set(PROJECT_COMPILE_OPTIONS -O3 -msha -msse4.1)

#######################################################
## ================================================= ##
## ================================================= ##
## ================================================= ##
#######################################################

if(MSVC)

else()
    add_compile_options(${PROJECT_COMPILE_OPTIONS})
    add_compile_options(-std=c++17)
    add_compile_options(-fvisibility=hidden)
endif()

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