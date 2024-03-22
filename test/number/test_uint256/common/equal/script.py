import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    std::uint8_t a{i}_data[32] = {a_val};
    std::uint8_t b{i}_data[32] = {b_val};
    bool         cmp{i}        = {cmp};
    uint256_from_bytes(a, a{i}_data);
    uint256_from_bytes(b, b{i}_data);
    if (uint256_equal(a, b) != cmp{i})
    {{
        throw std::runtime_error("err in common::uint256_equal");
    }}"""


c_code_template = """\
#include <gmlib/number/internal/uint256_common.h>
#include <stdexcept>

using namespace number::internal::common;

void test_uint256_common_equal()
{{
    uint256_t a, b;

{}
}}"""


def int_to_c_array(n: int):
    bytes_n = n.to_bytes(32, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


c_code = []
for i in range(TEST_VECTOR_NUM):
    a = random.randint(0, 2**256 - 1)
    b = random.randint(0, 2**256 - 1)
    if random.randint(0, 1) == 1:
        b = a
    cmp = "true" if a == b else "false"
    c_code.append(
        test_script_template.format(
            i=i, a_val=int_to_c_array(a), b_val=int_to_c_array(b), cmp=cmp
        )
    )
with open("test_uint256_common_equal.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
