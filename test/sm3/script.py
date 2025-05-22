import hashlib
import os
import random


code_template = """\
    static std::uint8_t msg{i}[{msg_size}]    = {msg_val};
    static std::uint8_t digest{i}[32] = {digest_val};
    ctx.reset();
    ctx.do_final(digest, msg{i}, sizeof(msg{i}));
    if (std::memcmp(digest{i}, digest, SM3::DIGEST_SIZE) != 0)
    {{
        throw std::runtime_error("err in sm3");
    }}"""

code_script = """\
#include <gmlib/sm3/sm3.h>
#include <cstring>
#include <stdexcept>

using namespace sm3;

void test_sm3()
{{
    SM3 ctx;
    std::uint8_t  digest[SM3::DIGEST_SIZE];

{code}
}}
"""


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
with open("test_sm3.cpp", "w") as fp:
    fp.write(code_script.format(code=os.linesep.join(code)))
