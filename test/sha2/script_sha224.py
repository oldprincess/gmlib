import hashlib
import os
import random

random.seed(224)

code_template = """\
    std::uint8_t msg{i}[{msg_size}]    = {msg_val};
    std::uint8_t digest{i}[SHA224::DIGEST_SIZE] = {digest_val};
    ctx.reset();
    ctx.do_final(digest, msg{i}, sizeof(msg{i}));
    if (std::memcmp(digest{i}, digest, SHA224::DIGEST_SIZE) != 0)
    {{
        throw std::runtime_error("err in sha224");
    }}"""

code_script = """\
#include <gmlib/sha2/sha2.h>
#include <cstring>
#include <stdexcept>

using namespace sha2;

void test_sha224()
{{
    SHA224 ctx;
    std::uint8_t  digest[SHA224::DIGEST_SIZE];

{code}
}}
"""


def to_c_array(b: bytes):
    return "{" + ",".join(map(lambda c: "0x" + hex(c)[2::].zfill(2), b)) + "}"


TEST_VECTOR_NUM = 100
code = []
for i in range(TEST_VECTOR_NUM):
    msg_size = random.randint(1, 512)
    msg = bytes([random.randint(0, 255) for _ in range(msg_size)])
    digest = hashlib.new("sha224", msg).digest()
    code.append(
        code_template.format(
            i=i,
            msg_size=msg_size,
            msg_val=to_c_array(msg),
            digest_val=to_c_array(digest),
        )
    )

with open("test_sha224.cpp", "w") as fp:
    fp.write(code_script.format(code=os.linesep.join(code)))
