cmake_minimum_required(VERSION 3.0)

project(GMLib LANGUAGES CXX)

if(MSVC)
    # set source charset, encoding as utf-8
    add_compile_options(/source-charset:utf-8)
else()
    add_compile_options(-mpclmul -mssse3)
endif()

# set cmake output dir
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# set thirdparty include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TinyCrypto)

file(GLOB_RECURSE GMLIB_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/gmlib/*.h)
file(GLOB_RECURSE GMLIB_TEST_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)

add_subdirectory(TinyCrypto)
add_executable(gmlib_test ${GMLIB_TEST_SOURCE_FILES} ${GMLIB_HEADER_FILES})
target_link_libraries(gmlib_test static_tinycrypto)