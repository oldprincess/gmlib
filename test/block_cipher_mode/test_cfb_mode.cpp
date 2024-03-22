#include <gmlib/block_cipher_mode/cfb_mode.h>

#include <cstring>

#include "sm4.h"
#include "test.h"

using namespace block_cipher_mode;
using SM4CfbEncryptor = CfbEncryptor<SM4>;
using SM4CfbDecryptor = CfbDecryptor<SM4>;

static std::uint8_t iv[16] = {
    0x1d, 0x4a, 0x0c, 0x5b, 0x24, 0xb4, 0x7e, 0x4b,
    0xa3, 0xeb, 0x31, 0xe5, 0xe4, 0xdb, 0x29, 0xd0,
};
static std::uint8_t user_key[16] = {
    0x8f, 0xc9, 0x56, 0x4d, 0xa6, 0x41, 0x43, 0xb9,
    0x00, 0x18, 0x02, 0x38, 0x5c, 0x85, 0xbe, 0xed,
};
static std::uint8_t pt[1024] = {
    0x54, 0x84, 0xde, 0xe5, 0xc9, 0xe8, 0x3d, 0x72, 0xcc, 0x06, 0x81, 0x80,
    0xc0, 0xc0, 0x32, 0x3a, 0xe8, 0xb2, 0x12, 0xd8, 0xc0, 0xec, 0xc3, 0xe9,
    0x5b, 0xcd, 0xf9, 0x0a, 0xec, 0x85, 0x20, 0xc9, 0x48, 0xef, 0x0a, 0x08,
    0xa9, 0x12, 0x99, 0xa9, 0xf5, 0x86, 0x14, 0xac, 0xbd, 0xcd, 0xd1, 0xc0,
    0xa6, 0xdc, 0x41, 0x30, 0xc8, 0x9d, 0x8b, 0xf5, 0xc8, 0x27, 0xd3, 0x8d,
    0x38, 0x9b, 0xe4, 0x5a, 0x45, 0xec, 0x44, 0xd0, 0x17, 0xed, 0x77, 0x77,
    0xff, 0x99, 0xd7, 0x75, 0x5b, 0xd8, 0xaf, 0xaf, 0xdc, 0x27, 0xe4, 0xb9,
    0x16, 0x6c, 0xe1, 0xdc, 0x2d, 0x66, 0xaf, 0x5f, 0x30, 0x1a, 0x5d, 0xb6,
    0xba, 0xd3, 0x45, 0xf6, 0xb3, 0xa5, 0xda, 0x6d, 0x28, 0x97, 0x5c, 0x9e,
    0x2b, 0x7f, 0x3f, 0xc3, 0x0b, 0x74, 0x5f, 0x9c, 0x05, 0xc7, 0x49, 0xaa,
    0xe4, 0xce, 0x9e, 0xa4, 0x61, 0xea, 0x1f, 0xd2, 0xbc, 0x47, 0x03, 0x8c,
    0x36, 0x41, 0xe1, 0x27, 0x8f, 0x1c, 0x15, 0xf8, 0x6b, 0xe0, 0xd8, 0x73,
    0x92, 0x97, 0xd6, 0x79, 0x45, 0x83, 0x05, 0x61, 0xb4, 0x8b, 0x0f, 0x18,
    0x97, 0x41, 0xd1, 0x2c, 0x52, 0x4e, 0x29, 0xa9, 0xea, 0xa9, 0xc6, 0x9a,
    0x8c, 0x04, 0xa5, 0x89, 0x74, 0xfa, 0x01, 0x85, 0x7b, 0x95, 0x0a, 0x2d,
    0xd3, 0xb1, 0x1c, 0x51, 0x8d, 0x4b, 0x18, 0x66, 0xa2, 0xb1, 0x53, 0x2d,
    0x4b, 0x54, 0xe5, 0x2a, 0x49, 0x3e, 0x3e, 0xd2, 0x92, 0x5b, 0xcc, 0x94,
    0x94, 0x33, 0x0b, 0xd3, 0x4e, 0x33, 0xca, 0x4c, 0x7a, 0x34, 0x2c, 0xce,
    0x3e, 0x53, 0x6f, 0xab, 0x5d, 0xd2, 0x6e, 0x31, 0xe8, 0x46, 0xe7, 0x71,
    0xbc, 0xd1, 0x6a, 0x38, 0x8f, 0x1d, 0x7e, 0x1b, 0xcb, 0xea, 0x90, 0x67,
    0x6e, 0x26, 0x51, 0x8b, 0x04, 0xed, 0x3e, 0xf8, 0xe6, 0x84, 0xfb, 0x5d,
    0x98, 0x65, 0x4e, 0x86, 0x0c, 0x75, 0xcf, 0xe8, 0x2d, 0xca, 0x78, 0x6a,
    0x5f, 0x38, 0xe6, 0xf6, 0x14, 0x23, 0x16, 0xb7, 0xac, 0x13, 0x01, 0xb1,
    0x2d, 0x4b, 0x7c, 0x2a, 0xd7, 0x1d, 0xae, 0x68, 0xfd, 0xc6, 0x99, 0x4b,
    0x8d, 0xd1, 0x17, 0x97, 0x3e, 0x08, 0x78, 0x01, 0x65, 0xd3, 0x23, 0x0b,
    0x17, 0xd5, 0x6b, 0xd8, 0x6a, 0x96, 0x49, 0x0d, 0x59, 0xa6, 0x32, 0xda,
    0xd6, 0xac, 0x1b, 0x00, 0xc8, 0xee, 0x54, 0xee, 0xc6, 0x10, 0x57, 0x5c,
    0x43, 0x5a, 0x98, 0xe6, 0x1a, 0x8e, 0x85, 0x47, 0xd1, 0xbd, 0xc4, 0x3a,
    0xe4, 0xf1, 0x7f, 0x9a, 0x73, 0x13, 0xd4, 0xb9, 0x45, 0x9b, 0xa6, 0x2f,
    0x7c, 0x83, 0xe8, 0x01, 0x0c, 0x43, 0xf5, 0x46, 0x10, 0xf8, 0x1d, 0xf3,
    0x12, 0x14, 0x0b, 0xd6, 0x22, 0x96, 0x13, 0x84, 0x04, 0xd1, 0x0e, 0x77,
    0x96, 0xa2, 0xf4, 0x5b, 0xec, 0xf7, 0x52, 0xcb, 0xfe, 0xd3, 0x8f, 0x0e,
    0x62, 0x6b, 0xc4, 0xa1, 0x8b, 0x36, 0xd2, 0xff, 0x50, 0x4f, 0x50, 0x26,
    0xd6, 0xa5, 0xfa, 0x23, 0x51, 0x60, 0x52, 0x89, 0x53, 0x2a, 0x4f, 0xff,
    0x8c, 0xf8, 0xa8, 0xc8, 0x4c, 0x59, 0x25, 0x5c, 0xd4, 0xde, 0x12, 0x3d,
    0xe8, 0xce, 0x58, 0xbd, 0xf2, 0xd5, 0x5f, 0x46, 0xde, 0x4a, 0xbe, 0x48,
    0xb5, 0x60, 0x84, 0x36, 0x0e, 0xad, 0x4b, 0xbf, 0x82, 0x93, 0x9c, 0x4e,
    0x0e, 0xad, 0xfe, 0x37, 0x7c, 0x85, 0xc5, 0xd3, 0x80, 0x8c, 0x20, 0x03,
    0x84, 0x5b, 0xb1, 0xf7, 0x7d, 0xca, 0xd3, 0x30, 0x64, 0x08, 0xa4, 0x47,
    0x2e, 0x34, 0x25, 0x62, 0xe1, 0x8f, 0xeb, 0x1f, 0x5b, 0x81, 0x2f, 0x81,
    0x32, 0x0d, 0x4e, 0x37, 0x9f, 0xa4, 0x0e, 0x35, 0xd4, 0x5a, 0x6c, 0xb7,
    0x2b, 0xc2, 0x50, 0x24, 0x8e, 0x4b, 0xe9, 0x57, 0x1f, 0xea, 0xd2, 0xf5,
    0x89, 0x25, 0xf2, 0x4a, 0xb7, 0x99, 0xb3, 0x4c, 0x5b, 0xf3, 0x0d, 0xfc,
    0x7e, 0x69, 0x88, 0x2e, 0x02, 0x6f, 0x1c, 0xb0, 0x9c, 0xae, 0x28, 0xa7,
    0xa0, 0xc8, 0x5e, 0x46, 0xb4, 0xb9, 0xa3, 0x07, 0xd9, 0x46, 0xa0, 0x0d,
    0xe3, 0xef, 0x1e, 0x11, 0xb9, 0xab, 0x6a, 0xa2, 0xed, 0x95, 0x8a, 0x69,
    0x42, 0x7e, 0x45, 0x6a, 0x7d, 0xa0, 0x99, 0x58, 0x66, 0x0f, 0x94, 0x86,
    0x04, 0xbd, 0x01, 0xfe, 0x1a, 0xe8, 0x1a, 0x34, 0xaa, 0xc5, 0x48, 0xea,
    0x78, 0xd8, 0x34, 0xf7, 0xc5, 0x9f, 0x23, 0x3f, 0xb6, 0xf0, 0x2c, 0x3e,
    0x9d, 0x33, 0xe2, 0x82, 0x02, 0x14, 0x3e, 0xf9, 0x0d, 0xdd, 0x59, 0xb5,
    0x8b, 0xd6, 0x50, 0xd5, 0x55, 0xeb, 0x91, 0xde, 0x31, 0xb2, 0xac, 0xb5,
    0x69, 0x40, 0x28, 0x31, 0xf6, 0x66, 0x85, 0x9f, 0xd0, 0xe5, 0x0a, 0x51,
    0x95, 0x34, 0xf1, 0x7e, 0x16, 0x94, 0xbb, 0xb8, 0x3c, 0x95, 0xe9, 0x03,
    0x51, 0x3a, 0x21, 0xe0, 0x58, 0x7f, 0x32, 0xeb, 0x44, 0x31, 0x57, 0x8d,
    0xa9, 0xb6, 0x72, 0xb2, 0x72, 0xe0, 0x7d, 0xa8, 0x47, 0x1e, 0x5c, 0x3c,
    0x36, 0x9d, 0x37, 0xa7, 0xe1, 0x82, 0x56, 0x96, 0x54, 0x4f, 0x56, 0x65,
    0x22, 0xf7, 0x0c, 0x36, 0x51, 0x47, 0x93, 0x97, 0xa3, 0x52, 0xbd, 0x06,
    0x80, 0x19, 0x56, 0x1d, 0x1a, 0xe4, 0x55, 0x8c, 0x99, 0xee, 0x33, 0xe5,
    0x00, 0xa7, 0x84, 0x84, 0xc4, 0xa5, 0x3a, 0xfc, 0x44, 0xc6, 0x90, 0x36,
    0x1f, 0x82, 0x26, 0x82, 0x16, 0x77, 0xa5, 0x28, 0x68, 0xa2, 0x66, 0xec,
    0x7d, 0xa1, 0xb0, 0xbf, 0x9a, 0x20, 0x97, 0x21, 0x15, 0x0c, 0xf7, 0xeb,
    0xca, 0x50, 0x31, 0x88, 0x16, 0x0c, 0x64, 0x42, 0xfe, 0x87, 0x82, 0xb4,
    0xfe, 0x8a, 0xd2, 0xea, 0x82, 0x7d, 0xa3, 0xf5, 0xbc, 0x48, 0x89, 0xcc,
    0xcc, 0x6b, 0x26, 0x58, 0x46, 0xa1, 0x1f, 0x55, 0xfd, 0xb3, 0xb6, 0xe1,
    0x79, 0xe0, 0x96, 0x10, 0x1c, 0x39, 0x32, 0x5a, 0xf6, 0xf9, 0x53, 0x66,
    0xf6, 0x8a, 0xfd, 0xc2, 0xcc, 0x2a, 0x3d, 0x9d, 0xcc, 0xd0, 0x27, 0x92,
    0xd7, 0x63, 0x0f, 0xb9, 0x45, 0xc7, 0x26, 0xfc, 0x23, 0x41, 0x97, 0xc4,
    0x2e, 0x6d, 0xc9, 0x63, 0x2d, 0xb4, 0x32, 0xc4, 0x0f, 0x55, 0x8a, 0x80,
    0xe9, 0xdc, 0x35, 0xcd, 0x7c, 0x23, 0x90, 0x6c, 0x59, 0x52, 0xf6, 0xc7,
    0xd9, 0x10, 0xe2, 0xac, 0x72, 0xd0, 0xac, 0x61, 0x4c, 0x22, 0x50, 0xc9,
    0x2e, 0xac, 0x5c, 0xab, 0xd9, 0x49, 0x09, 0x2a, 0xaf, 0xb0, 0xcf, 0x42,
    0x9d, 0x17, 0x10, 0x41, 0x10, 0x03, 0xb4, 0xe6, 0x9c, 0x32, 0xc0, 0x0e,
    0x67, 0x36, 0xd2, 0x4f, 0x79, 0x93, 0xde, 0x6d, 0xd0, 0xcc, 0x36, 0x89,
    0x92, 0x9e, 0xbb, 0x62, 0x6f, 0xe7, 0x95, 0xf6, 0xac, 0x5a, 0x14, 0x86,
    0x9b, 0xec, 0xdd, 0xbb, 0x4d, 0x9d, 0xb4, 0x04, 0xcd, 0x5f, 0xc5, 0xd5,
    0xe5, 0xd6, 0x1c, 0x29, 0x7b, 0xe7, 0x27, 0xb8, 0x3d, 0x03, 0x43, 0x30,
    0xa3, 0x0d, 0x5c, 0x8f, 0x55, 0x40, 0xeb, 0x12, 0x0b, 0xf3, 0xa8, 0xa3,
    0x21, 0x7b, 0x8f, 0x12, 0x24, 0x43, 0x03, 0xee, 0x1f, 0x4d, 0x36, 0x74,
    0x6e, 0x57, 0xaf, 0xe0, 0x25, 0x18, 0x75, 0xb9, 0x8a, 0xb3, 0x15, 0x67,
    0xe2, 0x6a, 0xaf, 0x24, 0xee, 0xa1, 0xf7, 0xa0, 0x10, 0xc3, 0xad, 0xda,
    0x8c, 0x19, 0xa6, 0x24, 0x5f, 0x2f, 0x32, 0x66, 0x41, 0xf6, 0xaf, 0xd6,
    0xc7, 0xae, 0xb3, 0x91, 0xca, 0x89, 0x95, 0x4e, 0x07, 0xd1, 0x11, 0x65,
    0xd3, 0x53, 0xf1, 0x67, 0x6b, 0x48, 0xb4, 0xa3, 0xc3, 0x9e, 0xfa, 0x35,
    0x86, 0x0c, 0x6b, 0xb4, 0x55, 0xdc, 0x59, 0x9b, 0x98, 0x61, 0x56, 0x47,
    0x7a, 0x77, 0x10, 0x75, 0x7a, 0xeb, 0x2b, 0x14, 0x04, 0x29, 0xe2, 0x0c,
    0x2b, 0x75, 0x31, 0xe7,
};
static std::uint8_t ct[1024] = {
    0x58, 0x92, 0x9b, 0xad, 0x21, 0x4e, 0x6c, 0x67, 0x79, 0x30, 0x67, 0xaa,
    0xa0, 0x27, 0x58, 0xb7, 0xe7, 0x1e, 0x1f, 0x90, 0xf1, 0x15, 0xef, 0xb2,
    0xaf, 0x4b, 0x3d, 0xd9, 0x79, 0xcc, 0x79, 0xcf, 0x1d, 0xb7, 0x60, 0x57,
    0x17, 0x6a, 0xe7, 0xfe, 0x6e, 0x2b, 0x55, 0x88, 0x92, 0x49, 0x03, 0xca,
    0x79, 0xee, 0x88, 0x56, 0x2a, 0xbd, 0xfd, 0xba, 0xcf, 0xa9, 0xa9, 0x82,
    0x42, 0xbf, 0xdc, 0xb7, 0x48, 0x6a, 0x81, 0x92, 0x48, 0xf1, 0x1a, 0x73,
    0x4d, 0xeb, 0xfb, 0xb2, 0xae, 0x52, 0xb3, 0x10, 0x00, 0x6a, 0xa3, 0xad,
    0x75, 0xc1, 0x1b, 0x59, 0xc2, 0x0c, 0x28, 0x63, 0xd1, 0xbf, 0x46, 0xb1,
    0xa0, 0x4a, 0x29, 0xa8, 0xcc, 0xfd, 0x5c, 0xce, 0xd8, 0xae, 0x16, 0x63,
    0x74, 0xb0, 0x14, 0x8b, 0x95, 0x05, 0x14, 0x6c, 0x73, 0x16, 0xe3, 0x90,
    0xc6, 0xff, 0xac, 0xe4, 0x28, 0xa0, 0xa3, 0xc6, 0xdc, 0x15, 0xdb, 0x74,
    0xcc, 0x67, 0x5d, 0x64, 0x1c, 0x31, 0xe3, 0x72, 0xfa, 0x0c, 0x3e, 0x5f,
    0xc5, 0x6b, 0x68, 0x70, 0xf5, 0xf2, 0x39, 0x83, 0x17, 0x01, 0x7e, 0xa0,
    0x0e, 0x00, 0x08, 0xb5, 0x3b, 0xb1, 0x38, 0x80, 0x67, 0x84, 0xee, 0x19,
    0x1c, 0x57, 0xf9, 0xc6, 0x13, 0xc0, 0x89, 0xf8, 0x81, 0x26, 0xfe, 0x52,
    0x10, 0xca, 0xfc, 0xab, 0x79, 0xe5, 0x3b, 0x51, 0xc3, 0x6b, 0xef, 0xd9,
    0x13, 0x31, 0x41, 0xfa, 0xf2, 0xe7, 0xcc, 0x40, 0x1b, 0x51, 0x5a, 0x6b,
    0x67, 0xcc, 0x2d, 0xb5, 0x36, 0x1b, 0x64, 0x15, 0x66, 0xc9, 0x06, 0x84,
    0x70, 0x10, 0xd4, 0x2c, 0x49, 0xf7, 0xc8, 0xb8, 0x12, 0xa5, 0x86, 0x96,
    0x33, 0x2f, 0x27, 0x39, 0xe4, 0x1f, 0x2d, 0x1f, 0xfc, 0x7c, 0xfd, 0xd5,
    0x3b, 0x4b, 0x40, 0x44, 0x4e, 0x70, 0xa6, 0x80, 0x52, 0x6f, 0xd7, 0x16,
    0xf7, 0x9e, 0xb2, 0x47, 0x27, 0x4c, 0xe6, 0xb0, 0x95, 0x46, 0xf4, 0xa9,
    0xcd, 0x5b, 0x83, 0xe2, 0x19, 0x0b, 0xb2, 0x05, 0x02, 0x9b, 0xa7, 0x2b,
    0xff, 0xd0, 0xfb, 0x96, 0x09, 0x70, 0x1b, 0x62, 0x7a, 0xe4, 0xb6, 0x49,
    0xff, 0x97, 0x81, 0x1d, 0xa1, 0x89, 0xc8, 0xa7, 0xa4, 0xfe, 0xa6, 0xca,
    0xfd, 0xda, 0x77, 0x19, 0xe8, 0x41, 0x98, 0x04, 0x5a, 0xcf, 0x9a, 0xbc,
    0x16, 0x88, 0x54, 0x67, 0x95, 0x3d, 0x20, 0xd6, 0x24, 0x4b, 0xca, 0x71,
    0xb3, 0x91, 0x4f, 0x1a, 0xb7, 0x66, 0xcd, 0xc5, 0xe0, 0x8e, 0xa5, 0xf6,
    0x43, 0x41, 0xeb, 0x2f, 0x34, 0x81, 0x9d, 0x30, 0xf3, 0x5b, 0x58, 0xe6,
    0xb5, 0xdc, 0xc8, 0xb2, 0xb5, 0x39, 0x1a, 0x03, 0xba, 0x6b, 0xb1, 0x6f,
    0x74, 0x7b, 0x9b, 0x1e, 0xdf, 0x56, 0x40, 0x7d, 0xee, 0x6f, 0x92, 0x0a,
    0x0a, 0xb4, 0x6b, 0xb6, 0x43, 0x5e, 0xb5, 0x94, 0x7a, 0xf1, 0x3a, 0xb7,
    0x6b, 0x20, 0x90, 0x44, 0xb9, 0xad, 0xe7, 0xd5, 0xad, 0x71, 0xd0, 0x37,
    0x98, 0x2a, 0x18, 0x75, 0xbd, 0x45, 0x2d, 0x23, 0x7a, 0x1d, 0x03, 0x3c,
    0x89, 0xd8, 0xd0, 0x0b, 0x11, 0xc3, 0x9b, 0x70, 0x2c, 0xfb, 0x90, 0x40,
    0x06, 0xbd, 0xa0, 0xd7, 0x28, 0x88, 0x0a, 0x4d, 0x75, 0xf4, 0x28, 0x2c,
    0x13, 0xa2, 0x03, 0x35, 0x85, 0xb1, 0xdc, 0x42, 0x71, 0x4a, 0xad, 0x37,
    0x50, 0x2e, 0x40, 0x8a, 0x94, 0x72, 0xae, 0x04, 0x6d, 0x95, 0x14, 0x7e,
    0xd6, 0xe3, 0x00, 0xab, 0x2f, 0x0a, 0x3e, 0x97, 0x9f, 0xd0, 0xde, 0xad,
    0xe2, 0xaf, 0x43, 0xb5, 0xbf, 0x1d, 0x33, 0xbd, 0x7b, 0xf7, 0x91, 0xa0,
    0x29, 0x7d, 0x60, 0x82, 0xba, 0x83, 0x47, 0xdb, 0xb0, 0x7a, 0x28, 0xba,
    0x10, 0x23, 0x21, 0x5d, 0xdc, 0x26, 0xcf, 0x32, 0x4c, 0x57, 0x50, 0xd0,
    0x03, 0x3d, 0xee, 0xf1, 0xff, 0x27, 0x78, 0x0d, 0x97, 0x27, 0x0d, 0x42,
    0x28, 0xfe, 0xb2, 0x4d, 0xe5, 0xe2, 0x85, 0x0a, 0x7a, 0xa9, 0x09, 0xb2,
    0xe1, 0x73, 0x7d, 0x27, 0x41, 0x5b, 0xff, 0xcd, 0xed, 0xfc, 0xb0, 0xe5,
    0x85, 0x7a, 0x2c, 0x8b, 0x94, 0x3b, 0xed, 0xa1, 0xaa, 0x9f, 0xdf, 0x05,
    0xcb, 0xe1, 0x05, 0x14, 0x54, 0x55, 0xf0, 0x73, 0x84, 0xee, 0x27, 0x24,
    0xe5, 0xeb, 0x2d, 0xde, 0xbc, 0xee, 0x68, 0xc3, 0x1f, 0x16, 0x88, 0x30,
    0x39, 0xdf, 0x52, 0x6c, 0x72, 0x1d, 0x79, 0x61, 0x2a, 0xdb, 0xc8, 0x65,
    0xed, 0x65, 0xc8, 0x8e, 0x7f, 0xeb, 0xb0, 0x03, 0xef, 0x1a, 0x84, 0xd3,
    0x57, 0xd0, 0x2b, 0x38, 0xb5, 0x3b, 0x3e, 0xaf, 0xe2, 0x46, 0x25, 0x9b,
    0xb8, 0x22, 0x5a, 0xb0, 0xd2, 0x67, 0x31, 0x60, 0x0e, 0x76, 0x5d, 0xc0,
    0x10, 0x92, 0xf5, 0x13, 0x28, 0x69, 0x71, 0x51, 0xf4, 0x1b, 0xa4, 0x75,
    0x1f, 0x32, 0x93, 0x08, 0x38, 0x8e, 0x39, 0xb4, 0xb9, 0xff, 0xf3, 0xf7,
    0x48, 0x03, 0xc5, 0xc6, 0x31, 0x8d, 0x7d, 0x8b, 0x80, 0xaa, 0xee, 0x17,
    0x8e, 0xba, 0xd1, 0x01, 0xf9, 0x1a, 0x8e, 0x23, 0xd4, 0x00, 0x0f, 0xcb,
    0x56, 0xa1, 0xab, 0xe5, 0x39, 0x07, 0x8f, 0xfe, 0x88, 0x7b, 0xe7, 0x75,
    0x8c, 0xc7, 0xdc, 0x88, 0x66, 0x30, 0x1c, 0xd9, 0xc7, 0xb1, 0x6d, 0xa6,
    0xc7, 0xe6, 0xfd, 0x96, 0xbb, 0x32, 0x2e, 0xec, 0x27, 0x69, 0xbb, 0xa3,
    0x1f, 0x66, 0xee, 0xcc, 0x13, 0x08, 0x3c, 0x4c, 0x50, 0xc3, 0x4e, 0x4a,
    0xbc, 0xa6, 0xb3, 0xdc, 0x33, 0xfc, 0xea, 0xd4, 0x4f, 0xa8, 0x81, 0x66,
    0x7c, 0xd8, 0x38, 0xff, 0xb5, 0xf7, 0x44, 0x66, 0x65, 0x0d, 0x44, 0x14,
    0x2f, 0x3b, 0xa9, 0x20, 0x2e, 0x6c, 0xe1, 0xd1, 0xa6, 0x79, 0x0d, 0xf1,
    0x69, 0xa2, 0x3d, 0x55, 0xaf, 0x9f, 0x7a, 0xb5, 0x60, 0x21, 0x97, 0x0c,
    0x8a, 0xfc, 0x84, 0x7c, 0xe4, 0x73, 0xbc, 0xdd, 0x70, 0xfa, 0x2d, 0xf3,
    0xdc, 0xf5, 0x4e, 0xa9, 0x65, 0x59, 0xac, 0xfc, 0x12, 0x22, 0x25, 0x3b,
    0x66, 0xe7, 0xd7, 0x26, 0xaa, 0xc5, 0xd4, 0x6d, 0x61, 0x6d, 0x89, 0x51,
    0x45, 0x0a, 0xa5, 0xd6, 0x7f, 0xc6, 0x0c, 0x96, 0x86, 0x41, 0xe3, 0x93,
    0x9f, 0x69, 0xa3, 0xfd, 0xb4, 0x1d, 0x97, 0xd9, 0x4e, 0x9c, 0xff, 0x77,
    0xea, 0xf0, 0xc6, 0x02, 0x8e, 0xce, 0x25, 0x1b, 0x18, 0x91, 0x0e, 0x0b,
    0x4d, 0x64, 0x7a, 0x00, 0xd8, 0xac, 0x1e, 0xd7, 0x96, 0xc5, 0x0f, 0xab,
    0x67, 0x77, 0x0f, 0x67, 0xf5, 0x54, 0xda, 0x94, 0x4f, 0xd9, 0xe3, 0x20,
    0x13, 0x66, 0xf2, 0x03, 0xc8, 0x7a, 0xf6, 0xb4, 0x74, 0xd6, 0x38, 0x33,
    0x19, 0x77, 0xd6, 0x6d, 0x7a, 0xd7, 0xea, 0x94, 0xdd, 0x5f, 0x4d, 0x3e,
    0x2f, 0x4f, 0xb0, 0x5a, 0x75, 0x9c, 0xbe, 0x5b, 0xd8, 0x25, 0x05, 0xe9,
    0xaa, 0x78, 0x56, 0x5d, 0xf3, 0xed, 0x98, 0xcb, 0x9f, 0x3d, 0xe5, 0x83,
    0x0e, 0x02, 0xb5, 0xde, 0xf1, 0xa2, 0x7b, 0x5e, 0x5a, 0x7d, 0x6f, 0x87,
    0x51, 0xcd, 0x90, 0xbe, 0xb2, 0x8b, 0x6b, 0x49, 0x65, 0xdf, 0x50, 0xbd,
    0xed, 0xec, 0x6b, 0x1c, 0x1c, 0x3e, 0xae, 0x0a, 0x57, 0x16, 0xdc, 0x51,
    0xf6, 0x58, 0x3e, 0x17, 0x21, 0x12, 0xac, 0x8d, 0xae, 0x36, 0xac, 0xf1,
    0xb1, 0x4d, 0x4b, 0x22, 0xc6, 0x32, 0x5c, 0x62, 0x6d, 0xef, 0x82, 0x1a,
    0x18, 0xab, 0x0f, 0x13, 0x98, 0x03, 0x65, 0x19, 0x4a, 0x60, 0x63, 0x75,
    0xf9, 0xe6, 0x6e, 0xad, 0x95, 0x6a, 0xf4, 0x4a, 0xee, 0xb3, 0x0b, 0x2e,
    0xa5, 0x21, 0x29, 0x58, 0x2a, 0xa5, 0x96, 0xdb, 0xed, 0x53, 0xc2, 0xcd,
    0xa2, 0x6a, 0xd7, 0x35, 0xdc, 0xfc, 0xb2, 0x72, 0xf9, 0x8b, 0x8d, 0xef,
    0x02, 0x1e, 0xbf, 0xc9,
};

void test_cfb_mode()
{
    std::uint8_t buf[1024];
    std::size_t  size, n;

    auto e = SM4CfbEncryptor(user_key, iv);
    e.do_final(buf, &size, pt, 1024);
    if (std::memcmp(buf, ct, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in cfb_mode");
    }
    e.reset(iv);
    e.update(buf, &n, pt, 100);
    size = n;
    e.do_final(buf + size, &n, pt + 100, 1024 - 100);
    size += n;
    if (std::memcmp(buf, ct, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in cfb_mode");
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
        throw std::runtime_error("err in Cfb_mode");
    }

    auto d = SM4CfbDecryptor(user_key, iv);
    d.do_final(buf, &size, ct, 1024);
    if (std::memcmp(buf, pt, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in cfb_mode");
    }
    d.reset(iv);
    d.update(buf, &n, ct, 100);
    size = n;
    d.do_final(buf + size, &n, ct + 100, 1024 - 100);
    size += n;
    if (std::memcmp(buf, pt, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in cfb_mode");
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
        throw std::runtime_error("err in cfb_mode");
    }
}