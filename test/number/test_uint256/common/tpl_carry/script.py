import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t product{i}[32]     = {product_val};
    static std::uint8_t multiplier{i}[32]  = {multiplier_val};
    static int          carry{i}           = {carry_val};
    uint256_from_bytes(multiplier, multiplier{i});
    carry = uint256_tpl_carry(product, multiplier);
    uint256_to_bytes(product_data, product);
    if (std::memcmp(product{i}, product_data, 32) != 0 || carry{i} != carry)
    {{
        throw std::runtime_error("err in common::uint256_tpl_carry");
    }}"""


c_code_template = """\
#include <gmlib/number/internal/uint256_common.h>
#include <stdexcept>
#include <cstring>

using namespace number::internal::common;

void test_uint256_common_tpl_carry()
{{
    uint256_t    product, multiplier;
    int          carry;
    std::uint8_t product_data[32];

{}
}}"""


def int_to_c_array(n: int):
    bytes_n = n.to_bytes(32, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


c_code = []
for i in range(TEST_VECTOR_NUM):
    multiplier = random.randint(0, 2**256 - 1)
    carry, product = divmod(3 * multiplier, 2**256)
    c_code.append(
        test_script_template.format(
            i=i,
            multiplier_val=int_to_c_array(multiplier),
            product_val=int_to_c_array(product),
            carry_val=carry,
        )
    )
with open("test_uint256_common_tpl_carry.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
