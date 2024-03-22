import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    std::uint32_t num{i}          = {num};
    std::uint8_t  num{i}_data[32] = {num_val};
    uint256_set_uint32(a, num{i});
    uint256_to_bytes(a_data, a);
    if (std::memcmp(num{i}_data, a_data, 32) != 0)
    {{
        throw std::runtime_error("err in common::uint256_set_uint32");
    }}"""


c_code_template = """\
#include <gmlib/number/internal/uint256_common.h>
#include <stdexcept>
#include <cstring>

using namespace number::internal::common;

void test_uint256_common_set_uint32()
{{
    std::uint8_t a_data[32];
    uint256_t    a;

{}
}}"""


def int_to_c_array(n: int):
    bytes_n = n.to_bytes(32, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


c_code = []
for i in range(TEST_VECTOR_NUM):
    num = random.randint(0, 2**32 - 1)
    c_code.append(
        test_script_template.format(i=i, num=hex(num), num_val=int_to_c_array(num))
    )
with open("test_uint256_common_set_uint32.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
