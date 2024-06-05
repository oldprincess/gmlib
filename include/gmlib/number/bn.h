#ifndef NUMBER_BN_H
#define NUMBER_BN_H

#include <gmlib/number/internal/bn_common.h>

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <vector>

namespace number {

namespace alg = number::internal::common;

class BigNum
{
private:
    alg::BigNum_st*            ctx_;
    std::pmr::memory_resource* mp_;

private:
    BigNum(std::size_t                bits = 0,
           std::pmr::memory_resource* mp   = std::pmr::get_default_resource())
    {
        mp_ = mp;
        if (alg::bn_alloc(&ctx_, bits, mp_) == -1)
        {
            throw std::runtime_error("err");
        }
        alg::bn_set_zero(ctx_);
    }

public:
    BigNum(const BigNum& other)
    {
        mp_ = other.mp_;
        if (alg::bn_alloc(&ctx_, other.ctx_->data_len * 32, mp_) == -1)
        {
            throw std::runtime_error("err");
        }
        if (alg::bn_cpy(ctx_, other.ctx_) == -1)
        {
            throw std::runtime_error("err");
        }
    }

    ~BigNum()
    {
        alg::bn_free(ctx_, mp_);
    }

    BigNum operator+(const BigNum& other) const
    {
        std::size_t max_ret_bits =
            32 * (std::max(ctx_->data_len, other.ctx_->data_len) + 1);
        BigNum ret = BigNum(max_ret_bits, mp_);
        if (alg::bn_add(ret.ctx_, ctx_, other.ctx_) == -1)
        {
            throw std::runtime_error("err in add");
        }
        return ret;
    }

    BigNum operator-(const BigNum& other) const
    {
        std::size_t max_ret_bits =
            32 * (std::max(ctx_->data_len, other.ctx_->data_len) + 1);
        BigNum ret = BigNum(max_ret_bits, mp_);
        if (alg::bn_sub(ret.ctx_, ctx_, other.ctx_) == -1)
        {
            throw std::runtime_error("err in sub");
        }
        return ret;
    }

    BigNum operator*(const BigNum& other) const
    {
        std::size_t max_ret_bits = 32 * (ctx_->data_len + other.ctx_->data_len);
        BigNum      ret          = BigNum(max_ret_bits, mp_);
        if (alg::bn_mul(ret.ctx_, ctx_, other.ctx_) == -1)
        {
            throw std::runtime_error("err in mul");
        }
        return ret;
    }

    BigNum operator/(const BigNum& other) const
    {
        std::size_t max_ret_bits = 32 * ctx_->data_len;
        BigNum      ret          = BigNum(max_ret_bits, mp_);
        if (alg::bn_div(ret.ctx_, ctx_, other.ctx_, mp_) == -1)
        {
            throw std::runtime_error("err in div");
        }
        return ret;
    }

    BigNum operator%(const BigNum& other) const
    {
        std::size_t max_ret_bits = 32 * other.ctx_->data_len;
        BigNum      ret          = BigNum(max_ret_bits, mp_);
        if (alg::bn_mod(ret.ctx_, ctx_, other.ctx_, mp_) == -1)
        {
            throw std::runtime_error("err in mod");
        }
        return ret;
    }

    void operator=(const BigNum& other)
    {
        if (ctx_ != nullptr)
        {
            alg::bn_free(ctx_, mp_);
        }
        if (alg::bn_alloc(&ctx_, other.ctx_->data_len * 32, mp_) == -1)
        {
            throw std::runtime_error("err in =");
        }
        if (alg::bn_cpy(ctx_, other.ctx_) == -1)
        {
            throw std::runtime_error("err in =");
        }
    }

    bool operator==(const BigNum& other) const noexcept
    {
        return alg::bn_cmp(ctx_, other.ctx_) == 0;
    }

    bool operator<(const BigNum& other) const noexcept
    {
        return alg::bn_cmp(ctx_, other.ctx_) < 0;
    }

    bool operator>(const BigNum& other) const noexcept
    {
        return alg::bn_cmp(ctx_, other.ctx_) > 0;
    }

    bool operator<=(const BigNum& other) const noexcept
    {
        return alg::bn_cmp(ctx_, other.ctx_) <= 0;
    }

    bool operator>=(const BigNum& other) const noexcept
    {
        return alg::bn_cmp(ctx_, other.ctx_) >= 0;
    }

    std::tuple<BigNum, BigNum> divmod(const BigNum& other) const
    {
        std::size_t max_ret1_bits = 32 * ctx_->data_len;
        std::size_t max_ret2_bits = 32 * other.ctx_->data_len;
        BigNum      ret1          = BigNum(max_ret1_bits, mp_);
        BigNum      ret2          = BigNum(max_ret2_bits, mp_);
        if (alg::bn_divmod(ret1.ctx_, ret2.ctx_, ctx_, other.ctx_, mp_) == -1)
        {
            throw std::runtime_error("err in divmod");
        }
        return std::make_tuple(ret1, ret2);
    }

    std::string to_str(int radix = 10) const
    {
        char* tmp = (char*)mp_->allocate(ctx_->data_len * 32 + 1);
        if (alg::bn_to_str(tmp, ctx_, radix, mp_) == -1)
        {
            throw std::runtime_error("err in to_str");
        }
        std::string ret = std::string(tmp);
        mp_->deallocate(tmp, ctx_->data_len * 32 + 1);
        return ret;
    }

    std::size_t bits_lenth() const noexcept
    {
        return alg::bn_bits_length(ctx_);
    }

    int test(std::size_t idx) const noexcept
    {
        return alg::bn_test(ctx_, idx);
    }

    std::vector<std::uint8_t> to_bytes(std::size_t bytes_len,
                                       bool        is_big_endian = true) const
    {
        std::vector<std::uint8_t> ret;
        ret.resize(bytes_len);
        if (alg::bn_to_bytes(ret.data(), bytes_len, ctx_, is_big_endian) == -1)
        {
            throw std::runtime_error("err in to_bytes");
        }
        return ret;
    }

    static BigNum from_str(
        const std::string&         s,
        int                        radix = 10,
        std::pmr::memory_resource* mp    = std::pmr::get_default_resource())
    {
        BigNum ret = BigNum(s.length() * radix, mp);
        if (alg::bn_from_str(ret.ctx_, s.c_str(), radix) == -1)
        {
            throw std::runtime_error("err in to_str");
        }
        return ret;
    }

    static BigNum from_bytes(
        const std::vector<std::uint8_t>& bytes,
        bool                             is_big_endian = true,
        std::pmr::memory_resource*       mp = std::pmr::get_default_resource())
    {
        BigNum ret = BigNum(bytes.size() * 8, mp);
        if (alg::bn_from_bytes(ret.ctx_, bytes.data(), bytes.size(),
                               is_big_endian) == -1)
        {
            throw std::runtime_error("err in from_bytes");
        }
        return ret;
    }

    static BigNum from_uint32(
        std::uint32_t              n,
        std::pmr::memory_resource* mp = std::pmr::get_default_resource())
    {
        BigNum ret = BigNum(32, mp);
        if (alg::bn_from_u32(ret.ctx_, n) == -1)
        {
            throw std::runtime_error("err in from_uint32");
        }
        return ret;
    }
};

} // namespace number

#endif