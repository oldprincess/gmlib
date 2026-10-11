#ifndef BLOCK_CIPHER_MODE_BLOCK_CIPHER_MODE_H
#define BLOCK_CIPHER_MODE_BLOCK_CIPHER_MODE_H

#include <gmlib/block_cipher_mode/block_cipher.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>

namespace block_cipher_mode {

struct Error
{
    // clang-format off
    static constexpr const char* BAD_DECRYPT                        = "BAD_DECRYPT";
    static constexpr const char* BUFFER_TOO_SMALL                   = "BUFFER_TOO_SMALL";
    static constexpr const char* CTRL_OPERATION_NOT_IMPLEMENTED     = "CTRL_OPERATION_NOT_IMPLEMENTED";
    static constexpr const char* DATA_NOT_MULTIPLE_OF_BLOCK_LENGTH  = "DATA_NOT_MULTIPLE_OF_BLOCK_LENGTH";
    static constexpr const char* DECODE_ERROR                       = "DECODE_ERROR";
    static constexpr const char* INVALID_KEY_LENGTH                 = "INVALID_KEY_LENGTH";
    static constexpr const char* INVALID_IV_LENGTH                  = "INVALID_IV_LENGTH";
    static constexpr const char* NO_KEY_SET                         = "NO_KEY_SET";
    static constexpr const char* OPERATION_NOT_INITIALIZED          = "OPERATION_NOT_INITIALIZED";
    // clang-format on
};

enum class Padding
{
    None,
    PKCS7,
};

enum class Mode : unsigned long
{
    Stream  = 0x00000, // EVP_CIPH_STREAM_CIPHER
    ECB     = 0x00001,
    CBC     = 0x00002,
    CFB     = 0x00003,
    OFB     = 0x00004,
    CTR     = 0x00005,
    GCM     = 0x00006,
    CCM     = 0x00007,
    XTS     = 0x10001,
    Wrap    = 0x10002,
    OCB     = 0x10003,
    SIV     = 0x10004,
    GCM_SIV = 0x10005,
};

class BlockCipherMode
{
public:
    /**
     * @brief Destroy the block cipher mode context.
     */
    virtual ~BlockCipherMode() = default;

public:
    /**
     * @brief Get the underlying block cipher context.
     * @return A constant reference to the block cipher context.
     */
    virtual const BlockCipher& get_cipher_ctx() const
    {
        throw std::runtime_error(std::string(__func__) + "is not support");
    }

    /**
     * @brief Get the name of the block cipher mode.
     * @return A null-terminated mode name owned by the implementation.
     */
    virtual const char* get_name() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

public:
    /**
     * @brief Create a copy of this block cipher mode context.
     * @return A newly allocated block cipher mode context.
     */
    virtual std::unique_ptr<BlockCipherMode> clone() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Initialize or reinitialize a message, optionally replacing
     *        the key and IV.
     *
     * @details Corresponds to OpenSSL's EVP_EncryptInit_ex2() or
     *          EVP_DecryptInit_ex2(). The concrete context selects the
     *          algorithm and encryption or decryption direction. Multiple
     *          calls are allowed before processing data, during a message,
     *          and after do_final(). Each call starts fresh message state;
     *          it does not resume buffered input from an earlier call.
     *
     * @param[in] user_key New user key, or nullptr to retain an installed
     *                     key or defer key setup until a later init().
     * @param[in] user_key_len Key length in bytes. Must be zero when
     *                         @p user_key is nullptr; otherwise it must
     *                         match the configured key length.
     * @param[in] iv New IV or nonce, or nullptr to omit IV setup.
     * @param[in] iv_len IV length in bytes. Must be zero when @p iv is
     *                   nullptr. Modes without an IV require zero.
     * @param[in] aad Optional initial AAD for this message, where supported.
     * @param[in] aad_len AAD length in bytes. Must be zero when @p aad is
     *                    nullptr. Non-AEAD modes require zero.
     *
     * @note A supplied key or IV is installed during initialization.
     *       Setup may be split across calls, but all parameters required
     *       by the mode must be available before processing data. For
     *       example, an ordinary CBC context may be initialized as follows:
     *       @code{.cpp}
     *       ctx.init(key, key_len, nullptr, 0, nullptr, 0);
     *       ctx.init(nullptr, 0, iv, iv_len, nullptr, 0);
     *       @endcode
     *       Passing nullptr for a key that has never been installed does
     *       not create a default key.
     *
     * @note Reinitialization discards pending input, processing offsets,
     *       and the previous message's authentication state. It preserves
     *       the installed key when omitted and persistent configuration,
     *       such as padding. Supply AAD and any expected authentication tag
     *       separately for each message, in the order required by the mode.
     *       Initial AAD passed here precedes AAD subsequently passed to
     *       update(); it is not retained by a later init().
     *
     * @note Omitting the IV is mode-specific, not a portable request to
     *       rewind or continue a message. OpenSSL's ordinary CBC, CFB and
     *       OFB restore their original IV, whereas CTR does not restore
     *       its original counter. AEAD modes have separate nonce rules.
     *       Pass an explicit IV when starting another message. To continue
     *       the current message, call update() without calling init().
     *
     * @note Use init(nullptr, 0, new_iv, new_iv_len, nullptr, 0) to start
     *       another message with the installed key. A separate reset()
     *       operation is not part of this interface. Reinitialization is
     *       not a request to erase the installed key or release the context.
     *       For GCM encryption, never reuse a nonce with the same key.
     *
     * @throws std::invalid_argument If a pointer/length pair, key length,
     *         IV length or AAD is invalid for the selected mode.
     * @throws std::runtime_error If initialization is unsupported or fails.
     *         The default implementation always throws.
     *
     * @see update()
     * @see do_final()
     */
    virtual void init(const std::uint8_t* user_key,
                      std::size_t         user_key_len,
                      const std::uint8_t* iv      = nullptr,
                      std::size_t         iv_len  = 0,
                      const std::uint8_t* aad     = nullptr,
                      std::size_t         aad_len = 0)
    {
        (void)user_key;
        (void)user_key_len;
        (void)iv;
        (void)iv_len;
        (void)aad;
        (void)aad_len;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Initialize a message through the legacy five-parameter API.
     *
     * @param[in] user_key User key with the length reported by get_key_len().
     * @param[in] iv IV or nonce, or nullptr to omit IV setup.
     * @param[in] iv_len IV length in bytes. When @p iv is non-null, zero
     *                   selects the length reported by get_iv_len().
     * @param[in] aad Optional initial AAD for this message, where supported.
     * @param[in] aad_len AAD length in bytes. Must be zero when @p aad is
     *                    nullptr. Non-AEAD modes require zero.
     *
     * @deprecated This overload is retained only for compatibility with
     *             the old API. Use the six-parameter virtual init() overload
     *             with an explicit user_key_len instead.
     */
    void init(const std::uint8_t* user_key,
              const std::uint8_t* iv      = nullptr,
              std::size_t         iv_len  = 0,
              const std::uint8_t* aad     = nullptr,
              std::size_t         aad_len = 0)
    {
        std::size_t key_len = this->get_key_len();
        iv_len = iv ? (iv_len != 0 ? iv_len : this->get_iv_len()) : 0;
        this->init(user_key, key_len, iv, iv_len, aad, aad_len);
    }

    /**
     * @brief Process message data or supply AAD without finishing the message.
     *
     * @details Corresponds to OpenSSL's EVP_EncryptUpdate() or
     *          EVP_DecryptUpdate(). Ordinary ECB, CBC, CFB, OFB and CTR
     *          permit multiple calls for successive portions of one message.
     *          Other modes may require the complete input in one call.
     *          Required key, IV and mode configuration must be installed
     *          before supplying message data.
     *
     * @param[out] out Buffer receiving ciphertext or plaintext. For AEAD
     *                 modes supporting AAD input, nullptr selects AAD rather
     *                 than message data; it is not an output-size query.
     * @param[out] outl Non-null pointer receiving this call's output length,
     *                  not the cumulative message length. AAD produces no
     *                  ciphertext or plaintext; do not advance an output
     *                  pointer using the length reported for an AAD call.
     * @param[in] outl_max Capacity of @p out in bytes; zero for AAD input.
     * @param[in] in Input data. A nonzero input length requires a non-null
     *               pointer, except for a mode-specific length declaration.
     * @param[in] inl Input length in bytes, or bits for a CFB1 implementation
     *                explicitly configured through set_use_bits(true).
     *
     * @note Incomplete blocks may be buffered; padded decryption may also
     *       retain the last block until do_final(). Output can be shorter
     *       or longer than this call's input because of earlier buffered
     *       data. Allocate for the mode's worst-case output and use @p outl
     *       to advance the output pointer. Do not assume in-place operation
     *       is supported; use disjoint buffers unless the mode documents it.
     *
     * @note For GCM, supply all AAD before any plaintext or ciphertext.
     *       AAD is authenticated but not encrypted, and may be omitted.
     *       CCM additionally requires a total-length declaration with both
     *       @p in and @p out null, followed by AAD and a single complete
     *       message-data call. These conventions apply only where the
     *       concrete implementation supports them.
     *
     * @note A zero-length ordinary data call does not finish or restart
     *       the message. Call do_final() to complete it. After do_final(),
     *       call init() before supplying another message; do not rely on
     *       an implementation accepting update() after finalization.
     *
     * @note AEAD plaintext remains unauthenticated until verification
     *       succeeds. GCM verifies at do_final(); CCM may verify in the
     *       message-data update(). Discard all plaintext on failure.
     *
     * @throws std::invalid_argument If buffers, lengths, parameters or the
     *         call order are invalid for the selected mode.
     * @throws std::length_error If @p outl_max is insufficient.
     * @throws std::runtime_error If processing or authentication fails.
     *
     * @see init()
     * @see do_final()
     */
    virtual void update(std::uint8_t*       out,
                        std::size_t*        outl,
                        std::size_t         outl_max,
                        const std::uint8_t* in,
                        std::size_t         inl)
    {
        (void)out;
        (void)outl;
        (void)outl_max;
        (void)in;
        (void)inl;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Process message data or supply AAD without finishing the message.
     * @param[out] out Buffer receiving ciphertext or plaintext. Must have
     *                 enough capacity for all output, including buffered data.
     *                 For AEAD modes supporting AAD input, nullptr selects
     *                 AAD rather than message data; it is not a size query.
     * @param[out] outl Non-null pointer receiving this call's output length,
     *                  not the cumulative message length. Do not use the
     *                  length reported for AAD to advance an output pointer.
     * @param[in] in Input data. A nonzero input length requires a non-null
     *               pointer, except for a mode-specific length declaration.
     * @param[in] inl Input length in bytes, or bits for a CFB1 implementation
     *                explicitly configured through set_use_bits(true).
     *
     * @note This is a simplified version of the full five-parameter virtual
     *       update() overload, passing (std::size_t)(-1) for outl_max.
     *       The caller is responsible for ensuring sufficient output capacity.
     */
    void update(std::uint8_t*       out,
                std::size_t*        outl,
                const std::uint8_t* in,
                std::size_t         inl)
    {
        this->update(out, outl, (std::size_t)(-1), in, inl);
    }

    /**
     * @brief Process the last input portion and finish the message.
     *
     * @details Equivalent to processing @p in with update() and then
     *          performing OpenSSL-style Final. Unlike EVP_EncryptFinal_ex()
     *          and EVP_DecryptFinal_ex(), this operation accepts input and
     *          reports the combined output of both steps. It also processes
     *          any data buffered by earlier update() calls.
     *
     * @param[out] out Buffer receiving the combined final output. Provide
     *                 writable storage when the mode may produce output,
     *                 even if @p inl is zero. This is not an AAD call.
     * @param[out] outl Non-null pointer receiving the total number of bytes
     *                  written by this call, excluding earlier updates.
     * @param[in] outl_max Capacity of @p out for both processing the final
     *                     input and emitting any buffered or padded output.
     * @param[in] in Optional last portion of plaintext or ciphertext.
     *               May be nullptr only when @p inl is zero.
     * @param[in] inl Final input length, with the same units as update().
     *
     * @note Both complete-message and incremental processing are supported
     *       where permitted by the mode:
     *       @code{.cpp}
     *       ctx.init(key, key_len, iv, iv_len, nullptr, 0);
     *       ctx.do_final(out, &outl, capacity, input, input_len);
     *
     *       ctx.init(nullptr, 0, next_iv, iv_len, nullptr, 0);
     *       ctx.update(out, &first_len, capacity, first, first_size);
     *       ctx.do_final(out + first_len, &last_len, capacity - first_len,
     *                    last, last_size);
     *       // Total output: first_len + last_len.
     *       @endcode
     *       If all input was already supplied, omit @p in and @p inl to
     *       perform finalization only. Do not submit the last portion twice.
     *
     * @note For ECB/CBC with PKCS7, encryption adds padding and decryption
     *       verifies and removes it. Without padding, the total message
     *       length must be a multiple of the cipher block size. Stream-like
     *       modes do not add PKCS7 padding, but still finish the message.
     *       Padding validation does not authenticate ordinary CBC or ECB.
     *
     * @note For GCM encryption, obtain the tag with get_tag() after this
     *       call succeeds. For GCM decryption, install the expected tag
     *       with set_tag() before this call. Authentication failure makes
     *       all plaintext from this message unusable, including bytes
     *       returned by earlier updates. Other AEAD modes may require the
     *       expected tag before the first message-data update().
     *
     * @note Finalization does not erase the installed key or automatically
     *       prepare another message. Call init() before another update()
     *       or do_final(). If processing fails, discard this message's
     *       output and reinitialize before reuse; failure does not promise
     *       to restore the context or output buffer to its previous state.
     *
     * @throws std::invalid_argument If buffers, lengths, call order or
     *         padding are invalid for the selected mode.
     * @throws std::length_error If @p outl_max is insufficient.
     * @throws std::runtime_error If finalization or authentication fails.
     *
     * @see init()
     * @see update()
     * @see get_tag()
     * @see set_tag()
     */
    virtual void do_final(std::uint8_t*       out,
                          std::size_t*        outl,
                          std::size_t         outl_max,
                          const std::uint8_t* in  = nullptr,
                          std::size_t         inl = 0)
    {
        (void)out;
        (void)outl;
        (void)outl_max;
        (void)in;
        (void)inl;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Process the last input portion and finish the message.
     * @param[out] out Buffer receiving the combined final output. Must have
     *                 enough capacity for the final input and any buffered
     *                 or padded output, even when @p inl is zero.
     * @param[out] outl Non-null pointer receiving the total number of bytes
     *                  written by this call, excluding earlier updates.
     * @param[in] in Optional last portion of plaintext or ciphertext.
     *               May be nullptr only when @p inl is zero.
     * @param[in] inl Final input length in bytes, or bits for a CFB1
     *                implementation configured through set_use_bits(true).
     *
     * @note This is a simplified version of the full five-parameter virtual
     *       do_final() overload, passing (std::size_t)(-1) for outl_max.
     *       The caller is responsible for ensuring sufficient output capacity.
     */
    void do_final(std::uint8_t*       out,
                  std::size_t*        outl,
                  const std::uint8_t* in  = nullptr,
                  std::size_t         inl = 0)
    {
        this->do_final(out, outl, (std::size_t)(-1), in, inl);
    }

public:
    // ************************************************************
    // ============================================================
    // =================== OpenSSL-like API =======================
    // ============================================================
    // ************************************************************

    /**
     * @brief Query whether the cipher supports authenticated encryption
     *        with associated data (AEAD).
     *
     * @details Corresponds to OpenSSL's "aead" parameter
     *          (OSSL_CIPHER_PARAM_AEAD). This property is applicable to
     *          both AEAD and non-AEAD modes, provided the implementation
     *          supports this query.
     *
     * @return true for AEAD ciphers, such as GCM, CCM, OCB, SIV and
     *         GCM-SIV; false for ordinary ECB, CBC, CFB, OFB, CTR and
     *         XTS ciphers.
     *
     * @note This is a read-only algorithm property, not a switch that
     *       enables authentication or an indication that tag verification
     *       has succeeded. Composite ciphers such as AES-CBC-HMAC-SHA256
     *       may report true even though ordinary CBC reports false.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws;
     *         an unsupported query must not be interpreted as false.
     */
    virtual bool get_aead() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Legacy alias for @ref get_algorithm_id_params().
     * @details For supported modes, output and usage notes, see
     *          @ref get_algorithm_id_params().
     * @deprecated Use @ref get_algorithm_id_params() instead.
     */
    [[deprecated("Use get_algorithm_id_params() instead.")]]
    void get_alg_id_param(std::uint8_t* out,
                          std::size_t*  outl,
                          std::size_t   outl_max) const
    {
        this->get_algorithm_id_params(out, outl, outl_max);
    }

    /**
     * @brief Legacy alias for @ref set_algorithm_id_params().
     * @details For parameter details, see @ref get_algorithm_id_params().
     *          For setting requirements, see @ref set_algorithm_id_params().
     * @deprecated Use @ref set_algorithm_id_params() instead.
     */
    [[deprecated("Use set_algorithm_id_params() instead.")]]
    void set_alg_id_param(const std::uint8_t* in, std::size_t inl)
    {
        this->set_algorithm_id_params(in, inl);
    }

    /**
     * @brief Export the complete DER-encoded AlgorithmIdentifier.
     *
     * @details Corresponds to OpenSSL's "algorithm-id" parameter.
     *          Supported only when the concrete implementation provides
     *          AlgorithmIdentifier export for the selected cipher and mode.
     *          Support is not guaranteed for every CBC, GCM or other
     *          mode implementation.
     *
     * @param[out] out Buffer receiving the DER-encoded AlgorithmIdentifier.
     * @param[out] outl Number of bytes written to @p out.
     * @param[in] outl_max Capacity of @p out in bytes.
     *
     * @note The output contains the algorithm OID and its parameters,
     *       if required by that algorithm. It never contains the secret key.
     *       For example, AES-128-CBC with IV 00 01 ... 0F is encoded as:
     *       @code
     *       30 1D
     *          06 09 60 86 48 01 65 03 04 01 02
     *          04 10 00 01 02 03 04 05 06 07
     *                08 09 0A 0B 0C 0D 0E 0F
     *       @endcode
     *       Here the OID identifies AES-128-CBC, and the parameters
     *       contain the 16-byte IV. The complete encoding is 31 bytes.
     *
     * @note Initialize any required parameters, such as the IV, before
     *       exporting. Null-buffer size queries are not guaranteed by
     *       this interface.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     *
     * @see get_algorithm_id_params()
     */
    virtual void get_algorithm_id(std::uint8_t* out,
                                  std::size_t*  outl,
                                  std::size_t   outl_max) const
    {
        (void)out;
        (void)outl;
        (void)outl_max;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Export DER-encoded AlgorithmIdentifier parameters.
     *
     * @details Corresponds to OpenSSL's "algorithm-id-params" parameter.
     *          Supported only when the concrete implementation provides
     *          ASN.1 parameter export for the selected cipher and mode.
     *          Having an IV or using CBC does not by itself guarantee
     *          support for this query.
     *
     * @param[out] out Buffer receiving the DER-encoded parameters.
     * @param[out] outl Number of bytes written to @p out.
     * @param[in] outl_max Capacity of @p out in bytes.
     *
     * @note The output contains only the parameters field, including its
     *       ASN.1 tag and length. It does not contain the algorithm OID,
     *       the enclosing AlgorithmIdentifier SEQUENCE or the secret key.
     *       Use @ref get_algorithm_id() to export the complete structure.
     *
     * @note For AES-CBC with IV 00 01 ... 0F, the parameter encoding is:
     *       @code
     *       04 10 00 01 02 03 04 05 06 07
     *             08 09 0A 0B 0C 0D 0E 0F
     *       @endcode
     *       This is an 18-byte DER OCTET STRING containing the 16-byte IV.
     *       Other algorithms may use different structures.
     *       RC2-CBC parameters contain two values: an encoded effective
     *       key size and an 8-byte IV, wrapped in an ASN.1 SEQUENCE.
     *       For example, 128 effective key bits are encoded as the
     *       integer 58, not 128.
     *
     * @note Initialize the required parameters before exporting, and
     *       export before processing message data. The encoding depends
     *       on the selected cipher and mode.
     *       The output contains algorithm parameters only; it does not
     *       include the key or buffered message data.
     *       Null-buffer size queries are not guaranteed by this interface.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual void get_algorithm_id_params(std::uint8_t* out,
                                         std::size_t*  outl,
                                         std::size_t   outl_max) const
    {
        (void)out;
        (void)outl;
        (void)outl_max;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Import DER-encoded AlgorithmIdentifier parameters.
     *
     * @details For parameter formats and examples, see
     *          @ref get_algorithm_id_params().
     *          Supported only when the concrete implementation provides
     *          ASN.1 parameter import for the selected cipher and mode.
     *          Support for export does not guarantee support for import.
     *
     * @param[in] in Buffer containing the DER-encoded parameters.
     * @param[in] inl Length of @p in in bytes.
     *
     * @note Pass only the encoded parameters field, not the complete
     *       AlgorithmIdentifier or a raw IV. The encoding must match
     *       the cipher and mode selected by this context.
     *
     * @note The fields and their order follow the algorithm's ASN.1
     *       specification. For example, AES-GCM parameters defined by
     *       RFC 5084 contain the nonce and tag length, but neither AAD
     *       nor the authentication tag itself. These are supplied
     *       separately.
     *
     * @note Import may change the IV and algorithm-specific settings,
     *       such as the effective key size for RC2. It does not install
     *       a secret key.
     *
     * @note Use this operation to import parameters extracted from
     *       an ASN.1 file or protocol message. The following example
     *       imports an AES-CBC IV encoded as a DER OCTET STRING:
     *       @code{.cpp}
     *       const std::uint8_t params[] = {
     *           0x04, 0x10,
     *           0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
     *           0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
     *       };
     *       ctx.set_algorithm_id_params(params, sizeof(params));
     *       @endcode
     *       This requires an AES-CBC context that supports parameter
     *       import, at a stage where the implementation permits it.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation. The default implementation always throws.
     */
    virtual void set_algorithm_id_params(const std::uint8_t* in,
                                         std::size_t         inl)
    {
        (void)in;
        (void)inl;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Get the mode's processing block size in bytes.
     *
     * @details Corresponds to OpenSSL's "blocksize" parameter
     *          (OSSL_CIPHER_PARAM_BLOCK_SIZE). This property applies
     *          to all modes, provided the implementation supports
     *          this query.
     *
     * @return The processing block size in bytes. OpenSSL examples:
     *         - AES-ECB and AES-CBC: 16.
     *         - DES-ECB and DES-CBC: 8.
     *         - AES-CFB, AES-OFB, AES-CTR and AES-GCM: 1.
     *         - AES-OCB: 16.
     *
     * @note This may differ from the underlying cipher's block size.
     *       For example, AES-CTR reports 1 here, while the underlying
     *       AES primitive has a block size of 16 bytes.
     *       The value is unrelated to the key, IV or tag length.
     *
     * @note This value alone does not define all input-length rules.
     *       A value greater than 1 does not require every update call
     *       to contain whole blocks, since partial data may be buffered.
     *       For ordinary ECB and CBC without padding, the total message
     *       length must be a multiple of the block size.
     *       A value of 1 does not imply that padding is required or
     *       that the mode has no other input-length restrictions.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual std::size_t get_block_size() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query the ciphertext-stealing (CTS) flag.
     *
     * @details Corresponds to OpenSSL's "cts" parameter
     *          (OSSL_CIPHER_PARAM_CTS / EVP_CIPH_FLAG_CTS).
     *          This property can be queried for both CTS and non-CTS
     *          ciphers, provided the implementation supports the query.
     *
     * @return true if the CTS flag is set, otherwise false.
     *         OpenSSL examples:
     *         - AES-CBC-CTS and CAMELLIA-CBC-CTS: true.
     *         - Ordinary AES-CBC, AES-ECB and AES-CTR: false.
     *         - AES-XTS: false, despite using ciphertext stealing.
     *
     * @note This is a read-only property, not a switch that enables CTS.
     *       For CBC-CTS, use @ref get_cts_mode() to query the selected
     *       variant (CS1, CS2 or CS3).
     *
     * @note OpenSSL also uses this flag to identify ciphers that require
     *       the entire message in a single EVP_CipherUpdate() call.
     *       A false result does not guarantee that multiple update
     *       calls are supported; other modes may impose their own
     *       restrictions.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual bool get_cts() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Get the selected CBC ciphertext-stealing variant.
     *
     * @details Corresponds to OpenSSL's "cts_mode" parameter
     *          (OSSL_CIPHER_PARAM_CTS_MODE). Supported by OpenSSL's
     *          AES-CBC-CTS and CAMELLIA-CBC-CTS with 128-, 192- or
     *          256-bit keys. Not applicable to ordinary CBC or XTS.
     *
     * @return A NUL-terminated static string: "CS1", "CS2" or "CS3".
     *         The caller must not modify or free the string.
     *         The pointer remains valid for the lifetime of the program.
     *
     * @note OpenSSL defaults to "CS1". The variants determine the order
     *       of the final ciphertext portions:
     *       - CS1: for a partial final block, output the partial
     *         ciphertext portion before the final complete block.
     *       - CS2: for a partial final block, output the final complete
     *         block before the partial ciphertext portion.
     *       - CS3: use the same order as CS2 for a partial final block;
     *         for aligned input, swap the final two complete blocks.
     *       CS1 and CS2 use ordinary CBC ordering for aligned input.
     *       All three use ordinary CBC for a single-block message.
     *
     * @note All variants preserve the message length and require at
     *       least 16 bytes for AES and CAMELLIA. Encryption and decryption
     *       must use the same variant. Select it before processing data.
     *
     * @note This getter returns a string pointer directly. OpenSSL's
     *       EVP_CIPHER_CTX_get_params() instead copies the string into
     *       a caller-provided buffer.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual const char* get_cts_mode() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Set the CBC ciphertext-stealing variant.
     *
     * @details For supported ciphers, variant differences and usage
     *          requirements, see @ref get_cts_mode().
     *
     * @param[in] in Buffer containing "CS1", "CS2" or "CS3".
     * @param[in] inl Length of @p in in bytes, excluding the terminating
     *                NUL byte. Pass 3 for each supported value.
     *
     * @note Select the variant before processing message data.
     *       This operation does not enable CTS for an ordinary CBC
     *       context; the selected cipher must already support CBC-CTS.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation. The default implementation always throws.
     */
    virtual void set_cts_mode(const std::uint8_t* in, std::size_t inl)
    {
        (void)in;
        (void)inl;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query whether the cipher uses custom IV handling.
     *
     * @details Corresponds to OpenSSL's "custom-iv" parameter
     *          (OSSL_CIPHER_PARAM_CUSTOM_IV) and the equivalent
     *          EVP_CIPH_CUSTOM_IV flag.
     *          This property applies to all modes, provided the
     *          implementation supports the query.
     *
     * @return true if IV storage and initialization are handled by
     *         the cipher implementation instead of OpenSSL's generic
     *         IV handling; otherwise false. OpenSSL examples:
     *         - AES-XTS: true.
     *         - Ordinary AES-CBC, AES-CFB, AES-OFB and AES-CTR: false.
     *         - AES-ECB: false; this mode does not use an IV.
     *
     * @note "Custom IV" refers to internal IV handling, not to an IV
     *       supplied by the caller. For example, both AES-CBC and AES-XTS
     *       accept caller-supplied IVs, although their flag values differ.
     *
     * @note This is a read-only property. It does not indicate whether
     *       variable IV lengths are accepted or whether an IV has been
     *       generated internally.
     *
     * @note A false result does not mean that the cipher has no IV.
     *       Use @ref get_iv_len() to query the IV length.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual bool get_custom_iv() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query whether the cipher implementation supports decryption only.
     *
     * @details Corresponds to OpenSSL's "decrypt-only" parameter
     *          (OSSL_CIPHER_PARAM_DECRYPT_ONLY).
     *          Availability depends on the algorithm implementation and
     *          provider, rather than on the working mode alone.
     *
     * @return true if the implementation supports decryption only;
     *         false if it is not restricted to decryption.
     *         OpenSSL documents FIPS-provider 3DES ciphers as examples
     *         that report true. An implementation supporting both
     *         encryption and decryption reports false when it exposes
     *         this parameter.
     *
     * @note This is a read-only capability property, not the current
     *       operation direction. Initializing a cipher for decryption
     *       does not by itself make this property true.
     *
     * @note OpenSSL implementations may omit this parameter.
     *       An unsupported query must not be interpreted as false.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual bool get_decrypt_only() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Control whether restricted encryption operations are rejected.
     *
     * @details Corresponds to OpenSSL's "encrypt-check" parameter
     *          (OSSL_CIPHER_PARAM_FIPS_ENCRYPT_CHECK).
     *          Supported by applicable OpenSSL FIPS-provider ciphers,
     *          such as DES-EDE3-ECB and DES-EDE3-CBC.
     *          Support depends on the algorithm and provider, not
     *          simply on the working mode.
     *          For these 3DES implementations, the check detects an
     *          attempt to encrypt; decryption does not trigger this
     *          encryption restriction.
     *
     * @param[in] value true to enforce the encryption restriction
     *                  (OpenSSL's default); false to bypass this check.
     *
     * @note For the affected 3DES implementations, true causes an
     *       encryption attempt to fail. Setting false permits the
     *       operation past this check, but the resulting encryption
     *       is not FIPS approved and its FIPS indicator is false.
     *       Other errors may still cause the operation to fail.
     *
     * @note OpenSSL requires this option to be configured early,
     *       through the parameters passed to an encryption initialization
     *       function such as EVP_EncryptInit_ex2().
     *
     * @note This option does not select encryption or decryption,
     *       disable authentication-tag verification, or disable all
     *       FIPS checks. Use @ref get_fips_indicator() to query the
     *       completed operation's approval status.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation. The default implementation always throws.
     */
    virtual void set_encrypt_check(bool value)
    {
        (void)value;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query the FIPS approval status of the encryption or decryption
     *        operation after finalization.
     *
     * @details Corresponds to OpenSSL's "fips-indicator" parameter
     *          (OSSL_CIPHER_PARAM_FIPS_APPROVED_INDICATOR).
     *          Supported by OpenSSL FIPS-provider implementations that
     *          expose this indicator. Availability depends on the
     *          algorithm and provider, not simply on the working mode.
     *          Approval means that the operation satisfies the applicable
     *          FIPS requirements checked by the provider.
     *
     * @return true if the operation is reported as FIPS approved;
     *         false if it is reported as not approved.
     *
     * @note For example, with applicable OpenSSL FIPS-provider 3DES
     *       implementations such as DES-EDE3-ECB and DES-EDE3-CBC:
     *       - Decryption can report true when the applicable requirements
     *         are satisfied.
     *       - Encryption is rejected when the encryption check is enabled
     *         (the default). This is an operation failure, not a completed
     *         encryption whose approval status should be queried.
     *       - Disabling the check through @ref set_encrypt_check() allows
     *         encryption to pass that check, but the operation reports
     *         false. Other errors may still cause encryption to fail.
     *
     * @note Query after completing the cipher operation, such as after
     *       EVP_EncryptFinal_ex() or EVP_DecryptFinal_ex() in OpenSSL,
     *       and before reinitializing the context for another operation.
     *
     * @note This indicator describes the individual operation, not
     *       the FIPS certification status of the entire application.
     *       Using the FIPS provider alone does not guarantee a true
     *       result for every operation.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual bool get_fips_indicator() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query whether algorithm-specific random key generation is
     *        supported.
     *
     * @details Corresponds to OpenSSL's "has-randkey" parameter
     *          (OSSL_CIPHER_PARAM_HAS_RANDKEY).
     *          Indicates support for the "randkey" parameter
     *          (OSSL_CIPHER_PARAM_RANDOM_KEY), exposed here through
     *          @ref get_randkey().
     *          This capability depends on the cipher implementation,
     *          rather than a particular working mode.
     *
     * @return true for OpenSSL DES and 3DES implementations, for example
     *         DES-CBC and DES-EDE3-CBC; false for other OpenSSL ciphers,
     *         for example AES-128-CBC and AES-128-GCM.
     *
     * @note DES and 3DES use their algorithm-specific generator to set
     *       odd parity in each key byte. A false result does not mean
     *       that random keys cannot be used: ciphers such as AES can
     *       use key bytes from a suitable random number generator.
     *
     * @note This query does not generate a key or indicate whether
     *       a key has already been installed in the context.
     *       A true result does not guarantee that a subsequent key
     *       generation request will succeed.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual bool get_has_randkey() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Get a read-only pointer to the original initialization vector.
     *
     * @details Corresponds to OpenSSL's "iv" parameter
     *          (OSSL_CIPHER_PARAM_IV).
     *          Supported by implementations that expose their original
     *          IV or nonce, such as CBC, CFB, OFB, CTR, GCM and CCM.
     *          ECB does not use an IV. For other modes, support depends
     *          on whether the implementation exposes this parameter.
     *
     * @return A pointer to the original IV bytes owned by the context.
     *         The length is returned by @ref get_iv_len().
     *         The data is binary, with no terminating NUL byte.
     *
     * @note Typical lengths are 16 bytes for AES-CBC, AES-CFB, AES-OFB
     *       and AES-CTR, 8 bytes for DES-CBC and 3DES-CBC, and 12 bytes
     *       for AES-GCM with its default nonce length.
     *       The bytes are the IV or nonce established for the operation;
     *       they are not ASN.1-encoded algorithm parameters.
     *
     * @note Query after the IV has been established. For example,
     *       if AES-CBC was initialized with the 16 bytes 00 01 ... 0F,
     *       this function exposes those same bytes even after processing
     *       plaintext or ciphertext.
     *       Use @ref get_updated_iv() to inspect the current IV state.
     *
     * @note Do not modify or free the returned memory. The pointer is
     *       valid until the context is reinitialized, its IV is replaced,
     *       or the context is destroyed. Obtain a new pointer after
     *       reinitialization or IV replacement. Copy the bytes if they
     *       must be retained independently of the context.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual const std::uint8_t* get_iv() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query whether the encryption IV was generated internally.
     *
     * @details Corresponds to OpenSSL's "iv-generated" parameter
     *          (OSSL_CIPHER_PARAM_AEAD_IV_GENERATED).
     *          Supported by GCM implementations that expose this indicator,
     *          such as OpenSSL AES-GCM.
     *          Other modes may not support this query.
     *
     * @return true if the IV was generated internally during encryption;
     *         false otherwise. For example, AES-GCM encryption using an
     *         internally generated IV reports true, while encryption using
     *         a caller-supplied IV reports false.
     *
     * @note Query after encryption has finished, such as after
     *       EVP_EncryptFinal_ex() in OpenSSL, and before reinitializing
     *       the context for another operation.
     *
     * @note This query does not generate an IV or return its bytes.
     *       A caller-supplied IV remains externally supplied even if
     *       the caller generated it using a random number generator.
     *
     * @note For decryption, this query cannot determine how the sender
     *       originally generated the supplied IV.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual bool get_iv_generated() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query the current IV or nonce length in bytes.
     *
     * @details Corresponds to OpenSSL's "ivlen" parameter
     *          (OSSL_CIPHER_PARAM_IVLEN and OSSL_CIPHER_PARAM_AEAD_IVLEN)
     *          and EVP_CIPHER_CTX_get_iv_length().
     *          Applicable to modes with an IV or nonce, including CBC,
     *          CFB, OFB, CTR, GCM, CCM and OCB, and to modes without
     *          an IV, such as ECB.
     *
     * @return The IV or nonce length currently configured in the context,
     *         or zero if the cipher does not use an IV.
     *         Examples in OpenSSL:
     *         - AES-ECB: 0 bytes.
     *         - AES-CBC, AES-CFB, AES-OFB and AES-CTR: 16 bytes.
     *         - DES-CBC and 3DES-CBC: 8 bytes.
     *         - AES-GCM and AES-OCB: 12 bytes by default.
     *         - AES-CCM: 7 bytes by default.
     *
     * @note For modes with configurable nonce lengths, this query returns
     *       the current setting rather than always returning the default.
     *       Support for this query does not imply that
     *       @ref set_iv_len() can change the length.
     *
     * @note The length describes the IV expected by the context.
     *       A nonzero value does not indicate that IV bytes have already
     *       been supplied or generated.
     *
     * @note IV length is separate from block size and authentication-tag
     *       length. For example, AES-GCM normally uses a 12-byte nonce
     *       even though the underlying AES block size is 16 bytes.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual std::size_t get_iv_len() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Set the IV or nonce length in bytes.
     *
     * @details Corresponds to OpenSSL's settable "ivlen" parameter
     *          (OSSL_CIPHER_PARAM_IVLEN and OSSL_CIPHER_PARAM_AEAD_IVLEN).
     *          For the parameter meaning, default lengths and query
     *          behavior, see @ref get_iv_len().
     *
     * @param[in] value Requested IV or nonce length in bytes.
     *                 OpenSSL examples include:
     *                 - AES-GCM: 12 bytes, or another supported length.
     *                 - AES-CCM: 7 to 13 bytes.
     *                 - AES-OCB: 1 to 15 bytes.
     *
     * @note Supported by implementations with configurable IV lengths,
     *       such as GCM, CCM and OCB. Ordinary AES-CBC, AES-CFB,
     *       AES-OFB and AES-CTR have a fixed 16-byte IV; this function
     *       cannot be used to select a different length for those modes.
     *
     * @note In OpenSSL, configure the length before supplying the IV
     *       or nonce bytes. This function does not supply, generate,
     *       pad or truncate an IV.
     *
     * @note For CCM, the nonce length determines the message-length
     *       field size L through L = 15 - value. A longer nonce leaves
     *       fewer bytes for that field and reduces the maximum message
     *       length.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation. The default implementation always throws.
     */
    virtual void set_iv_len(std::size_t value)
    {
        (void)value;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query the current input key length in bytes.
     *
     * @details Corresponds to OpenSSL's "keylen" parameter
     *          (OSSL_CIPHER_PARAM_KEYLEN)
     *          and EVP_CIPHER_CTX_get_key_length().
     *          Applicable to all block cipher modes, including ECB, CBC,
     *          CFB, OFB, CTR, GCM, CCM, OCB and XTS.
     *          The length depends on the selected cipher and mode.
     *
     * @return The input key length currently configured in the context.
     *         Examples in OpenSSL:
     *         - AES-128-CBC and AES-128-GCM: 16 bytes.
     *         - AES-192-CBC: 24 bytes.
     *         - AES-256-CBC: 32 bytes.
     *         - DES-CBC: 8 bytes, including parity bits.
     *         - DES-EDE3-CBC: 24 bytes, including parity bits.
     *         - AES-128-XTS: 32 bytes; AES-256-XTS: 64 bytes.
     *
     * @note XTS uses two keys. The returned length includes both,
     *       rather than describing either individual AES key.
     *
     * @note For variable-key-length ciphers, the current length may
     *       differ from the algorithm's default. Support for this query
     *       does not imply that @ref set_key_len() can change the length.
     *
     * @note This is the input key size, not the expanded key schedule
     *       size or a measure of security strength. For RC2, effective
     *       key bits are a separate parameter; see @ref get_keybits().
     *
     * @note A nonzero length does not indicate that a key has already
     *       been installed. This query does not return the key bytes.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual std::size_t get_key_len() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Set the input key length in bytes.
     *
     * @details Corresponds to OpenSSL's settable "keylen" parameter
     *          (OSSL_CIPHER_PARAM_KEYLEN)
     *          and EVP_CIPHER_CTX_set_key_length().
     *          For the parameter meaning and usage notes,
     *          see @ref get_key_len().
     *
     * @param[in] value Requested input key length in bytes.
     *                  For example, RC2-CBC can use 5, 8 or 16 bytes.
     *                  Accepted lengths depend on the cipher implementation.
     *
     * @note Changing the length is supported by variable-key-length
     *       ciphers such as RC2 and Blowfish, including their CBC modes.
     *       This capability depends on the cipher, not simply on the mode.
     *
     * @note For fixed-key-length ciphers, OpenSSL's
     *       EVP_CIPHER_CTX_set_key_length() accepts the existing length
     *       and rejects a different length. For example, AES-128-CBC
     *       accepts 16 bytes; setting 32 does not select AES-256-CBC.
     *
     * @note Configure the desired length before supplying the key bytes.
     *       This function does not supply, generate, pad or truncate a key.
     *
     * @note For RC2, input key length and effective key bits are separate
     *       parameters. Use @ref set_keybits() to configure the latter.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation. The default implementation always throws.
     */
    virtual void set_key_len(std::size_t value)
    {
        (void)value;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query the configured RC2 effective key length in bits.
     *
     * @details Corresponds to OpenSSL's "keybits" parameter
     *          (OSSL_CIPHER_PARAM_RC2_KEYBITS).
     *          Supported by RC2 implementations, including OpenSSL's
     *          ECB, CBC, CFB and OFB modes.
     *          This is an RC2-specific parameter, not a general query
     *          for the key size of ciphers such as AES or DES.
     *
     * @return The configured RC2 effective key length in bits.
     *         Typical values are 40, 64 and 128.
     *         OpenSSL defaults to 128 for ordinary RC2 implementations,
     *         40 for RC2-40-CBC, and 64 for RC2-64-CBC.
     *
     * @note This parameter controls RC2 key expansion. It is separate
     *       from the input key length returned by @ref get_key_len(),
     *       which is measured in bytes.
     *       For example, a 16-byte input key can be used with an
     *       effective key length of 40 bits.
     *
     * @note Encryption and decryption must use the same effective key
     *       length as well as the same key bytes. Changing this parameter
     *       changes the expanded key; it does not simply truncate the
     *       input key to the requested number of bits.
     *
     * @note The returned value is the bit count itself, not its ASN.1
     *       parameter encoding. For example, an effective key length
     *       of 128 bits returns 128, not the encoded RC2 parameter
     *       version value 58.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual std::size_t get_keybits() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Set the RC2 effective key length in bits.
     *
     * @details Corresponds to OpenSSL's settable "keybits" parameter
     *          (OSSL_CIPHER_PARAM_RC2_KEYBITS).
     *          For supported modes, parameter meaning, defaults and
     *          usage notes, see @ref get_keybits().
     *
     * @param[in] value RC2 effective key length in bits.
     *                  Typical values are 40, 64 and 128.
     *                  Supply the bit count itself, not its ASN.1 encoding.
     *
     * @note In OpenSSL, set this parameter before supplying the key.
     *       Setting it does not rebuild an existing expanded key.
     *       If a key has already been installed, supply the key again
     *       during initialization so that the new setting takes effect.
     *
     * @note This function does not change the input key length or
     *       supply key bytes. Use @ref set_key_len() to configure
     *       the input key length separately.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation. The default implementation always throws.
     */
    virtual void set_keybits(std::size_t value)
    {
        (void)value;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Set the MAC key for a composite cipher.
     *
     * @details Corresponds to OpenSSL's "mackey" parameter
     *          (OSSL_CIPHER_PARAM_AEAD_MAC_KEY).
     *          Supported by composite ciphers such as
     *          AES-128-CBC-HMAC-SHA1, AES-256-CBC-HMAC-SHA1,
     *          AES-128-CBC-HMAC-SHA256 and AES-256-CBC-HMAC-SHA256.
     *          Ordinary AES-CBC, GCM and CCM do not use this parameter.
     *
     * @param[in] in MAC key bytes, separate from the encryption key.
     * @param[in] inl Length of @p in in bytes. Typical TLS values are
     *                20 for HMAC-SHA1 and 32 for HMAC-SHA256.
     *                These are protocol examples, not a general restriction
     *                requiring every HMAC key to match the digest length.
     *
     * @note Supply the MAC key before processing records.
     *       This function does not set the AES encryption key, supply
     *       an expected MAC value, or configure the MAC output length.
     *
     * @note The 128 or 256 in the composite cipher name describes the
     *       AES encryption key size, not the MAC key size.
     *       For example, AES-128-CBC-HMAC-SHA256 can use a 16-byte AES
     *       key and a separate 32-byte TLS MAC key.
     *
     * @note OpenSSL's AES-CBC-HMAC ciphers require TLS record parameters,
     *       such as the record header information supplied through
     *       @ref set_tlsaad(), in addition to the encryption and MAC keys.
     *       They cannot be used through the same sequence of calls as GCM.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation. The default implementation always throws.
     */
    virtual void set_mackey(const std::uint8_t* in, std::size_t inl)
    {
        (void)in;
        (void)inl;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query the cipher's working mode.
     *
     * @details Corresponds to OpenSSL's "mode" parameter
     *          (OSSL_CIPHER_PARAM_MODE)
     *          and EVP_CIPHER_CTX_get_mode().
     *          Applicable to all modes represented by Mode.
     *
     * @return The working mode, for example:
     *         - AES-128-ECB: Mode::ECB.
     *         - AES-256-CBC: Mode::CBC.
     *         - AES-128-CTR: Mode::CTR.
     *         - AES-128-GCM: Mode::GCM.
     *         - AES-128-XTS: Mode::XTS.
     *
     * @note The result identifies the mode, not the underlying cipher,
     *       key length, or encryption/decryption direction.
     *       For example, AES-128-CBC and DES-CBC both return Mode::CBC.
     *
     * @note Variants may share the same mode value. For example,
     *       AES-CBC and AES-CBC-CTS both return Mode::CBC.
     *       Use @ref get_cts() and @ref get_cts_mode() to query
     *       ciphertext-stealing support and its selected variant.
     *
     * @note CFB, OFB and CTR retain their respective mode values even
     *       though they process data like stream ciphers; they do not
     *       return Mode::Stream.
     *
     * @note Mode uses unsigned long as its underlying type. Its values
     *       match OpenSSL's EVP_CIPH_*_MODE constants, with Mode::Stream
     *       matching EVP_CIPH_STREAM_CIPHER. An explicit cast is required
     *       to obtain the corresponding integer value.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual Mode get_mode() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query the cipher-specific position within the current block.
     *
     * @details Corresponds to OpenSSL's "num" parameter
     *          (OSSL_CIPHER_PARAM_NUM) and EVP_CIPHER_CTX_get_num().
     *          Used by modes such as full-block CFB, OFB and CTR to track
     *          the byte position within the current underlying block.
     *          Availability and meaning depend on the cipher implementation.
     *
     * @return The current position. For OpenSSL AES-CFB128, AES-OFB
     *         and AES-CTR, values range from 0 to 15.
     *         Starting from a freshly initialized context, processing
     *         5 bytes produces 5; processing another 11 bytes produces 0.
     *         For DES-CFB64 and DES-OFB, values range from 0 to 7.
     *
     * @note For these modes, zero indicates a block boundary, including
     *       the initial state. The value is not the total number of bytes
     *       processed and does not count completed blocks.
     *
     * @note This position refers to the underlying cipher block.
     *       It is not bounded by the processing granularity returned by
     *       @ref get_block_size(), which can be 1 for these modes.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual std::size_t get_num() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Set the cipher-specific position within the current block.
     *
     * @details Corresponds to OpenSSL's settable "num" parameter
     *          (OSSL_CIPHER_PARAM_NUM) and EVP_CIPHER_CTX_set_num().
     *          For supported modes, parameter meaning, value examples
     *          and usage notes, see @ref get_num().
     *
     * @param[in] value Position within the current underlying block.
     *                  Its meaning and valid range depend on the cipher
     *                  implementation, as described in @ref get_num().
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation. The default implementation always throws.
     */
    virtual void set_num(std::size_t value)
    {
        (void)value;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query whether block padding is enabled.
     *
     * @details Corresponds to OpenSSL's "padding" parameter
     *          (OSSL_CIPHER_PARAM_PADDING).
     *          The setting matters for modes that process complete
     *          blocks, such as ECB and CBC.
     *
     * @return true if padding is enabled; false if it is disabled.
     *         For example, OpenSSL AES-128-CBC defaults to true,
     *         whereas gmlib's AES-128-CBC defaults to false.
     *         Calling @ref set_padding(bool) "set_padding(true)" enables
     *         padding where the implementation supports it.
     *
     * @warning OpenSSL enables standard block padding by default.
     *          For compatibility with gmlib's existing API, gmlib's
     *          ECB and CBC implementations disable padding by default.
     *          Call @ref set_padding(bool) "set_padding(true)" when padding is
     *          required.
     *
     * @note With OpenSSL's standard padding enabled, AES-CBC can
     *       encrypt a message whose length is not a multiple of
     *       16 bytes. With padding disabled, such a message fails
     *       during finalization.
     *
     * @note This reports the padding setting, not the exact padding
     *       scheme an implementation applies. For modes such as CTR
     *       or GCM, the setting does not imply that plaintext will
     *       receive PKCS#7 padding.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual bool get_padding() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Enable or disable block padding.
     *
     * @details Corresponds to OpenSSL's "padding" parameter
     *          (OSSL_CIPHER_PARAM_PADDING)
     *          and EVP_CIPHER_CTX_set_padding().
     *          For supported modes, behavior and default-value
     *          differences, see @ref get_padding().
     *
     * @param[in] value true to enable padding; false to disable it.
     *
     * @note For gmlib's ECB and CBC implementations, true selects
     *       PKCS#7 padding and false selects no padding. Padding is
     *       disabled by default in these implementations; call this
     *       function with true when it is required.
     *
     * @note Configure padding before processing the message. OpenSSL
     *       calls EVP_CIPHER_CTX_set_padding() after selecting the cipher
     *       for encryption or decryption.
     *
     * @note With padding disabled, ECB and CBC require the complete
     *       message length to be a multiple of the block size.
     *       For stream-like modes such as CTR, setting this flag does
     *       not add PKCS#7 padding.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation. The default implementation always throws.
     */
    virtual void set_padding(bool value)
    {
        (void)value;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query the number of parallel cipher operations.
     *
     * @details Similar to the numpipes argument of OpenSSL's
     *          EVP_CipherPipelineEncryptInit() and
     *          EVP_CipherPipelineDecryptInit(), this value describes
     *          how many cipher operations are processed in parallel.
     *          Supported only by implementations that offer cipher
     *          pipelining and expose the configured count.
     *
     * @return The configured number of parallel operations.
     *         For example, a pipeline initialized with numpipes
     *         equal to 4 returns 4.
     *
     * @note This counts independent operations processed together,
     *       not blocks or bytes processed by one operation.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual std::size_t get_pipeline_count() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Get the authentication tags for parallel AEAD operations.
     *
     * @details Similar to OpenSSL's "pipeline-tag" parameter
     *          (OSSL_CIPHER_PARAM_PIPELINE_AEAD_TAG).
     *          Supported only when the implementation offers both
     *          cipher pipelining and AEAD tags.
     *
     * @return A borrowed array of read-only tag pointers.
     *         The array contains @ref get_pipeline_count() entries;
     *         each entry points to one operation's tag, whose length
     *         is reported by @ref get_tag_len().
     *
     * @note After parallel encryption has completed, copy every tag
     *       into caller-owned storage. Here @p ctx is the completed
     *       pipeline context:
     *       @code{.cpp}
     *       #include <vector>
     *
     *       const auto count = ctx.get_pipeline_count();
     *       const auto tag_len = ctx.get_tag_len();
     *       const auto tags = ctx.get_pipeline_tag();
     *
     *       std::vector<std::vector<std::uint8_t>> saved_tags;
     *       saved_tags.reserve(count);
     *       for (std::size_t i = 0; i < count; ++i) {
     *           saved_tags.emplace_back(tags[i], tags[i] + tag_len);
     *       }
     *       @endcode
     *       saved_tags[i] contains the tag bytes for operation i.
     *
     * @note The returned array and tag bytes belong to the context.
     *       Do not modify or free them. Copy tags that must be retained
     *       after the context changes or is destroyed.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual const std::uint8_t* const* get_pipeline_tag() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Supply authentication tags for parallel AEAD decryption.
     *
     * @details Similar to OpenSSL's "pipeline-tag" parameter
     *          (OSSL_CIPHER_PARAM_PIPELINE_AEAD_TAG).
     *          Supported only when the implementation offers both
     *          cipher pipelining and AEAD tags. For the number of
     *          operations and tag length, see @ref get_pipeline_count()
     *          and @ref get_tag_len().
     *
     * @param[in] tags Array of pointers in pipeline order.
     *                 Each pointer identifies one operation's expected
     *                 tag, with @ref get_tag_len() bytes.
     * @param[in] count Number of pointers in @p tags. It must equal
     *                  @ref get_pipeline_count(); for example, 4 for
     *                  a pipeline with four operations.
     *
     * @note Supply the expected tags before completing decryption.
     *       This function does not itself verify them.
     *
     * @note The implementation copies every tag before returning.
     *       The caller may reuse or release the pointer array and tag
     *       buffers after this call returns successfully.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation. The default implementation always throws.
     */
    virtual void set_pipeline_tag(const std::uint8_t* const* tags,
                                  std::size_t                count)
    {
        (void)tags;
        (void)count;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Generate an algorithm-specific random key.
     *
     * @details Similar to OpenSSL's "randkey" parameter
     *          (OSSL_CIPHER_PARAM_RANDOM_KEY).
     *          Supported by cipher implementations with
     *          @ref get_has_randkey() equal to true.
     *          In OpenSSL, these are DES and 3DES implementations;
     *          availability depends on the cipher, not its working mode.
     *
     * @param[out] out Buffer receiving the generated key.
     *                 It must have space for @ref get_key_len() bytes.
     *
     * @note OpenSSL examples are 8 bytes for DES-CBC and 24 bytes
     *       for DES-EDE3-CBC. Each DES key byte has odd parity.
     *
     * @note The caller must provide a sufficiently large buffer;
     *       this interface has no capacity argument to check.
     *       The function writes exactly @ref get_key_len() bytes.
     *
     * @note This function generates a new key; it neither exports
     *       the key currently installed in the context nor installs
     *       the generated key for an encryption or decryption operation.
     *       Supply the resulting bytes during initialization to use them.
     *
     * @note The output contains secret key material. Protect it and
     *       clear unneeded copies when finished.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation. The default implementation always throws.
     */
    virtual void get_randkey(std::uint8_t* out)
    {
        (void)out;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query the configured RC5 round count.
     *
     * @details Similar to OpenSSL's "rounds" parameter
     *          (OSSL_CIPHER_PARAM_ROUNDS).
     *          Supported by RC5 implementations, including OpenSSL's
     *          ECB, CBC, CFB and OFB modes.
     *
     * @return The configured number of RC5 rounds.
     *         OpenSSL supports 8, 12 and 16 rounds, with 12 as the default.
     *
     * @note This is an algorithm parameter, not a count of processed
     *       blocks or completed encryption operations.
     *
     * @note OpenSSL uses this parameter for RC5. It is not a general
     *       interface for querying the internal round count of
     *       algorithms such as AES or DES.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query. The default implementation always throws.
     */
    virtual unsigned int get_rounds() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Set the RC5 round count.
     *
     * @details Similar to OpenSSL's settable "rounds" parameter
     *          (OSSL_CIPHER_PARAM_ROUNDS).
     *          For supported modes, parameter meaning and defaults,
     *          see @ref get_rounds().
     *
     * @param[in] value Number of RC5 rounds. OpenSSL accepts 8, 12 or 16.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation. The default implementation always throws.
     */
    virtual void set_rounds(unsigned int value)
    {
        (void)value;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Configure repeated operations for performance testing.
     *
     * @details Similar to OpenSSL's settable "speed" parameter
     *          (OSSL_CIPHER_PARAM_SPEED).
     *          Supported by OpenSSL's AES-SIV and AES-GCM-SIV
     *          implementations.
     *
     * @param[in] value true to allow repeated encryption or decryption
     *                  operations on the same initialized context;
     *                  false to use the normal single-operation
     *                  restriction. OpenSSL defaults to false.
     *
     * @note Without this option, a second Update call that processes
     *       message data is rejected unless the context is reinitialized.
     *       The following OpenSSL example assumes an initialized
     *       AES-GCM-SIV encryption context and valid buffers:
     *       @code{.cpp}
     *       // Speed is disabled by default.
     *       int first = EVP_EncryptUpdate(ctx, out, &out_len, in, in_len);
     *       int second = EVP_EncryptUpdate(ctx, out, &out_len, in, in_len);
     *       // With valid inputs, first is 1 and second is 0.
     *
     *       // Enable repeated operations for benchmarking.
     *       EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_SET_SPEED, 1, nullptr);
     *       int repeated = EVP_EncryptUpdate(ctx, out, &out_len, in, in_len);
     *       // With valid inputs, repeated is 1.
     *       @endcode
     *       Each successful call processes a complete message.
     *       These calls do not concatenate their inputs into one message.
     *
     * @note This option is intended for performance testing.
     *       It is not a general switch for enabling faster encryption
     *       or hardware acceleration.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation.
     */
    virtual void set_speed(bool value)
    {
        (void)value;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Copy the authentication tag generated by encryption.
     *
     * @details Similar to OpenSSL's gettable "tag" parameter
     *          (OSSL_CIPHER_PARAM_AEAD_TAG) and EVP_CTRL_AEAD_GET_TAG.
     *          Supported by AEAD implementations such as GCM, CCM,
     *          OCB, SIV and GCM-SIV. Ordinary ECB, CBC, CFB, OFB,
     *          CTR and XTS modes do not provide authentication tags.
     *
     * @param[out] out Buffer receiving tag_len bytes.
     *                 Must provide at least tag_len writable bytes.
     * @param[in] tag_len Number of tag bytes to retrieve.
     *                    For example, AES-GCM commonly uses 16 bytes,
     *                    and AES-CCM uses 12 bytes by default.
     *                    AES-SIV and AES-GCM-SIV require 16 bytes.
     *
     * @note Retrieve the tag after encryption has completed.
     *       For decryption, supply the expected tag through
     *       @ref set_tag() instead.
     *
     * @note Tag length rules depend on the mode.
     *       CCM requires the configured tag length. OCB accepts
     *       16 bytes or the length previously configured through
     *       @ref set_tag(). See @ref get_tag_len() for the current
     *       configured length.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation.
     */
    virtual void get_tag(std::uint8_t* out, std::size_t tag_len) const
    {
        (void)out;
        (void)tag_len;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Set the expected authentication tag or configure its length.
     *
     * @details Similar to OpenSSL's settable "tag" parameter
     *          (OSSL_CIPHER_PARAM_AEAD_TAG) and EVP_CTRL_AEAD_SET_TAG.
     *          For supported modes and tag length information,
     *          see @ref get_tag().
     *
     * @param[in] in Expected authentication tag for decryption.
     *               For CCM and OCB, nullptr configures the tag length
     *               without supplying tag bytes.
     * @param[in] inl Tag length in bytes.
     *                For example, 16 for AES-SIV or AES-GCM-SIV.
     *
     * @note For GCM and OCB, set the expected tag before decryption
     *       Final. For CCM, SIV and GCM-SIV, set it before processing
     *       ciphertext.
     *
     * @note For CCM and OCB encryption, calling set_tag(nullptr, inl)
     *       selects the tag length before the IV is supplied.
     *       For GCM encryption, select the output tag length through
     *       the tag_len argument of @ref get_tag() instead.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation.
     */
    virtual void set_tag(const std::uint8_t* in, std::size_t inl)
    {
        (void)in;
        (void)inl;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query the authentication tag length in bytes.
     *
     * @details Similar to OpenSSL's gettable "taglen" parameter
     *          (OSSL_CIPHER_PARAM_AEAD_TAGLEN).
     *          Supported by AEAD implementations such as GCM, CCM,
     *          OCB, SIV and GCM-SIV.
     *
     * @return The current tag length, or the algorithm's default
     *         if no length has been configured.
     *         OpenSSL defaults to 16 bytes for AES-GCM and AES-OCB,
     *         and 12 bytes for AES-CCM.
     *         AES-SIV and AES-GCM-SIV always use 16 bytes.
     *
     * @note This query does not require a generated tag.
     *       Use @ref get_tag() to retrieve the tag bytes.
     *
     * @note For OpenSSL GCM encryption, requesting a shorter tag
     *       through @ref get_tag() does not change this value.
     *       For example, retrieving 12 bytes leaves it at 16.
     *       For GCM decryption, @ref set_tag() sets the expected
     *       tag length as well as its value.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query.
     */
    virtual std::size_t get_tag_len() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Access the MAC extracted during TLS record decryption.
     *
     * @details Similar to OpenSSL's gettable "tls-mac" parameter
     *          (OSSL_CIPHER_PARAM_TLS_MAC).
     *          Used by implementations supporting TLS record processing,
     *          such as AES-CBC with a separate record MAC.
     *          Ordinary CBC decryption alone does not extract a TLS MAC.
     *
     * @return A borrowed read-only pointer to the extracted MAC,
     *         or nullptr if no MAC is available.
     *         Its length is configured through @ref set_tls_mac_size().
     *         For example, a full HMAC-SHA1 is 20 bytes and a full
     *         HMAC-SHA256 is 32 bytes.
     *
     * @note For OpenSSL's generic TLS record processing, configure
     *       the protocol version through @ref set_tls_version()
     *       and the number of MAC bytes to extract through
     *       @ref set_tls_mac_size() before decrypting the record.
     *       The cipher does not infer the MAC algorithm from its
     *       encryption algorithm.
     *       Retrieve the MAC after the record's decryption Update call.
     *
     * @note This query does not compute or verify the record MAC.
     *       It does not retrieve the MAC key or an AEAD tag.
     *
     * @note Do not modify or free the returned memory.
     *       OpenSSL may store the MAC in the record buffer or in
     *       context-owned memory. Copy it before reusing the record
     *       buffer, processing another record or releasing the context.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query.
     */
    virtual const std::uint8_t* get_tls_mac() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Set the MAC length used for TLS record processing.
     *
     * @details Similar to OpenSSL's settable "tls-mac-size" parameter
     *          (OSSL_CIPHER_PARAM_TLS_MAC_SIZE).
     *          For supported implementations and MAC extraction details,
     *          see @ref get_tls_mac().
     *
     * @param[in] value Number of MAC bytes in the TLS record.
     *                  For example, 20 for a full HMAC-SHA1 or
     *                  32 for a full HMAC-SHA256.
     *
     * @note Set this value before processing the TLS record.
     *       It specifies how many MAC bytes to extract; it does not
     *       select a MAC algorithm or configure its key.
     *       The value must match the MAC length used by the record.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation.
     */
    virtual void set_tls_mac_size(std::size_t value)
    {
        (void)value;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query whether TLS multiblock processing is supported.
     *
     * @details Similar to OpenSSL's "tls-multi" parameter
     *          (OSSL_CIPHER_PARAM_TLS1_MULTIBLOCK) and
     *          EVP_CIPH_FLAG_TLS1_1_MULTIBLOCK.
     *          This capability is specific to TLS cipher implementations
     *          that support interleaved processing of multiple records.
     *
     * @return true if TLS multiblock processing is supported;
     *         false otherwise, for example for ordinary AES-CBC
     *         without TLS multiblock support.
     *
     * @note This reports whether the implementation supports TLS
     *       multiblock processing, not whether it is currently
     *       using that capability.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query.
     */
    virtual bool get_tls_multi() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Set the protocol version used for TLS record processing.
     *
     * @details Similar to OpenSSL's settable "tls-version" parameter
     *          (OSSL_CIPHER_PARAM_TLS_VERSION).
     *          Used by implementations supporting TLS record processing,
     *          such as AES-CBC with a separate record MAC.
     *
     * @param[in] value Protocol version identifier.
     *                  Examples are 0x0301 for TLS 1.0, 0x0302 for
     *                  TLS 1.1 and 0x0303 for TLS 1.2.
     *                  In OpenSSL's generic cipher implementation,
     *                  0 disables TLS-specific record processing.
     *
     * @note Set this value before processing records.
     *       It selects protocol-specific record handling, including
     *       padding rules. It does not negotiate a TLS connection
     *       or select a MAC algorithm.
     *
     * @note For TLS record MAC extraction, also configure
     *       @ref set_tls_mac_size(). See @ref get_tls_mac()
     *       for details.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation.
     */
    virtual void set_tls_version(unsigned int value)
    {
        (void)value;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Set the Additional Authenticated Data (AAD) for TLS
     *        multiblock processing.
     *
     * @details Similar to OpenSSL's settable "tls1multi_aad" parameter
     *          (OSSL_CIPHER_PARAM_TLS1_MULTIBLOCK_AAD).
     *          Requires a TLS cipher implementation with multiblock
     *          support. See @ref get_tls_multi().
     *
     * @param[in] in Buffer containing the 13-byte TLS multiblock AAD.
     *              Must provide at least 13 readable bytes.
     *              Bytes 0-7 contain the first record's sequence number.
     *              Byte 8 contains the record type.
     *              Bytes 9-10 contain the protocol version.
     *              Bytes 11-12 contain the input length, set to zero
     *              as specified by OpenSSL's parameter interface.
     *              Multibyte fields use network byte order.
     * @param[in] data_len Total input data length for the multiblock
     *                    operation, in bytes. Used when AAD bytes
     *                    11-12 are zero.
     *                    For OpenSSL's encryption operation, this is
     *                    the total plaintext length.
     *
     * @note For example, sequence number 1, application data and
     *       TLS 1.2 are represented as:
     *       @code
     *       00 00 00 00 00 00 00 01 17 03 03 00 00
     *       @endcode
     *
     * @note This input describes a batch of TLS records.
     *       It supplies the first record's sequence number and the
     *       shared record type and protocol version.
     *       Subsequent records use consecutive sequence numbers.
     *       Configure the record count through
     *       @ref set_tls1multi_interleave().
     *
     * @note Use @ref get_tls1multi_aadpacklen() to query the result
     *       of the AAD preparation operation.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation.
     */
    virtual void set_tls1multi_aad(const std::uint8_t* in, std::size_t data_len)
    {
        (void)in;
        (void)data_len;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query the TLS multiblock output length calculated during
     *        Additional Authenticated Data (AAD) preparation.
     *
     * @details Similar to OpenSSL's gettable "tls1multi_aadpacklen"
     *          parameter (OSSL_CIPHER_PARAM_TLS1_MULTIBLOCK_AAD_PACKLEN).
     *          Requires a TLS cipher implementation with multiblock
     *          support. See @ref get_tls_multi().
     *
     * @return The calculated total output length in bytes, including
     *         record headers, explicit IVs, MACs and padding.
     *         For example, splitting 4096 plaintext bytes into four
     *         TLS 1.2 records with AES-CBC-HMAC-SHA1 produces
     *         4 * (5 + 16 + 1024 + 20 + 12) = 4308 bytes:
     *         record header + explicit IV + plaintext + MAC + padding.
     *
     * @note Query this value after successful AAD preparation through
     *       @ref set_tls1multi_aad().
     *       The result depends on the input data length, record count
     *       and cipher. It is not the length of the 13-byte AAD.
     *
     * @note This is the calculated output size before encryption.
     *       Use @ref get_tls1multi_enclen() for the actual output length
     *       after encryption.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query.
     */
    virtual std::size_t get_tls1multi_aadpacklen() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Encrypt multiple TLS records and write the output.
     *
     * @details Similar to OpenSSL's settable "tls1multi_enc" parameter
     *          (OSSL_CIPHER_PARAM_TLS1_MULTIBLOCK_ENC).
     *          Requires a TLS cipher implementation with multiblock
     *          support. See @ref get_tls_multi().
     *          The operation computes record MACs, encrypts the data
     *          and constructs the TLS record headers.
     *
     * @param[out] out Buffer receiving the complete TLS records.
     * @param[out] outl Receives the total number of bytes written.
     * @param[in] outl_max Capacity of out in bytes.
     *                    Must accommodate the output size calculated
     *                    by @ref get_tls1multi_aadpacklen().
     *
     * @note Configure the record count through
     *       @ref set_tls1multi_interleave(), prepare the Additional
     *       Authenticated Data (AAD) through @ref set_tls1multi_aad(),
     *       and supply the input through @ref set_tls1multi_encin()
     *       before calling this function.
     *       The input length must match the length used during
     *       AAD preparation.
     *
     * @note Despite its get_ prefix, this function performs encryption
     *       and changes the context state. It does not merely retrieve
     *       previously generated output.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation.
     */
    virtual void get_tls1multi_enc(std::uint8_t* out,
                                   std::size_t*  outl,
                                   std::size_t   outl_max)
    {
        (void)out;
        (void)outl;
        (void)outl_max;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Supply the plaintext for TLS multiblock encryption.
     *
     * @details Similar to OpenSSL's settable "tls1multi_encin" parameter
     *          (OSSL_CIPHER_PARAM_TLS1_MULTIBLOCK_ENC_IN).
     *          For supported implementations and the encryption operation,
     *          see @ref get_tls1multi_enc().
     *
     * @param[in] in Contiguous plaintext buffer for the entire batch
     *              of TLS records. Must provide at least inl readable bytes.
     * @param[in] inl Total plaintext length in bytes.
     *               For example, 4096 for a batch containing
     *               4096 plaintext bytes.
     *
     * @note Supply the plaintext before calling @ref get_tls1multi_enc().
     *       Its length must match the data length used during
     *       preparation through @ref set_tls1multi_aad().
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation.
     */
    virtual void set_tls1multi_encin(const std::uint8_t* in, std::size_t inl)
    {
        (void)in;
        (void)inl;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query the output length of the last TLS multiblock encryption.
     *
     * @details Similar to OpenSSL's gettable "tls1multi_enclen" parameter
     *          (OSSL_CIPHER_PARAM_TLS1_MULTIBLOCK_ENC_LEN).
     *          For supported implementations and the encryption operation,
     *          see @ref get_tls1multi_enc().
     *
     * @return The total number of bytes produced for the batch of
     *         TLS records, including record headers, explicit IVs,
     *         MACs and padding.
     *         For example, four TLS 1.2 AES-CBC-HMAC-SHA1 records
     *         containing 4096 plaintext bytes produce 4308 output bytes.
     *
     * @note Query this value after a successful call to
     *       @ref get_tls1multi_enc(). It reports the same output length
     *       returned through that function's outl parameter.
     *
     * @note Use @ref get_tls1multi_aadpacklen() to query the calculated
     *       output size before encryption.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query.
     */
    virtual std::size_t get_tls1multi_enclen() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query the number of TLS records processed together.
     *
     * @details Similar to OpenSSL's "tls1multi_interleave" parameter
     *          (OSSL_CIPHER_PARAM_TLS1_MULTIBLOCK_INTERLEAVE).
     *          Requires a TLS cipher implementation with multiblock
     *          support. See @ref get_tls_multi().
     *
     * @return The number of records in a TLS multiblock batch.
     *         OpenSSL supports 4 or 8 records.
     *         For example, 4 means that one multiblock encryption
     *         operation processes four TLS records.
     *
     * @note This counts TLS records, not cipher blocks or bytes.
     *
     * @note AAD preparation through @ref set_tls1multi_aad()
     *       may update this value. Query it after successful
     *       preparation to obtain the selected record count.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query.
     */
    virtual std::size_t get_tls1multi_interleave() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Set the number of TLS records to process together.
     *
     * @details Similar to OpenSSL's settable "tls1multi_interleave"
     *          parameter (OSSL_CIPHER_PARAM_TLS1_MULTIBLOCK_INTERLEAVE).
     *          For supported implementations, parameter meaning and
     *          preparation behavior, see @ref get_tls1multi_interleave().
     *
     * @param[in] value Requested number of records in the batch.
     *                  OpenSSL supports 4 or 8.
     *
     * @note Configure this value before preparing the Additional
     *       Authenticated Data (AAD) through @ref set_tls1multi_aad().
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation.
     */
    virtual void set_tls1multi_interleave(std::size_t value)
    {
        (void)value;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query the maximum output size of one TLS multiblock record.
     *
     * @details Similar to OpenSSL's gettable "tls1multi_maxbufsz"
     *          parameter (OSSL_CIPHER_PARAM_TLS1_MULTIBLOCK_MAX_BUFSIZE).
     *          Requires a TLS cipher implementation with multiblock
     *          support. See @ref get_tls_multi().
     *
     * @return The maximum record size in bytes for the configured
     *         maximum send fragment, including the record header,
     *         explicit IV, MAC and padding.
     *         For example, AES-CBC-HMAC-SHA1 with a maximum plaintext
     *         fragment of 1024 bytes gives
     *         5 + 16 + 1024 + 20 + 12 = 1077 bytes.
     *
     * @note Configure @ref set_tls1multi_maxsndfrag() before this query.
     *
     * @note This value describes one record, not the entire batch.
     *       Use @ref get_tls1multi_aadpacklen() for the calculated
     *       batch output size after AAD preparation, or
     *       @ref get_tls1multi_enclen() for the actual output length
     *       after encryption.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query.
     */
    virtual std::size_t get_tls1multi_maxbufsz() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Set the maximum plaintext fragment size for TLS multiblock
     *        output buffer sizing.
     *
     * @details Similar to OpenSSL's settable "tls1multi_maxsndfrag"
     *          parameter (OSSL_CIPHER_PARAM_TLS1_MULTIBLOCK_MAX_SEND_FRAGMENT).
     *          For supported implementations and output size calculation,
     *          see @ref get_tls1multi_maxbufsz().
     *
     * @param[in] value Maximum plaintext fragment length per TLS record,
     *                  in bytes. For example, 1024 for a record carrying
     *                  at most 1024 plaintext bytes.
     *                  Excludes the record header, explicit IV, MAC
     *                  and padding.
     *
     * @note Set this value before calling @ref get_tls1multi_maxbufsz().
     *       It supplies the fragment size used to calculate the maximum
     *       output size of one record, not the total batch input length.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation.
     */
    virtual void set_tls1multi_maxsndfrag(std::size_t value)
    {
        (void)value;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Set the Additional Authenticated Data (AAD) for one TLS record.
     *
     * @details Similar to OpenSSL's settable "tlsaad" parameter
     *          (OSSL_CIPHER_PARAM_AEAD_TLS1_AAD).
     *          Used by TLS record implementations such as AES-GCM,
     *          AES-CCM and AES-CBC-HMAC-SHA1/SHA256.
     *
     * @param[in] in Buffer containing the 13-byte TLS record AAD.
     *              Must provide at least 13 readable bytes.
     *              Bytes 0-7 contain the record sequence number.
     *              Byte 8 contains the record type, such as 0x17
     *              for application data.
     *              Bytes 9-10 contain the protocol version, such as
     *              0x0303 for TLS 1.2.
     *              Bytes 11-12 contain the record length field.
     *              Multibyte fields use network byte order.
     *
     * @note Set the AAD before processing each record.
     *       This function supports both encryption and decryption.
     *
     * @note The length field follows the cipher's TLS processing rules.
     *       For OpenSSL TLS GCM encryption, it includes the plaintext
     *       and the 8-byte explicit IV, but excludes the tag.
     *       For decryption, it also includes the 16-byte tag.
     *
     * @note Use @ref get_tlsaadpad() to query the additional output
     *       length reported after setting the AAD.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation.
     */
    virtual void set_tlsaad(const std::uint8_t* in)
    {
        (void)in;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Query the TLS record overhead reported by AAD preparation.
     *
     * @details Similar to OpenSSL's gettable "tlsaadpad" parameter
     *          (OSSL_CIPHER_PARAM_AEAD_TLS1_AAD_PAD).
     *          Used by TLS record implementations such as AES-GCM,
     *          AES-CCM and AES-CBC-HMAC-SHA1/SHA256.
     *
     * @return The cipher-specific length in bytes reported after
     *         setting the Additional Authenticated Data (AAD).
     *         OpenSSL TLS GCM returns 16 for its authentication tag.
     *         TLS CCM returns the configured tag length.
     *
     * @note Query this value after a successful call to @ref set_tlsaad()
     *       for the current record.
     *
     * @note For OpenSSL AES-CBC-HMAC encryption, the value includes
     *       the MAC and TLS padding, including the padding-length byte.
     *       For example, AES-CBC-HMAC-SHA1 with 1024 plaintext bytes
     *       returns 20 + 12 = 32 bytes.
     *       For decryption, it reports the MAC length instead:
     *       20 bytes for SHA1 or 32 bytes for SHA256.
     *
     * @note The value excludes the record header and explicit IV.
     *       It is not the total record size or the AAD length.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query.
     */
    virtual std::size_t get_tlsaadpad() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Set the fixed part of the Initialization Vector (IV)
     *        used for TLS records.
     *
     * @details Similar to OpenSSL's settable "tlsivfixed" parameter
     *          (OSSL_CIPHER_PARAM_AEAD_TLS1_IV_FIXED).
     *          Supported by TLS GCM and CCM implementations.
     *
     * @param[in] in Buffer containing the fixed IV bytes.
     * @param[in] inl Fixed IV length in bytes.
     *               For TLS 1.2 AES-GCM and AES-CCM, use 4 bytes.
     *               The complete 12-byte IV consists of this fixed
     *               part followed by an 8-byte explicit part.
     *
     * @note Configure the fixed part before processing TLS records.
     *       It is shared across records using the same traffic key;
     *       the explicit part varies between records.
     *
     * @note OpenSSL GCM requires at least 4 fixed bytes and at least
     *       8 remaining bytes for the invocation field.
     *       During encryption, setting the fixed part also randomly
     *       initializes the remaining IV bytes.
     *       OpenSSL TLS CCM requires exactly 4 fixed bytes.
     *
     * @note OpenSSL GCM also accepts static_cast<std::size_t>(-1)
     *       as a special length that restores the complete IV.
     *       In that case, in must contain @ref get_iv_len() bytes.
     *       This special value is not supported by TLS CCM.
     *
     * @warning For TLS GCM record processing, use a 12-byte IV with
     *          a 4-byte fixed part and an 8-byte explicit part.
     *          OpenSSL may accept other IV lengths, but its TLS GCM
     *          record format still carries only 8 explicit IV bytes.
     *          For example, with a 16-byte IV and a 4-byte fixed part,
     *          encryption randomly initializes the remaining 12 bytes,
     *          but transmits only the last 8 bytes.
     *          The intervening 4 bytes are not transmitted, so a peer
     *          configured with only the same fixed part cannot
     *          reconstruct the complete IV reliably.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation.
     */
    virtual void set_tlsivfixed(const std::uint8_t* in, std::size_t inl)
    {
        (void)in;
        (void)inl;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Generate an IV for GCM encryption and copy its trailing bytes.
     *
     * @details Similar to OpenSSL's gettable "tlsivgen" parameter
     *          (OSSL_CIPHER_PARAM_AEAD_TLS1_GET_IV_GEN).
     *          Supported by GCM implementations with IV generation
     *          support. This operation is not provided by TLS CCM.
     *
     * @param[out] out Buffer receiving the trailing bytes of the IV.
     * @param[out] outl Receives the actual number of bytes written.
     * @param[in] outl_max Capacity of out in bytes. Must be greater than zero.
     *                    Writes min(outl_max, get_iv_len()) bytes.
     *                    Use 8 to retrieve the TLS GCM explicit IV.
     *
     * @note Set the encryption key and configure the fixed IV through
     *       @ref set_tlsivfixed() before calling this function.
     *
     * @note For a 12-byte IV, outl_max = 8 retrieves its last 8 bytes.
     *       outl_max >= 12 retrieves all 12 bytes and sets *outl to 12.
     *       Any remaining buffer capacity is left untouched.
     *
     * @note OpenSSL installs the current complete IV for the operation,
     *       copies the requested trailing bytes to the output, then
     *       increments the last 8 bytes as a big-endian counter for
     *       the next operation, regardless of the output length.
     *       It does not generate fresh random bytes on every call.
     *
     * @note Despite its get_ prefix, this function changes IV state.
     *       Repeated calls advance the counter rather than retrieve
     *       the same value.
     *
     * @throws std::invalid_argument If outl_max is zero.
     * @throws std::runtime_error If the implementation does not support
     *         this operation.
     */
    virtual void get_tlsivgen(std::uint8_t* out,
                              std::size_t*  outl,
                              std::size_t   outl_max)
    {
        (void)out;
        (void)outl;
        (void)outl_max;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Set the IV invocation field for GCM decryption.
     *
     * @details Similar to OpenSSL's settable "tlsivinv" parameter
     *          (OSSL_CIPHER_PARAM_AEAD_TLS1_SET_IV_INV).
     *          Supported by GCM implementations with this IV handling
     *          capability. This operation is not provided by TLS CCM.
     *
     * @param[in] in Buffer containing the invocation field received
     *              with the encrypted record.
     * @param[in] inl Number of bytes to copy into the end of the IV.
     *               For TLS 1.2 GCM, use the 8-byte explicit IV.
     *               Must be greater than zero and must not exceed
     *               @ref get_iv_len().
     *
     * @note Set the decryption key and configure the fixed IV through
     *       @ref set_tlsivfixed() before calling this function.
     *       Supply the invocation field before processing ciphertext.
     *
     * @note The supplied bytes replace the last inl bytes of the IV.
     *       The preceding bytes remain unchanged, and the complete IV
     *       is then installed for decryption.
     *       This operation does not increment the invocation field.
     *
     * @throws std::invalid_argument If inl is zero or exceeds the
     *         configured IV length.
     * @throws std::runtime_error If the implementation does not support
     *         this operation.
     */
    virtual void set_tlsivinv(const std::uint8_t* in, std::size_t inl)
    {
        (void)in;
        (void)inl;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Access the current Initialization Vector (IV) state.
     *
     * @details Similar to OpenSSL's gettable "updated-iv" parameter
     *          (OSSL_CIPHER_PARAM_UPDATED_IV).
     *          Supported by implementations exposing their current
     *          IV state, such as CBC, CFB, OFB and CTR.
     *
     * @return A borrowed read-only pointer to the current IV state.
     *         The length is @ref get_iv_len(), for example,
     *         16 bytes for AES-CBC or 8 bytes for DES-CBC.
     *
     * @note In CBC, the state is the most recently processed ciphertext
     *       block, or the initial IV before any block is processed.
     *       In OFB, it is the latest feedback block obtained by
     *       repeatedly encrypting the IV.
     *       The meaning of the state depends on the cipher mode.
     *
     * @note Use @ref get_iv() to access the original IV.
     *       This query accesses the current state without advancing it.
     *
     * @note Do not modify or free the returned memory.
     *       Its contents may change as cipher operations proceed.
     *       Copy the bytes if the current value must be preserved.
     *       The pointer must not be used after the context is destroyed.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this query.
     */
    virtual const std::uint8_t* get_updated_iv() const
    {
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Select bits or bytes as the CFB1 input length unit.
     *
     * @details Similar to OpenSSL's settable "use-bits" parameter
     *          (OSSL_CIPHER_PARAM_USE_BITS) and EVP_CIPH_FLAG_LENGTH_BITS.
     *          Used by CFB1 implementations, such as AES-CFB1.
     *          It does not apply to CFB8 or CFB128.
     *
     * @param[in] value true to interpret Update input lengths in bits;
     *                  false to interpret them in bytes.
     *                  OpenSSL defaults to false.
     *
     * @note For example, an input length of 13 means 13 bits when
     *       enabled, requiring at least 2 input bytes.
     *       When disabled, the same length means 13 input bytes.
     *
     * @note This changes the input length unit, not the CFB feedback
     *       size. Both settings still use one-bit feedback.
     *       Key and IV lengths remain measured in bytes.
     *
     * @throws std::runtime_error If the implementation does not support
     *         this operation.
     */
    virtual void set_use_bits(bool value)
    {
        (void)value;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }

    /**
     * @brief Select the standard used by SM4-XTS.
     *
     * @details Similar to OpenSSL's "xts_standard"
     *          (OSSL_CIPHER_PARAM_XTS_STANDARD) parameter.
     *          Supported for SM4-XTS. This is not a standard selector
     *          for AES-XTS.
     *
     * @param[in] in NUL-terminated standard name: "GB" for GB/T 17964-2021,
     *              or "IEEE" for IEEE Std 1619-2007.
     *              Must not be nullptr.
     *
     * @note OpenSSL defaults to "GB". The two standards use different
     *       representations for the XTS tweak update. Encryption and
     *       decryption must use the same standard.
     *
     * @throws std::runtime_error If the implementation does not support
     *                            this operation.
     */
    virtual void set_xts_standard(const char* in)
    {
        (void)in;
        throw std::runtime_error(std::string(__func__) + " is not supported");
    }
};

} // namespace block_cipher_mode

#endif
