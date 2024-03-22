import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t a{i}[32] = {a_val};
    static std::uint8_t c{i}[32] = {c_val};
    sm9_fp_from_bytes(a, a{i});
    if(sm9_fp_sqrt(c, a))
    {{
        throw std::runtime_error("err in call sm9_fp_sqrt");
    }}
    sm9_fp_sqr(c, c);
    if (!sm9_fp_equal(c, a))
    {{
        throw std::runtime_error("err in sm9_fp_sqrt");
    }}"""


c_code_template = """\
#include <gmlib/sm9/internal/sm9_field.h>
#include <stdexcept>
#include <cstring>

using namespace sm9::internal;

void test_sm9_fp_sqrt()
{{
    sm9_fp_t    a, c;

{}
}}"""


def int_to_c_array(n: int):
    bytes_n = n.to_bytes(32, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


P =  0xB640000002A3A6F1D603AB4FF58EC74521F2934B1A7AEEDBE56F9B27E351457D

c_code = []
for i in range(TEST_VECTOR_NUM):
    a = random.randint(1, P - 1)
    a2 = (a * a) % P
    c_code.append(
        test_script_template.format(
            i=i,
            a_val=int_to_c_array(a2),
            c_val=int_to_c_array(a),
        )
    )
with open("test_sm9_fp_sqrt.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
