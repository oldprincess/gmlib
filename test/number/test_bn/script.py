import random

template = """
#include <gmlib/number/bn.h>

#include <cstring>
#include <stdexcept>

using namespace number;
using namespace std;

void test_bn()
{{
    BigNum a1 = BigNum::from_uint32(0);
    BigNum a2 = BigNum::from_uint32(0);
    BigNum b1 = BigNum::from_uint32(0);
    BigNum b2 = BigNum::from_uint32(0);
    {}
}}
"""

code = []
MAX_SIZE = 1 << 512
# test add
for _ in range(100):
    a1 = random.randint(-MAX_SIZE, MAX_SIZE)
    a2 = random.randint(-MAX_SIZE, MAX_SIZE)
    code.append(
        f"""
    a1 = BigNum::from_str("{a1}");
    a2 = BigNum::from_str("{a2}");
    if((a1 + a2).to_str() != "{a1 + a2}")
    {{
        std::printf("line=%d\\n", __LINE__);
        throw std::runtime_error("err in bn_add");
    }}
"""
    )
# test sub
for _ in range(100):
    a1 = random.randint(-MAX_SIZE, MAX_SIZE)
    a2 = random.randint(-MAX_SIZE, MAX_SIZE)
    code.append(
        f"""
    a1 = BigNum::from_str("{a1}");
    a2 = BigNum::from_str("{a2}");
    if((a1 - a2).to_str() != "{a1 - a2}")
    {{
        std::printf("line=%d\\n", __LINE__);
        throw std::runtime_error("err in bn_sub");
    }}
"""
    )
# test mul
for _ in range(100):
    a1 = random.randint(-MAX_SIZE, MAX_SIZE)
    a2 = random.randint(-MAX_SIZE, MAX_SIZE)
    code.append(
        f"""
    a1 = BigNum::from_str("{a1}");
    a2 = BigNum::from_str("{a2}");
    if((a1 * a2).to_str() != "{a1 * a2}")
    {{
        std::printf("line=%d\\n", __LINE__);
        throw std::runtime_error("err in bn_mul");
    }}
"""
    )
# test div
for _ in range(100):
    a1 = random.randint(0, MAX_SIZE << random.randint(1, 256))
    a2 = random.randint(0, MAX_SIZE) 
    code.append(
        f"""
    a1 = BigNum::from_str("{a1}");
    a2 = BigNum::from_str("{a2}");
    if((a1 / a2).to_str() != "{a1 // a2}")
    {{
        std::printf("line=%d\\n", __LINE__);
        throw std::runtime_error("err in bn_div");
    }}
"""
    )
# test mod
for _ in range(100):
    a1 = random.randint(0, MAX_SIZE << random.randint(1, 256))
    a2 = random.randint(0, MAX_SIZE)
    code.append(
        f"""
    a1 = BigNum::from_str("{a1}");
    a2 = BigNum::from_str("{a2}");
    if((a1 % a2).to_str() != "{a1 % a2}")
    {{
        std::printf("line=%d\\n", __LINE__);
        throw std::runtime_error("err in bn_div");
    }}
"""
    )
with open("test_bn.cpp", "w") as fp:
    fp.write(template.format("".join(code)))
