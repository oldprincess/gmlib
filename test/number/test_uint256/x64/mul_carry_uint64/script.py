import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t  multiplier{i}[32]  = {multiplier_val};
    static std::uint64_t multiplicand{i}    = {multiplicand_val};
    static std::uint8_t  product{i}[32]     = {product_val};
    static std::uint64_t carry{i}           = {carry_val};
    uint256_from_bytes(multiplier, multiplier{i});
    carry = uint256_mul_carry_uint64(product, multiplier, multiplicand{i});
    uint256_to_bytes(product_data, product);
    if (std::memcmp(product{i}, product_data, 32) != 0 && carry{i} != carry)
    {{
        throw std::runtime_error("err in x64::uint256_mul_carry_uint64");
    }}"""


c_code_template = """\
#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#include <gmlib/number/internal/uint256_x64.h>
#include <stdexcept>
#include <cstring>

using namespace number::internal::x64;

void test_uint256_x64_mul_carry_uint64()
{{
    uint256_t     multiplier, product;
    std::uint64_t carry;
    std::uint8_t  product_data[32];

{}
}}
#else
void test_uint256_x64_mul_carry_uint64()
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
    multiplicand = random.randint(0, 2**64 - 1)
    carry, product = divmod(multiplier * multiplicand, 2**256)
    c_code.append(
        test_script_template.format(
            i=i,
            multiplier_val=int_to_c_array(multiplier, 256),
            multiplicand_val=hex(multiplicand),
            product_val=int_to_c_array(product, 256),
            carry_val = hex(carry),
        )
    )
with open("test_uint256_x64_mul_carry_uint64.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
