cmake_minimum_required(VERSION 3.13)

project(gmlibprov C CXX)

# ***************************************************
# ***************************************************
# ************ 1. Config third party library ********
# ***************************************************
# ***************************************************

# ===================================================
# ============ 1.1. Config OpenSSL Path =============
# ===================================================

if(${OPENSSL_BASE_DIR})
    # Windows
    if(WIN32)
        option(OPENSSL_BASE_DIR C:/Programming/OpenSSL-Win64)
        set(OPENSSL_INCLUDE_DIR ${OPENSSL_BASE_DIR}/include)
        set(OPENSSL_LIBRARY_DIR ${OPENSSL_BASE_DIR}/lib)
        set(OPENSSL_LIBRARIES libcrypto)

        message(STATUS "[GMLIBPROV] Platform: Windows")
        message(STATUS "[GMLIBPROV] OpenSSL Base Dir: " ${OPENSSL_BASE_DIR})
        message(STATUS "[GMLIBPROV] OpenSSL INCLUDE Dir: " ${OPENSSL_INCLUDE_DIR})
        message(STATUS "[GMLIBPROV] OpenSSL LIBRARY Dir: " ${OPENSSL_LIBRARY_DIR})
    endif()  
    # Linux
    if(UNIX)
        option(OPENSSL_BASE_DIR /usr/local/ssl)
        set(OPENSSL_INCLUDE_DIR ${OPENSSL_BASE_DIR}/include)
        set(OPENSSL_LIBRARY_DIR ${OPENSSL_BASE_DIR}/lib64)
        set(OPENSSL_LIBRARIES crypto)

        message(STATUS "[GMLIBPROV] Platform: UNIX")
        message(STATUS "[GMLIBPROV] OpenSSL Base Dir: " ${OPENSSL_BASE_DIR})
        message(STATUS "[GMLIBPROV] OpenSSL INCLUDE Dir: " ${OPENSSL_INCLUDE_DIR})
        message(STATUS "[GMLIBPROV] OpenSSL LIBRARY Dir: " ${OPENSSL_LIBRARY_DIR})
    endif()
endif()

# ===================================================
# ============ 1.2. Config GMLib Path ===============
# ===================================================
set(GMLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
set(GMLIB_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(GMLIB_LIBRARIES gmlib_static)

# ***************************************************
# ***************************************************
# ************ 2. Config GMLibProv library **********
# ***************************************************
# ***************************************************
file(GLOB_RECURSE GMLIBPROV_LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE GMLIBPROV_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/test/*.c)
set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    add_compile_options(/source-charset:utf-8)

    message(STATUS "[GMLIBPROV] Use Compiler MSVC")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-fvisibility=hidden)

    message(STATUS "[GMLIBPROV] Use Compiler GCC")
endif()

# ***************************************************
# ***************************************************
# ************ 3. Message Config ********************
# ***************************************************
# ***************************************************

# message(STATUS "[GMLIBPROV] OPENSSL_INCLUDE_DIR=" ${OPENSSL_INCLUDE_DIR})
# message(STATUS "[GMLIBPROV] OPENSSL_LIBRARY_DIR=" ${OPENSSL_LIBRARY_DIR})
# foreach(LIB ${OPENSSL_LIBRARIES})
#     message(STATUS "[GMLIBPROV] OPENSSL_LIBRARIES=" ${LIB})
# endforeach()

# message(STATUS "[GMLIBPROV] GMLIB_INCLUDE_DIR=" ${GMLIB_INCLUDE_DIR})
# message(STATUS "[GMLIBPROV] GMLIB_LIBRARY_DIR=" ${GMLIB_LIBRARY_DIR})
# message(STATUS "[GMLIBPROV] GMLIB_LIBRARIES=" ${GMLIB_LIBRARIES})

# foreach(FILE ${GMLIBPROV_LIB_SRC})
#     message(STATUS "[GMLIBPROV] GMLIBPROV_LIB_SRC=" ${FILE})
# endforeach()
# foreach(FILE ${GMLIBPROV_TEST_SRC})
#     message(STATUS "[GMLIBPROV] GMLIBPROV_TEST_SRC=" ${FILE})
# endforeach()

# ***************************************************
# ***************************************************
# ************ 3. Build GMLIBPROV SHARED LIBRARY  ***
# ***************************************************
# ***************************************************

add_library(gmlibprov SHARED ${GMLIBPROV_LIB_SRC})
target_include_directories(gmlibprov PUBLIC ${OPENSSL_INCLUDE_DIR})
target_include_directories(gmlibprov PRIVATE ${GMLIB_INCLUDE_DIR})
target_link_directories(gmlibprov PUBLIC ${OPENSSL_LIBRARY_DIR})
target_link_directories(gmlibprov PRIVATE ${GMLIB_LIBRARY_DIR})
target_link_libraries(gmlibprov PUBLIC ${OPENSSL_LIBRARIES})
target_link_libraries(gmlibprov PRIVATE ${GMLIB_LIBRARIES})

# ***************************************************
# ***************************************************
# ************ 4. Build GMLIBPROV TEST **************
# ***************************************************
# ***************************************************

foreach(FILE ${GMLIBPROV_TEST_SRC})
    get_filename_component(FILE_NAME ${FILE} NAME_WE)
    add_executable(${FILE_NAME} ${FILE})
    target_link_libraries(${FILE_NAME} PUBLIC gmlibprov)
endforeach()
