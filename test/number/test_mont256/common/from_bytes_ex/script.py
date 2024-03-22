import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    std::uint8_t num{i}[{num_size}] = {num_val};
    std::uint8_t ret{i}[32] = {ret_val};
    mont256_from_bytes_ex(&ctx, ret, num{i}, {num_size});
    mont256_to_bytes(&ctx, ret_data, ret);
    if (std::memcmp(ret{i}, ret_data, 32) != 0)
    {{
        throw std::runtime_error("err in common::mont256_from_bytes_ex");
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

void test_mont256_common_from_bytes_ex()
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

    mont256_t    ret;
    std::uint8_t ret_data[32];

{code}
}}"""


def int_to_c_array(n: int, bits: int):
    bytes_n = n.to_bytes(bits // 8, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


P = (2**256) - (2**224) - (2**96) + (2**64) - 1
P_SUB2 = P - 2
R = (2**256) % P
R_POW2 = (R * R) % P
N_ = 1

c_code = []
for i in range(TEST_VECTOR_NUM):
    num_size = random.randint(1, 100)
    num = int.from_bytes(os.urandom(num_size), "big")
    ret_ = num % P
    c_code.append(
        test_script_template.format(
            i=i,
            num_size=num_size,
            num_val=int_to_c_array(num, num_size * 8),
            ret_val=int_to_c_array(ret_, 256),
        )
    )
with open("test_mont256_common_from_bytes_ex.cpp", "w") as fp:
    fp.write(
        c_code_template.format(
            P_val=int_to_c_array(P, 256),
            P_SUB2_val=int_to_c_array(P_SUB2, 256),
            R_val=int_to_c_array(R, 256),
            R_POW2_val=int_to_c_array(R_POW2, 256),
            N_=N_,
            code=os.linesep.join(c_code),
        )
    )
