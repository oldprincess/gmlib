import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t augend{i}[32] = {augend_val};
    static std::uint8_t addend{i}[32] = {addend_val};
    static std::uint8_t sum{i}[32]    = {sum_val};
    static int          carry{i}      = {carry_val};
    mpz_from_bytes(augend, augend{i}, 8);
    mpz_from_bytes(addend, addend{i}, 8);
    carry = mpz_add_carry(sum, augend, addend, 0, 8);
    mpz_to_bytes(sum_data, sum, 8);
    if (std::memcmp(sum{i}, sum_data, 32) != 0 || carry{i} != carry)
    {{
        throw std::runtime_error("err in common::mpz_add_carry");
    }}"""


c_code_template = """\
#include <gmlib/number/internal/mpz_common.h>
#include <stdexcept>
#include <cstring>

using namespace number::internal::common;

void test_mpz_common_add_carry()
{{
    uint32_t    augend[8], addend[8], sum[8];
    int          carry;
    std::uint8_t sum_data[32];

{}
}}"""


def int_to_c_array(n: int):
    bytes_n = n.to_bytes(32, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


c_code = []
for i in range(TEST_VECTOR_NUM):
    augend = random.randint(0, 2**256 - 1)
    addend = random.randint(0, 2**256 - 1)
    carry, sum_ = divmod(augend + addend, 2**256)
    c_code.append(
        test_script_template.format(
            i=i,
            augend_val=int_to_c_array(augend),
            addend_val=int_to_c_array(addend),
            sum_val=int_to_c_array(sum_),
            carry_val=carry,
        )
    )
with open("test_mpz_common_add_carry.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
