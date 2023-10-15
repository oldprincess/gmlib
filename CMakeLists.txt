cmake_minimum_required(VERSION 3.0)

project(GMLib LANGUAGES CXX)

if(MSVC)
    # set source charset, encoding as utf-8
    add_compile_options(/source-charset:utf-8)
endif()

include_directories("./")

set(GMLIB_HEADER
    # cipher
    "gmlib/crypto/cipher/AesCipher.h"
    "gmlib/crypto/cipher/Sm4Cipher.h"
    "gmlib/crypto/cipher/CipherMode.hpp"
    # hash
    "gmlib/crypto/hash/GHashCipher.h"
    "gmlib/crypto/hash/Sm3Cipher.h"
    # rng
    "gmlib/crypto/rng/RngCipher.h"
)

set(GMLIB_SRC 
    # cipher
    "gmlib/crypto/cipher/AesCipher.cpp"
    "gmlib/crypto/cipher/Sm4Cipher.cpp"
    # hash
    "gmlib/crypto/hash/GHashCipher.cpp"
    "gmlib/crypto/hash/Sm3Cipher.cpp"
)

set(GMLIB_EX_HEADER
    "gmlib/crypto_ex/GHashCipher_Pclmul.h"
    "gmlib/crypto_ex/win/WinRng.hpp"
    "gmlib/crypto_ex/win/WinRng2.hpp"
)

set(GMLIB_EX_SRC
    "gmlib/crypto_ex/GHashCipher_Pclmul.cpp"
)

set(TEST_SRC 
    "test/crypto/cipher/TestAesCipher.cpp"
    "test/crypto/cipher/TestSm4Cipher.cpp"
    "test/crypto/cipher/TestGcmMode.cpp"
    "test/crypto/cipher/TestCipherMode.cpp"
    "test/crypto/hash/TestGHashCipher.cpp"
    "test/crypto/hash/TestSm3Cipher.cpp"
    "test/main.cpp"
)

add_library(gmlib STATIC ${GMLIB_SRC} ${GMLIB_HEADER} ${GMLIB_EX_SRC} ${GMLIB_EX_HEADER})
add_executable(gmlib_test ${TEST_SRC})
target_link_libraries(gmlib_test gmlib)