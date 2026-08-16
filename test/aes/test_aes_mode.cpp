#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

#include "test.h"

namespace {

std::vector<std::uint8_t> from_hex(const char* hex)
{
    auto nibble = [](char value) -> std::uint8_t {
        if (value >= '0' && value <= '9')
        {
            return static_cast<std::uint8_t>(value - '0');
        }
        if (value >= 'a' && value <= 'f')
        {
            return static_cast<std::uint8_t>(value - 'a' + 10);
        }
        if (value >= 'A' && value <= 'F')
        {
            return static_cast<std::uint8_t>(value - 'A' + 10);
        }
        throw std::runtime_error("invalid hexadecimal test vector");
    };

    const std::size_t length = std::char_traits<char>::length(hex);
    if ((length & 1U) != 0)
    {
        throw std::runtime_error("odd hexadecimal test vector length");
    }
    std::vector<std::uint8_t> output(length / 2);
    for (std::size_t i = 0; i < output.size(); ++i)
    {
        output[i] = static_cast<std::uint8_t>((nibble(hex[2 * i]) << 4) |
                                              nibble(hex[2 * i + 1]));
    }
    return output;
}

constexpr const char* SP800_38A_PLAINTEXT =
    "6bc1bee22e409f96e93d7e117393172a"
    "ae2d8a571e03ac9c9eb76fac45af8e51"
    "30c81c46a35ce411e5fbc1191a0a52ef"
    "f69f2445df4f9b17ad2b417be66c3710";
constexpr const char* SP800_38A_IV      = "000102030405060708090a0b0c0d0e0f";
constexpr const char* SP800_38A_COUNTER = "f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff";

struct KatSet
{
    const char*                key;
    std::array<const char*, 5> ciphertexts;
};

constexpr std::array<KatSet, 3> SP800_38A = {{
    {
        "2b7e151628aed2a6abf7158809cf4f3c",
        {
            "3ad77bb40d7a3660a89ecaf32466ef97"
            "f5d3d58503b9699de785895a96fdbaaf"
            "43b1cd7f598ece23881b00e3ed030688"
            "7b0c785e27e8ad3f8223207104725dd4",
            "7649abac8119b246cee98e9b12e9197d"
            "5086cb9b507219ee95db113a917678b2"
            "73bed6b8e3c1743b7116e69e22229516"
            "3ff1caa1681fac09120eca307586e1a7",
            "3b3fd92eb72dad20333449f8e83cfb4a"
            "c8a64537a0b3a93fcde3cdad9f1ce58b"
            "26751f67a3cbb140b1808cf187a4f4df"
            "c04b05357c5d1c0eeac4c66f9ff7f2e6",
            "3b3fd92eb72dad20333449f8e83cfb4a"
            "7789508d16918f03f53c52dac54ed825"
            "9740051e9c5fecf64344f7a82260edcc"
            "304c6528f659c77866a510d9c1d6ae5e",
            "874d6191b620e3261bef6864990db6ce"
            "9806f66b7970fdff8617187bb9fffdff"
            "5ae4df3edbd5d35e5b4f09020db03eab"
            "1e031dda2fbe03d1792170a0f3009cee",
        },
    },
    {
        "8e73b0f7da0e6452c810f32b809079e5"
        "62f8ead2522c6b7b",
        {
            "bd334f1d6e45f25ff712a214571fa5cc"
            "974104846d0ad3ad7734ecb3ecee4eef"
            "ef7afd2270e2e60adce0ba2face6444e"
            "9a4b41ba738d6c72fb16691603c18e0e",
            "4f021db243bc633d7178183a9fa071e8"
            "b4d9ada9ad7dedf4e5e738763f69145a"
            "571b242012fb7ae07fa9baac3df102e0"
            "08b0e27988598881d920a9e64f5615cd",
            "cdc80d6fddf18cab34c25909c99a4174"
            "67ce7f7f81173621961a2b70171d3d7a"
            "2e1e8a1dd59b88b1c8e60fed1efac4c9"
            "c05f9f9ca9834fa042ae8fba584b09ff",
            "cdc80d6fddf18cab34c25909c99a4174"
            "fcc28b8d4c63837c09e81700c1100401"
            "8d9a9aeac0f6596f559c6d4daf59a5f2"
            "6d9f200857ca6c3e9cac524bd9acc92a",
            "1abc932417521ca24f2b0459fe7e6e0b"
            "090339ec0aa6faefd5ccc2c6f4ce8e94"
            "1e36b26bd1ebc670d1bd1d665620abf7"
            "4f78a7f6d29809585a97daec58c6b050",
        },
    },
    {
        "603deb1015ca71be2b73aef0857d7781"
        "1f352c073b6108d72d9810a30914dff4",
        {
            "f3eed1bdb5d2a03c064b5a7e3db181f8"
            "591ccb10d410ed26dc5ba74a31362870"
            "b6ed21b99ca6f4f9f153e7b1beafed1d"
            "23304b7a39f9f3ff067d8d8f9e24ecc7",
            "f58c4c04d6e5f1ba779eabfb5f7bfbd6"
            "9cfc4e967edb808d679f777bc6702c7d"
            "39f23369a9d9bacfa530e26304231461"
            "b2eb05e2c39be9fcda6c19078c6a9d1b",
            "dc7e84bfda79164b7ecd8486985d3860"
            "39ffed143b28b1c832113c6331e5407b"
            "df10132415e54b92a13ed0a8267ae2f9"
            "75a385741ab9cef82031623d55b1e471",
            "dc7e84bfda79164b7ecd8486985d3860"
            "4febdc6740d20b3ac88f6ad82a4fb08d"
            "71ab47a086e86eedf39d1c5bba97c408"
            "0126141d67f37be8538f5a8be740e484",
            "601ec313775789a5b7a7f504bbf3d228"
            "f443e3ca4d62b59aca84e990cacaf5c5"
            "2b0930daa23de94ce87017ba2d84988d"
            "dfc9c58db67aada613c2dd08457941a6",
        },
    },
}};

struct GcmKat
{
    const char* ciphertext;
    const char* tag;
};

// NIST SP 800-38D/CAVP: zero key, 96-bit zero IV, one zero block, no AAD.
constexpr std::array<GcmKat, 3> GCM_KATS = {{
    {"0388dace60b6a392f328c2b971b2fe78", "ab6e47d42cec13bdf53a67b21257bddf"},
    {"98e7247c07f0fe411c267e4384b0f600", "2ff58d80033927ab8ef4d4587514f0fb"},
    {"cea7403d4d606b6e074ec5d3baf39d18", "d0d1c8a799996bf0265b98b5d48ab919"},
}};

std::vector<block_cipher_mode::test::ModeKat> make_mode_kats(
    std::size_t variant_index)
{
    const KatSet&                   vectors   = SP800_38A[variant_index];
    const std::vector<std::uint8_t> key       = from_hex(vectors.key);
    const std::vector<std::uint8_t> iv        = from_hex(SP800_38A_IV);
    const std::vector<std::uint8_t> counter   = from_hex(SP800_38A_COUNTER);
    const std::vector<std::uint8_t> plaintext = from_hex(SP800_38A_PLAINTEXT);
    return {
        {"nist-sp800-38a",
         "ECB",
         key,
         {},
         plaintext,
         from_hex(vectors.ciphertexts[0])},
        {"nist-sp800-38a", "CBC", key, iv, plaintext,
         from_hex(vectors.ciphertexts[1])},
        {"nist-sp800-38a", "CFB", key, iv, plaintext,
         from_hex(vectors.ciphertexts[2])},
        {"nist-sp800-38a", "OFB", key, iv, plaintext,
         from_hex(vectors.ciphertexts[3])},
        {"nist-sp800-38a", "CTR", key, counter, plaintext,
         from_hex(vectors.ciphertexts[4])},
    };
}

std::vector<block_cipher_mode::test::AeadKat> make_aead_kats(
    std::size_t variant_index,
    std::size_t key_len)
{
    const GcmKat& vectors = GCM_KATS[variant_index];
    return {{"nist-sp800-38d",
             "GCM",
             std::vector<std::uint8_t>(key_len, 0),
             std::vector<std::uint8_t>(12, 0),
             {},
             std::vector<std::uint8_t>(16, 0),
             from_hex(vectors.ciphertext),
             from_hex(vectors.tag)}};
}

} // namespace

std::vector<block_cipher_mode::test::ModeKat> get_aes128_mode_kats()
{
    return make_mode_kats(0);
}

std::vector<block_cipher_mode::test::ModeKat> get_aes192_mode_kats()
{
    return make_mode_kats(1);
}

std::vector<block_cipher_mode::test::ModeKat> get_aes256_mode_kats()
{
    return make_mode_kats(2);
}

std::vector<block_cipher_mode::test::AeadKat> get_aes128_aead_kats()
{
    return make_aead_kats(0, 16);
}

std::vector<block_cipher_mode::test::AeadKat> get_aes192_aead_kats()
{
    return make_aead_kats(1, 24);
}

std::vector<block_cipher_mode::test::AeadKat> get_aes256_aead_kats()
{
    return make_aead_kats(2, 32);
}
