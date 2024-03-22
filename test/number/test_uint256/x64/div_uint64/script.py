import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t  dividend{i}[32] = {dividend_val};
    static std::uint64_t divisor{i}     = {divisor_val}ULL;
    static std::uint8_t  quotient{i}[32]    = {quotient_val};
    static std::uint64_t remainder{i}      = {remainder_val}ULL;
    uint256_from_bytes(dividend, dividend{i});
    remainder = uint256_div_uint64(quotient, dividend, divisor{i});
    uint256_to_bytes(quotient_data, quotient);
    if (std::memcmp(quotient{i}, quotient_data, 32) != 0 || remainder{i} != remainder)
    {{
        throw std::runtime_error("err in x64::uint256_div_uint64");
    }}"""


c_code_template = """\
#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#include <gmlib/number/internal/uint256_x64.h>
#include <stdexcept>
#include <cstring>

using namespace number::internal::x64;

void test_uint256_x64_div_uint64()
{{
    uint256_t     dividend, quotient;
    std::uint64_t remainder;
    std::uint8_t  quotient_data[32];

{}
}}
#else
void test_uint256_x64_div_uint64()
{{
}}
#endif"""


def int_to_c_array(n: int):
    bytes_n = n.to_bytes(32, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


c_code = []
for i in range(TEST_VECTOR_NUM):
    dividend = random.randint(0, 2**256 - 1)
    divisor = random.randint(1, 2**64 - 1)
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
with open("test_uint256_x64_div_uint64.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
