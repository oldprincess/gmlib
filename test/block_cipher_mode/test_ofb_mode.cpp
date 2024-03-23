#include <gmlib/block_cipher_mode/ofb_mode.h>

#include <cstring>

#include "sm4.h"
#include "test.h"

using namespace block_cipher_mode;
using SM4OfbEncryptor = OfbEncryptor<SM4>;
using SM4OfbDecryptor = OfbDecryptor<SM4>;

static std::uint8_t iv[16] = {
    0xbe, 0x55, 0x89, 0x8f, 0xe7, 0x64, 0x47, 0x23,
    0x97, 0x72, 0x7e, 0x7c, 0x01, 0xd2, 0x91, 0xa9,
};
static std::uint8_t user_key[16] = {
    0x56, 0x32, 0x51, 0xd7, 0xe6, 0x63, 0xb7, 0xae,
    0xcd, 0xc4, 0x70, 0x98, 0x85, 0x1c, 0xe8, 0x06,
};
static std::uint8_t pt[1024] = {
    0xb4, 0x30, 0xf0, 0xe3, 0xf9, 0xaa, 0x21, 0x95, 0xc1, 0xb9, 0x72, 0xc2,
    0xe9, 0xfd, 0x9d, 0x5a, 0xec, 0x48, 0x8b, 0xc1, 0x97, 0x17, 0xc5, 0x3c,
    0xda, 0x2b, 0x0e, 0x14, 0xb5, 0x91, 0x0a, 0x8b, 0x66, 0x18, 0x94, 0x05,
    0xd4, 0x59, 0xb5, 0x81, 0x75, 0x8b, 0xaf, 0xe7, 0x8d, 0x27, 0x12, 0x8e,
    0x35, 0x0d, 0x42, 0xf3, 0x37, 0x80, 0x39, 0xf9, 0xad, 0x1b, 0xdc, 0xed,
    0x0a, 0xb8, 0x9d, 0x3e, 0x88, 0x92, 0x61, 0xbd, 0x42, 0x00, 0x31, 0x75,
    0xda, 0x1e, 0xd1, 0x9e, 0x13, 0x4a, 0xce, 0xd2, 0x2b, 0x27, 0x3c, 0xe4,
    0xf0, 0xa3, 0xf0, 0x51, 0x48, 0xd3, 0x0e, 0xef, 0xe8, 0x23, 0xd6, 0x92,
    0x8e, 0x6e, 0xe5, 0x0b, 0x5f, 0x5c, 0xba, 0x72, 0x47, 0xd6, 0xe7, 0xc0,
    0x93, 0x86, 0xbe, 0xac, 0x70, 0x4f, 0x7c, 0xb1, 0x61, 0x19, 0xb3, 0xe4,
    0x4a, 0xb5, 0x03, 0x7a, 0x26, 0x75, 0xc3, 0x81, 0x6c, 0x37, 0xb1, 0xa6,
    0x8f, 0x74, 0xba, 0x98, 0x77, 0x03, 0xb3, 0x25, 0xe9, 0x7e, 0x3b, 0x05,
    0xc8, 0x63, 0x30, 0x20, 0x35, 0x79, 0xbc, 0x55, 0x9f, 0xbc, 0x2e, 0x51,
    0xe6, 0x73, 0x84, 0xc9, 0x39, 0xb5, 0x7b, 0x91, 0xbe, 0x18, 0xfc, 0xde,
    0x66, 0x3c, 0x47, 0x5b, 0x3c, 0xd5, 0xec, 0x12, 0x69, 0x34, 0x3b, 0xeb,
    0xf2, 0xec, 0x31, 0x0c, 0x7b, 0xe4, 0x43, 0xfd, 0xc2, 0x49, 0x33, 0xdb,
    0xff, 0xc4, 0x5f, 0xe3, 0x89, 0xd0, 0xe7, 0x98, 0x99, 0x22, 0xb5, 0x51,
    0xfc, 0xd4, 0xd8, 0x09, 0x5f, 0xa3, 0xcb, 0x7c, 0x9d, 0x66, 0x87, 0x66,
    0x28, 0xb9, 0x5b, 0x4e, 0x53, 0x5c, 0xe1, 0xbc, 0x01, 0xb6, 0xee, 0x5e,
    0x16, 0x17, 0x76, 0x35, 0xdb, 0x86, 0x1e, 0xbe, 0x3b, 0xab, 0x29, 0x7a,
    0x98, 0x53, 0x4b, 0x8d, 0x5a, 0xd9, 0x76, 0xa0, 0x9c, 0xc6, 0x7c, 0x3e,
    0xc8, 0xc1, 0xfc, 0x42, 0xdf, 0xc1, 0x75, 0x8d, 0x50, 0x83, 0xc6, 0x65,
    0xd4, 0x40, 0xae, 0x9c, 0x63, 0x43, 0xce, 0x58, 0xf0, 0x99, 0xd1, 0x7a,
    0x3b, 0x50, 0xeb, 0xbd, 0x38, 0xb7, 0x4d, 0x79, 0x74, 0xa6, 0xd7, 0x28,
    0x8d, 0x6c, 0xaf, 0xd0, 0x53, 0x94, 0x0d, 0x12, 0xab, 0x1d, 0xb5, 0x5c,
    0x32, 0xce, 0x37, 0x9e, 0x55, 0x79, 0x3e, 0xe5, 0x72, 0xa0, 0x82, 0x00,
    0x35, 0x01, 0x11, 0x54, 0x99, 0x54, 0xae, 0x86, 0x96, 0xcf, 0x53, 0x7c,
    0xef, 0x66, 0x70, 0x2b, 0x4c, 0x5c, 0xfd, 0x10, 0x3d, 0x10, 0x2c, 0x12,
    0x7a, 0x46, 0x1f, 0xac, 0x90, 0xb8, 0x6b, 0xd9, 0xb0, 0xcc, 0x95, 0x38,
    0x8f, 0x90, 0x83, 0x8f, 0xc6, 0xba, 0x2e, 0xa6, 0x76, 0x83, 0x86, 0x9c,
    0xed, 0xc9, 0x1e, 0xf2, 0xa8, 0xc2, 0xa2, 0x7a, 0x31, 0x8f, 0x2a, 0x31,
    0xd8, 0xb5, 0xbc, 0x71, 0x09, 0xa7, 0xaf, 0xfe, 0xa6, 0x07, 0x18, 0x4c,
    0x02, 0xfd, 0x7f, 0xde, 0xf5, 0x01, 0x2d, 0x9b, 0x01, 0x3e, 0xff, 0x4a,
    0xe9, 0xcc, 0x28, 0xa7, 0x4c, 0x68, 0x73, 0x34, 0xc0, 0x05, 0x5c, 0x95,
    0xcb, 0xa4, 0x83, 0x32, 0xdd, 0x79, 0x4e, 0x80, 0x6c, 0x58, 0x94, 0x79,
    0xdf, 0x7b, 0xf7, 0xed, 0x86, 0x44, 0x84, 0x75, 0x69, 0xb7, 0x30, 0xe8,
    0xc6, 0xe0, 0xee, 0xeb, 0xb3, 0x8b, 0xf8, 0x9c, 0x2a, 0x87, 0x39, 0xeb,
    0x17, 0x75, 0xda, 0xb3, 0xd7, 0x4e, 0xb4, 0x3f, 0xa3, 0xcf, 0x50, 0x77,
    0x3e, 0xc2, 0xf1, 0x3e, 0x08, 0x97, 0x48, 0x35, 0x52, 0x0f, 0x1f, 0xd0,
    0xff, 0x3c, 0x8a, 0xdf, 0xcc, 0xce, 0x11, 0xf4, 0x23, 0xa9, 0xc6, 0xc2,
    0x12, 0x4a, 0x5b, 0x61, 0x36, 0xd0, 0xca, 0x23, 0x18, 0xb6, 0xc8, 0x50,
    0x65, 0x02, 0x77, 0xbb, 0xa0, 0x2e, 0xf5, 0x0c, 0x0d, 0xa2, 0x70, 0x34,
    0xbb, 0x47, 0x71, 0x0f, 0x9f, 0x2e, 0xe9, 0xb2, 0xbe, 0xb1, 0x52, 0x17,
    0x06, 0x3f, 0x52, 0x73, 0xc0, 0x3c, 0x23, 0x4a, 0xcc, 0x47, 0x31, 0x3a,
    0xbe, 0xd6, 0xa4, 0xb0, 0xb8, 0x64, 0x9b, 0x3b, 0xf6, 0x0c, 0xdb, 0x6e,
    0x29, 0x2f, 0x2a, 0xda, 0xbc, 0xdf, 0x92, 0xe9, 0x30, 0x15, 0xbe, 0xdd,
    0x90, 0x5b, 0xab, 0xc2, 0xb6, 0x01, 0x64, 0x43, 0xa2, 0xe7, 0x74, 0x6f,
    0xfe, 0x19, 0x17, 0x7c, 0x15, 0xeb, 0x48, 0x0d, 0x39, 0xfc, 0x0a, 0xe3,
    0x1e, 0xe2, 0x64, 0x72, 0xd0, 0xcc, 0xc0, 0x23, 0x4b, 0xfd, 0x16, 0x8a,
    0xb4, 0x54, 0x1a, 0xa1, 0x39, 0xf9, 0x02, 0xdf, 0x85, 0xce, 0x3a, 0xd5,
    0x6f, 0xf3, 0x3d, 0x6b, 0xef, 0xbf, 0x97, 0xac, 0xcc, 0x42, 0x15, 0x0e,
    0x07, 0x51, 0x05, 0x97, 0xba, 0x28, 0xe5, 0xb6, 0xb3, 0x7b, 0xe1, 0xfc,
    0x92, 0x67, 0x49, 0x18, 0xf0, 0xe7, 0x42, 0x29, 0xa7, 0xb9, 0xd4, 0xf2,
    0x47, 0xb3, 0xfa, 0xc8, 0x06, 0x7c, 0x68, 0xd2, 0xb5, 0x3b, 0x47, 0xed,
    0x68, 0x1a, 0xbf, 0xc3, 0xd8, 0x7f, 0x4f, 0x74, 0xe4, 0xd7, 0xc2, 0x84,
    0x44, 0x96, 0x9f, 0x75, 0x8e, 0x29, 0x55, 0x09, 0x96, 0xa2, 0x4f, 0xf1,
    0xeb, 0x82, 0x95, 0x0a, 0x05, 0x86, 0xcf, 0x88, 0xb5, 0x86, 0x1d, 0x85,
    0x77, 0x5a, 0xc7, 0x69, 0x54, 0x0b, 0xe2, 0xa7, 0x07, 0x85, 0x2a, 0x95,
    0x90, 0xc8, 0x58, 0x9c, 0x12, 0x57, 0xf0, 0xb4, 0x30, 0xf6, 0xbd, 0x6f,
    0xa4, 0xa6, 0x0a, 0xe0, 0x8a, 0xd2, 0x7a, 0xef, 0xdc, 0xf7, 0x7b, 0xf1,
    0x7f, 0xfd, 0x00, 0x00, 0x9c, 0x8b, 0x0e, 0xb3, 0x4c, 0x2b, 0x61, 0x20,
    0x3f, 0x9a, 0x96, 0x89, 0x34, 0x81, 0xea, 0xa1, 0x07, 0x4c, 0x32, 0x0d,
    0xb3, 0x8b, 0x60, 0x56, 0xcc, 0xd7, 0x62, 0x7c, 0xb5, 0x16, 0x24, 0xe3,
    0xa1, 0x61, 0x7a, 0xf3, 0x95, 0xd5, 0xf3, 0x00, 0x51, 0x5c, 0x11, 0xfa,
    0x96, 0x70, 0x14, 0x95, 0x4c, 0x21, 0x91, 0xa0, 0xeb, 0x0d, 0x37, 0x1b,
    0x5e, 0x2a, 0x7c, 0xdc, 0x6f, 0x08, 0xb1, 0xd1, 0x83, 0x6a, 0x71, 0x6e,
    0x58, 0xdc, 0x5a, 0xe1, 0xbd, 0x10, 0x8f, 0x8a, 0x4f, 0x47, 0x2f, 0x23,
    0xad, 0x46, 0xed, 0xe8, 0xf0, 0x79, 0xfb, 0x6f, 0x8c, 0xae, 0xe2, 0x7c,
    0x54, 0xb0, 0xdf, 0x8d, 0xa6, 0x68, 0x56, 0x6a, 0xdc, 0xf1, 0x2e, 0xad,
    0x7c, 0x1b, 0x34, 0x05, 0x87, 0x87, 0x3d, 0x3a, 0xde, 0xc3, 0xaa, 0xdc,
    0xe5, 0x2c, 0xf7, 0x9f, 0x32, 0xb3, 0xb4, 0x3c, 0x72, 0xc4, 0xa3, 0x4a,
    0x74, 0x96, 0xee, 0x15, 0xda, 0x41, 0x96, 0xe4, 0xce, 0x6c, 0xea, 0x29,
    0xbe, 0xc4, 0x68, 0x9e, 0xf2, 0x57, 0x83, 0x1e, 0x57, 0x1f, 0x91, 0x3d,
    0x8a, 0x52, 0x7b, 0x59, 0xf2, 0xa6, 0x0d, 0x26, 0x27, 0x28, 0xee, 0xb3,
    0x1b, 0xe8, 0xf4, 0x76, 0xbd, 0x15, 0xfa, 0xb4, 0xc0, 0x33, 0x01, 0x75,
    0xf1, 0x3d, 0x06, 0x1c, 0x47, 0x44, 0xd6, 0xe6, 0xe9, 0x1b, 0x07, 0x32,
    0x36, 0x0d, 0xe0, 0xdf, 0x4d, 0x87, 0xf6, 0x0f, 0x6e, 0xfb, 0x28, 0xef,
    0x6c, 0x40, 0x2c, 0xae, 0xaa, 0xb7, 0xe4, 0x66, 0xd2, 0x64, 0xa5, 0x19,
    0x6d, 0x54, 0x4a, 0x15, 0xc2, 0x3c, 0xff, 0xfe, 0x1e, 0x3a, 0x30, 0xb4,
    0x3e, 0x1e, 0xe1, 0x84, 0x2e, 0x4f, 0xd2, 0xec, 0x6f, 0x75, 0x2f, 0x3d,
    0x1b, 0xfd, 0xd8, 0xdb, 0x22, 0xd0, 0xec, 0x45, 0xf9, 0x61, 0x12, 0xf5,
    0x0a, 0x9a, 0x08, 0x16, 0xcf, 0x46, 0x50, 0x19, 0x73, 0xba, 0x29, 0xc7,
    0x95, 0xff, 0x99, 0x50, 0x47, 0x45, 0xb0, 0xf2, 0x94, 0x56, 0x01, 0xac,
    0x6c, 0x18, 0x00, 0xa6, 0xff, 0xad, 0xbc, 0xfc, 0xf3, 0x24, 0x2a, 0x4f,
    0x51, 0xa3, 0x24, 0x11, 0xae, 0xa9, 0x83, 0x8e, 0x77, 0xb3, 0xd1, 0xd5,
    0xa2, 0x3b, 0x7e, 0xc1,
};
static std::uint8_t ct[1024] = {
    0x7a, 0x5d, 0x5f, 0xbf, 0x89, 0x3f, 0x7a, 0x91, 0x3e, 0x02, 0xa8, 0x9a,
    0xb4, 0x11, 0x32, 0xcc, 0xbd, 0x1e, 0x1f, 0x60, 0x9e, 0xc0, 0xfb, 0x27,
    0x71, 0x66, 0xaf, 0x1d, 0x3c, 0x56, 0x56, 0x5d, 0x38, 0x53, 0xd0, 0x2e,
    0xb1, 0x99, 0x98, 0xab, 0x72, 0x2c, 0x48, 0x1e, 0xd5, 0x79, 0x8f, 0xc0,
    0xf0, 0xef, 0x71, 0x45, 0xce, 0xa3, 0x4c, 0xe7, 0x8d, 0xd5, 0x5a, 0x0f,
    0x17, 0x50, 0xaf, 0x8d, 0xbe, 0xbe, 0x94, 0xba, 0x55, 0xeb, 0x8d, 0xd9,
    0x20, 0x1b, 0x4b, 0xf9, 0xe2, 0x61, 0x77, 0x66, 0xb9, 0x51, 0xd2, 0x2c,
    0x36, 0xb5, 0x5d, 0xe4, 0x2a, 0x9f, 0x39, 0xbb, 0x96, 0x3a, 0x00, 0x44,
    0x60, 0xd3, 0xd0, 0x5b, 0xe3, 0xe6, 0x8a, 0xc3, 0x30, 0x57, 0x18, 0xf8,
    0x99, 0xdc, 0x7a, 0x1f, 0x3c, 0xed, 0x45, 0xd5, 0x59, 0x34, 0xc8, 0xc2,
    0x77, 0x10, 0xbf, 0x17, 0xc3, 0x34, 0x74, 0x25, 0xb7, 0x0f, 0x7d, 0x61,
    0x3f, 0xf1, 0xea, 0x5c, 0x83, 0xda, 0xa9, 0xd1, 0xa7, 0x8c, 0x7a, 0x33,
    0xe3, 0xbd, 0xeb, 0x6f, 0xbe, 0x00, 0x27, 0x64, 0xa6, 0xb3, 0x34, 0x93,
    0x13, 0x4e, 0xda, 0xd1, 0x15, 0x12, 0xbf, 0x1e, 0xd6, 0xf7, 0xde, 0xb1,
    0x59, 0xf8, 0xec, 0x75, 0xe1, 0x74, 0x54, 0x61, 0x07, 0xbc, 0x4c, 0x09,
    0x56, 0xde, 0x11, 0xa9, 0x11, 0x2e, 0x20, 0x0d, 0xeb, 0x6b, 0x61, 0x79,
    0x7c, 0xf6, 0x4e, 0x6b, 0x91, 0x29, 0xea, 0xf0, 0x61, 0xfb, 0xb7, 0x07,
    0x5b, 0xb3, 0xe6, 0xf3, 0x1e, 0x51, 0x39, 0x1a, 0x32, 0xfc, 0x31, 0x1d,
    0xac, 0x74, 0xf2, 0xb7, 0xa0, 0x23, 0x2c, 0x4c, 0x4a, 0xcd, 0x74, 0x4b,
    0x11, 0x17, 0xe2, 0xa3, 0x19, 0xb5, 0x9e, 0xbd, 0xb9, 0xff, 0x92, 0x0b,
    0x59, 0xb3, 0x0f, 0x53, 0xeb, 0x11, 0xaf, 0x26, 0x1a, 0x02, 0x90, 0x14,
    0x12, 0x8e, 0xbf, 0xa7, 0xd3, 0xac, 0xfd, 0xd5, 0xd5, 0x4b, 0xed, 0x12,
    0x0e, 0xb5, 0xbc, 0x2b, 0x2e, 0x1e, 0x67, 0x84, 0x5d, 0x5c, 0x8b, 0xca,
    0xec, 0xb2, 0x50, 0x23, 0x94, 0x1f, 0x5a, 0x1a, 0xd4, 0x71, 0xdd, 0x06,
    0x78, 0x40, 0xf0, 0xa4, 0x43, 0xe9, 0x5b, 0x08, 0x2a, 0xd7, 0x90, 0x93,
    0x48, 0xb9, 0x19, 0xd1, 0x49, 0xf8, 0x88, 0xff, 0x64, 0xbe, 0x4a, 0xca,
    0xc2, 0x6f, 0x3b, 0xf5, 0xc4, 0x31, 0xb4, 0xc6, 0x5d, 0x70, 0x0f, 0x58,
    0x7a, 0x3b, 0x1b, 0xfb, 0xe6, 0x90, 0x60, 0x8d, 0x53, 0x0a, 0xeb, 0x5a,
    0x2a, 0x91, 0x3f, 0x25, 0x3e, 0x66, 0xa2, 0xb9, 0x5b, 0xca, 0xf2, 0x06,
    0xf0, 0x37, 0xc1, 0x3d, 0x99, 0x1e, 0xcd, 0x7b, 0x97, 0x9c, 0x7d, 0xaf,
    0xae, 0xc8, 0xf5, 0xfa, 0xa4, 0x10, 0xec, 0x0b, 0x5b, 0xe4, 0x90, 0x9a,
    0x67, 0x8a, 0x7c, 0xef, 0xe0, 0x4f, 0x8c, 0x9c, 0xf7, 0x03, 0xc3, 0xf7,
    0xfb, 0x43, 0x68, 0x0d, 0xf5, 0x6c, 0xe8, 0x8a, 0xfd, 0x4b, 0x6b, 0xee,
    0x11, 0xda, 0x82, 0x65, 0x2b, 0x79, 0x47, 0x79, 0x49, 0x1e, 0xb9, 0x12,
    0x25, 0x98, 0xec, 0x40, 0x4a, 0x10, 0x20, 0x76, 0xeb, 0x98, 0x54, 0x98,
    0x70, 0xcf, 0x42, 0xa3, 0xeb, 0x35, 0x7e, 0x91, 0xda, 0xd1, 0xb4, 0x4a,
    0xf9, 0xa3, 0x00, 0xba, 0x78, 0x93, 0x53, 0x15, 0xa6, 0x95, 0xc0, 0xd4,
    0x4c, 0xc5, 0x35, 0xe5, 0x75, 0x3b, 0x42, 0xd0, 0x08, 0x75, 0xcb, 0xef,
    0x6d, 0xd9, 0x01, 0xb4, 0xfd, 0x35, 0x2b, 0x06, 0x45, 0x63, 0xae, 0xc4,
    0xc8, 0x94, 0xc4, 0x5a, 0xd6, 0xbf, 0xf5, 0x23, 0x0e, 0x89, 0x61, 0xb7,
    0x00, 0x91, 0xe5, 0xad, 0x1d, 0x00, 0x04, 0xf0, 0xaf, 0x5d, 0x7e, 0x6d,
    0x74, 0x97, 0xfb, 0xb9, 0xcc, 0x24, 0xa8, 0x7b, 0x35, 0xc4, 0xc6, 0x82,
    0xb5, 0x8b, 0x5d, 0x8d, 0x98, 0x31, 0x89, 0x51, 0x2f, 0x41, 0x53, 0xf2,
    0x49, 0xcf, 0x5f, 0x10, 0x67, 0x04, 0xc8, 0xd0, 0x40, 0x39, 0x71, 0x11,
    0xb7, 0x29, 0xb7, 0x2a, 0xc8, 0xbd, 0x08, 0x0b, 0xd3, 0xf6, 0xc0, 0x1c,
    0x02, 0xfd, 0x04, 0xed, 0xa9, 0x76, 0x63, 0x2e, 0x02, 0x19, 0x45, 0xa6,
    0x5b, 0x44, 0x3c, 0x8e, 0xa7, 0x9b, 0x76, 0xcf, 0x6f, 0x24, 0x71, 0x14,
    0x08, 0x26, 0x5e, 0xaa, 0xfe, 0x7e, 0xc9, 0xc8, 0x9a, 0xde, 0xd4, 0x3f,
    0x0c, 0xe5, 0x9f, 0x8f, 0x3c, 0x4d, 0xf7, 0xdb, 0xa5, 0xcb, 0xf1, 0x43,
    0xc7, 0xd2, 0x7b, 0x09, 0xe8, 0xdf, 0x5d, 0xa8, 0xcd, 0xd6, 0x8d, 0xda,
    0xe2, 0x81, 0x1c, 0x89, 0xe8, 0xf3, 0xcb, 0xdd, 0x89, 0x72, 0x95, 0x64,
    0x0b, 0x7a, 0xff, 0x49, 0x45, 0xc7, 0x94, 0x1d, 0x86, 0xcf, 0x42, 0x21,
    0x0f, 0x2f, 0x9b, 0x02, 0xbf, 0x86, 0x4a, 0xb3, 0xa1, 0x84, 0xb7, 0x66,
    0xf1, 0xb7, 0x9a, 0xd6, 0x61, 0xeb, 0xc1, 0x3d, 0x3b, 0x73, 0x48, 0xd7,
    0x79, 0xe9, 0xca, 0x0a, 0x0c, 0x3b, 0xc6, 0x65, 0xac, 0xdd, 0xeb, 0x27,
    0x4b, 0x37, 0x5b, 0xba, 0xf4, 0xb3, 0xea, 0x82, 0xca, 0x56, 0x00, 0x0e,
    0xd3, 0x1d, 0x3a, 0xa3, 0x60, 0x42, 0x5e, 0xb9, 0xfc, 0xc2, 0x97, 0x3a,
    0x88, 0xc8, 0x80, 0x48, 0x11, 0x69, 0x13, 0xa0, 0x49, 0xc3, 0xd6, 0x0a,
    0xae, 0x84, 0x4d, 0x6a, 0x5f, 0xc6, 0x60, 0xb2, 0x0c, 0xa3, 0x24, 0xb8,
    0x28, 0x1d, 0x99, 0xbb, 0xdf, 0x06, 0x52, 0x57, 0x79, 0xac, 0x8e, 0x67,
    0xfb, 0xe4, 0x02, 0x52, 0x46, 0x3a, 0xa0, 0xf9, 0x9f, 0x3d, 0xb6, 0xdf,
    0xee, 0x18, 0x17, 0xb5, 0xd4, 0xc1, 0xe1, 0x35, 0x95, 0x38, 0x05, 0xfc,
    0xe4, 0x02, 0x4c, 0xab, 0xc8, 0x36, 0xd4, 0x48, 0x1b, 0xed, 0xb1, 0x7d,
    0x0f, 0xbe, 0xad, 0x0d, 0x2a, 0x7c, 0x07, 0xf4, 0x25, 0x2c, 0xc5, 0x5d,
    0x91, 0x6c, 0x7c, 0x70, 0xed, 0x0d, 0x69, 0x79, 0xba, 0xac, 0xc5, 0x49,
    0x1b, 0x3c, 0xdb, 0x99, 0x09, 0x1e, 0x75, 0xef, 0xa5, 0xf8, 0xa6, 0x8f,
    0xde, 0x6f, 0xec, 0x0e, 0x6b, 0xec, 0xa5, 0xd8, 0xa4, 0x4f, 0xca, 0x2e,
    0xd9, 0xb6, 0xbb, 0xd0, 0xca, 0x3a, 0x29, 0xed, 0x94, 0xd1, 0x7f, 0xe3,
    0x9c, 0x97, 0x58, 0xef, 0xce, 0x55, 0xec, 0xef, 0x8e, 0x55, 0x05, 0x34,
    0xf1, 0xb1, 0x18, 0xd9, 0x80, 0x29, 0x59, 0xe7, 0x97, 0xdd, 0x7d, 0x9f,
    0x29, 0x79, 0x63, 0x34, 0xe6, 0xb1, 0xb3, 0x7a, 0xcc, 0x51, 0x1c, 0x4a,
    0xdb, 0x73, 0x99, 0x8f, 0x32, 0xcb, 0xf0, 0x64, 0xa1, 0x61, 0x71, 0x15,
    0x89, 0x30, 0x6e, 0xa3, 0x84, 0x0d, 0x30, 0x8b, 0x40, 0x13, 0xb6, 0xae,
    0x68, 0x01, 0xa3, 0xd8, 0x55, 0xcb, 0x23, 0xcd, 0xd3, 0x75, 0x96, 0xd2,
    0x1f, 0x48, 0x92, 0xbd, 0x8a, 0x50, 0x86, 0x79, 0x11, 0x5f, 0x24, 0xcc,
    0x60, 0x2d, 0xc4, 0x53, 0xd6, 0xdb, 0xcb, 0x5c, 0x09, 0xe2, 0xc2, 0xf9,
    0xd7, 0x78, 0xd3, 0x74, 0x6d, 0x14, 0x31, 0x0b, 0x9d, 0x0a, 0x4a, 0xfd,
    0x79, 0x8f, 0xfd, 0xf8, 0x50, 0x66, 0x9b, 0x7a, 0x27, 0x3f, 0xe3, 0x40,
    0x90, 0xa2, 0xc1, 0xfe, 0x9f, 0x90, 0xab, 0x7a, 0xb1, 0xd6, 0xf5, 0xf6,
    0x63, 0xa6, 0xfe, 0x06, 0x7c, 0x36, 0x27, 0xe0, 0x41, 0xf7, 0xe9, 0x2a,
    0x29, 0x18, 0xfa, 0xfd, 0xea, 0x11, 0x51, 0x1e, 0x26, 0xff, 0x98, 0xd8,
    0xaa, 0x9b, 0xe1, 0x10, 0xc8, 0x59, 0xca, 0xeb, 0x86, 0x94, 0x73, 0x6f,
    0x40, 0x56, 0xac, 0x62, 0xb6, 0x48, 0x88, 0x0a, 0xf9, 0xa7, 0x43, 0x6a,
    0x20, 0x6b, 0x4f, 0xd6, 0x20, 0x74, 0x17, 0x51, 0x2c, 0x9c, 0xf3, 0xc2,
    0x14, 0x3f, 0xd6, 0xca, 0x2e, 0x67, 0xd3, 0x70, 0x3d, 0xaa, 0x0c, 0x71,
    0x9a, 0x1f, 0xf7, 0x79,
};

void test_ofb_mode()
{
    std::uint8_t buf[1024];
    std::size_t  size, n;

    auto e = SM4OfbEncryptor(user_key, iv);
    e.do_final(buf, &size, pt, 1024);
    if (std::memcmp(buf, ct, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in ofb_mode");
    }
    e.reset(iv);
    e.update(buf, &n, pt, 100);
    size = n;
    e.do_final(buf + size, &n, pt + 100, 1024 - 100);
    size += n;
    if (std::memcmp(buf, ct, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in ofb_mode");
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
        throw std::runtime_error("err in Ofb_mode");
    }

    auto d = SM4OfbDecryptor(user_key, iv);
    d.do_final(buf, &size, ct, 1024);
    if (std::memcmp(buf, pt, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in ofb_mode");
    }
    d.reset(iv);
    d.update(buf, &n, ct, 100);
    size = n;
    d.do_final(buf + size, &n, ct + 100, 1024 - 100);
    size += n;
    if (std::memcmp(buf, pt, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in ofb_mode");
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
        throw std::runtime_error("err in ofb_mode");
    }
}