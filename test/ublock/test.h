#ifndef UBLOCK_TEST_H
#define UBLOCK_TEST_H

#include "../block_cipher_mode/test_suite.h"

std::vector<block_cipher_mode::test::CipherKat> get_ublock128128_cipher_kats();
std::vector<block_cipher_mode::test::ModeKat>   get_ublock128128_mode_kats();

std::vector<block_cipher_mode::test::CipherKat> get_ublock128256_cipher_kats();
std::vector<block_cipher_mode::test::ModeKat>   get_ublock128256_mode_kats();

std::vector<block_cipher_mode::test::CipherKat> get_ublock256256_cipher_kats();
std::vector<block_cipher_mode::test::ModeKat>   get_ublock256256_mode_kats();

#endif
