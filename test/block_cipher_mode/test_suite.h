#ifndef BLOCK_CIPHER_MODE_TEST_SUITE_H
#define BLOCK_CIPHER_MODE_TEST_SUITE_H

#include <gmlib/block_cipher_mode/provider.h>
#include <gmlib/ghash/ghash.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <limits>
#include <memory>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace block_cipher_mode::test {

struct CipherSpec
{
    std::string logical_name;
    std::size_t block_size;
    std::size_t user_key_len;
    std::size_t security_strength;
};

struct CipherKat
{
    std::string               case_name;
    std::vector<std::uint8_t> key;
    std::vector<std::uint8_t> plaintext;
    std::vector<std::uint8_t> ciphertext;
};

struct ModeKat
{
    std::string               case_name;
    std::string               mode;
    std::vector<std::uint8_t> key;
    std::vector<std::uint8_t> iv;
    std::vector<std::uint8_t> plaintext;
    std::vector<std::uint8_t> ciphertext;
};

struct AeadKat
{
    std::string               case_name;
    std::string               mode;
    std::vector<std::uint8_t> key;
    std::vector<std::uint8_t> nonce;
    std::vector<std::uint8_t> aad;
    std::vector<std::uint8_t> plaintext;
    std::vector<std::uint8_t> ciphertext;
    std::vector<std::uint8_t> tag;
};

struct TestSuite
{
    std::string            name;
    CipherSpec             cipher;
    std::vector<CipherKat> cipher_kats;
    std::vector<ModeKat>   mode_kats;
    std::vector<AeadKat>   aead_kats;
};

namespace detail {

using ModeFactory = std::unique_ptr<BlockCipherMode> (*)();

struct ModeFactories
{
    ModeFactory encryptor;
    ModeFactory decryptor;
};

enum class Feed
{
    ONE_SHOT,
    BYTEWISE,
    IRREGULAR,
};

struct CryptResult
{
    std::vector<std::uint8_t> output;
    std::vector<std::uint8_t> tag;
};

[[noreturn]] inline void invalid(const std::string& message)
{
    throw std::invalid_argument(message);
}

[[noreturn]] inline void fail(const std::string& context,
                              const std::string& message)
{
    throw std::runtime_error(context + ": " + message);
}

inline void require_config(bool condition, const std::string& message)
{
    if (!condition)
    {
        invalid(message);
    }
}

inline bool is_mode(const std::string& mode)
{
    return mode == "ECB" || mode == "CBC" || mode == "CFB" || mode == "OFB" ||
           mode == "CTR";
}

inline ModeFactories mode_factories(const BlockCipherModeProvider& provider,
                                    const std::string&             mode)
{
    if (mode == "ECB")
    {
        return {provider.create_ecb_encryptor, provider.create_ecb_decryptor};
    }
    if (mode == "CBC")
    {
        return {provider.create_cbc_encryptor, provider.create_cbc_decryptor};
    }
    if (mode == "CFB")
    {
        return {provider.create_cfb_encryptor, provider.create_cfb_decryptor};
    }
    if (mode == "OFB")
    {
        return {provider.create_ofb_encryptor, provider.create_ofb_decryptor};
    }
    if (mode == "CTR")
    {
        return {provider.create_ctr_encryptor, provider.create_ctr_decryptor};
    }
    if (mode == "GCM")
    {
        return {provider.create_gcm_encryptor, provider.create_gcm_decryptor};
    }
    invalid("unknown block cipher mode: " + mode);
}

inline const char* feed_name(Feed feed)
{
    switch (feed)
    {
        case Feed::ONE_SHOT:
            return "one-shot";
        case Feed::BYTEWISE:
            return "bytewise";
        case Feed::IRREGULAR:
            return "irregular";
    }
    return "unknown";
}

inline std::string case_context(const TestSuite&   suite,
                                const char*        provider_name,
                                const std::string& mode,
                                const std::string& case_name,
                                Feed               feed)
{
    std::ostringstream out;
    out << suite.name << '/' << provider_name << '/' << mode << '/' << case_name
        << '/' << feed_name(feed);
    return out.str();
}

inline void init_mode(BlockCipherMode&                 context,
                      const std::string&               mode,
                      const std::vector<std::uint8_t>& key,
                      const std::vector<std::uint8_t>& iv,
                      const std::vector<std::uint8_t>& aad)
{
    const std::uint8_t* key_ptr = key.data();
    if (mode == "ECB")
    {
        void* args[] = {&key_ptr};
        context.ctrl("init", 1, args);
        return;
    }

    const std::uint8_t* iv_ptr = iv.data();
    if (mode == "GCM")
    {
        const std::uint8_t* aad_ptr = aad.data();
        std::size_t         iv_len  = iv.size();
        std::size_t         aad_len = aad.size();
        void* args[] = {&key_ptr, &iv_ptr, &iv_len, &aad_ptr, &aad_len};
        context.ctrl("init", 5, args);
        return;
    }

    void* args[] = {&key_ptr, &iv_ptr};
    context.ctrl("init", 2, args);
}

inline void reset_mode(BlockCipherMode&                 context,
                       const std::string&               mode,
                       const std::vector<std::uint8_t>& iv,
                       const std::vector<std::uint8_t>& aad)
{
    if (mode == "ECB")
    {
        context.ctrl("reset", 0, nullptr);
        return;
    }

    const std::uint8_t* iv_ptr = iv.data();
    if (mode == "GCM")
    {
        const std::uint8_t* aad_ptr = aad.data();
        std::size_t         iv_len  = iv.size();
        std::size_t         aad_len = aad.size();
        void*               args[]  = {&iv_ptr, &iv_len, &aad_ptr, &aad_len};
        context.ctrl("reset", 4, args);
        return;
    }

    void* args[] = {&iv_ptr};
    context.ctrl("reset", 1, args);
}

inline void get_tag(BlockCipherMode& context, std::uint8_t* tag)
{
    std::uint8_t* tag_ptr = tag;
    void*         args[]  = {&tag_ptr};
    context.ctrl("get_tag", 1, args);
}

inline void set_tag(BlockCipherMode&                 context,
                    const std::vector<std::uint8_t>& tag)
{
    const std::uint8_t* tag_ptr = tag.data();
    void*               args[]  = {&tag_ptr};
    context.ctrl("set_tag", 1, args);
}

inline std::size_t process(BlockCipherMode&                 context,
                           Feed                             feed,
                           std::uint8_t*                    output,
                           std::size_t                      output_capacity,
                           const std::vector<std::uint8_t>& input)
{
    std::size_t written = 0;
    auto        update  = [&](const std::uint8_t* data, std::size_t size) {
        std::size_t       n         = 0;
        const std::size_t remaining = output_capacity - written;
        context.update(output == nullptr ? nullptr : output + written, &n,
                       remaining, data, size);
        if (n > remaining)
        {
            throw std::runtime_error(
                "block cipher mode reported an invalid output length");
        }
        written += n;
    };

    if (feed == Feed::ONE_SHOT)
    {
        context.do_final(output, &written, output_capacity, input.data(),
                         input.size());
        if (written > output_capacity)
        {
            throw std::runtime_error(
                "block cipher mode reported an invalid final output length");
        }
        return written;
    }

    if (feed == Feed::BYTEWISE)
    {
        for (std::size_t i = 0; i < input.size(); ++i)
        {
            update(input.data() + i, 1);
        }
    }
    else
    {
        static constexpr std::array<std::size_t, 10> CHUNKS = {
            1, 2, 3, 5, 8, 13, 16, 17, 31, 33,
        };
        std::size_t offset = 0;
        std::size_t index  = 0;
        while (offset != input.size())
        {
            const std::size_t size =
                std::min(CHUNKS[index], input.size() - offset);
            update(input.data() + offset, size);
            offset += size;
            index = (index + 1) % CHUNKS.size();
        }
    }

    std::size_t       n         = 0;
    const std::size_t remaining = output_capacity - written;
    context.do_final(output == nullptr ? nullptr : output + written, &n,
                     remaining, nullptr, 0);
    if (n > remaining)
    {
        throw std::runtime_error(
            "block cipher mode reported an invalid final output length");
    }
    return written + n;
}

inline void validate_mode_metadata(const BlockCipherMode& context,
                                   const CipherSpec&      spec,
                                   const std::string&     test_context,
                                   const std::string&     mode,
                                   bool                   encrypt)
{
    if (context.fetch_name() == nullptr || context.fetch_name()[0] == '\0')
    {
        fail(test_context, "mode name is empty");
    }
    std::string expected_name = mode;
    if (mode != "OFB" && mode != "CTR")
    {
        expected_name += encrypt ? "-ENC" : "-DEC";
    }
    if (expected_name != context.fetch_name())
    {
        fail(test_context, "mode name or direction mismatch");
    }
    if (context.fetch_block_size() != spec.block_size)
    {
        fail(test_context, "mode block size mismatch");
    }
    if (context.fetch_user_key_len() != spec.user_key_len)
    {
        fail(test_context, "mode user key length mismatch");
    }
    const BlockCipher& cipher = context.fetch_cipher_ctx();
    if (cipher.fetch_block_size() != spec.block_size ||
        cipher.fetch_user_key_len() != spec.user_key_len)
    {
        fail(test_context, "underlying cipher metadata mismatch");
    }
}

inline std::unique_ptr<BlockCipherMode> create_initialized_mode(
    const TestSuite&                 suite,
    const BlockCipherModeProvider&   provider,
    const std::string&               mode,
    bool                             encrypt,
    const std::vector<std::uint8_t>& key,
    const std::vector<std::uint8_t>& iv,
    const std::vector<std::uint8_t>& aad,
    const std::string&               context);

inline CryptResult crypt(const TestSuite&                 suite,
                         const BlockCipherModeProvider&   provider,
                         const std::string&               mode,
                         bool                             encrypt,
                         const std::vector<std::uint8_t>& key,
                         const std::vector<std::uint8_t>& iv,
                         const std::vector<std::uint8_t>& aad,
                         const std::vector<std::uint8_t>& tag,
                         const std::vector<std::uint8_t>& input,
                         const std::string&               case_name,
                         Feed                             feed)
{
    const std::string context =
        case_context(suite, provider.algo_name, mode, case_name, feed);
    auto mode_context = create_initialized_mode(suite, provider, mode, encrypt,
                                                key, iv, aad, context);
    if (mode == "GCM" && !encrypt)
    {
        set_tag(*mode_context, tag);
    }

    static constexpr std::size_t  GUARD_SIZE = 16;
    static constexpr std::uint8_t GUARD      = 0xa5;
    CryptResult                   result;
    result.output.assign(input.size() + GUARD_SIZE, GUARD);
    std::uint8_t* out = result.output.empty() ? nullptr : result.output.data();
    const std::size_t written =
        process(*mode_context, feed, out, input.size(), input);
    if (written != input.size())
    {
        fail(context, "output size mismatch");
    }
    for (std::size_t i = input.size(); i < result.output.size(); ++i)
    {
        if (result.output[i] != GUARD)
        {
            fail(context, "output buffer guard was overwritten");
        }
    }
    result.output.resize(written);

    if (mode == "GCM" && encrypt)
    {
        result.tag.resize(16);
        get_tag(*mode_context, result.tag.data());
    }
    return result;
}

inline void require_equal(const std::vector<std::uint8_t>& actual,
                          const std::vector<std::uint8_t>& expected,
                          const std::string&               context,
                          const char*                      what)
{
    if (actual != expected)
    {
        fail(context, std::string(what) + " mismatch");
    }
}

inline std::unique_ptr<BlockCipherMode> create_initialized_mode(
    const TestSuite&                 suite,
    const BlockCipherModeProvider&   provider,
    const std::string&               mode,
    bool                             encrypt,
    const std::vector<std::uint8_t>& key,
    const std::vector<std::uint8_t>& iv,
    const std::vector<std::uint8_t>& aad,
    const std::string&               context)
{
    const ModeFactories factories = mode_factories(provider, mode);
    const ModeFactory   factory =
        encrypt ? factories.encryptor : factories.decryptor;
    if (factory == nullptr)
    {
        fail(context, "mode factory is unavailable");
    }
    auto mode_context = factory();
    if (mode_context == nullptr)
    {
        fail(context, "mode factory returned null");
    }
    validate_mode_metadata(*mode_context, suite.cipher, context, mode, encrypt);
    init_mode(*mode_context, mode, key, iv, aad);
    return mode_context;
}

inline void test_mode_lifecycle(
    const TestSuite&                 suite,
    const BlockCipherModeProvider&   provider,
    const std::string&               mode,
    bool                             encrypt,
    const std::vector<std::uint8_t>& key,
    const std::vector<std::uint8_t>& iv,
    const std::vector<std::uint8_t>& aad,
    const std::vector<std::uint8_t>& input,
    const std::vector<std::uint8_t>& expected_output,
    const std::vector<std::uint8_t>& expected_tag,
    const std::string&               case_name)
{
    const std::string context =
        suite.name + "/" + provider.algo_name + "/" + mode + "/" + case_name +
        "/" + (encrypt ? "encrypt" : "decrypt") + "-lifecycle";
    auto mode_context = create_initialized_mode(suite, provider, mode, encrypt,
                                                key, iv, aad, context);
    if (mode == "GCM" && !encrypt)
    {
        set_tag(*mode_context, expected_tag);
    }

    std::vector<std::uint8_t> output(input.size());
    const std::size_t         written = process(*mode_context, Feed::ONE_SHOT,
                                                output.data(), output.size(), input);
    output.resize(written);
    require_equal(output, expected_output, context, "reset baseline output");
    if (mode == "GCM" && encrypt)
    {
        std::vector<std::uint8_t> tag(16);
        get_tag(*mode_context, tag.data());
        require_equal(tag, expected_tag, context, "reset baseline tag");
    }

    reset_mode(*mode_context, mode, iv, aad);
    if (mode == "GCM" && !encrypt)
    {
        set_tag(*mode_context, expected_tag);
    }
    output.assign(input.size(), 0);
    const std::size_t reset_written = process(
        *mode_context, Feed::ONE_SHOT, output.data(), output.size(), input);
    output.resize(reset_written);
    require_equal(output, expected_output, context, "reset output");
    if (mode == "GCM" && encrypt)
    {
        std::vector<std::uint8_t> tag(16);
        get_tag(*mode_context, tag.data());
        require_equal(tag, expected_tag, context, "reset tag");
    }

    if (!input.empty())
    {
        mode_context = create_initialized_mode(suite, provider, mode, encrypt,
                                               key, iv, aad, context);
        if (mode == "GCM" && !encrypt)
        {
            set_tag(*mode_context, expected_tag);
        }
        static constexpr std::uint8_t SENTINEL = 0xa5;
        std::vector<std::uint8_t>     too_small(input.size(), SENTINEL);
        std::size_t                   ignored  = 0;
        bool                          rejected = false;
        try
        {
            mode_context->do_final(too_small.data(), &ignored, input.size() - 1,
                                   input.data(), input.size());
        }
        catch (const std::length_error&)
        {
            rejected = true;
        }
        if (!rejected)
        {
            fail(context, "undersized output buffer was accepted");
        }
        if (!std::all_of(too_small.begin(), too_small.end(),
                         [](std::uint8_t value) { return value == SENTINEL; }))
        {
            fail(context, "output changed after capacity failure");
        }

        if (input.size() >= suite.cipher.block_size)
        {
            mode_context = create_initialized_mode(
                suite, provider, mode, encrypt, key, iv, aad, context);
            if (mode == "GCM" && !encrypt)
            {
                set_tag(*mode_context, expected_tag);
            }
            const std::size_t update_output =
                input.size() - input.size() % suite.cipher.block_size;
            too_small.assign(input.size(), SENTINEL);
            rejected = false;
            try
            {
                mode_context->update(too_small.data(), &ignored,
                                     update_output - 1, input.data(),
                                     input.size());
            }
            catch (const std::length_error&)
            {
                rejected = true;
            }
            if (!rejected)
            {
                fail(context, "undersized update output buffer was accepted");
            }
            if (!std::all_of(
                    too_small.begin(), too_small.end(),
                    [](std::uint8_t value) { return value == SENTINEL; }))
            {
                fail(context, "output changed after update capacity failure");
            }
        }
    }

    mode_context = create_initialized_mode(suite, provider, mode, encrypt, key,
                                           iv, aad, context);
    if (mode == "GCM" && !encrypt)
    {
        set_tag(*mode_context, expected_tag);
    }
    const std::size_t         prefix = input.size() / 2;
    std::vector<std::uint8_t> original_output(input.size());
    std::size_t               prefix_written = 0;
    mode_context->update(original_output.data(), &prefix_written,
                         original_output.size(), input.data(), prefix);
    if (prefix_written > original_output.size())
    {
        fail(context, "mode reported an invalid cloned-prefix output length");
    }
    auto cloned_context = mode_context->clone();
    if (cloned_context == nullptr)
    {
        fail(context, "clone returned null");
    }
    std::vector<std::uint8_t> cloned_output = original_output;

    const std::uint8_t* tail = input.data();
    if (tail != nullptr)
    {
        tail += prefix;
    }
    const std::size_t tail_size             = input.size() - prefix;
    std::size_t       original_tail_written = 0;
    std::uint8_t*     original_tail         = original_output.empty()
                                                  ? nullptr
                                                  : original_output.data() + prefix_written;
    mode_context->do_final(original_tail, &original_tail_written,
                           original_output.size() - prefix_written, tail,
                           tail_size);
    if (original_tail_written > original_output.size() - prefix_written)
    {
        fail(context, "mode reported an invalid original-tail output length");
    }
    std::size_t   cloned_tail_written = 0;
    std::uint8_t* cloned_tail =
        cloned_output.empty() ? nullptr : cloned_output.data() + prefix_written;
    cloned_context->do_final(cloned_tail, &cloned_tail_written,
                             cloned_output.size() - prefix_written, tail,
                             tail_size);
    if (cloned_tail_written > cloned_output.size() - prefix_written)
    {
        fail(context, "mode reported an invalid cloned-tail output length");
    }
    original_output.resize(prefix_written + original_tail_written);
    cloned_output.resize(prefix_written + cloned_tail_written);
    require_equal(original_output, expected_output, context,
                  "original output after clone");
    require_equal(cloned_output, expected_output, context, "cloned output");
    if (mode == "GCM" && encrypt)
    {
        std::vector<std::uint8_t> original_tag(16);
        std::vector<std::uint8_t> cloned_tag(16);
        get_tag(*mode_context, original_tag.data());
        get_tag(*cloned_context, cloned_tag.data());
        require_equal(original_tag, expected_tag, context,
                      "original tag after clone");
        require_equal(cloned_tag, expected_tag, context, "cloned tag");
    }

    mode_context = create_initialized_mode(suite, provider, mode, encrypt, key,
                                           iv, aad, context);
    if (mode == "GCM" && !encrypt)
    {
        set_tag(*mode_context, expected_tag);
    }
    output.assign(input.size(), 0);
    const std::size_t legacy_prefix  = input.size() / 2;
    std::size_t       legacy_written = 0;
    mode_context->update(output.data(), &legacy_written, input.data(),
                         legacy_prefix);
    if (legacy_written > output.size())
    {
        fail(context,
             "legacy update overload reported an invalid output length");
    }
    const std::uint8_t* legacy_tail = input.data();
    if (legacy_tail != nullptr)
    {
        legacy_tail += legacy_prefix;
    }
    std::size_t legacy_final_written = 0;
    mode_context->do_final(
        output.empty() ? nullptr : output.data() + legacy_written,
        &legacy_final_written, legacy_tail, input.size() - legacy_prefix);
    if (legacy_final_written > output.size() - legacy_written)
    {
        fail(context,
             "legacy final overload reported an invalid output length");
    }
    output.resize(legacy_written + legacy_final_written);
    require_equal(output, expected_output, context, "legacy overload output");
}

inline void run_cipher_kat(const TestSuite&               suite,
                           const BlockCipherModeProvider& provider,
                           const CipherKat&               kat)
{
    const std::string context =
        suite.name + "/" + provider.algo_name + "/cipher/" + kat.case_name;
    auto cipher = provider.create_cipher();
    if (cipher == nullptr)
    {
        fail(context, "cipher factory returned null");
    }
    if (cipher->fetch_name() == nullptr ||
        suite.cipher.logical_name != cipher->fetch_name() ||
        cipher->fetch_block_size() != suite.cipher.block_size ||
        cipher->fetch_user_key_len() != suite.cipher.user_key_len ||
        cipher->fetch_security_strength() != suite.cipher.security_strength ||
        cipher->fetch_parallel_num() == 0)
    {
        fail(context, "cipher metadata mismatch");
    }
    const char* implementation = cipher->fetch_impl_algo();
    if (implementation == nullptr ||
        std::strcmp(implementation, provider.algo_name) != 0)
    {
        fail(context, "cipher implementation name mismatch");
    }

    const std::size_t blocks = kat.plaintext.size() / suite.cipher.block_size;
    std::vector<std::uint8_t> output(kat.ciphertext.size());
    cipher->set_key(kat.key.data(), BlockCipher::ENCRYPTION);

    std::vector<std::uint8_t> single_block(suite.cipher.block_size);
    cipher->encrypt_block(single_block.data(), kat.plaintext.data());
    if (!std::equal(single_block.begin(), single_block.end(),
                    kat.ciphertext.begin()))
    {
        fail(context, "single-block ciphertext mismatch");
    }

    auto cloned_cipher = cipher->clone();
    if (cloned_cipher == nullptr)
    {
        fail(context, "cipher clone returned null");
    }
    cipher->encrypt_blocks(output.data(), kat.plaintext.data(), blocks);
    require_equal(output, kat.ciphertext, context, "ciphertext");

    cipher->set_key(kat.key.data(), BlockCipher::DECRYPTION);
    cipher->decrypt_block(single_block.data(), kat.ciphertext.data());
    if (!std::equal(single_block.begin(), single_block.end(),
                    kat.plaintext.begin()))
    {
        fail(context, "single-block plaintext mismatch");
    }
    cipher->decrypt_blocks(output.data(), kat.ciphertext.data(), blocks);
    require_equal(output, kat.plaintext, context, "plaintext");

    cloned_cipher->encrypt_blocks(output.data(), kat.plaintext.data(), blocks);
    require_equal(output, kat.ciphertext, context,
                  "independent cloned cipher output");

    std::vector<std::uint8_t> in_place = kat.plaintext;
    cipher->set_key(kat.key.data(), BlockCipher::ENCRYPTION);
    cipher->encrypt_blocks(in_place.data(), in_place.data(), blocks);
    require_equal(in_place, kat.ciphertext, context,
                  "in-place multi-block ciphertext");
    cipher->set_key(kat.key.data(), BlockCipher::DECRYPTION);
    cipher->decrypt_blocks(in_place.data(), in_place.data(), blocks);
    require_equal(in_place, kat.plaintext, context,
                  "in-place multi-block plaintext");

    in_place.assign(kat.plaintext.begin(),
                    kat.plaintext.begin() + suite.cipher.block_size);
    cipher->set_key(kat.key.data(), BlockCipher::ENCRYPTION);
    cipher->encrypt_block(in_place.data(), in_place.data());
    if (!std::equal(in_place.begin(), in_place.end(), kat.ciphertext.begin()))
    {
        fail(context, "in-place single-block ciphertext mismatch");
    }
    cipher->set_key(kat.key.data(), BlockCipher::DECRYPTION);
    cipher->decrypt_block(in_place.data(), in_place.data());
    if (!std::equal(in_place.begin(), in_place.end(), kat.plaintext.begin()))
    {
        fail(context, "in-place single-block plaintext mismatch");
    }
}

inline void run_mode_kat(const TestSuite&               suite,
                         const BlockCipherModeProvider& provider,
                         const ModeKat&                 kat)
{
    static const std::vector<std::uint8_t> EMPTY;
    for (Feed feed : {Feed::ONE_SHOT, Feed::BYTEWISE, Feed::IRREGULAR})
    {
        const std::string context = case_context(suite, provider.algo_name,
                                                 kat.mode, kat.case_name, feed);
        CryptResult       encrypted =
            crypt(suite, provider, kat.mode, true, kat.key, kat.iv, EMPTY,
                  EMPTY, kat.plaintext, kat.case_name, feed);
        require_equal(encrypted.output, kat.ciphertext, context, "ciphertext");

        CryptResult decrypted =
            crypt(suite, provider, kat.mode, false, kat.key, kat.iv, EMPTY,
                  EMPTY, kat.ciphertext, kat.case_name, feed);
        require_equal(decrypted.output, kat.plaintext, context, "plaintext");
    }
    test_mode_lifecycle(suite, provider, kat.mode, true, kat.key, kat.iv, EMPTY,
                        kat.plaintext, kat.ciphertext, EMPTY, kat.case_name);
    test_mode_lifecycle(suite, provider, kat.mode, false, kat.key, kat.iv,
                        EMPTY, kat.ciphertext, kat.plaintext, EMPTY,
                        kat.case_name);
}

inline void run_aead_kat(const TestSuite&               suite,
                         const BlockCipherModeProvider& provider,
                         const AeadKat&                 kat)
{
    for (Feed feed : {Feed::ONE_SHOT, Feed::BYTEWISE, Feed::IRREGULAR})
    {
        const std::string context = case_context(suite, provider.algo_name,
                                                 kat.mode, kat.case_name, feed);
        CryptResult       encrypted =
            crypt(suite, provider, kat.mode, true, kat.key, kat.nonce, kat.aad,
                  kat.tag, kat.plaintext, kat.case_name, feed);
        require_equal(encrypted.output, kat.ciphertext, context, "ciphertext");
        require_equal(encrypted.tag, kat.tag, context, "authentication tag");

        CryptResult decrypted =
            crypt(suite, provider, kat.mode, false, kat.key, kat.nonce, kat.aad,
                  kat.tag, kat.ciphertext, kat.case_name, feed);
        require_equal(decrypted.output, kat.plaintext, context, "plaintext");
    }

    test_mode_lifecycle(suite, provider, kat.mode, true, kat.key, kat.nonce,
                        kat.aad, kat.plaintext, kat.ciphertext, kat.tag,
                        kat.case_name);
    test_mode_lifecycle(suite, provider, kat.mode, false, kat.key, kat.nonce,
                        kat.aad, kat.ciphertext, kat.plaintext, kat.tag,
                        kat.case_name);

    auto expect_authentication_failure =
        [&](const std::vector<std::uint8_t>& ciphertext,
            const std::vector<std::uint8_t>& tag, const char* suffix) {
            const std::string context = suite.name + "/" + provider.algo_name +
                                        "/" + kat.mode + "/" + kat.case_name +
                                        suffix;
            auto mode_context =
                create_initialized_mode(suite, provider, kat.mode, false,
                                        kat.key, kat.nonce, kat.aad, context);
            set_tag(*mode_context, tag);
            std::vector<std::uint8_t> output(ciphertext.size());
            std::size_t               written = 0;
            mode_context->update(output.data(), &written, output.size(),
                                 ciphertext.data(), ciphertext.size());
            if (written > output.size())
            {
                fail(context,
                     "decryptor reported an invalid update output length");
            }

            std::size_t final_written = 0;
            try
            {
                mode_context->do_final(
                    output.empty() ? nullptr : output.data() + written,
                    &final_written, output.size() - written, nullptr, 0);
            }
            catch (const std::runtime_error&)
            {
                return;
            }
            fail(context, "authentication failure was accepted");
        };

    std::vector<std::uint8_t> invalid_tag = kat.tag;
    invalid_tag[0] ^= 1;
    expect_authentication_failure(kat.ciphertext, invalid_tag, "-invalid-tag");

    if (!kat.ciphertext.empty())
    {
        std::vector<std::uint8_t> invalid_ciphertext = kat.ciphertext;
        invalid_ciphertext[0] ^= 1;
        expect_authentication_failure(invalid_ciphertext, kat.tag,
                                      "-invalid-ciphertext");
    }
}

inline std::uint64_t random_seed()
{
    std::random_device source;
    return (static_cast<std::uint64_t>(source()) << 32) ^
           static_cast<std::uint64_t>(source());
}

inline std::vector<std::uint8_t> random_bytes(std::mt19937_64& generator,
                                              std::size_t      size)
{
    std::vector<std::uint8_t> output(size);
    for (std::uint8_t& value : output)
    {
        value = static_cast<std::uint8_t>(generator());
    }
    return output;
}

template <class Kat>
inline std::vector<std::string> unique_modes(const std::vector<Kat>& kats)
{
    std::vector<std::string> modes;
    for (const Kat& kat : kats)
    {
        if (std::find(modes.begin(), modes.end(), kat.mode) == modes.end())
        {
            modes.push_back(kat.mode);
        }
    }
    return modes;
}

inline void run_generated_cases(const TestSuite&               suite,
                                const BlockCipherModeProvider& provider,
                                std::uint64_t                  seed)
{
    std::mt19937_64 generator(seed);
    if (!suite.cipher_kats.empty())
    {
        auto cipher = provider.create_cipher();
        if (cipher == nullptr)
        {
            fail(suite.name + "/" + provider.algo_name + "/cipher/generated",
                 "cipher factory returned null");
        }
        const std::vector<std::uint8_t> key =
            random_bytes(generator, suite.cipher.user_key_len);
        const std::size_t parallel = cipher->fetch_parallel_num();
        const std::array<std::size_t, 4> block_counts = {
            1,
            2,
            parallel,
            parallel + 1,
        };
        for (std::size_t blocks : block_counts)
        {
            const std::size_t size = blocks * suite.cipher.block_size;
            const std::vector<std::uint8_t> plaintext =
                random_bytes(generator, size);
            std::vector<std::uint8_t> ciphertext(size);
            std::vector<std::uint8_t> recovered(size);
            cipher->set_key(key.data(), BlockCipher::ENCRYPTION);
            cipher->encrypt_blocks(ciphertext.data(), plaintext.data(), blocks);
            cipher->set_key(key.data(), BlockCipher::DECRYPTION);
            cipher->decrypt_blocks(recovered.data(), ciphertext.data(), blocks);
            require_equal(recovered, plaintext,
                          suite.name + "/" + provider.algo_name +
                              "/cipher/generated-" + std::to_string(blocks) +
                              "-blocks",
                          "generated round-trip plaintext");
        }
    }

    const std::size_t              block_size   = suite.cipher.block_size;
    const std::vector<std::string> tested_modes = unique_modes(suite.mode_kats);
    for (const std::string& mode : tested_modes)
    {
        const std::vector<std::size_t> lengths =
            (mode == "ECB" || mode == "CBC")
                ? std::vector<std::size_t>{0, block_size, 2 * block_size}
                : std::vector<std::size_t>{0,
                                           1,
                                           block_size - 1,
                                           block_size,
                                           block_size + 1,
                                           2 * block_size + 1};
        const std::vector<std::uint8_t> key =
            random_bytes(generator, suite.cipher.user_key_len);
        const std::vector<std::uint8_t> iv =
            mode == "ECB" ? std::vector<std::uint8_t>{}
                          : random_bytes(generator, block_size);
        for (std::size_t length : lengths)
        {
            const std::vector<std::uint8_t> plaintext =
                random_bytes(generator, length);
            const std::string case_name =
                "generated-" + std::to_string(length) + "-bytes";
            static const std::vector<std::uint8_t> EMPTY;
            CryptResult                            encrypted =
                crypt(suite, provider, mode, true, key, iv, EMPTY, EMPTY,
                      plaintext, case_name, Feed::IRREGULAR);
            CryptResult decrypted =
                crypt(suite, provider, mode, false, key, iv, EMPTY, EMPTY,
                      encrypted.output, case_name, Feed::BYTEWISE);
            require_equal(decrypted.output, plaintext,
                          case_context(suite, provider.algo_name, mode,
                                       case_name, Feed::BYTEWISE),
                          "generated round-trip plaintext");
        }
    }

    if (!suite.aead_kats.empty())
    {
        const std::vector<std::uint8_t> key =
            random_bytes(generator, suite.cipher.user_key_len);
        const std::vector<std::uint8_t> nonce = random_bytes(generator, 12);
        const std::vector<std::uint8_t> aad =
            random_bytes(generator, block_size + 1);
        for (std::size_t length :
             {std::size_t(0), std::size_t(1), block_size, block_size + 1})
        {
            const std::vector<std::uint8_t> plaintext =
                random_bytes(generator, length);
            const std::string case_name =
                "generated-" + std::to_string(length) + "-bytes";
            static const std::vector<std::uint8_t> EMPTY_TAG;
            CryptResult                            encrypted =
                crypt(suite, provider, "GCM", true, key, nonce, aad, EMPTY_TAG,
                      plaintext, case_name, Feed::IRREGULAR);
            CryptResult decrypted = crypt(
                suite, provider, "GCM", false, key, nonce, aad, encrypted.tag,
                encrypted.output, case_name, Feed::BYTEWISE);
            require_equal(decrypted.output, plaintext,
                          case_context(suite, provider.algo_name, "GCM",
                                       case_name, Feed::BYTEWISE),
                          "generated round-trip plaintext");
        }
    }
}

using BenchmarkClock = std::chrono::steady_clock;

inline volatile std::uint8_t& benchmark_sink()
{
    static volatile std::uint8_t sink = 0;
    return sink;
}

template <class RunBatch>
inline double measure_mbits_per_second(std::size_t bytes_per_iteration,
                                       RunBatch&&  run_batch)
{
    static constexpr double      MIN_SAMPLE_SECONDS     = 0.1;
    static constexpr std::size_t SAMPLE_COUNT           = 5;
    static constexpr std::size_t MAX_CALIBRATION_ROUNDS = 32;
    static constexpr double      MAX_SCALE              = 1024.0;

    std::size_t iterations = 1;
    bool        calibrated = false;
    for (std::size_t round = 0; round < MAX_CALIBRATION_ROUNDS; ++round)
    {
        const auto start = BenchmarkClock::now();
        run_batch(iterations);
        const double seconds =
            std::chrono::duration<double>(BenchmarkClock::now() - start)
                .count();
        if (seconds >= MIN_SAMPLE_SECONDS)
        {
            calibrated = true;
            break;
        }
        const double scale = seconds > 0 ? MIN_SAMPLE_SECONDS / seconds : 10.0;
        const std::size_t multiplier = std::max<std::size_t>(
            2, static_cast<std::size_t>(std::min(scale, MAX_SCALE)) + 1);
        if (iterations > std::numeric_limits<std::size_t>::max() / multiplier)
        {
            throw std::runtime_error(
                "benchmark iteration calibration overflow");
        }
        iterations *= multiplier;
    }
    if (!calibrated)
    {
        throw std::runtime_error("benchmark iteration calibration failed");
    }

    std::array<double, SAMPLE_COUNT> samples{};
    for (double& sample : samples)
    {
        const auto start = BenchmarkClock::now();
        run_batch(iterations);
        const double seconds =
            std::chrono::duration<double>(BenchmarkClock::now() - start)
                .count();
        if (seconds <= 0)
        {
            throw std::runtime_error("benchmark sample duration is zero");
        }
        sample = static_cast<double>(bytes_per_iteration) * 8.0 *
                 static_cast<double>(iterations) / (1024.0 * 1024.0) / seconds;
    }
    std::sort(samples.begin(), samples.end());
    return samples[SAMPLE_COUNT / 2];
}

inline void print_speed_result(const std::string& cipher_name,
                               const char*        provider_name,
                               const char*        operation,
                               bool               encrypt,
                               std::size_t        size,
                               double             mbits_per_second)
{
    std::printf(
        "cipher=%s provider=%s operation=%s direction=%s bytes=%zu "
        "%.3f Mbit/s\n",
        cipher_name.c_str(), provider_name, operation,
        encrypt ? "encrypt" : "decrypt", size, mbits_per_second);
    std::fflush(stdout);
}

struct SpeedCipherInfo
{
    std::string name;
    std::size_t block_size;
    std::size_t user_key_len;
};

inline SpeedCipherInfo speed_cipher_info(const BlockCipher& cipher,
                                         const std::string& context)
{
    const char* name = cipher.fetch_name();
    if (name == nullptr || name[0] == '\0')
    {
        fail(context, "cipher name is empty");
    }
    if (cipher.fetch_block_size() == 0)
    {
        fail(context, "cipher block size is zero");
    }
    if (cipher.fetch_user_key_len() == 0)
    {
        fail(context, "cipher user key length is zero");
    }
    return {name, cipher.fetch_block_size(), cipher.fetch_user_key_len()};
}

inline std::size_t benchmark_size(std::size_t block_size)
{
    static constexpr std::size_t TARGET_SIZE = 16 * 1024;
    return std::max<std::size_t>(1, TARGET_SIZE / block_size) * block_size;
}

inline void run_cipher_speed(const BlockCipherModeProvider& provider,
                             std::mt19937_64&               generator)
{
    const std::string context =
        std::string("speed/") + provider.algo_name + "/BlockCipher";
    auto probe = provider.create_cipher();
    if (probe == nullptr)
    {
        fail(context, "cipher factory returned null");
    }
    const SpeedCipherInfo           info   = speed_cipher_info(*probe, context);
    const std::size_t               size   = benchmark_size(info.block_size);
    const std::size_t               blocks = size / info.block_size;
    const std::vector<std::uint8_t> key =
        random_bytes(generator, info.user_key_len);
    const std::vector<std::uint8_t> input = random_bytes(generator, size);
    std::vector<std::uint8_t>       output(size);

    for (bool encrypt : {true, false})
    {
        auto cipher = provider.create_cipher();
        if (cipher == nullptr)
        {
            fail(context, "cipher factory returned null");
        }
        const SpeedCipherInfo current = speed_cipher_info(*cipher, context);
        if (current.name != info.name ||
            current.block_size != info.block_size ||
            current.user_key_len != info.user_key_len)
        {
            fail(context, "cipher factory returned inconsistent metadata");
        }
        cipher->set_key(key.data(), encrypt ? BlockCipher::ENCRYPTION
                                            : BlockCipher::DECRYPTION);
        const double speed =
            measure_mbits_per_second(size, [&](std::size_t iterations) {
                for (std::size_t i = 0; i < iterations; ++i)
                {
                    if (encrypt)
                    {
                        cipher->encrypt_blocks(output.data(), input.data(),
                                               blocks);
                    }
                    else
                    {
                        cipher->decrypt_blocks(output.data(), input.data(),
                                               blocks);
                    }
                }
                benchmark_sink() ^= output[0];
            });
        print_speed_result(info.name, provider.algo_name, "BlockCipher",
                           encrypt, size, speed);
    }
}

struct SpeedModeData
{
    std::vector<std::uint8_t> key;
    std::vector<std::uint8_t> iv;
    std::vector<std::uint8_t> aad;
    std::vector<std::uint8_t> plaintext;
    std::vector<std::uint8_t> ciphertext;
    std::vector<std::uint8_t> tag;
    SpeedCipherInfo           cipher;
};

inline void increment_gcm_counter(std::array<std::uint8_t, 16>& counter)
{
    for (std::size_t i = counter.size(); i-- > 12;)
    {
        if (++counter[i] != 0)
        {
            return;
        }
    }
}

inline void store_u64_be(std::uint8_t out[8], std::uint64_t value)
{
    for (std::size_t i = 8; i-- > 0;)
    {
        out[i] = static_cast<std::uint8_t>(value);
        value >>= 8;
    }
}

inline void ghash_padded(ghash::GHash&                    hash,
                         const std::vector<std::uint8_t>& data)
{
    hash.update(data.data(), data.size());
    const std::size_t remainder = data.size() % 16;
    if (remainder != 0)
    {
        static constexpr std::array<std::uint8_t, 16> ZERO = {};
        hash.update(ZERO.data(), ZERO.size() - remainder);
    }
}

inline void prepare_gcm_decryption_data(const BlockCipher& cipher,
                                        SpeedModeData&     data)
{
    std::array<std::uint8_t, 16> hash_key{};
    std::array<std::uint8_t, 16> zero{};
    cipher.encrypt_block(hash_key.data(), zero.data());

    std::array<std::uint8_t, 16> initial_counter{};
    std::copy(data.iv.begin(), data.iv.end(), initial_counter.begin());
    initial_counter.back() = 1;

    data.ciphertext.resize(data.plaintext.size());
    std::array<std::uint8_t, 16> counter = initial_counter;
    std::array<std::uint8_t, 16> stream{};
    for (std::size_t offset = 0; offset < data.plaintext.size(); offset += 16)
    {
        increment_gcm_counter(counter);
        cipher.encrypt_block(stream.data(), counter.data());
        const std::size_t size =
            std::min<std::size_t>(16, data.plaintext.size() - offset);
        for (std::size_t i = 0; i < size; ++i)
        {
            data.ciphertext[offset + i] =
                data.plaintext[offset + i] ^ stream[i];
        }
    }

    ghash::GHash hash(hash_key.data());
    ghash_padded(hash, data.aad);
    ghash_padded(hash, data.ciphertext);
    std::array<std::uint8_t, 16> lengths{};
    store_u64_be(lengths.data(),
                 static_cast<std::uint64_t>(data.aad.size()) * 8);
    store_u64_be(lengths.data() + 8,
                 static_cast<std::uint64_t>(data.ciphertext.size()) * 8);
    std::array<std::uint8_t, 16> authentication{};
    hash.do_final(authentication.data(), lengths.data(), lengths.size());

    std::array<std::uint8_t, 16> tag_mask{};
    cipher.encrypt_block(tag_mask.data(), initial_counter.data());
    data.tag.resize(16);
    for (std::size_t i = 0; i < data.tag.size(); ++i)
    {
        data.tag[i] = authentication[i] ^ tag_mask[i];
    }
}

inline std::unique_ptr<BlockCipherMode> create_speed_mode(
    ModeFactory                      factory,
    const std::string&               mode,
    const SpeedCipherInfo&           cipher,
    const std::vector<std::uint8_t>& key,
    const std::vector<std::uint8_t>& iv,
    const std::vector<std::uint8_t>& aad,
    const std::string&               context)
{
    auto mode_context = factory();
    if (mode_context == nullptr)
    {
        fail(context, "mode factory returned null");
    }
    const SpeedCipherInfo current =
        speed_cipher_info(mode_context->fetch_cipher_ctx(), context);
    if (current.name != cipher.name ||
        current.block_size != cipher.block_size ||
        current.user_key_len != cipher.user_key_len)
    {
        fail(context, "mode factory returned inconsistent cipher metadata");
    }
    if (mode_context->fetch_block_size() != cipher.block_size ||
        mode_context->fetch_user_key_len() != cipher.user_key_len)
    {
        fail(context, "mode metadata does not match its cipher");
    }
    init_mode(*mode_context, mode, key, iv, aad);
    return mode_context;
}

inline SpeedModeData prepare_speed_mode_data(
    const BlockCipherModeProvider& provider,
    const std::string&             mode,
    const ModeFactories&           factories,
    std::mt19937_64&               generator)
{
    const std::string context =
        std::string("speed/") + provider.algo_name + "/" + mode;
    const ModeFactory probe_factory = factories.encryptor != nullptr
                                          ? factories.encryptor
                                          : factories.decryptor;
    auto              probe         = probe_factory();
    if (probe == nullptr)
    {
        fail(context, "mode factory returned null");
    }

    SpeedModeData data;
    data.cipher = speed_cipher_info(probe->fetch_cipher_ctx(), context);
    if (mode == "GCM" && data.cipher.block_size != 16)
    {
        fail(context, "GCM requires a 16-byte block cipher");
    }
    if (probe->fetch_block_size() != data.cipher.block_size ||
        probe->fetch_user_key_len() != data.cipher.user_key_len)
    {
        fail(context, "mode metadata does not match its cipher");
    }
    const std::size_t size = benchmark_size(data.cipher.block_size);
    data.key               = random_bytes(generator, data.cipher.user_key_len);
    data.iv                = mode == "ECB"
                                 ? std::vector<std::uint8_t>{}
                                 : random_bytes(generator,
                                 mode == "GCM" ? 12 : data.cipher.block_size);
    data.aad               = mode == "GCM"
                                 ? random_bytes(generator, data.cipher.block_size + 1)
                                 : std::vector<std::uint8_t>{};
    data.plaintext         = random_bytes(generator, size);
    if (factories.encryptor != nullptr)
    {
        auto encryptor =
            create_speed_mode(factories.encryptor, mode, data.cipher, data.key,
                              data.iv, data.aad, context);
        data.ciphertext.resize(size);
        const std::size_t written =
            process(*encryptor, Feed::ONE_SHOT, data.ciphertext.data(),
                    data.ciphertext.size(), data.plaintext);
        if (written != size)
        {
            fail(context, "speed preparation output size mismatch");
        }
        if (mode == "GCM")
        {
            data.tag.resize(16);
            get_tag(*encryptor, data.tag.data());
        }
    }
    else
    {
        if (mode == "GCM")
        {
            auto decryptor =
                create_speed_mode(factories.decryptor, mode, data.cipher,
                                  data.key, data.iv, data.aad, context);
            prepare_gcm_decryption_data(decryptor->fetch_cipher_ctx(), data);
        }
        else
        {
            data.ciphertext = random_bytes(generator, size);
        }
    }
    return data;
}

inline void run_mode_speed(const BlockCipherModeProvider& provider,
                           const std::string&             mode,
                           const ModeFactories&           factories,
                           const SpeedModeData&           data)
{
    const std::size_t         size = data.plaintext.size();
    std::vector<std::uint8_t> output(size);
    for (bool encrypt : {true, false})
    {
        const ModeFactory factory =
            encrypt ? factories.encryptor : factories.decryptor;
        if (factory == nullptr)
        {
            continue;
        }
        const std::string context =
            data.cipher.name + "/" + provider.algo_name + "/" + mode + "/speed";
        auto mode_context = create_speed_mode(
            factory, mode, data.cipher, data.key, data.iv, data.aad, context);
        const std::vector<std::uint8_t>& input =
            encrypt ? data.plaintext : data.ciphertext;
        std::vector<std::uint8_t> measured_tag(16);
        const double              speed =
            measure_mbits_per_second(size, [&](std::size_t iterations) {
                for (std::size_t i = 0; i < iterations; ++i)
                {
                    reset_mode(*mode_context, mode, data.iv, data.aad);
                    if (mode == "GCM" && !encrypt)
                    {
                        set_tag(*mode_context, data.tag);
                    }
                    const std::size_t written =
                        process(*mode_context, Feed::ONE_SHOT, output.data(),
                                output.size(), input);
                    if (written != size)
                    {
                        fail(context, "benchmark output size mismatch");
                    }
                    if (mode == "GCM" && encrypt)
                    {
                        get_tag(*mode_context, measured_tag.data());
                        benchmark_sink() ^= measured_tag[0];
                    }
                }
                benchmark_sink() ^= output[0];
            });
        print_speed_result(data.cipher.name, provider.algo_name, mode.c_str(),
                           encrypt, size, speed);
    }
}

} // namespace detail

/**
 * @brief Validate the structure and test vectors of a test suite.
 * @throws std::invalid_argument if the suite is invalid.
 */
inline void validate_test_suite(const TestSuite& suite)
{
    detail::require_config(!suite.name.empty(), "test suite name is empty");
    detail::require_config(!suite.cipher.logical_name.empty(),
                           suite.name + ": cipher name is empty");
    detail::require_config(suite.cipher.block_size != 0,
                           suite.name + ": block size is zero");
    detail::require_config(suite.cipher.user_key_len != 0,
                           suite.name + ": user key length is zero");
    detail::require_config(suite.cipher.security_strength != 0,
                           suite.name + ": security strength is zero");
    for (const CipherKat& kat : suite.cipher_kats)
    {
        const std::string prefix = suite.name + "/cipher/" + kat.case_name;
        detail::require_config(!kat.case_name.empty(),
                               suite.name + ": empty cipher KAT name");
        detail::require_config(kat.key.size() == suite.cipher.user_key_len,
                               prefix + ": invalid key length");
        detail::require_config(!kat.plaintext.empty(),
                               prefix + ": plaintext is empty");
        detail::require_config(kat.plaintext.size() == kat.ciphertext.size(),
                               prefix + ": plaintext/ciphertext size mismatch");
        detail::require_config(
            kat.plaintext.size() % suite.cipher.block_size == 0,
            prefix + ": data is not block aligned");
    }

    for (const ModeKat& kat : suite.mode_kats)
    {
        const std::string prefix =
            suite.name + "/" + kat.mode + "/" + kat.case_name;
        detail::require_config(!kat.case_name.empty(),
                               suite.name + ": empty mode KAT name");
        detail::require_config(detail::is_mode(kat.mode),
                               prefix + ": unknown mode");
        detail::require_config(kat.key.size() == suite.cipher.user_key_len,
                               prefix + ": invalid key length");
        detail::require_config(kat.plaintext.size() == kat.ciphertext.size(),
                               prefix + ": plaintext/ciphertext size mismatch");
        detail::require_config(kat.mode == "ECB"
                                   ? kat.iv.empty()
                                   : kat.iv.size() == suite.cipher.block_size,
                               prefix + ": invalid IV length");
        if (kat.mode == "ECB" || kat.mode == "CBC")
        {
            detail::require_config(
                kat.plaintext.size() % suite.cipher.block_size == 0,
                prefix + ": data is not block aligned");
        }
    }

    for (const AeadKat& kat : suite.aead_kats)
    {
        const std::string prefix =
            suite.name + "/" + kat.mode + "/" + kat.case_name;
        detail::require_config(!kat.case_name.empty(),
                               suite.name + ": empty AEAD KAT name");
        detail::require_config(kat.mode == "GCM",
                               prefix + ": unknown AEAD mode");
        detail::require_config(suite.cipher.block_size == 16,
                               prefix + ": GCM requires a 16-byte block");
        detail::require_config(kat.key.size() == suite.cipher.user_key_len,
                               prefix + ": invalid key length");
        detail::require_config(kat.plaintext.size() == kat.ciphertext.size(),
                               prefix + ": plaintext/ciphertext size mismatch");
        detail::require_config(kat.tag.size() == 16,
                               prefix + ": GCM tag must be 16 bytes");
    }
}

/**
 * @brief Run a test suite against one block cipher mode provider.
 * @throws std::invalid_argument if the suite or provider is invalid.
 * @throws std::runtime_error if a test fails.
 */
inline void run_test_suite(const TestSuite&               suite,
                           const BlockCipherModeProvider* provider)
{
    validate_test_suite(suite);
    detail::require_config(provider != nullptr,
                           suite.name + ": provider is null");
    detail::require_config(
        provider->algo_name != nullptr && provider->algo_name[0] != '\0',
        suite.name + ": provider name is empty");
    if (!suite.cipher_kats.empty())
    {
        detail::require_config(provider->create_cipher != nullptr,
                               suite.name + "/" + provider->algo_name +
                                   ": cipher factory is unavailable");
    }

    for (const CipherKat& kat : suite.cipher_kats)
    {
        detail::run_cipher_kat(suite, *provider, kat);
    }
    for (const ModeKat& kat : suite.mode_kats)
    {
        detail::run_mode_kat(suite, *provider, kat);
    }
    for (const AeadKat& kat : suite.aead_kats)
    {
        detail::run_aead_kat(suite, *provider, kat);
    }

    const std::uint64_t seed = detail::random_seed();
    std::printf(
        "Testing generated block cipher cases. suite: %s, provider: "
        "%s, seed: %llu\n",
        suite.name.c_str(), provider->algo_name,
        static_cast<unsigned long long>(seed));
    try
    {
        detail::run_generated_cases(suite, *provider, seed);
    }
    catch (const std::exception& error)
    {
        std::ostringstream message;
        message << error.what() << " (generated-case seed: " << seed << ')';
        throw std::runtime_error(message.str());
    }
}

/**
 * @brief Measure all throughput operations exposed by a provider.
 *
 * Uses an approximately 16 KiB message to match TLS's 2^14-byte plaintext
 * fragment limit, adaptive iteration counts, five samples, and reports the
 * median Mbit/s. Context creation, key setup, and allocation are outside the
 * timed region. Modes include reset/final and GCM tag handling in each timed
 * message.
 */
inline void run_speed_test(const BlockCipherModeProvider* provider)
{
    detail::require_config(provider != nullptr, "provider is null");
    detail::require_config(
        provider->algo_name != nullptr && provider->algo_name[0] != '\0',
        "provider name is empty");

    std::mt19937_64 generator(detail::random_seed());
    if (provider->create_cipher != nullptr)
    {
        detail::run_cipher_speed(*provider, generator);
    }

    static constexpr std::array<const char*, 6> MODES = {
        "ECB", "CBC", "CFB", "OFB", "CTR", "GCM",
    };
    for (const char* mode : MODES)
    {
        const detail::ModeFactories factories =
            detail::mode_factories(*provider, mode);
        if (factories.encryptor == nullptr && factories.decryptor == nullptr)
        {
            continue;
        }
        const detail::SpeedModeData data = detail::prepare_speed_mode_data(
            *provider, mode, factories, generator);
        detail::run_mode_speed(*provider, mode, factories, data);
    }
}

} // namespace block_cipher_mode::test

#endif // BLOCK_CIPHER_MODE_TEST_SUITE_H
