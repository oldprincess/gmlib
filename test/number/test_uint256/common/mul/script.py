import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t multiplier{i}[32]   = {multiplier_val};
    static std::uint8_t multiplicand{i}[32] = {multiplicand_val};
    static std::uint8_t product{i}[64]      = {product_val};
    uint256_from_bytes(multiplier, multiplier{i});
    uint256_from_bytes(multiplicand, multiplicand{i});
    uint256_mul(product[0], multiplier, multiplicand);
    uint256_to_bytes(product_data + 32, product[0]);
    uint256_to_bytes(product_data, product[1]);
    if (std::memcmp(product{i}, product_data, 64) != 0)
    {{
        throw std::runtime_error("err in common::uint256_mul");
    }}"""


c_code_template = """\
#include <gmlib/number/internal/uint256_common.h>
#include <stdexcept>
#include <cstring>

using namespace number::internal::common;

void test_uint256_common_mul()
{{
    uint256_t    multiplier, multiplicand, product[2];
    std::uint8_t product_data[64];

{}
}}"""


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
with open("test_uint256_common_mul.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
