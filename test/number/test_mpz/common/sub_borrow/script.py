import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t minuend{i}[32]    = {minuend_val};
    static std::uint8_t subtrahend{i}[32] = {subtrahend_val};
    static std::uint8_t sum{i}[32]        = {differenceval};
    static int          borrow{i}         = {borrow_val};
    mpz_from_bytes(minuend, minuend{i}, 8);
    mpz_from_bytes(subtrahend, subtrahend{i}, 8);
    borrow = mpz_sub_borrow(sum, minuend, subtrahend, 0, 8);
    mpz_to_bytes(differencedata, sum, 8);
    if (std::memcmp(sum{i}, differencedata, 32) != 0 || borrow{i} != borrow)
    {{
        throw std::runtime_error("err in common::mpz_sub_borrow");
    }}"""


c_code_template = """\
#include <gmlib/number/internal/mpz_common.h>
#include <stdexcept>
#include <cstring>

using namespace number::internal::common;

void test_mpz_common_sub_borrow()
{{
    uint32_t    minuend[8], subtrahend[8], sum[8];
    int          borrow;
    std::uint8_t differencedata[32];

{}
}}"""


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
with open("test_mpz_common_sub_borrow.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
