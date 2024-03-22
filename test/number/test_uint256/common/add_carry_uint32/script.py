import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t  augend{i}[32] = {augend_val};
    static std::uint32_t addend{i}     = {addend_val};
    static std::uint8_t  sum{i}[32]    = {sum_val};
    static int           carry{i}      = {carry_val};
    uint256_from_bytes(augend, augend{i});
    carry = uint256_add_carry_uint32(sum, augend, addend{i});
    uint256_to_bytes(sum_data, sum);
    if (std::memcmp(sum{i}, sum_data, 32) != 0 || carry{i} != carry)
    {{
        throw std::runtime_error("err in common::uint256_add_carry_uint32");
    }}"""


c_code_template = """\
#include <gmlib/number/internal/uint256_common.h>
#include <stdexcept>
#include <cstring>

using namespace number::internal::common;

void test_uint256_common_add_carry_uint32()
{{
    uint256_t    augend, sum;
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
    addend = random.randint(0, 2**32 - 1)
    carry, sum_ = divmod(augend + addend, 2**256)
    c_code.append(
        test_script_template.format(
            i=i,
            augend_val=int_to_c_array(augend),
            addend_val=addend,
            sum_val=int_to_c_array(sum_),
            carry_val=carry,
        )
    )
with open("test_uint256_common_add_carry_uint32.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
