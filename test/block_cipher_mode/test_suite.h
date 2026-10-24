#ifndef BLOCK_CIPHER_MODE_TEST_SUITE_H
#define BLOCK_CIPHER_MODE_TEST_SUITE_H

#include <gmlib/block_cipher_mode/provider.h>
#include <gmlib/rng/cstd_rng.h>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace block_cipher_mode::test {

namespace detail {

inline void run_final_safe(BlockCipherMode&    cryptor,
                           std::uint8_t*       out,
                           std::size_t*        outl,
                           std::size_t         outl_max,
                           const std::uint8_t* in,
                           std::size_t         inl)
{
    cryptor.do_final(out, outl, outl_max, in, inl);
}

inline void run_final_unsafe(BlockCipherMode&    cryptor,
                             std::uint8_t*       out,
                             std::size_t*        outl,
                             const std::uint8_t* in,
                             std::size_t         inl)
{
    cryptor.do_final(out, outl, in, inl);
}

inline void run_update_final0_safe(BlockCipherMode&    cryptor,
                                   std::uint8_t*       out,
                                   std::size_t*        outl,
                                   std::size_t         outl_max,
                                   const std::uint8_t* in,
                                   std::size_t         inl)
{
    std::size_t outl_tmp = 0;
    *outl                = 0;
    cryptor.update(out, &outl_tmp, outl_max, in, inl);
    out += outl_tmp, outl_max -= outl_tmp, *outl += outl_tmp;
    cryptor.do_final(out, &outl_tmp, outl_max);
    *outl += outl_tmp;
}

inline void run_update_final0_unsafe(BlockCipherMode&    cryptor,
                                     std::uint8_t*       out,
                                     std::size_t*        outl,
                                     const std::uint8_t* in,
                                     std::size_t         inl)
{
    std::size_t outl_tmp = 0;
    *outl                = 0;
    cryptor.update(out, &outl_tmp, in, inl);
    out += outl_tmp, *outl += outl_tmp;
    cryptor.do_final(out, &outl_tmp);
    *outl += outl_tmp;
}

inline void run_update_update_final0_safe(BlockCipherMode&    cryptor,
                                          std::uint8_t*       out,
                                          std::size_t*        outl,
                                          std::size_t         outl_max,
                                          const std::uint8_t* in,
                                          std::size_t         inl,
                                          rng::Rng&           rng)
{
    std::size_t part0_len = rng.rand<std::size_t>() % (inl ? inl : 1);
    std::size_t part1_len = inl - part0_len;

    std::size_t outl_tmp = 0;
    *outl                = 0;
    cryptor.update(out, &outl_tmp, outl_max, in, part0_len);
    out += outl_tmp, outl_max -= outl_tmp, *outl += outl_tmp;
    cryptor.update(out, &outl_tmp, outl_max, in + part0_len, part1_len);
    out += outl_tmp, outl_max -= outl_tmp, *outl += outl_tmp;
    cryptor.do_final(out, &outl_tmp, outl_max);
    *outl += outl_tmp;
}

inline void run_update_update_final0_unsafe(BlockCipherMode&    cryptor,
                                            std::uint8_t*       out,
                                            std::size_t*        outl,
                                            const std::uint8_t* in,
                                            std::size_t         inl,
                                            rng::Rng&           rng)
{
    std::size_t part0_len = rng.rand<std::size_t>() % (inl ? inl : 1);
    std::size_t part1_len = inl - part0_len;

    std::size_t outl_tmp = 0;
    *outl                = 0;
    cryptor.update(out, &outl_tmp, in, part0_len);
    out += outl_tmp, *outl += outl_tmp;
    cryptor.update(out, &outl_tmp, in + part0_len, part1_len);
    out += outl_tmp, *outl += outl_tmp;
    cryptor.do_final(out, &outl_tmp);
    *outl += outl_tmp;
}

inline void run_update_update_final_safe(BlockCipherMode&    cryptor,
                                         std::uint8_t*       out,
                                         std::size_t*        outl,
                                         std::size_t         outl_max,
                                         const std::uint8_t* in,
                                         std::size_t         inl,
                                         rng::Rng&           rng)
{
    std::size_t part0_len = rng.rand<std::size_t>() % (inl ? inl : 1);
    std::size_t remain0   = inl - part0_len;
    std::size_t part1_len = rng.rand<std::size_t>() % (remain0 ? remain0 : 1);
    std::size_t remain1   = remain0 - part1_len;
    std::size_t part2_len = remain1;

    std::size_t outl_tmp = 0;
    *outl                = 0;
    cryptor.update(out, &outl_tmp, outl_max, in, part0_len);
    out += outl_tmp, outl_max -= outl_tmp, *outl += outl_tmp, in += part0_len;
    cryptor.update(out, &outl_tmp, outl_max, in, part1_len);
    out += outl_tmp, outl_max -= outl_tmp, *outl += outl_tmp, in += part1_len;
    cryptor.do_final(out, &outl_tmp, outl_max, in, part2_len);
    *outl += outl_tmp;
}

inline void run_update_update_final_unsafe(BlockCipherMode&    cryptor,
                                           std::uint8_t*       out,
                                           std::size_t*        outl,
                                           const std::uint8_t* in,
                                           std::size_t         inl,
                                           rng::Rng&           rng)
{
    std::size_t part0_len = rng.rand<std::size_t>() % (inl ? inl : 1);
    std::size_t remain0   = inl - part0_len;
    std::size_t part1_len = rng.rand<std::size_t>() % (remain0 ? remain0 : 1);
    std::size_t remain1   = remain0 - part1_len;
    std::size_t part2_len = remain1;

    std::size_t outl_tmp = 0;
    *outl                = 0;
    cryptor.update(out, &outl_tmp, in, part0_len);
    out += outl_tmp, *outl += outl_tmp, in += part0_len;
    cryptor.update(out, &outl_tmp, in, part1_len);
    out += outl_tmp, *outl += outl_tmp, in += part1_len;
    cryptor.do_final(out, &outl_tmp, in, part2_len);
    *outl += outl_tmp;
}

class TestCase
{
public:
    virtual ~TestCase() = default;

    virtual BlockCipherMode&           get_inited_encryptor()  = 0;
    virtual BlockCipherMode&           get_inited_decryptor()  = 0;
    virtual std::vector<std::uint8_t>& get_plaintext()         = 0;
    virtual std::vector<std::uint8_t>& get_ciphertext()        = 0;
    virtual std::vector<std::uint8_t>& get_encrypt_out_buf()   = 0;
    virtual std::vector<std::uint8_t>& get_decrypt_out_buf()   = 0;
    virtual bool                       check_encrypt_results() = 0;
    virtual bool                       check_decrypt_results() = 0;

public:
    void run(std::size_t iterations, rng::Rng& rng)
    {
        auto& plaintext          = this->get_plaintext();
        auto& ciphertext         = this->get_ciphertext();
        auto& encrypt_output_buf = this->get_encrypt_out_buf();
        auto& decrypt_output_buf = this->get_decrypt_out_buf();
        auto  encrypt_capacity   = encrypt_output_buf.size();
        auto  decrypt_capacity   = decrypt_output_buf.size();

        using run_case_fn =
            std::function<void(BlockCipherMode&,                // cryptor
                               std::vector<std::uint8_t>&,      // output
                               std::size_t*,                    // outl
                               const std::vector<std::uint8_t>& // input
                               )>;

        auto run_case = [&](std::string name, const run_case_fn& runner) {
            for (bool enc : {true, false})
            {
                // get cryptor and buffer
                auto& encryptor = this->get_inited_encryptor();
                auto& decryptor = this->get_inited_decryptor();
                auto& cryptor   = enc ? encryptor : decryptor;
                auto& input     = enc ? plaintext : ciphertext;
                auto& output    = enc ? encrypt_output_buf : decrypt_output_buf;
                // randomize output
                output.resize(enc ? encrypt_capacity : decrypt_capacity);
                rng.gen(output.data(), output.size());
                // run
                std::size_t outl = 0;
                runner(cryptor, output, &outl, input);
                output.resize(outl);
                // check
                if (!(enc ? this->check_encrypt_results()
                          : this->check_decrypt_results()))
                {
                    auto msg = name + (enc ? "encrypt" : "decrypt") + "fail";
                    throw std::runtime_error(msg);
                }
            }
        };

        for (std::size_t i = 0; i < iterations; ++i)
        {
            run_case(
                "run_final_safe",
                [&](BlockCipherMode& cryptor, std::vector<std::uint8_t>& output,
                    std::size_t* outl, const std::vector<std::uint8_t>& input) {
                    run_final_safe(cryptor, output.data(), outl, output.size(),
                                   input.data(), input.size());
                });
            run_case(
                "run_final_unsafe",
                [&](BlockCipherMode& cryptor, std::vector<std::uint8_t>& output,
                    std::size_t* outl, const std::vector<std::uint8_t>& input) {
                    run_final_unsafe(cryptor, output.data(), outl, input.data(),
                                     input.size());
                });
            run_case(
                "run_update_final0_safe",
                [&](BlockCipherMode& cryptor, std::vector<std::uint8_t>& output,
                    std::size_t* outl, const std::vector<std::uint8_t>& input) {
                    run_update_final0_safe(cryptor, output.data(), outl,
                                           output.size(), input.data(),
                                           input.size());
                });
            run_case(
                "run_update_final0_unsafe",
                [&](BlockCipherMode& cryptor, std::vector<std::uint8_t>& output,
                    std::size_t* outl, const std::vector<std::uint8_t>& input) {
                    run_update_final0_unsafe(cryptor, output.data(), outl,
                                             input.data(), input.size());
                });
            run_case(
                "run_update_update_final0_safe",
                [&](BlockCipherMode& cryptor, std::vector<std::uint8_t>& output,
                    std::size_t* outl, const std::vector<std::uint8_t>& input) {
                    run_update_update_final0_safe(cryptor, output.data(), outl,
                                                  output.size(), input.data(),
                                                  input.size(), rng);
                });
            run_case(
                "run_update_update_final0_unsafe",
                [&](BlockCipherMode& cryptor, std::vector<std::uint8_t>& output,
                    std::size_t* outl, const std::vector<std::uint8_t>& input) {
                    run_update_update_final0_unsafe(cryptor, output.data(),
                                                    outl, input.data(),
                                                    input.size(), rng);
                });
            run_case(
                "run_update_update_final_safe",
                [&](BlockCipherMode& cryptor, std::vector<std::uint8_t>& output,
                    std::size_t* outl, const std::vector<std::uint8_t>& input) {
                    run_update_update_final_safe(cryptor, output.data(), outl,
                                                 output.size(), input.data(),
                                                 input.size(), rng);
                });
            run_case(
                "run_update_update_final_unsafe",
                [&](BlockCipherMode& cryptor, std::vector<std::uint8_t>& output,
                    std::size_t* outl, const std::vector<std::uint8_t>& input) {
                    run_update_update_final_unsafe(cryptor, output.data(), outl,
                                                   input.data(), input.size(),
                                                   rng);
                });
        }
    }
};

class CfbModeTestCase : public TestCase
{
private:
    std::vector<std::uint8_t> key_;
    std::vector<std::uint8_t> iv_;
    std::vector<std::uint8_t> plaintext_;
    std::vector<std::uint8_t> ciphertext_;

    std::vector<std::uint8_t>        encrypt_out_buf_;
    std::vector<std::uint8_t>        decrypt_out_buf_;
    std::unique_ptr<BlockCipherMode> encryptor_;
    std::unique_ptr<BlockCipherMode> decryptor_;

public:
    CfbModeTestCase(const BlockCipherModeProvider*   provider,
                    const std::vector<std::uint8_t>& key,
                    const std::vector<std::uint8_t>& iv,
                    const std::vector<std::uint8_t>& plaintext,
                    const std::vector<std::uint8_t>& ciphertext)
        : key_(key),
          iv_(iv),
          plaintext_(plaintext),
          ciphertext_(ciphertext),
          encrypt_out_buf_(plaintext.size()),
          decrypt_out_buf_(ciphertext.size()),
          encryptor_(provider && provider->create_cfb_encryptor
                         ? provider->create_cfb_encryptor()
                         : nullptr),
          decryptor_(provider && provider->create_cfb_decryptor
                         ? provider->create_cfb_decryptor()
                         : nullptr)
    {
    }

public:
    BlockCipherMode& get_inited_encryptor() override
    {
        if (!encryptor_)
        {
            throw std::invalid_argument("CFB encryptor is unavailable");
        }
        encryptor_->init(key_.data(), key_.size(), iv_.data(), iv_.size());
        return *encryptor_;
    }

    BlockCipherMode& get_inited_decryptor() override
    {
        if (!decryptor_)
        {
            throw std::invalid_argument("CFB decryptor is unavailable");
        }
        decryptor_->init(key_.data(), key_.size(), iv_.data(), iv_.size());
        return *decryptor_;
    }

    std::vector<std::uint8_t>& get_plaintext() override
    {
        return plaintext_;
    }

    std::vector<std::uint8_t>& get_ciphertext() override
    {
        return ciphertext_;
    }

    std::vector<std::uint8_t>& get_encrypt_out_buf() override
    {
        return encrypt_out_buf_;
    }

    std::vector<std::uint8_t>& get_decrypt_out_buf() override
    {
        return decrypt_out_buf_;
    }

    bool check_encrypt_results() override
    {
        return ciphertext_ == encrypt_out_buf_;
    }

    bool check_decrypt_results() override
    {
        return plaintext_ == decrypt_out_buf_;
    }
};

// No padding: plaintext and ciphertext must be block-aligned.
class EcbModeTestCase : public TestCase
{
private:
    std::vector<std::uint8_t> key_;
    std::vector<std::uint8_t> plaintext_;
    std::vector<std::uint8_t> ciphertext_;

    std::vector<std::uint8_t>        encrypt_out_buf_;
    std::vector<std::uint8_t>        decrypt_out_buf_;
    std::unique_ptr<BlockCipherMode> encryptor_;
    std::unique_ptr<BlockCipherMode> decryptor_;

public:
    EcbModeTestCase(const BlockCipherModeProvider*   provider,
                    const std::vector<std::uint8_t>& key,
                    const std::vector<std::uint8_t>& plaintext,
                    const std::vector<std::uint8_t>& ciphertext)
        : key_(key),
          plaintext_(plaintext),
          ciphertext_(ciphertext),
          encrypt_out_buf_(plaintext.size()),
          decrypt_out_buf_(ciphertext.size()),
          encryptor_(provider && provider->create_ecb_encryptor
                         ? provider->create_ecb_encryptor()
                         : nullptr),
          decryptor_(provider && provider->create_ecb_decryptor
                         ? provider->create_ecb_decryptor()
                         : nullptr)
    {
    }

public:
    BlockCipherMode& get_inited_encryptor() override
    {
        if (!encryptor_)
        {
            throw std::invalid_argument("ECB encryptor is unavailable");
        }
        encryptor_->init(key_.data(), key_.size());
        encryptor_->set_padding(false);
        return *encryptor_;
    }

    BlockCipherMode& get_inited_decryptor() override
    {
        if (!decryptor_)
        {
            throw std::invalid_argument("ECB decryptor is unavailable");
        }
        decryptor_->init(key_.data(), key_.size());
        decryptor_->set_padding(false);
        return *decryptor_;
    }

    std::vector<std::uint8_t>& get_plaintext() override
    {
        return plaintext_;
    }

    std::vector<std::uint8_t>& get_ciphertext() override
    {
        return ciphertext_;
    }

    std::vector<std::uint8_t>& get_encrypt_out_buf() override
    {
        return encrypt_out_buf_;
    }

    std::vector<std::uint8_t>& get_decrypt_out_buf() override
    {
        return decrypt_out_buf_;
    }

    bool check_encrypt_results() override
    {
        return ciphertext_ == encrypt_out_buf_;
    }

    bool check_decrypt_results() override
    {
        return plaintext_ == decrypt_out_buf_;
    }
};

// No padding: plaintext and ciphertext must be block-aligned.
class CbcModeTestCase : public TestCase
{
private:
    std::vector<std::uint8_t> key_;
    std::vector<std::uint8_t> iv_;
    std::vector<std::uint8_t> plaintext_;
    std::vector<std::uint8_t> ciphertext_;

    std::vector<std::uint8_t>        encrypt_out_buf_;
    std::vector<std::uint8_t>        decrypt_out_buf_;
    std::unique_ptr<BlockCipherMode> encryptor_;
    std::unique_ptr<BlockCipherMode> decryptor_;

public:
    CbcModeTestCase(const BlockCipherModeProvider*   provider,
                    const std::vector<std::uint8_t>& key,
                    const std::vector<std::uint8_t>& iv,
                    const std::vector<std::uint8_t>& plaintext,
                    const std::vector<std::uint8_t>& ciphertext)
        : key_(key),
          iv_(iv),
          plaintext_(plaintext),
          ciphertext_(ciphertext),
          encrypt_out_buf_(plaintext.size()),
          decrypt_out_buf_(ciphertext.size()),
          encryptor_(provider && provider->create_cbc_encryptor
                         ? provider->create_cbc_encryptor()
                         : nullptr),
          decryptor_(provider && provider->create_cbc_decryptor
                         ? provider->create_cbc_decryptor()
                         : nullptr)
    {
    }

public:
    BlockCipherMode& get_inited_encryptor() override
    {
        if (!encryptor_)
        {
            throw std::invalid_argument("CBC encryptor is unavailable");
        }
        encryptor_->init(key_.data(), key_.size(), iv_.data(), iv_.size());
        encryptor_->set_padding(false);
        return *encryptor_;
    }

    BlockCipherMode& get_inited_decryptor() override
    {
        if (!decryptor_)
        {
            throw std::invalid_argument("CBC decryptor is unavailable");
        }
        decryptor_->init(key_.data(), key_.size(), iv_.data(), iv_.size());
        decryptor_->set_padding(false);
        return *decryptor_;
    }

    std::vector<std::uint8_t>& get_plaintext() override
    {
        return plaintext_;
    }

    std::vector<std::uint8_t>& get_ciphertext() override
    {
        return ciphertext_;
    }

    std::vector<std::uint8_t>& get_encrypt_out_buf() override
    {
        return encrypt_out_buf_;
    }

    std::vector<std::uint8_t>& get_decrypt_out_buf() override
    {
        return decrypt_out_buf_;
    }

    bool check_encrypt_results() override
    {
        return ciphertext_ == encrypt_out_buf_;
    }

    bool check_decrypt_results() override
    {
        return plaintext_ == decrypt_out_buf_;
    }
};

class OfbModeTestCase : public TestCase
{
private:
    std::vector<std::uint8_t> key_;
    std::vector<std::uint8_t> iv_;
    std::vector<std::uint8_t> plaintext_;
    std::vector<std::uint8_t> ciphertext_;

    std::vector<std::uint8_t>        encrypt_out_buf_;
    std::vector<std::uint8_t>        decrypt_out_buf_;
    std::unique_ptr<BlockCipherMode> encryptor_;
    std::unique_ptr<BlockCipherMode> decryptor_;

public:
    OfbModeTestCase(const BlockCipherModeProvider*   provider,
                    const std::vector<std::uint8_t>& key,
                    const std::vector<std::uint8_t>& iv,
                    const std::vector<std::uint8_t>& plaintext,
                    const std::vector<std::uint8_t>& ciphertext)
        : key_(key),
          iv_(iv),
          plaintext_(plaintext),
          ciphertext_(ciphertext),
          encrypt_out_buf_(plaintext.size()),
          decrypt_out_buf_(ciphertext.size()),
          encryptor_(provider && provider->create_ofb_encryptor
                         ? provider->create_ofb_encryptor()
                         : nullptr),
          decryptor_(provider && provider->create_ofb_decryptor
                         ? provider->create_ofb_decryptor()
                         : nullptr)
    {
    }

public:
    BlockCipherMode& get_inited_encryptor() override
    {
        if (!encryptor_)
        {
            throw std::invalid_argument("OFB encryptor is unavailable");
        }
        encryptor_->init(key_.data(), key_.size(), iv_.data(), iv_.size());
        return *encryptor_;
    }

    BlockCipherMode& get_inited_decryptor() override
    {
        if (!decryptor_)
        {
            throw std::invalid_argument("OFB decryptor is unavailable");
        }
        decryptor_->init(key_.data(), key_.size(), iv_.data(), iv_.size());
        return *decryptor_;
    }

    std::vector<std::uint8_t>& get_plaintext() override
    {
        return plaintext_;
    }

    std::vector<std::uint8_t>& get_ciphertext() override
    {
        return ciphertext_;
    }

    std::vector<std::uint8_t>& get_encrypt_out_buf() override
    {
        return encrypt_out_buf_;
    }

    std::vector<std::uint8_t>& get_decrypt_out_buf() override
    {
        return decrypt_out_buf_;
    }

    bool check_encrypt_results() override
    {
        return ciphertext_ == encrypt_out_buf_;
    }

    bool check_decrypt_results() override
    {
        return plaintext_ == decrypt_out_buf_;
    }
};

class CtrModeTestCase : public TestCase
{
private:
    std::vector<std::uint8_t> key_;
    std::vector<std::uint8_t> iv_;
    std::vector<std::uint8_t> plaintext_;
    std::vector<std::uint8_t> ciphertext_;

    std::vector<std::uint8_t>        encrypt_out_buf_;
    std::vector<std::uint8_t>        decrypt_out_buf_;
    std::unique_ptr<BlockCipherMode> encryptor_;
    std::unique_ptr<BlockCipherMode> decryptor_;

public:
    CtrModeTestCase(const BlockCipherModeProvider*   provider,
                    const std::vector<std::uint8_t>& key,
                    const std::vector<std::uint8_t>& iv,
                    const std::vector<std::uint8_t>& plaintext,
                    const std::vector<std::uint8_t>& ciphertext)
        : key_(key),
          iv_(iv),
          plaintext_(plaintext),
          ciphertext_(ciphertext),
          encrypt_out_buf_(plaintext.size()),
          decrypt_out_buf_(ciphertext.size()),
          encryptor_(provider && provider->create_ctr_encryptor
                         ? provider->create_ctr_encryptor()
                         : nullptr),
          decryptor_(provider && provider->create_ctr_decryptor
                         ? provider->create_ctr_decryptor()
                         : nullptr)
    {
    }

public:
    BlockCipherMode& get_inited_encryptor() override
    {
        if (!encryptor_)
        {
            throw std::invalid_argument("CTR encryptor is unavailable");
        }
        encryptor_->init(key_.data(), key_.size(), iv_.data(), iv_.size());
        return *encryptor_;
    }

    BlockCipherMode& get_inited_decryptor() override
    {
        if (!decryptor_)
        {
            throw std::invalid_argument("CTR decryptor is unavailable");
        }
        decryptor_->init(key_.data(), key_.size(), iv_.data(), iv_.size());
        return *decryptor_;
    }

    std::vector<std::uint8_t>& get_plaintext() override
    {
        return plaintext_;
    }

    std::vector<std::uint8_t>& get_ciphertext() override
    {
        return ciphertext_;
    }

    std::vector<std::uint8_t>& get_encrypt_out_buf() override
    {
        return encrypt_out_buf_;
    }

    std::vector<std::uint8_t>& get_decrypt_out_buf() override
    {
        return decrypt_out_buf_;
    }

    bool check_encrypt_results() override
    {
        return ciphertext_ == encrypt_out_buf_;
    }

    bool check_decrypt_results() override
    {
        return plaintext_ == decrypt_out_buf_;
    }
};

class GcmModeTestCase : public TestCase
{
private:
    std::vector<std::uint8_t> key_;
    std::vector<std::uint8_t> iv_;
    std::vector<std::uint8_t> aad_;
    std::vector<std::uint8_t> tag_;
    std::vector<std::uint8_t> plaintext_;
    std::vector<std::uint8_t> ciphertext_;

    std::vector<std::uint8_t>        encrypt_out_buf_;
    std::vector<std::uint8_t>        decrypt_out_buf_;
    std::unique_ptr<BlockCipherMode> encryptor_;
    std::unique_ptr<BlockCipherMode> decryptor_;

public:
    GcmModeTestCase(const BlockCipherModeProvider*   provider,
                    const std::vector<std::uint8_t>& key,
                    const std::vector<std::uint8_t>& iv,
                    const std::vector<std::uint8_t>& aad,
                    const std::vector<std::uint8_t>& plaintext,
                    const std::vector<std::uint8_t>& ciphertext,
                    const std::vector<std::uint8_t>& tag)
        : key_(key),
          iv_(iv),
          aad_(aad),
          tag_(tag),
          plaintext_(plaintext),
          ciphertext_(ciphertext),
          encrypt_out_buf_(plaintext.size()),
          decrypt_out_buf_(ciphertext.size()),
          encryptor_(provider && provider->create_gcm_encryptor
                         ? provider->create_gcm_encryptor()
                         : nullptr),
          decryptor_(provider && provider->create_gcm_decryptor
                         ? provider->create_gcm_decryptor()
                         : nullptr)
    {
        if (tag_.empty() || tag_.size() > 16)
        {
            throw std::invalid_argument(
                "GCM tag length must be between 1 and 16 bytes");
        }
    }

public:
    BlockCipherMode& get_inited_encryptor() override
    {
        if (!encryptor_)
        {
            throw std::invalid_argument("GCM encryptor is unavailable");
        }
        encryptor_->set_iv_len(iv_.size());
        encryptor_->init(key_.data(), key_.size(), iv_.data(), iv_.size(),
                         aad_.data(), aad_.size());
        return *encryptor_;
    }

    BlockCipherMode& get_inited_decryptor() override
    {
        if (!decryptor_)
        {
            throw std::invalid_argument("GCM decryptor is unavailable");
        }
        decryptor_->set_iv_len(iv_.size());
        decryptor_->init(key_.data(), key_.size(), iv_.data(), iv_.size(),
                         aad_.data(), aad_.size());
        decryptor_->set_tag(tag_.data(), tag_.size());
        return *decryptor_;
    }

    std::vector<std::uint8_t>& get_plaintext() override
    {
        return plaintext_;
    }

    std::vector<std::uint8_t>& get_ciphertext() override
    {
        return ciphertext_;
    }

    std::vector<std::uint8_t>& get_encrypt_out_buf() override
    {
        return encrypt_out_buf_;
    }

    std::vector<std::uint8_t>& get_decrypt_out_buf() override
    {
        return decrypt_out_buf_;
    }

    bool check_encrypt_results() override
    {
        std::vector<std::uint8_t> actual_tag(tag_.size());
        encryptor_->get_tag(actual_tag.data(), actual_tag.size());
        return ciphertext_ == encrypt_out_buf_ && tag_ == actual_tag;
    }

    bool check_decrypt_results() override
    {
        return plaintext_ == decrypt_out_buf_;
    }
};

} // namespace detail

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
    // Consecutive cipher applications, feeding each output into the next.
    std::size_t iterations = 1;
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

class CipherTestCase
{
private:
    std::string                  case_name_;
    std::vector<std::uint8_t>    key_;
    std::vector<std::uint8_t>    plaintext_;
    std::vector<std::uint8_t>    ciphertext_;
    std::size_t                  cipher_iterations_;
    std::unique_ptr<BlockCipher> cipher_;

public:
    CipherTestCase(const BlockCipherModeProvider& provider,
                   const CipherKat&               kat)
        : case_name_(kat.case_name),
          key_(kat.key),
          plaintext_(kat.plaintext),
          ciphertext_(kat.ciphertext),
          cipher_iterations_(kat.iterations),
          cipher_(provider.create_cipher ? provider.create_cipher() : nullptr)
    {
        if (!cipher_)
        {
            throw std::invalid_argument("cipher is unavailable");
        }
        auto block_size = cipher_->get_block_size();
        if (block_size == 0 || plaintext_.empty() ||
            plaintext_.size() % block_size != 0 ||
            plaintext_.size() != ciphertext_.size() ||
            key_.size() != cipher_->get_key_len() || cipher_iterations_ == 0)
        {
            throw std::invalid_argument(case_name_ + ": invalid cipher vector");
        }
    }

    void run(std::size_t iterations, rng::Rng& rng)
    {
        std::size_t               block_size = cipher_->get_block_size();
        std::vector<std::uint8_t> input(plaintext_.size());
        std::vector<std::uint8_t> output(input.size());

        using run_case_fn =
            std::function<void(BlockCipher&,                    // cipher
                               std::vector<std::uint8_t>&,      // output
                               const std::vector<std::uint8_t>& // input
                               )>;

        auto run_case = [&](const char* name, int direction,
                            const std::vector<std::uint8_t>& source,
                            const std::vector<std::uint8_t>& expected,
                            const run_case_fn&               runner) {
            cipher_->set_key(key_.data(), direction);
            input = source;
            rng.gen(output.data(), output.size());
            for (std::size_t round = 0; round < cipher_iterations_; ++round)
            {
                runner(*cipher_, output, input);
                input.swap(output);
            }
            if (input != expected)
            {
                throw std::runtime_error(case_name_ + ": " + name + " failed");
            }
        };

        for (std::size_t i = 0; i < iterations; ++i)
        {
            run_case("encrypt_block", BlockCipher::ENCRYPTION, plaintext_,
                     ciphertext_,
                     [&](BlockCipher& cipher, std::vector<std::uint8_t>& out,
                         const std::vector<std::uint8_t>& in) {
                         for (std::size_t j = 0; j < in.size(); j += block_size)
                         {
                             std::uint8_t*       out_ptr = out.data() + j;
                             const std::uint8_t* in_ptr  = in.data() + j;
                             cipher.encrypt_block(out_ptr, in_ptr);
                         }
                     });
            run_case("decrypt_block", BlockCipher::DECRYPTION, ciphertext_,
                     plaintext_,
                     [&](BlockCipher& cipher, std::vector<std::uint8_t>& out,
                         const std::vector<std::uint8_t>& in) {
                         for (std::size_t j = 0; j < in.size(); j += block_size)
                         {
                             std::uint8_t*       out_ptr = out.data() + j;
                             const std::uint8_t* in_ptr  = in.data() + j;
                             cipher.decrypt_block(out_ptr, in_ptr);
                         }
                     });
            run_case("encrypt_blocks", BlockCipher::ENCRYPTION, plaintext_,
                     ciphertext_,
                     [&](BlockCipher& cipher, std::vector<std::uint8_t>& out,
                         const std::vector<std::uint8_t>& in) {
                         cipher.encrypt_blocks(out.data(), in.data(),
                                               in.size() / block_size);
                     });
            run_case("decrypt_blocks", BlockCipher::DECRYPTION, ciphertext_,
                     plaintext_,
                     [&](BlockCipher& cipher, std::vector<std::uint8_t>& out,
                         const std::vector<std::uint8_t>& in) {
                         cipher.decrypt_blocks(out.data(), in.data(),
                                               in.size() / block_size);
                     });
        }
    }
};

inline std::unique_ptr<TestCase> make_mode_test_case(
    const BlockCipherModeProvider* provider,
    const ModeKat&                 kat)
{
    if (kat.mode == "ECB")
    {
        return std::make_unique<EcbModeTestCase>(            //
            provider, kat.key, kat.plaintext, kat.ciphertext //
        );
    }
    if (kat.mode == "CBC")
    {
        return std::make_unique<CbcModeTestCase>(                    //
            provider, kat.key, kat.iv, kat.plaintext, kat.ciphertext //
        );
    }
    if (kat.mode == "CFB")
    {
        return std::make_unique<CfbModeTestCase>(                    //
            provider, kat.key, kat.iv, kat.plaintext, kat.ciphertext //
        );
    }
    if (kat.mode == "OFB")
    {
        return std::make_unique<OfbModeTestCase>(                    //
            provider, kat.key, kat.iv, kat.plaintext, kat.ciphertext //
        );
    }
    if (kat.mode == "CTR")
    {
        return std::make_unique<CtrModeTestCase>(                    //
            provider, kat.key, kat.iv, kat.plaintext, kat.ciphertext //
        );
    }
    throw std::invalid_argument("unsupported test case mode: " + kat.mode);
}

inline std::unique_ptr<TestCase> make_mode_test_case(
    const BlockCipherModeProvider* provider,
    const AeadKat&                 kat)
{
    if (kat.mode != "GCM")
    {
        throw std::invalid_argument("unsupported AEAD mode: " + kat.mode);
    }
    return std::make_unique<GcmModeTestCase>( //
        provider, kat.key, kat.nonce, kat.aad, kat.plaintext, kat.ciphertext,
        kat.tag);
}

} // namespace detail

/**
 * @brief Run the mode test cases against one provider.
 * @throws std::invalid_argument if the provider or mode is unavailable.
 * @throws std::runtime_error if a test fails.
 */
inline void run_test_suite(const TestSuite&               suite,
                           const BlockCipherModeProvider* provider)
{
    if (provider == nullptr)
    {
        throw std::invalid_argument("provider is null");
    }
    rng::CstdRng rng;
    for (const CipherKat& kat : suite.cipher_kats)
    {
        detail::CipherTestCase test_case(*provider, kat);
        test_case.run(10, rng);
    }
    for (const ModeKat& kat : suite.mode_kats)
    {
        auto test_case = detail::make_mode_test_case(provider, kat);
        test_case->run(1000, rng);
    }
    for (const AeadKat& kat : suite.aead_kats)
    {
        auto test_case = detail::make_mode_test_case(provider, kat);
        test_case->run(1000, rng);
    }
}

inline void run_speed_test(const BlockCipherModeProvider* provider,
                           std::size_t                    msg_len = 1 << 14)
{
    using namespace std::chrono;
    using clock_t = std::chrono::high_resolution_clock;
    using Factory = std::unique_ptr<BlockCipherMode> (*)();

    if (provider == nullptr || msg_len == 0)
    {
        throw std::invalid_argument(
            "provider is null or message length is zero");
    }

    struct Mode
    {
        const char* name;
        Factory     encrypt;
        Factory     decrypt;
    };

    Mode modes[] = {
        {"ECB", provider->create_ecb_encryptor, provider->create_ecb_decryptor},
        {"CBC", provider->create_cbc_encryptor, provider->create_cbc_decryptor},
        {"CFB", provider->create_cfb_encryptor, provider->create_cfb_decryptor},
        {"OFB", provider->create_ofb_encryptor, provider->create_ofb_decryptor},
        {"CTR", provider->create_ctr_encryptor, provider->create_ctr_decryptor},
        {"GCM", provider->create_gcm_encryptor, provider->create_gcm_decryptor},
    };

    auto cipher = provider->create_cipher ? provider->create_cipher() : nullptr;
    std::unique_ptr<BlockCipherMode> probe;
    if (!cipher)
    {
        for (auto& mode : modes)
        {
            auto factory = mode.encrypt ? mode.encrypt : mode.decrypt;
            if (factory)
            {
                probe = factory();
                break;
            }
        }
    }
    if (!cipher && !probe)
    {
        throw std::invalid_argument("provider has no cipher or modes");
    }
    auto& metadata   = cipher ? *cipher : probe->get_cipher_ctx();
    auto  block_size = metadata.get_block_size();

    std::vector<std::uint8_t> key(metadata.get_key_len());
    std::vector<std::uint8_t> input(msg_len);
    std::vector<std::uint8_t> output(msg_len);
    volatile std::uint8_t     sink = 0;
    const char*               border =
        "+--------------------" // Test
        "+------------------"   // Data length
        "+--------------"       // Loops
        "+------------------+"; // Speed

    std::printf("\n%s / %s\n%s\n", //
                metadata.get_name(), provider->algo_name, border);
    std::printf("| %-18s | %16s | %12s | %16s |\n", //
                "Test", "Data length (KB)", "Loops", "Speed (Mbit/s)");
    std::puts(border);
    std::fflush(stdout);

    auto measure = [&](const std::string&           name,
                       const std::function<void()>& run) {
        std::size_t         loops   = 0;
        double              seconds = 0;
        clock_t::time_point start   = clock_t::now();
        do
        {
            for (std::size_t i = 0; i < 1024; ++i)
            {
                run();
            }
            loops += 1024;
            sink ^= output[0];
            seconds = duration<double>(clock_t::now() - start).count();
        } while (seconds < 1.0);
        double speed = (double)(msg_len)*loops * 8 / seconds / 1024 / 1024;
        std::printf("| %-18s | %16.3f | %12zu | %16.3f |\n", name.c_str(),
                    msg_len / 1024.0, loops, speed);
        std::fflush(stdout);
    };

    if (cipher)
    {
        measure("Cipher Encrypt", [&]() {
            cipher->set_key(key.data(), BlockCipher::ENCRYPTION);
            cipher->encrypt_blocks(output.data(), input.data(),
                                   msg_len / block_size);
        });
        measure("Cipher Decrypt", [&]() {
            cipher->set_key(key.data(), BlockCipher::DECRYPTION);
            cipher->decrypt_blocks(output.data(), input.data(),
                                   msg_len / block_size);
        });
    }
    bool skipped_gcm_decrypt = false;
    for (auto& mode : modes)
    {
        bool gcm      = std::strcmp(mode.name, "GCM") == 0;
        bool buffered = std::strcmp(mode.name, "ECB") == 0 ||
                        std::strcmp(mode.name, "CBC") == 0;
        std::vector<std::uint8_t> iv(
            std::strcmp(mode.name, "ECB") == 0 ? 0 : (gcm ? 12 : block_size));
        std::vector<std::uint8_t> ciphertext(msg_len);
        std::vector<std::uint8_t> tag(16);
        auto encryptor = mode.encrypt ? mode.encrypt() : nullptr;
        auto decryptor = mode.decrypt ? mode.decrypt() : nullptr;
        if (gcm && encryptor && decryptor)
        {
            // Prepare authenticated dummy ciphertext outside the timed region.
            encryptor->set_iv_len(iv.size());
            encryptor->init(key.data(), key.size(), iv.data(), iv.size());
            std::size_t written = 0;
            detail::run_final_safe(*encryptor, ciphertext.data(), &written,
                                   ciphertext.size(), input.data(),
                                   input.size());
            encryptor->get_tag(tag.data(), tag.size());
        }
        for (bool encrypt : {true, false})
        {
            auto* cryptor = encrypt ? encryptor.get() : decryptor.get();
            if (cryptor == nullptr)
            {
                continue;
            }
            if (gcm && !encrypt && !encryptor)
            {
                skipped_gcm_decrypt = true;
                continue;
            }
            if (gcm)
            {
                cryptor->set_iv_len(iv.size());
            }
            auto& data = gcm && !encrypt ? ciphertext : input;
            measure(
                std::string(mode.name) + (encrypt ? " Encrypt" : " Decrypt"),
                [&]() {
                    cryptor->init(key.data(), key.size(), iv.data(), iv.size());
                    if (buffered)
                    {
                        cryptor->set_padding(false);
                    }
                    if (gcm && !encrypt)
                    {
                        cryptor->set_tag(tag.data(), tag.size());
                    }
                    std::size_t written = 0;
                    detail::run_final_safe(*cryptor, output.data(), &written,
                                           output.size(), data.data(),
                                           data.size());
                });
        }
    }
    std::puts(border);
    if (skipped_gcm_decrypt)
    {
        std::puts(
            "GCM Decrypt skipped: an encryptor is required to prepare the "
            "tag.");
    }
    std::fflush(stdout);
}

} // namespace block_cipher_mode::test

#endif // BLOCK_CIPHER_MODE_TEST_SUITE_H
