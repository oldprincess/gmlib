#ifndef TEST_H
#define TEST_H

#include "../block_cipher_mode/test_suite.h"

std::vector<block_cipher_mode::test::CipherKat> get_aes128_cipher_kats();
std::vector<block_cipher_mode::test::CipherKat> get_aes192_cipher_kats();
std::vector<block_cipher_mode::test::CipherKat> get_aes256_cipher_kats();

std::vector<block_cipher_mode::test::ModeKat> get_aes128_mode_kats();
std::vector<block_cipher_mode::test::ModeKat> get_aes192_mode_kats();
std::vector<block_cipher_mode::test::ModeKat> get_aes256_mode_kats();

std::vector<block_cipher_mode::test::AeadKat> get_aes128_aead_kats();
std::vector<block_cipher_mode::test::AeadKat> get_aes192_aead_kats();
std::vector<block_cipher_mode::test::AeadKat> get_aes256_aead_kats();

#endif
