import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    std::uint8_t  a{i}_data[32] = {a_val};
    std::uint32_t b{i}          = {b};
    int           cmp{i}        = {cmp};
    uint256_from_bytes(a, a{i}_data);
    if (uint256_cmp_uint32(a, b{i}) != cmp{i})
    {{
        throw std::runtime_error("err in uint256_common_cmp_uint32");
    }}"""


c_code_template = """\
#include <gmlib/number/internal/uint256_common.h>
#include <stdexcept>

using namespace number::internal::common;

void test_uint256_common_cmp_uint32()
{{
    uint256_t a;

{}
}}"""


def int_to_c_array(n: int):
    bytes_n = n.to_bytes(32, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


c_code = []
for i in range(TEST_VECTOR_NUM):
    a = random.randint(0, 2**256 - 1)
    b = random.randint(0, 2**32 - 1)
    if random.randint(0, 4) == 1:
        a = b
    elif random.randint(0, 2) == 1:
        a = random.randint(0, b)
    if a == b:
        cmp = 0
    elif a < b:
        cmp = -1
    else:
        cmp = 1
    c_code.append(
        test_script_template.format(
            i=i, a_val=int_to_c_array(a), b=b, cmp=cmp
        )
    )
with open("test_uint256_common_cmp_uint32.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
