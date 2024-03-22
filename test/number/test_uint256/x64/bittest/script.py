import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    std::uint8_t a{i}_data[32]  = {a_val};
    bool         a{i}_bits[256] = {a_bits};
    uint256_from_bytes(a, a{i}_data);
    for (int i = 0; i < 256; i++)
    {{
        if (uint256_bittest(a, i) != a{i}_bits[i])
        {{
            throw std::runtime_error("err in uint256_x64_bittest");
        }}
    }}"""


c_code_template = """\
#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#include <gmlib/number/internal/uint256_x64.h>
#include <stdexcept>

using namespace number::internal::x64;

void test_uint256_x64_bittest()
{{
    uint256_t a;

{}
}}
#else
void test_uint256_x64_bittest()
{{
}}
#endif"""


def int_to_c_array(n: int):
    bytes_n = n.to_bytes(32, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


c_code = []
for i in range(TEST_VECTOR_NUM):
    a = random.randint(0, 2**256 - 1)
    a_bin = bin(a)[2::].zfill(256)
    a_bits = ["true" if a_bin[255 - j] == "1" else "false" for j in range(256)]
    c_code.append(
        test_script_template.format(
            i=i, a_val=int_to_c_array(a), a_bits="{" + ",".join(a_bits) + "}"
        )
    )
with open("test_uint256_x64_bittest.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
