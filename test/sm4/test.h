#ifndef SM4_TEST_H
#define SM4_TEST_H

#include "../block_cipher_mode/test_suite.h"

std::vector<block_cipher_mode::test::CipherKat> get_sm4_cipher_kats();
std::vector<block_cipher_mode::test::ModeKat>   get_sm4_ecb_kats();
std::vector<block_cipher_mode::test::ModeKat>   get_sm4_cbc_kats();
std::vector<block_cipher_mode::test::ModeKat>   get_sm4_cfb_kats();
std::vector<block_cipher_mode::test::ModeKat>   get_sm4_ofb_kats();
std::vector<block_cipher_mode::test::ModeKat>   get_sm4_ctr_kats();

#endif
