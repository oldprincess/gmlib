#ifndef DES_TEST_H
#define DES_TEST_H

#include "../block_cipher_mode/test_suite.h"

std::vector<block_cipher_mode::test::CipherKat> get_des_cipher_kats();
std::vector<block_cipher_mode::test::ModeKat>   get_des_mode_kats();

#endif
