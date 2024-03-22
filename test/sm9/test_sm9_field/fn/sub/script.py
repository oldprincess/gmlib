import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t a{i}[32] = {a_val};
    static std::uint8_t b{i}[32] = {b_val};
    static std::uint8_t c{i}[32] = {c_val};
    sm9_fn_from_bytes(a, a{i});
    sm9_fn_from_bytes(b, b{i});
    sm9_fn_sub(c, a, b);
    sm9_fn_to_bytes(c_data, c);
    if (std::memcmp(c{i}, c_data, 32) != 0)
    {{
        throw std::runtime_error("err in sm9_fn_sub");
    }}"""


c_code_template = """\
#include <gmlib/sm9/internal/sm9_field.h>
#include <stdexcept>
#include <cstring>

using namespace sm9::internal;

void test_sm9_fn_sub()
{{
    sm9_fn_t    a, b, c;
    std::uint8_t c_data[32];

{}
}}"""


def int_to_c_array(n: int):
    bytes_n = n.to_bytes(32, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


N = 0xb640000002a3a6f1d603ab4ff58ec74449f2934b18ea8beee56ee19cd69ecf25
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
with open("test_sm9_fn_sub.cpp", "w") as fn:
    fn.write(c_code_template.format(os.linesep.join(c_code)))
