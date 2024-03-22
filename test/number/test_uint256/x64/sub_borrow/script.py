import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t minuend{i}[32]    = {minuend_val};
    static std::uint8_t subtrahend{i}[32] = {subtrahend_val};
    static std::uint8_t sum{i}[32]        = {differenceval};
    static int          borrow{i}         = {borrow_val};
    uint256_from_bytes(minuend, minuend{i});
    uint256_from_bytes(subtrahend, subtrahend{i});
    borrow = uint256_sub_borrow(sum, minuend, subtrahend);
    uint256_to_bytes(differencedata, sum);
    if (std::memcmp(sum{i}, differencedata, 32) != 0 || borrow{i} != borrow)
    {{
        throw std::runtime_error("err in x64::uint256_sub_borrow");
    }}"""


c_code_template = """\
#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#include <gmlib/number/internal/uint256_x64.h>
#include <stdexcept>
#include <cstring>

using namespace number::internal::x64;

void test_uint256_x64_sub_borrow()
{{
    uint256_t    minuend, subtrahend, sum;
    int          borrow;
    std::uint8_t differencedata[32];

{}
}}
#else
void test_uint256_x64_sub_borrow()
{{
}}
#endif"""


def int_to_c_array(n: int):
    bytes_n = n.to_bytes(32, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


c_code = []
for i in range(TEST_VECTOR_NUM):
    minuend = random.randint(0, 2**256 - 1)
    subtrahend = random.randint(0, 2**256 - 1)
    borrow, difference = divmod(minuend - subtrahend, 2**256)
    c_code.append(
        test_script_template.format(
            i=i,
            minuend_val=int_to_c_array(minuend),
            subtrahend_val=int_to_c_array(subtrahend),
            differenceval=int_to_c_array(difference),
            borrow_val=borrow,
        )
    )
with open("test_uint256_x64_sub_borrow.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
