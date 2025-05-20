import hashlib
import os
import random


code_template = """\
    std::uint8_t msg{i}[{msg_size}]    = {msg_val};
    std::uint8_t digest{i}[16] = {digest_val};
    ctx.reset();
    ctx.do_final(digest, msg{i}, sizeof(msg{i}));
    if (std::memcmp(digest{i}, digest, MD5::DIGEST_SIZE) != 0)
    {{
        throw std::runtime_error("err in md5");
    }}"""


code_script = """\
#include <gmlib/md5/md5.h>
#include <cstring>
#include <stdexcept>

using namespace md5;

void test_md5()
{{
    MD5 ctx;
    std::uint8_t  digest[MD5::DIGEST_SIZE];

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
    digest = hashlib.new("md5", msg).digest()
    code.append(
        code_template.format(
            i=i,
            msg_size=msg_size,
            msg_val=to_c_array(msg),
            digest_val=to_c_array(digest),
        )
    )

with open("test_md5.cpp", "w") as fp:
    fp.write(code_script.format(code=os.linesep.join(code)))
