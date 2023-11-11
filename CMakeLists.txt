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
    "gmlib/crypto/cipher/CipherMode.h"
    # hash
    "gmlib/crypto/hash/GHashCipher.h"
    "gmlib/crypto/hash/Md5Cipher.h"
    "gmlib/crypto/hash/Sha1Cipher.h"
    "gmlib/crypto/hash/Sm3Cipher.h"
    # rng
    "gmlib/crypto/rng/RngCipher.h"
)

set(TINY_CRYPTO_SRC
    "TinyCrypto/cipher/aes/aes_lut.cpp"
    "TinyCrypto/cipher/sm4/sm4_lut.cpp"
    "TinyCrypto/hash/ghash/ghash_lut256.cpp"
    "TinyCrypto/hash/sm3/sm3_fast.cpp"
)

set(TINY_CRYPTO_EX_SRC
    "TinyCrypto/cipher/ublock/ublock_standard.cpp"
    "TinyCrypto/hash/ghash/ghash_pclmul.cpp"
)

# set(GMLIB_SRC 

# )

set(GMLIB_EX_HEADER
    "gmlib/crypto_ex/GHashCipher_Pclmul.h"
    "gmlib/crypto_ex/UBlockCipher_Standard.h"
    "gmlib/crypto_ex/win/WinRng.h"
    "gmlib/crypto_ex/win/WinRng2.h"
)

set(TEST_SRC 
    "test/crypto/cipher/TestAesCipher.cpp"
    "test/crypto/cipher/TestSm4Cipher.cpp"
    "test/crypto/cipher/TestGcmMode.cpp"
    "test/crypto/cipher/TestCipherMode.cpp"
    "test/crypto/hash/TestGHashCipher.cpp"
    "test/crypto/hash/TestSm3Cipher.cpp"

    "test/crypto_ex/TestUBlockCipher_Standard.cpp"
    "test/main.cpp"
)

add_library(gmlib STATIC 
    ${TINY_CRYPTO_SRC} ${TINY_CRYPTO_EX_SRC}
    ${GMLIB_HEADER} ${GMLIB_EX_SRC} ${GMLIB_EX_HEADER})
add_executable(gmlib_test ${TEST_SRC})
target_link_libraries(gmlib_test gmlib)