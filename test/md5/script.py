import hashlib
import os
import random


code_template = """\
    std::uint8_t msg{i}[{msg_size}]    = {msg_val};
    std::uint8_t digest{i}[16] = {digest_val};
    md5_reset(&ctx);
    block_num = sizeof(msg{i}) / MD5_BLOCK_SIZE;
    process_n = block_num * MD5_BLOCK_SIZE;
    md5_update_blocks(&ctx, msg{i}, block_num);
    md5_final_block(&ctx, digest, msg{i} + process_n,
                        sizeof(msg{i}) - process_n);
    if (std::memcmp(digest{i}, digest, MD5_DIGEST_SIZE) != 0)
    {{
        throw std::runtime_error("err in md5");
    }}"""


code_script_common = """\
#include <gmlib/md5/internal/md5_common.h>
#include <cstring>
#include <stdexcept>

using namespace md5::internal::common;

void test_md5_common()
{{
    Md5CTX ctx;
    md5_init(&ctx);
    std::uint8_t  digest[MD5_DIGEST_SIZE];
    std::size_t   block_num, process_n;

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

with open("test_md5_common.cpp", "w") as fp:
    fp.write(code_script_common.format(code=os.linesep.join(code)))

