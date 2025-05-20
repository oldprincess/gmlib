import hashlib
import os
import random


code_template = """\
    std::uint8_t msg{i}[{msg_size}]    = {msg_val};
    std::uint8_t digest{i}[20] = {digest_val};
    ctx.reset();
    ctx.do_final(digest, msg{i}, sizeof(msg{i}));
    if (std::memcmp(digest{i}, digest, SHA1::DIGEST_SIZE) != 0)
    {{
        throw std::runtime_error("err in sha1");
    }}"""

code_script = """\
#include <gmlib/sha1/sha1.h>
#include <cstring>
#include <stdexcept>

using namespace sha1;

void test_sha1()
{{
    SHA1 ctx;
    std::uint8_t  digest[SHA1::DIGEST_SIZE];

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
    digest = hashlib.new("sha1", msg).digest()
    code.append(
        code_template.format(
            i=i,
            msg_size=msg_size,
            msg_val=to_c_array(msg),
            digest_val=to_c_array(digest),
        )
    )

with open("test_sha1.cpp", "w") as fp:
    fp.write(code_script.format(code=os.linesep.join(code)))
