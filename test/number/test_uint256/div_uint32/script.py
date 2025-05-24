import random
import os


random.seed(7)
TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t  dividend{i}[32] = {dividend_val};
    static std::uint32_t divisor{i}     = {divisor_val};
    static std::uint8_t  quotient{i}[32]    = {quotient_val};
    static std::uint32_t remainder{i}      = {remainder_val};
    uint256_from_bytes(dividend, dividend{i});
    remainder = uint256_div_uint32(quotient, dividend, divisor{i});
    uint256_to_bytes(quotient_data, quotient);
    if (std::memcmp(quotient{i}, quotient_data, 32) != 0 || remainder{i} != remainder)
    {{
        throw std::runtime_error("err in uint256_div_uint32");
    }}"""


c_code_template = """\
#include <gmlib/number/uint256.h>

#include <stdexcept>
#include <cstring>

using namespace number;

void test_uint256_div_uint32()
{{
    uint256_t     dividend, quotient;
    std::uint32_t remainder;
    std::uint8_t  quotient_data[32];

{}
}}
"""


def int_to_c_array(n: int):
    bytes_n = n.to_bytes(32, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


c_code = []
for i in range(TEST_VECTOR_NUM):
    dividend = random.randint(0, 2**256 - 1)
    divisor = random.randint(1, 2**32 - 1)
    quotient_, remainder = divmod(dividend, divisor)
    c_code.append(
        test_script_template.format(
            i=i,
            dividend_val=int_to_c_array(dividend),
            divisor_val=divisor,
            quotient_val=int_to_c_array(quotient_),
            remainder_val=remainder,
        )
    )
with open("test_uint256_div_uint32.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
