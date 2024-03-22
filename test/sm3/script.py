import hashlib
import os
import random


code_template = """\
    std::uint8_t msg{i}[{msg_size}]    = {msg_val};
    std::uint8_t digest{i}[32] = {digest_val};
    sm3_reset(&ctx);
    block_num = sizeof(msg{i}) / SM3_BLOCK_SIZE;
    process_n = block_num * SM3_BLOCK_SIZE;
    if (sm3_update_blocks(&ctx, msg{i}, block_num))
    {{
        throw std::runtime_error("err in sm3_yang15");
    }}
    if (sm3_final_block(&ctx, digest, msg{i} + process_n,
                        sizeof(msg{i}) - process_n))
    {{
        throw std::runtime_error("err in sm3_yang15");
    }}
    if (std::memcmp(digest{i}, digest, SM3_DIGEST_SIZE) != 0)
    {{
        throw std::runtime_error("err in sm3_yang15");
    }}"""

code_script = """\
#if defined(SUPPORT_SM3_YANG15)
#include <gmlib/sm3/internal/sm3_yang15.h>
#include <cstring>
#include <stdexcept>

using namespace sm3::internal::yang15;

void test_sm3_yang15()
{{
    Sm3CTX ctx;
    sm3_init(&ctx);
    std::uint8_t  digest[SM3_DIGEST_SIZE];
    std::size_t   block_num, process_n;

{code}
}}
#else
void test_sm3_yang15()
{{
}}
#endif"""


def to_c_array(b: bytes):
    return "{" + ",".join(map(lambda c: "0x" + hex(c)[2::].zfill(2), b)) + "}"


TEST_VECTOR_NUM = 100
code = []
for i in range(TEST_VECTOR_NUM):
    msg_size = random.randint(1, 512)
    msg = os.urandom(msg_size)
    digest = hashlib.new("sm3", msg).digest()
    code.append(
        code_template.format(
            i=i,
            msg_size=msg_size,
            msg_val=to_c_array(msg),
            digest_val=to_c_array(digest),
        )
    )
with open("test_sm3_yang15.cpp", "w") as fp:
    fp.write(code_script.format(code=os.linesep.join(code)))
