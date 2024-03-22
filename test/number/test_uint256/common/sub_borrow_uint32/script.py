import random
import os


TEST_VECTOR_NUM = 100


test_script_template = """\
    static std::uint8_t  minuend{i}[32]    = {minuend_val};
    static std::uint32_t subtrahend{i}     = {subtrahend_val};
    static std::uint8_t  difference{i}[32] = {difference_val};
    static int           borrow{i}         = {borrow_val};
    uint256_from_bytes(minuend, minuend{i});
    borrow = uint256_sub_borrow_uint32(difference, minuend, subtrahend{i});
    uint256_to_bytes(difference_data, difference);
    if (std::memcmp(difference{i}, difference_data, 32) != 0 || borrow{i} != borrow)
    {{
        throw std::runtime_error("err in common::uint256_sub_borrow_uint32");
    }}"""


c_code_template = """\
#include <gmlib/number/internal/uint256_common.h>
#include <stdexcept>
#include <cstring>

using namespace number::internal::common;

void test_uint256_common_sub_borrow_uint32()
{{
    uint256_t    minuend, difference;
    int          borrow;
    std::uint8_t difference_data[32];

{}
}}"""


def int_to_c_array(n: int):
    bytes_n = n.to_bytes(32, "big")
    hex_n = map(lambda c: "0x" + hex(c)[2::].zfill(2), bytes_n)
    return "{" + ",".join(hex_n) + "}"


c_code = []
for i in range(TEST_VECTOR_NUM):
    minuend = random.randint(0, 2**256 - 1)
    subtrahend = random.randint(0, 2**32 - 1)
    borrow, difference_ = divmod(minuend - subtrahend, 2**256)
    c_code.append(
        test_script_template.format(
            i=i,
            minuend_val=int_to_c_array(minuend),
            subtrahend_val=subtrahend,
            difference_val=int_to_c_array(difference_),
            borrow_val=borrow,
        )
    )
with open("test_uint256_common_sub_borrow_uint32.cpp", "w") as fp:
    fp.write(c_code_template.format(os.linesep.join(c_code)))
