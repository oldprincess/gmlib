#include <gmlib/block_cipher_mode/ctr_mode.h>

#include <cstring>

#include "sm4.h"
#include "test.h"

using namespace block_cipher_mode;
using SM4CtrEncryptor = CtrEncryptor<SM4>;
using SM4CtrDecryptor = CtrDecryptor<SM4>;

static std::uint8_t iv[16] = {
    0x88, 0x80, 0xbd, 0xd8, 0xa0, 0x19, 0xc3, 0x20,
    0xe3, 0x02, 0x68, 0x25, 0x0f, 0xc5, 0x52, 0x5c,
};
static std::uint8_t user_key[16] = {
    0x02, 0xad, 0x71, 0x9f, 0x97, 0x05, 0xd7, 0x9c,
    0x29, 0x50, 0xfc, 0xcf, 0x61, 0x85, 0x23, 0x7d,
};
static std::uint8_t pt[1024] = {
    0xcc, 0xc6, 0x91, 0x46, 0xfd, 0xd9, 0x5c, 0x2a, 0x25, 0xc8, 0xb3, 0x38,
    0xfa, 0xcd, 0xd1, 0x09, 0xad, 0xcc, 0x84, 0x0c, 0xf1, 0x94, 0x13, 0x26,
    0x39, 0xb9, 0xa9, 0x2b, 0xe7, 0xa4, 0xa5, 0xb6, 0x7f, 0xf8, 0x11, 0x28,
    0xeb, 0x18, 0xfa, 0x1e, 0x83, 0xf4, 0xde, 0xcc, 0xd6, 0x48, 0x73, 0x7e,
    0xb2, 0xa6, 0xf8, 0x46, 0x2e, 0x34, 0x32, 0x34, 0x11, 0xd5, 0x78, 0xe5,
    0x5c, 0x38, 0x2a, 0x3c, 0x45, 0x0a, 0x7e, 0x20, 0x55, 0xff, 0xe9, 0xe8,
    0x5f, 0x32, 0xd0, 0xa2, 0xf4, 0x67, 0xec, 0xb8, 0x53, 0x44, 0x94, 0xbe,
    0xc7, 0x20, 0xcc, 0x1e, 0xfe, 0x71, 0x77, 0x3f, 0x5c, 0x8a, 0x1d, 0x0d,
    0x2b, 0xf5, 0x42, 0xf2, 0x0a, 0x42, 0x19, 0x3a, 0xf1, 0x99, 0xed, 0x12,
    0x4b, 0x76, 0x94, 0x5b, 0x6b, 0xa4, 0xdf, 0x9a, 0xa6, 0xd8, 0xa6, 0x26,
    0x78, 0xd9, 0x80, 0xb3, 0x92, 0xf3, 0x83, 0xaf, 0x45, 0x34, 0x8b, 0xe5,
    0x34, 0x6c, 0xc7, 0xb9, 0xea, 0x90, 0x34, 0xdb, 0x73, 0x61, 0x9a, 0xa6,
    0x2b, 0xa2, 0x7e, 0x3a, 0x8d, 0x66, 0x77, 0xbf, 0xc8, 0x91, 0xcd, 0x9c,
    0xd7, 0x61, 0x6d, 0xa9, 0xd4, 0x27, 0x5f, 0x51, 0x60, 0x52, 0x4c, 0xae,
    0x9c, 0x12, 0xc7, 0x06, 0x5b, 0xd5, 0x21, 0xd1, 0x15, 0x72, 0xb0, 0xb4,
    0x5a, 0xc9, 0x80, 0xcb, 0x6f, 0xf8, 0xc5, 0x65, 0x45, 0xf8, 0xa5, 0xd2,
    0x85, 0x91, 0xf3, 0x5b, 0x81, 0xbe, 0x76, 0x9e, 0xba, 0x88, 0x81, 0x0d,
    0xa8, 0x52, 0xcb, 0x86, 0xf0, 0x81, 0x3e, 0xf9, 0x42, 0xc0, 0xde, 0xef,
    0x13, 0xd1, 0xaf, 0xbe, 0x87, 0x95, 0x00, 0x6d, 0x87, 0x19, 0x26, 0x0c,
    0x9e, 0xca, 0x89, 0x1d, 0x52, 0xa0, 0x46, 0xe9, 0x26, 0x69, 0x60, 0xea,
    0xd2, 0x25, 0x8c, 0xe6, 0xd3, 0xd6, 0x31, 0x3d, 0x56, 0xbf, 0xb2, 0xc3,
    0x0a, 0x1d, 0x7d, 0x1e, 0xae, 0x20, 0x9b, 0xad, 0x2c, 0x68, 0x39, 0x4a,
    0xa6, 0x0e, 0x1f, 0xec, 0xdb, 0x82, 0x2f, 0xe5, 0x59, 0xd0, 0xd9, 0x9a,
    0x49, 0x65, 0x8a, 0x44, 0x45, 0xae, 0xb0, 0x85, 0xfc, 0x45, 0xa7, 0x75,
    0xe0, 0xf1, 0xd3, 0x73, 0xf5, 0x72, 0xa0, 0x08, 0x56, 0x36, 0x44, 0x69,
    0x16, 0x17, 0xc7, 0x41, 0xe3, 0x67, 0xb5, 0xaf, 0x86, 0xef, 0x5c, 0xaa,
    0xac, 0x5d, 0xac, 0xfb, 0x1c, 0x5c, 0x76, 0x06, 0x4c, 0x58, 0x6c, 0xee,
    0xb6, 0x22, 0x23, 0x08, 0xa7, 0x04, 0xd3, 0xdf, 0xf9, 0x47, 0x88, 0x1c,
    0x40, 0xd5, 0x4d, 0x5b, 0x58, 0x41, 0x75, 0xfa, 0xea, 0xf0, 0xed, 0xfe,
    0x4c, 0xd8, 0x26, 0xe7, 0x93, 0x47, 0x25, 0x58, 0x68, 0xdc, 0x93, 0x44,
    0x3a, 0x34, 0x9f, 0xc7, 0x72, 0xc7, 0x9b, 0xc1, 0x22, 0xfe, 0xd0, 0xb2,
    0xa3, 0x99, 0x10, 0xf4, 0xf8, 0xcb, 0xa1, 0x3a, 0x66, 0x12, 0xfb, 0xac,
    0xa7, 0x75, 0x1b, 0x3d, 0x69, 0x1f, 0xbe, 0x97, 0x69, 0xbc, 0x35, 0xef,
    0x25, 0x20, 0x94, 0xb3, 0x06, 0x96, 0x58, 0x76, 0x59, 0xa5, 0xea, 0x7f,
    0xe8, 0x9b, 0xfc, 0x25, 0x20, 0xc5, 0xd5, 0x93, 0x26, 0x34, 0x39, 0x6e,
    0x70, 0xf6, 0x49, 0x0d, 0x07, 0x9c, 0xd5, 0x81, 0x9c, 0xb5, 0x42, 0xd1,
    0xf5, 0x4e, 0xf5, 0xee, 0x37, 0xd3, 0x17, 0x6b, 0x05, 0x40, 0x70, 0x09,
    0x2d, 0x53, 0x24, 0x31, 0x81, 0x2f, 0x30, 0xe6, 0x99, 0x36, 0x3b, 0x09,
    0xc2, 0xdd, 0x5c, 0xe1, 0x94, 0xc7, 0xb0, 0xb2, 0x60, 0xb4, 0x8c, 0xa4,
    0xc4, 0xbc, 0xd6, 0xeb, 0xca, 0x14, 0xa4, 0xe6, 0x3f, 0xd5, 0xe0, 0xc1,
    0xea, 0x8d, 0x4b, 0xcf, 0x66, 0xd2, 0x57, 0xa3, 0xe2, 0xe4, 0xc0, 0xe8,
    0x25, 0x10, 0x4e, 0xd6, 0xb7, 0xfc, 0x26, 0x2f, 0x89, 0x4b, 0xc3, 0xcf,
    0x99, 0x19, 0x20, 0x3d, 0x05, 0x5e, 0xfe, 0xa8, 0x7b, 0x4b, 0x38, 0x81,
    0x54, 0x90, 0x09, 0xe7, 0x93, 0x9b, 0xe2, 0xfd, 0x3b, 0xa5, 0xb0, 0x93,
    0xc7, 0x2e, 0x51, 0x66, 0x23, 0x5d, 0x27, 0x0a, 0x0a, 0x65, 0x9d, 0xa1,
    0x8c, 0x1f, 0xc8, 0xff, 0xe3, 0x0e, 0x02, 0xd5, 0x25, 0xed, 0x6f, 0x10,
    0x7e, 0x50, 0x79, 0x0c, 0x10, 0xe4, 0xc9, 0x4f, 0x24, 0x8a, 0xfe, 0xf2,
    0x1e, 0xb1, 0xc4, 0x9a, 0xc0, 0x35, 0x8b, 0x15, 0x20, 0x20, 0x2e, 0xed,
    0xb1, 0xb8, 0xfb, 0x0e, 0xab, 0x66, 0xa5, 0xda, 0x19, 0xbe, 0x4b, 0xbb,
    0xce, 0xfd, 0xc7, 0x30, 0xb0, 0x3a, 0xb7, 0x60, 0xbe, 0x51, 0x21, 0x07,
    0x50, 0xf0, 0x15, 0x0c, 0x77, 0xa2, 0xbf, 0x9a, 0x9d, 0x6d, 0xcf, 0x26,
    0x8b, 0xdb, 0x0a, 0xa1, 0x9e, 0x58, 0x0d, 0xe8, 0x16, 0xc1, 0xed, 0x6f,
    0x28, 0xb0, 0x77, 0x19, 0xe2, 0x10, 0xb2, 0x58, 0xc5, 0xff, 0xbe, 0x32,
    0x47, 0x9f, 0x38, 0x39, 0x08, 0xb0, 0x63, 0x14, 0x5d, 0xf9, 0xd0, 0xbc,
    0x9f, 0x66, 0x79, 0x9f, 0xe2, 0x48, 0xc3, 0x08, 0x14, 0xa4, 0xd9, 0x85,
    0x16, 0x8b, 0x9b, 0x29, 0x8f, 0x28, 0x4a, 0x97, 0xf2, 0xb0, 0x94, 0x98,
    0x80, 0x9a, 0xc1, 0x13, 0x49, 0xaa, 0xb6, 0x3a, 0x3e, 0x2c, 0x3e, 0x97,
    0x72, 0xfc, 0xdf, 0xd5, 0x33, 0x58, 0xe9, 0x0a, 0x41, 0xcc, 0xd2, 0x7a,
    0x7d, 0x72, 0x1e, 0x65, 0x6e, 0x6b, 0x1b, 0x75, 0x34, 0x70, 0x3c, 0x74,
    0x0f, 0x04, 0x34, 0x73, 0x41, 0x7a, 0x55, 0x4a, 0x1e, 0x44, 0x7a, 0xbe,
    0xe7, 0xbc, 0x72, 0x9b, 0x4a, 0x48, 0x4d, 0xbe, 0xb0, 0xf3, 0x10, 0x94,
    0xf9, 0x64, 0xe2, 0xba, 0xcf, 0x10, 0xc5, 0xc0, 0x2e, 0x01, 0x01, 0x59,
    0x43, 0x67, 0x37, 0xc3, 0x41, 0x58, 0x3a, 0xe1, 0xbe, 0xbc, 0xc5, 0x42,
    0x3f, 0x25, 0x6a, 0x24, 0x1c, 0xfb, 0x16, 0x64, 0x2c, 0xc0, 0x34, 0xbb,
    0xa4, 0xe4, 0xaa, 0x66, 0xa2, 0xa9, 0x18, 0x8d, 0xf1, 0x37, 0x1e, 0x3d,
    0xe2, 0xbc, 0xd0, 0x3a, 0xd9, 0xe1, 0xc0, 0x36, 0xb2, 0xa4, 0x90, 0xb1,
    0xbd, 0x39, 0x7c, 0x82, 0x41, 0xd0, 0xfe, 0x9a, 0x83, 0x1d, 0x14, 0x59,
    0x36, 0x83, 0x5e, 0x02, 0x2b, 0x55, 0xef, 0x56, 0x45, 0xca, 0xf8, 0x15,
    0xfc, 0x0f, 0xdd, 0x2f, 0xa6, 0x46, 0x28, 0x7d, 0x3c, 0x7b, 0xd3, 0xb3,
    0x5b, 0x45, 0x11, 0x5d, 0x66, 0x3a, 0xfa, 0xd6, 0xe8, 0x0a, 0x3a, 0xa3,
    0x35, 0xa2, 0xab, 0xe7, 0x37, 0x1b, 0x87, 0x25, 0x27, 0x89, 0xf5, 0x2c,
    0x06, 0xe1, 0xbb, 0xaf, 0x76, 0x82, 0x79, 0xfd, 0x74, 0xc4, 0x86, 0xe0,
    0x45, 0xef, 0x58, 0xf0, 0xc1, 0x4f, 0x3c, 0x29, 0xbb, 0x97, 0xf8, 0x54,
    0xed, 0x82, 0x7c, 0x8c, 0x59, 0xd5, 0xae, 0x28, 0x3f, 0xac, 0x8e, 0x8a,
    0x2a, 0x82, 0x0c, 0xde, 0x41, 0xec, 0xf5, 0x1e, 0x32, 0x76, 0xb3, 0xda,
    0x7d, 0x43, 0xe8, 0x8e, 0x3e, 0x9f, 0x80, 0x0c, 0x66, 0x91, 0xee, 0x28,
    0xdf, 0x3a, 0x81, 0xab, 0xb7, 0x13, 0x4c, 0x67, 0x7d, 0x5e, 0x61, 0xb0,
    0x04, 0xf1, 0xb7, 0x0d, 0xd9, 0x47, 0xdc, 0xc4, 0x33, 0xbc, 0xb2, 0x22,
    0xf1, 0x0b, 0x65, 0x65, 0x17, 0xb6, 0xd8, 0x1d, 0x29, 0xa3, 0x85, 0xc4,
    0xea, 0x64, 0xb8, 0x5b, 0x15, 0x2e, 0xa7, 0x0f, 0x69, 0x88, 0xfa, 0x57,
    0x48, 0x21, 0x88, 0x6c, 0x5f, 0x8d, 0x8e, 0xf9, 0xbf, 0x9a, 0x3a, 0xc9,
    0x86, 0x4e, 0xe8, 0x79, 0xae, 0x56, 0x7c, 0x5e, 0x43, 0xdd, 0x82, 0x48,
    0x23, 0x83, 0x5c, 0xd9, 0xca, 0x63, 0x39, 0xf8, 0x18, 0x67, 0x42, 0xde,
    0xd7, 0xe1, 0x0c, 0x12, 0x88, 0x45, 0xfc, 0x20, 0xe9, 0xcf, 0x0d, 0xd8,
    0xa0, 0x56, 0x09, 0xe7, 0xf3, 0x75, 0xe4, 0x8f, 0x99, 0xf5, 0xb3, 0x86,
    0x83, 0x6a, 0x4f, 0xd6,
};
static std::uint8_t ct[1024] = {
    0xaa, 0xc9, 0xb9, 0x10, 0xe0, 0x19, 0xd4, 0xc0, 0xbf, 0xcc, 0xf3, 0x7e,
    0xfd, 0x7b, 0xbe, 0x38, 0xfa, 0xaa, 0xf2, 0x17, 0x70, 0xab, 0x43, 0x4e,
    0x15, 0xee, 0x4f, 0x3d, 0x98, 0xd6, 0x65, 0x79, 0xff, 0x96, 0x26, 0x16,
    0x9f, 0x95, 0x9d, 0x22, 0xb9, 0x82, 0x84, 0x80, 0x99, 0xa7, 0x5e, 0x09,
    0x05, 0x09, 0xb9, 0xdb, 0x15, 0x63, 0xc8, 0x34, 0x1a, 0x46, 0x65, 0xd4,
    0xa2, 0x7d, 0x47, 0xcb, 0x55, 0x9d, 0x14, 0x58, 0xbe, 0x66, 0x76, 0x73,
    0x41, 0xd3, 0x90, 0x66, 0xbe, 0xe3, 0xa9, 0x34, 0xcd, 0x00, 0xee, 0x2f,
    0xac, 0x63, 0x7b, 0x05, 0x0f, 0xf0, 0x04, 0xb3, 0x25, 0x04, 0xc6, 0xd4,
    0x4c, 0xe5, 0x23, 0xbc, 0xf8, 0xb9, 0x9e, 0x93, 0xbc, 0x74, 0x54, 0xf2,
    0x7a, 0xd1, 0x4a, 0xd5, 0x8f, 0x4b, 0xdc, 0xd1, 0xaa, 0xb0, 0x1f, 0xdc,
    0x6f, 0xe2, 0xb6, 0xfd, 0xc2, 0xd4, 0xf0, 0xaa, 0x10, 0x42, 0x74, 0xde,
    0x39, 0x81, 0x77, 0x39, 0xd4, 0xee, 0x2c, 0x86, 0x62, 0x01, 0x73, 0x9c,
    0x53, 0x53, 0x81, 0xc6, 0x21, 0x3e, 0xdb, 0x30, 0xdc, 0xfd, 0xcb, 0xb9,
    0x9a, 0x35, 0x21, 0x7e, 0x1b, 0x36, 0x61, 0xd6, 0x55, 0xdf, 0x0f, 0xf6,
    0xf3, 0x73, 0x31, 0xc2, 0xda, 0x5c, 0xa8, 0xf4, 0x99, 0x9e, 0xd1, 0xf8,
    0x38, 0xe3, 0x55, 0x1e, 0x15, 0x0f, 0xa8, 0x8c, 0x0b, 0xe7, 0x08, 0xb4,
    0xc6, 0xfa, 0x80, 0xb9, 0x23, 0x57, 0x60, 0xf9, 0x49, 0x18, 0x41, 0x80,
    0x6d, 0xd7, 0x9b, 0x29, 0x1f, 0xd3, 0x0b, 0x8b, 0x03, 0x94, 0xaa, 0xe8,
    0xef, 0xb7, 0xce, 0xd3, 0xe2, 0x31, 0xad, 0xcf, 0x55, 0x19, 0x74, 0xd0,
    0xd5, 0x80, 0x60, 0xd0, 0x43, 0x70, 0xa4, 0x3e, 0xa4, 0xfc, 0xa0, 0x6d,
    0x85, 0xe3, 0xa1, 0xe8, 0x95, 0xea, 0xe3, 0x3a, 0x4c, 0xf6, 0xd6, 0x18,
    0x7c, 0x14, 0xda, 0xe9, 0x95, 0xbb, 0x51, 0x46, 0x42, 0x88, 0xef, 0xa8,
    0x2b, 0xfd, 0x01, 0x79, 0x01, 0x2d, 0x49, 0x99, 0x3e, 0x10, 0x36, 0x5d,
    0x6d, 0xff, 0x8a, 0xf7, 0x18, 0xac, 0x3b, 0x1e, 0x7b, 0x85, 0x91, 0x81,
    0x18, 0xf6, 0x17, 0xc0, 0x2c, 0xc6, 0xcb, 0x19, 0x89, 0x72, 0xe7, 0x70,
    0x0f, 0x01, 0xc5, 0x55, 0x03, 0xe8, 0x89, 0xe1, 0xe5, 0x15, 0xb0, 0x46,
    0x7b, 0xf4, 0x28, 0x6c, 0xb2, 0x4e, 0xe3, 0xac, 0xd5, 0xee, 0x47, 0x8c,
    0x52, 0x81, 0xcc, 0x6e, 0x0d, 0xcd, 0x57, 0xba, 0x1d, 0x46, 0xc5, 0x7f,
    0x7b, 0x30, 0xb3, 0xa4, 0x3d, 0xea, 0x3f, 0x2f, 0x5e, 0x9c, 0xdb, 0x61,
    0xbe, 0xcd, 0x93, 0x26, 0xb9, 0xac, 0xc0, 0x10, 0x3a, 0x8b, 0xba, 0x63,
    0xd1, 0xad, 0xc7, 0xf2, 0x13, 0x71, 0x53, 0xd9, 0x4b, 0xbc, 0xc0, 0xd5,
    0xe0, 0xb5, 0x59, 0x71, 0xff, 0x79, 0x20, 0xa9, 0x87, 0x6d, 0x54, 0x05,
    0xf7, 0xaa, 0x29, 0xee, 0x59, 0xa6, 0xe3, 0x5e, 0x68, 0x97, 0x48, 0x76,
    0xa0, 0x9a, 0xbf, 0xaa, 0xb9, 0xca, 0xbd, 0xb7, 0x85, 0x39, 0xb6, 0x4b,
    0x45, 0xbe, 0x4e, 0xe9, 0xd7, 0xdd, 0x9d, 0x2c, 0x0a, 0x5a, 0xcb, 0xf4,
    0xa9, 0xb6, 0x8b, 0x2f, 0xd2, 0x98, 0xce, 0x9d, 0x77, 0x51, 0x4f, 0x81,
    0x46, 0x73, 0xa0, 0xf5, 0x3c, 0xf1, 0x69, 0xab, 0x04, 0xe9, 0xf2, 0xb9,
    0x8e, 0xa2, 0xfe, 0x76, 0x79, 0xca, 0x0a, 0xae, 0x12, 0x1b, 0x37, 0x93,
    0x28, 0xfd, 0x1b, 0x27, 0xde, 0xd0, 0x32, 0x6f, 0xdf, 0x43, 0x46, 0x80,
    0x96, 0x14, 0xb4, 0x65, 0x04, 0x1c, 0x2d, 0x6b, 0xcc, 0x1f, 0x73, 0xde,
    0x0e, 0xef, 0x59, 0xc5, 0xf1, 0x7a, 0xa3, 0x99, 0x8b, 0xaa, 0xbb, 0x8b,
    0x97, 0x60, 0x8b, 0x7e, 0x6c, 0x73, 0x31, 0x42, 0x76, 0xdf, 0x69, 0x02,
    0xcd, 0x0d, 0x0b, 0x87, 0xa1, 0x5c, 0x44, 0x8b, 0xb9, 0xa7, 0x48, 0xf8,
    0x7e, 0xcc, 0xf0, 0xdb, 0x08, 0xd6, 0x1b, 0x10, 0xec, 0xcd, 0xa9, 0x34,
    0x90, 0x86, 0x53, 0x59, 0x93, 0x23, 0xd8, 0x44, 0x51, 0x4a, 0x7a, 0x5e,
    0x48, 0x8e, 0xc5, 0x95, 0xcc, 0x46, 0xcb, 0xbc, 0x17, 0x9d, 0xa4, 0x28,
    0xeb, 0x0c, 0x65, 0xda, 0x3a, 0x0a, 0x06, 0xbe, 0xc7, 0xc8, 0x38, 0x85,
    0x37, 0x77, 0xcc, 0xce, 0x90, 0xfb, 0xe8, 0xad, 0xda, 0xc6, 0x9d, 0x59,
    0x83, 0xda, 0xb2, 0x01, 0x12, 0xce, 0x0b, 0xcb, 0x63, 0x12, 0x2f, 0x07,
    0x1d, 0x86, 0x94, 0xb9, 0x98, 0xac, 0x58, 0xf9, 0x26, 0x2b, 0xe5, 0x37,
    0xa1, 0xb2, 0x25, 0x51, 0xd0, 0xc3, 0xa3, 0x8d, 0xf8, 0x9d, 0xaa, 0x20,
    0xa9, 0xef, 0x9c, 0xfb, 0x4a, 0x5d, 0xf5, 0x67, 0xd5, 0xa0, 0x10, 0x9f,
    0x98, 0x34, 0xc3, 0x61, 0x54, 0x84, 0xa6, 0x72, 0xc5, 0x32, 0x4f, 0x69,
    0x24, 0x09, 0x33, 0x11, 0xab, 0x84, 0x56, 0x83, 0x28, 0x8d, 0x4b, 0xd0,
    0x2c, 0x75, 0x89, 0xc5, 0xb5, 0xe1, 0xf3, 0x9d, 0xff, 0x74, 0xff, 0x96,
    0xb7, 0x0b, 0xc2, 0xde, 0xe4, 0x09, 0xd9, 0xfa, 0x56, 0x2a, 0x14, 0x33,
    0x6b, 0xd4, 0x1c, 0xdd, 0x13, 0x5b, 0xf3, 0xea, 0x0e, 0x6c, 0x23, 0xfe,
    0x59, 0x99, 0x15, 0x87, 0xba, 0xe5, 0x2d, 0xea, 0x3c, 0xb7, 0x7b, 0xc8,
    0x8a, 0x0a, 0x06, 0x32, 0xd1, 0x1e, 0x22, 0xa3, 0x17, 0x04, 0x53, 0xb4,
    0x83, 0x63, 0x41, 0x0b, 0x6e, 0x69, 0x78, 0x27, 0x99, 0xde, 0xe1, 0xf8,
    0x8a, 0xf4, 0x26, 0xde, 0xf2, 0xaa, 0xbc, 0x62, 0xb7, 0xaa, 0xac, 0x36,
    0xbb, 0xba, 0xae, 0x78, 0x53, 0x2c, 0x2d, 0xcf, 0x0d, 0xc3, 0xd6, 0xf9,
    0xc2, 0x55, 0xb8, 0x88, 0x98, 0x1a, 0x90, 0x93, 0x52, 0x29, 0x2a, 0x5c,
    0xa6, 0xbd, 0xcb, 0xe9, 0x1d, 0x86, 0xb0, 0x1e, 0x09, 0x18, 0x31, 0x35,
    0x97, 0xb9, 0xb7, 0x1b, 0x65, 0x12, 0x09, 0x73, 0x79, 0x18, 0x58, 0xb8,
    0xbb, 0x5d, 0x31, 0x22, 0x9a, 0x79, 0x8c, 0xb2, 0xfa, 0x32, 0xf8, 0x19,
    0x06, 0x03, 0x7a, 0x36, 0xfd, 0x6b, 0x46, 0x26, 0xb0, 0x57, 0x85, 0x75,
    0xa9, 0x4c, 0x7e, 0x76, 0x9f, 0x7b, 0x6c, 0xf3, 0x6e, 0x18, 0x84, 0x5d,
    0x9c, 0xc5, 0x94, 0xf0, 0xe6, 0xf5, 0xcd, 0xd5, 0x14, 0xcb, 0x1c, 0xad,
    0xbd, 0xec, 0x09, 0x87, 0xdd, 0x7e, 0x42, 0x75, 0x3b, 0xac, 0x1d, 0x07,
    0xf6, 0x73, 0xdf, 0x85, 0xc0, 0x81, 0xf2, 0xa9, 0x3d, 0x29, 0x86, 0x9e,
    0xea, 0x28, 0x8c, 0xd6, 0x65, 0x52, 0x7b, 0x9a, 0xb3, 0x3f, 0xd0, 0x3e,
    0x5c, 0xe9, 0x38, 0x35, 0x4c, 0x79, 0x8e, 0x47, 0xc1, 0x50, 0xc0, 0xaf,
    0x5d, 0x68, 0xd5, 0x7f, 0x1f, 0xe8, 0xf1, 0xf5, 0x9c, 0x6c, 0x51, 0x9a,
    0x31, 0xef, 0x8a, 0xd4, 0x99, 0x1a, 0x27, 0xc6, 0x0a, 0xc4, 0x30, 0x87,
    0xbf, 0x47, 0xfb, 0x06, 0x50, 0x90, 0x9b, 0x5e, 0xa4, 0x8d, 0x45, 0x5d,
    0x74, 0x0a, 0x70, 0x12, 0x22, 0x16, 0xb2, 0xc7, 0x34, 0xf1, 0xae, 0x6c,
    0x27, 0xbc, 0x6f, 0x50, 0xd2, 0x33, 0x98, 0xcb, 0xd5, 0x0f, 0xeb, 0xa2,
    0x15, 0xc3, 0xde, 0x19, 0x4c, 0x44, 0xf8, 0x23, 0x3b, 0xd4, 0x83, 0xfb,
    0x70, 0xe3, 0x8b, 0x28, 0xe4, 0x39, 0xbd, 0x7c, 0x39, 0x9e, 0xdd, 0x4c,
    0xf9, 0x5d, 0x4a, 0xf8, 0x70, 0x21, 0xc4, 0xe2, 0x60, 0x4c, 0x02, 0x82,
    0x60, 0x74, 0x2f, 0x79, 0xc3, 0xd5, 0x9f, 0x78, 0xdf, 0xd8, 0x6d, 0xd9,
    0xd8, 0x06, 0xc9, 0x30, 0x67, 0x0b, 0x31, 0xa2, 0x31, 0x8f, 0xd5, 0xaf,
    0x90, 0x93, 0x72, 0xd5, 0xc4, 0x04, 0x6e, 0x2b, 0x39, 0x01, 0x25, 0x2b,
    0xb7, 0xf1, 0x57, 0xdd, 0x2e, 0xdc, 0xc2, 0xca, 0x57, 0xb8, 0x17, 0x6c,
    0x03, 0xc1, 0xc9, 0xa9,
};

void test_ctr_mode()
{
    std::uint8_t buf[1024];
    std::size_t  size, n;

    auto e = SM4CtrEncryptor(user_key, iv);
    e.do_final(buf, &size, pt, 1024);
    if (std::memcmp(buf, ct, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in ctr_mode");
    }
    e.reset(iv);
    e.update(buf, &n, pt, 100);
    size = n;
    e.do_final(buf + size, &n, pt + 100, 1024 - 100);
    size += n;
    if (std::memcmp(buf, ct, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in ctr_mode");
    }
    e.reset(iv);
    e.update(buf, &n, pt, 100);
    size = n;
    e.update(buf + size, &n, pt + 100, 1024 - 100);
    size += n;
    e.do_final(buf + size, &n, nullptr, 0);
    size += n;
    if (std::memcmp(buf, ct, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in Ctr_mode");
    }

    auto d = SM4CtrDecryptor(user_key, iv);
    d.do_final(buf, &size, ct, 1024);
    if (std::memcmp(buf, pt, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in ctr_mode");
    }
    d.reset(iv);
    d.update(buf, &n, ct, 100);
    size = n;
    d.do_final(buf + size, &n, ct + 100, 1024 - 100);
    size += n;
    if (std::memcmp(buf, pt, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in ctr_mode");
    }
    d.reset(iv);
    d.update(buf, &n, ct, 100);
    size = n;
    d.update(buf + size, &n, ct + 100, 1024 - 100);
    size += n;
    d.do_final(buf + size, &n, nullptr, 0);
    size += n;
    if (std::memcmp(buf, pt, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in ctr_mode");
    }
}