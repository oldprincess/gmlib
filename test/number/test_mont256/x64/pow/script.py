import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    std::uint8_t base{i}[32]     = {base_val};
    std::uint8_t exponent{i}[32] = {exponent_val};
    std::uint8_t power{i}[32]    = {power_val};
    mont256_from_bytes(&ctx, base, base{i});
    uint256_from_bytes(exponent, exponent{i});
    mont256_pow(&ctx, power, base, exponent);
    mont256_to_bytes(&ctx, power_data, power);
    if (std::memcmp(power{i}, power_data, 32) != 0)
    {{
        throw std::runtime_error("err in x64::mont256_pow");
    }}"""


c_code_template = """\
#if defined(CPU_FLAG_MOVBE) && defined(CPU_FLAG_BMI2)
#include <gmlib/number/internal/mont256_x64.h>
#include <gmlib/number/internal/uint256_x64.h>
#include <stdexcept>
#include <cstring>

using namespace number::internal::x64;

static std::uint8_t  P_data[32]      = {P_val};
static std::uint8_t  P_SUB2_data[32] = {P_SUB2_val};
static std::uint8_t  R_data[32]      = {R_val};
static std::uint8_t  R_POW2_data[32] = {R_POW2_val};
static std::uint32_t N_              = {N_};

void test_mont256_x64_pow()
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

    mont256_t    base, exponent, power;
    std::uint8_t power_data[32];

{code}
}}
#else
void test_mont256_x64_pow()
{{
}}
#endif"""


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
    base = random.randint(0, P - 1)
    exponent = random.randint(0, 2**256 - 1)
    power_ = pow(base, exponent, P)
    c_code.append(
        test_script_template.format(
            i=i,
            base_val=int_to_c_array(base),
            exponent_val=int_to_c_array(exponent),
            power_val=int_to_c_array(power_),
        )
    )
with open("test_mont256_x64_pow.cpp", "w") as fp:
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
