/**
 * part of the code is "derived from Alfred Klomp's
 * https://github.com/aklomp/base64 (published under BSD) with minor
 * modifications by D. Lemire. "
 *
 * Copyright (c) 2013-2015, Alfred Klomp All rights reserved.
 */
#if defined(SUPPORT_BASE64_AVX2)

#ifndef BASE64_INTERNAL_BASE64_AVX2_H
#define BASE64_INTERNAL_BASE64_AVX2_H

#include <cstddef>
#include <cstdint>

namespace base64::internal::avx2 {

bool base64_is_b64(const char* in, std::size_t inl) noexcept;

std::size_t base64_encode_outl(std::size_t inl) noexcept;

std::size_t base64_encode_strl(std::size_t inl) noexcept;

std::size_t base64_decode_outl(const char* in, std::size_t inl) noexcept;

void base64_encode(char* out, const std::uint8_t* in, std::size_t inl) noexcept;

int base64_decode(std::uint8_t* out, const char* in, std::size_t inl) noexcept;

} // namespace base64::internal::avx2

#endif
#endif
