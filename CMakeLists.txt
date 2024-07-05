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
    ublock
)

add_definitions(-DSUPPORT_SM3_YANG15)
add_definitions(-DSUPPORT_SM4_LANG18)

# *************************************
# ****** set definitions in here ******
# *************************************

# add_definitions(-DCPU_FLAG_ADX)
# add_definitions(-DCPU_FLAG_AES)
# add_definitions(-DCPU_FLAG_AVX)
# add_definitions(-DCPU_FLAG_AVX2)
# add_definitions(-DCPU_FLAG_BMI1)
# add_definitions(-DCPU_FLAG_BMI2)
# add_definitions(-DCPU_FLAG_CLFSH)
# add_definitions(-DCPU_FLAG_CMPXCHG16B)
# add_definitions(-DCPU_FLAG_CX8)
# add_definitions(-DCPU_FLAG_ERMS)
# add_definitions(-DCPU_FLAG_F16C)
# add_definitions(-DCPU_FLAG_FMA)
# add_definitions(-DCPU_FLAG_FSGSBASE)
# add_definitions(-DCPU_FLAG_FXSR)
# add_definitions(-DCPU_FLAG_INVPCID)
# add_definitions(-DCPU_FLAG_LAHF)
# add_definitions(-DCPU_FLAG_LZCNT)
# add_definitions(-DCPU_FLAG_MMX)
# add_definitions(-DCPU_FLAG_MONITOR)
# add_definitions(-DCPU_FLAG_MOVBE)
# add_definitions(-DCPU_FLAG_MSR)
# add_definitions(-DCPU_FLAG_OSXSAVE)
# add_definitions(-DCPU_FLAG_PCLMULQDQ)
# add_definitions(-DCPU_FLAG_POPCNT)
# add_definitions(-DCPU_FLAG_RDRAND)
# add_definitions(-DCPU_FLAG_RDSEED)
# add_definitions(-DCPU_FLAG_RDTSCP)
# add_definitions(-DCPU_FLAG_SEP)
# add_definitions(-DCPU_FLAG_SHA)
# add_definitions(-DCPU_FLAG_SSE)
# add_definitions(-DCPU_FLAG_SSE2)
# add_definitions(-DCPU_FLAG_SSE3)
# add_definitions(-DCPU_FLAG_SSE4_1)
# add_definitions(-DCPU_FLAG_SSE4_2)
# add_definitions(-DCPU_FLAG_SSSE3)
# add_definitions(-DCPU_FLAG_SYSCALL)
# add_definitions(-DCPU_FLAG_XSAVE)
# set(PROJECT_COMPILE_OPTIONS -madx -maes -mavx -mavx2 -mbmi1 -mbmi2 -mclfsh -mcmpxchg16b -mcx8 -merms -mf16c -mfma -mfsgsbase -mfxsr -minvpcid -mlahf -mlzcnt -mmmx -mmonitor -mmovbe -mmsr -mosxsave -mpclmulqdq -mpopcnt -mrdrand -mrdseed -mrdtscp -msep -msha -msse -msse2 -msse3 -msse4.1 -msse4.2 -mssse3 -msyscall -mxsave )

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