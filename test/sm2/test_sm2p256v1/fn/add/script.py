import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t augend{i}[32] = {augend_val};
    static std::uint8_t addend{i}[32] = {addend_val};
    static std::uint8_t sum{i}[32]    = {sum_val};
    sm2_fn_from_bytes(augend, augend{i});
    sm2_fn_from_bytes(addend, addend{i});
    sm2_fn_add(sum, augend, addend);
    sm2_fn_to_bytes(sum_data, sum);
    if (std::memcmp(sum{i}, sum_data, 32) != 0)
    {{
        throw std::runtime_error("err in sm2_fn_add");
    }}"""


c_code_template = """\
#include <gmlib/sm2/internal/sm2p256v1.h>
#include <stdexcept>
#include <cstring>

using namespace sm2::internal;

void test_sm2_fn_add()
{{
    sm2_fn_t    augend, addend, sum;
    std::uint8_t sum_data[32];

{}
}}"""


def int_to_c_array(n: int):
    bytes_n = n.to_bytes(32, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


N = 0xfffffffe_ffffffff_ffffffff_ffffffff_7203df6b_21c6052b_53bbf409_39d54123
c_code = []
for i in range(TEST_VECTOR_NUM):
    augend = random.randint(0, 2**256 - 1) % N
    addend = random.randint(0, 2**256 - 1) % N
    sum_ = (augend + addend) % N
    c_code.append(
        test_script_template.format(
            i=i,
            augend_val=int_to_c_array(augend),
            addend_val=int_to_c_array(addend),
            sum_val=int_to_c_array(sum_),
        )
    )
with open("test_sm2_fn_add.cpp", "w") as fn:
    fn.write(c_code_template.format(os.linesep.join(c_code)))
