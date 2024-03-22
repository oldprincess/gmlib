#ifndef ASN1_ASN1_DUMP_H
#define ASN1_ASN1_DUMP_H

#include <cstddef>
#include <cstdint>

namespace asn1 {

/**
 * @brief       dump asn1 encoding to stdout
 * @param in    input asn1 encoding
 * @param inl   input length
 * @return      error code
 * @retval       0: Success
 * @retval      -1: Invalid Encoding
 * @retval      -2: Unsupport Encoding
 */
int asn1_dump(const std::uint8_t* in, std::size_t inl) noexcept;

} // namespace asn1

#endif