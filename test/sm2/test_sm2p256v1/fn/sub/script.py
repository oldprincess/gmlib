import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t a{i}[32] = {a_val};
    static std::uint8_t b{i}[32] = {b_val};
    static std::uint8_t c{i}[32] = {c_val};
    sm2_fn_from_bytes(a, a{i});
    sm2_fn_from_bytes(b, b{i});
    sm2_fn_sub(c, a, b);
    sm2_fn_to_bytes(c_data, c);
    if (std::memcmp(c{i}, c_data, 32) != 0)
    {{
        throw std::runtime_error("err in sm2_fn_sub");
    }}"""


c_code_template = """\
#include <gmlib/sm2/internal/sm2p256v1.h>
#include <stdexcept>
#include <cstring>

using namespace sm2::internal;

void test_sm2_fn_sub()
{{
    sm2_fn_t    a, b, c;
    std::uint8_t c_data[32];

{}
}}"""


def int_to_c_array(n: int):
    bytes_n = n.to_bytes(32, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


N = 0xfffffffe_ffffffff_ffffffff_ffffffff_7203df6b_21c6052b_53bbf409_39d54123
c_code = []
for i in range(TEST_VECTOR_NUM):
    a = random.randint(0, 2**256 - 1) % N
    b = random.randint(0, 2**256 - 1) % N
    c = (a - b) % N
    c_code.append(
        test_script_template.format(
            i=i,
            a_val=int_to_c_array(a),
            b_val=int_to_c_array(b),
            c_val=int_to_c_array(c),
        )
    )
with open("test_sm2_fn_sub.cpp", "w") as fn:
    fn.write(c_code_template.format(os.linesep.join(c_code)))
