import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t multiplier{i}[32]   = {multiplier_val};
    static std::uint8_t multiplicand{i}[32] = {multiplicand_val};
    static std::uint8_t product{i}[64]      = {product_val};
    mpz_from_bytes(multiplier, multiplier{i}, 4);
    mpz_from_bytes(multiplicand, multiplicand{i}, 4);
    mpz_mul(product[0], multiplier, multiplicand, 4);
    mpz_to_bytes(product_data + 32, product[0], 4);
    mpz_to_bytes(product_data, product[1], 4);
    if (std::memcmp(product{i}, product_data, 64) != 0)
    {{
        throw std::runtime_error("err in x64::mpz_mul");
    }}"""


c_code_template = """\
#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#include <gmlib/number/internal/mpz_x64.h>
#include <stdexcept>
#include <cstring>

using namespace number::internal::x64;

void test_mpz_x64_mul()
{{
    uint64_t    multiplier[4], multiplicand[4], product[2][4];
    std::uint8_t product_data[64];

{}
}}
#else
void test_mpz_x64_mul()
{{
}}
#endif"""


def int_to_c_array(n: int, bits: int):
    bytes_n = n.to_bytes(bits // 8, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


c_code = []
for i in range(TEST_VECTOR_NUM):
    multiplier = random.randint(0, 2**256 - 1)
    multiplicand = random.randint(0, 2**256 - 1)
    product = multiplier * multiplicand
    c_code.append(
        test_script_template.format(
            i=i,
            multiplier_val=int_to_c_array(multiplier, 256),
            multiplicand_val=int_to_c_array(multiplicand, 256),
            product_val=int_to_c_array(product, 512),
        )
    )
with open("test_mpz_x64_mul.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
