import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    std::uint8_t num{i}[{num_size}] = {num_val};
    std::uint8_t ret{i}[32] = {ret_val};
    sm9_bn_mod_n_sub1_ex(ret, num{i}, {num_size});
    sm9_bn_to_bytes(ret_data, ret);
    if (std::memcmp(ret{i}, ret_data, 32) != 0)
    {{
        throw std::runtime_error("err in sm9_bn_mod_n_sub1_ex");
    }}"""


c_code_template = """\
#include <gmlib/sm9/internal/sm9_field.h>
#include <gmlib/number/uint256.h>
#include <stdexcept>
#include <cstring>

using namespace sm9::internal;
using namespace number;

static std::uint8_t  N_SUB1_data[32]      = {N_SUB1_val};

void test_sm9_bn_mod_n_sub1_ex()
{{
    uint256_t N_SUB1;
    uint256_from_bytes(N_SUB1, N_SUB1_data);

    sm9_bn_t    ret;
    std::uint8_t ret_data[32];

{code}
}}"""


def int_to_c_array(n: int, bits: int):
    bytes_n = n.to_bytes(bits // 8, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


N_SUB1 = 0xb640000002a3a6f1d603ab4ff58ec74449f2934b18ea8beee56ee19cd69ecf25 - 1

c_code = []
for i in range(TEST_VECTOR_NUM):
    num_size = random.randint(1, 100)
    num = int.from_bytes(os.urandom(num_size), "big")
    ret_ = num % N_SUB1
    c_code.append(
        test_script_template.format(
            i=i,
            num_size=num_size,
            num_val=int_to_c_array(num, num_size * 8),
            ret_val=int_to_c_array(ret_, 256),
        )
    )
with open("test_sm9_bn_mod_n_sub1_ex.cpp", "w") as fp:
    fp.write(
        c_code_template.format(
            N_SUB1_val=int_to_c_array(N_SUB1, 256),
            code=os.linesep.join(c_code),
        )
    )
