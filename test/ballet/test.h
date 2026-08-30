#ifndef BALLET_TEST_H
#define BALLET_TEST_H

#include "../block_cipher_mode/test_suite.h"

std::vector<block_cipher_mode::test::CipherKat> get_ballet128128_cipher_kats();
std::vector<block_cipher_mode::test::ModeKat>   get_ballet128128_mode_kats();

std::vector<block_cipher_mode::test::CipherKat> get_ballet128256_cipher_kats();
std::vector<block_cipher_mode::test::ModeKat>   get_ballet128256_mode_kats();

std::vector<block_cipher_mode::test::CipherKat> get_ballet256256_cipher_kats();
std::vector<block_cipher_mode::test::ModeKat>   get_ballet256256_mode_kats();

#endif
