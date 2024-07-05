import hashlib
import os
import random


code_template = """\
    std::uint8_t msg{i}[{msg_size}]    = {msg_val};
    std::uint8_t digest{i}[20] = {digest_val};
    sha1_reset(&ctx);
    block_num = sizeof(msg{i}) / SHA1_BLOCK_SIZE;
    process_n = block_num * SHA1_BLOCK_SIZE;
    if (sha1_update_blocks(&ctx, msg{i}, block_num))
    {{
        throw std::runtime_error("err in sha1");
    }}
    if (sha1_final_block(&ctx, digest, msg{i} + process_n,
                        sizeof(msg{i}) - process_n))
    {{
        throw std::runtime_error("err in sha1");
    }}
    if (std::memcmp(digest{i}, digest, SHA1_DIGEST_SIZE) != 0)
    {{
        throw std::runtime_error("err in sha1");
    }}"""

code_script_sha = """\
#if defined(CPU_FLAG_SHA) && defined(CPU_FLAG_SSE4_1)
#include <gmlib/sha1/internal/sha1_sha.h>
#include <cstring>
#include <stdexcept>

using namespace sha1::internal::sha;

void test_sha1_sha()
{{
    Sha1CTX ctx;
    sha1_init(&ctx);
    std::uint8_t  digest[SHA1_DIGEST_SIZE];
    std::size_t   block_num, process_n;

{code}
}}
#else
void test_sha1_sha()
{{
}}
#endif"""

code_script_common = """\
#include <gmlib/sha1/internal/sha1_common.h>
#include <cstring>
#include <stdexcept>

using namespace sha1::internal::common;

void test_sha1_common()
{{
    Sha1CTX ctx;
    sha1_init(&ctx);
    std::uint8_t  digest[SHA1_DIGEST_SIZE];
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
    digest = hashlib.new("sha1", msg).digest()
    code.append(
        code_template.format(
            i=i,
            msg_size=msg_size,
            msg_val=to_c_array(msg),
            digest_val=to_c_array(digest),
        )
    )

with open("test_sha1_common.cpp", "w") as fp:
    fp.write(code_script_common.format(code=os.linesep.join(code)))
with open("test_sha1_sha.cpp", "w") as fp:
    fp.write(code_script_sha.format(code=os.linesep.join(code)))
