import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t augend{i}[32] = {augend_val};
    static std::uint8_t addend{i}[32] = {addend_val};
    static std::uint8_t sum{i}[32]    = {sum_val};
    sm9_fp_from_bytes(augend, augend{i});
    sm9_fp_from_bytes(addend, addend{i});
    sm9_fp_add(sum, augend, addend);
    sm9_fp_to_bytes(sum_data, sum);
    if (std::memcmp(sum{i}, sum_data, 32) != 0)
    {{
        throw std::runtime_error("err in sm9_fp_add");
    }}"""


c_code_template = """\
#include <gmlib/sm9/internal/sm9_field.h>
#include <stdexcept>
#include <cstring>

using namespace sm9::internal;

void test_sm9_fp_add()
{{
    sm9_fp_t    augend, addend, sum;
    std::uint8_t sum_data[32];

{}
}}"""


def int_to_c_array(n: int):
    bytes_n = n.to_bytes(32, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


P = 0xb640000002a3a6f1d603ab4ff58ec74521f2934b1a7aeedbe56f9b27e351457d
c_code = []
for i in range(TEST_VECTOR_NUM):
    augend = random.randint(0, 2**256 - 1) % P
    addend = random.randint(0, 2**256 - 1) % P
    sum_ = (augend + addend) % P
    c_code.append(
        test_script_template.format(
            i=i,
            augend_val=int_to_c_array(augend),
            addend_val=int_to_c_array(addend),
            sum_val=int_to_c_array(sum_),
        )
    )
with open("test_sm9_fp_add.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
