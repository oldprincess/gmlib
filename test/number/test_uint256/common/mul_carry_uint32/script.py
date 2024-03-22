import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t  multiplier{i}[32]  = {multiplier_val};
    static std::uint32_t multiplicand{i}    = {multiplicand_val};
    static std::uint8_t  product{i}[32]     = {product_val};
    static std::uint32_t carry{i}           = {carry_val};
    uint256_from_bytes(multiplier, multiplier{i});
    carry = uint256_mul_carry_uint32(product, multiplier, multiplicand{i});
    uint256_to_bytes(product_data, product);
    if (std::memcmp(product{i}, product_data, 32) != 0 && carry{i} != carry)
    {{
        throw std::runtime_error("err in common::uint256_mul_carry_uint32");
    }}"""


c_code_template = """\
#include <gmlib/number/internal/uint256_common.h>
#include <stdexcept>
#include <cstring>

using namespace number::internal::common;

void test_uint256_common_mul_carry_uint32()
{{
    uint256_t     multiplier, product;
    std::uint32_t carry;
    std::uint8_t  product_data[32];

{}
}}"""


def int_to_c_array(n: int, bits: int):
    bytes_n = n.to_bytes(bits // 8, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


c_code = []
for i in range(TEST_VECTOR_NUM):
    multiplier = random.randint(0, 2**256 - 1)
    multiplicand = random.randint(0, 2**32 - 1)
    carry, product = divmod(multiplier * multiplicand, 2**256)
    c_code.append(
        test_script_template.format(
            i=i,
            multiplier_val=int_to_c_array(multiplier, 256),
            multiplicand_val=multiplicand,
            product_val=int_to_c_array(product, 256),
            carry_val = carry,
        )
    )
with open("test_uint256_common_mul_carry_uint32.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
