import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t a{i}[32] = {a_val};
    static std::uint8_t c{i}[32] = {c_val};
    sm2_fp_from_bytes(a, a{i});
    sm2_fp_tpl(c, a);
    sm2_fp_to_bytes(c_data, c);
    if (std::memcmp(c{i}, c_data, 32) != 0)
    {{
        throw std::runtime_error("err in sm2_fp_tpl");
    }}"""


c_code_template = """\
#include <gmlib/sm2/internal/sm2p256v1.h>
#include <stdexcept>
#include <cstring>

using namespace sm2::internal;

void test_sm2_fp_tpl()
{{
    sm2_fp_t    a, c;
    std::uint8_t c_data[32];

{}
}}"""


def int_to_c_array(n: int):
    bytes_n = n.to_bytes(32, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


P = (2**256) - (2**224) - (2**96) + (2**64) - 1
c_code = []
for i in range(TEST_VECTOR_NUM):
    a = random.randint(0, 2**256 - 1) % P
    c = (3 * a) % P
    c_code.append(
        test_script_template.format(
            i=i,
            a_val=int_to_c_array(a),
            c_val=int_to_c_array(c),
        )
    )
with open("test_sm2_fp_tpl.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
