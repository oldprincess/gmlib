import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    std::uint8_t augend{i}[32] = {augend_val};
    std::uint8_t addend{i}[32] = {addend_val};
    std::uint8_t sum{i}[32]    = {sum_val};
    mont256_from_bytes(&ctx, augend, augend{i});
    mont256_from_bytes(&ctx, addend, addend{i});
    mont256_add(&ctx, sum, augend, addend);
    mont256_to_bytes(&ctx, sum_data, sum);
    if (std::memcmp(sum{i}, sum_data, 32) != 0)
    {{
        throw std::runtime_error("err in common::mont256_add");
    }}"""


c_code_template = """\
#include <gmlib/number/internal/mont256_common.h>
#include <gmlib/number/internal/uint256_common.h>
#include <stdexcept>
#include <cstring>

using namespace number::internal::common;

static std::uint8_t  P_data[32]      = {P_val};
static std::uint8_t  P_SUB2_data[32] = {P_SUB2_val};
static std::uint8_t  R_data[32]      = {R_val};
static std::uint8_t  R_POW2_data[32] = {R_POW2_val};
static std::uint32_t N_              = {N_};

void test_mont256_common_add()
{{
    uint256_t P, P_SUB2, R, R_POW2;
    uint256_from_bytes(P, P_data);
    uint256_from_bytes(P_SUB2, P_SUB2_data);
    uint256_from_bytes(R, R_data);
    uint256_from_bytes(R_POW2, R_POW2_data);

    Mont256CTX ctx;
    ctx.P = P, ctx.P_SUB2 = P_SUB2;
    ctx.R = R, ctx.R_POW2 = R_POW2;
    ctx.N_ = N_;

    mont256_t    augend, addend, sum;
    std::uint8_t sum_data[32];

{code}
}}"""


def int_to_c_array(n: int):
    bytes_n = n.to_bytes(32, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


P = (2**256) - (2**224) - (2**96) + (2**64) - 1
P_SUB2 = P - 2
R = (2**256) % P
R_POW2 = (R * R) % P
N_ = 1

c_code = []
for i in range(TEST_VECTOR_NUM):
    augend = random.randint(0, P - 1)
    addend = random.randint(0, P - 1)
    sum_ = (augend + addend) % P
    c_code.append(
        test_script_template.format(
            i=i,
            augend_val=int_to_c_array(augend),
            addend_val=int_to_c_array(addend),
            sum_val=int_to_c_array(sum_),
        )
    )
with open("test_mont256_common_add.cpp", "w") as fp:
    fp.write(
        c_code_template.format(
            P_val=int_to_c_array(P),
            P_SUB2_val=int_to_c_array(P_SUB2),
            R_val=int_to_c_array(R),
            R_POW2_val=int_to_c_array(R_POW2),
            N_=N_,
            code=os.linesep.join(c_code),
        )
    )
