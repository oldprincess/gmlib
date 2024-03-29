#include <gmlib/block_cipher_mode/ecb_mode.h>

#include <cstring>

#include "sm4.h"
#include "test.h"

using namespace block_cipher_mode;
using SM4EcbEncryptor = EcbEncryptor<SM4>;
using SM4EcbDecryptor = EcbDecryptor<SM4>;

static std::uint8_t user_key[16] = {
    0xd1, 0x37, 0xc6, 0xa7, 0xe8, 0x0c, 0x32, 0x31,
    0x34, 0xdf, 0x61, 0x15, 0x82, 0x39, 0x93, 0x8a,
};
static std::uint8_t pt[1024] = {
    0x34, 0x04, 0x5a, 0x8f, 0x7c, 0xa0, 0x92, 0x83, 0x00, 0x0f, 0x83, 0xce,
    0x40, 0x07, 0x40, 0xe5, 0x77, 0x74, 0xd0, 0xdc, 0xb6, 0xbc, 0x6e, 0x7f,
    0x65, 0x4e, 0x35, 0x53, 0xe7, 0x80, 0x4b, 0xe0, 0x12, 0xfb, 0xa5, 0x6c,
    0x04, 0x47, 0x38, 0xf1, 0x58, 0xb6, 0xe0, 0x8f, 0x81, 0x5f, 0xcc, 0xde,
    0xdf, 0x08, 0xc9, 0xba, 0x09, 0xc1, 0x90, 0x26, 0x5c, 0xba, 0x6e, 0xb8,
    0x4a, 0x2c, 0x39, 0x7a, 0x2a, 0xdb, 0x54, 0x66, 0xe2, 0xa9, 0x12, 0x42,
    0x11, 0x70, 0x09, 0x31, 0xde, 0x5c, 0x0d, 0xb4, 0xd2, 0xf2, 0xbd, 0xd3,
    0x70, 0xd2, 0xac, 0x15, 0x49, 0x8a, 0x5b, 0x2c, 0xc1, 0x00, 0xe1, 0x48,
    0xb7, 0x60, 0x61, 0x49, 0x52, 0x86, 0x3f, 0xca, 0x76, 0xeb, 0x85, 0x92,
    0x63, 0x8d, 0x0e, 0xd3, 0x26, 0xe8, 0xab, 0xe0, 0xb0, 0x22, 0xa4, 0x8e,
    0xf6, 0x1a, 0x80, 0x57, 0x1f, 0x36, 0x03, 0xa0, 0x0e, 0xf3, 0x7a, 0xf2,
    0x25, 0x71, 0x95, 0x25, 0x0b, 0x51, 0x12, 0x3b, 0x76, 0x5c, 0x8d, 0x14,
    0x07, 0x99, 0x96, 0xb8, 0xe0, 0x50, 0x98, 0xc7, 0x3b, 0xe2, 0xbf, 0x03,
    0x13, 0x28, 0x11, 0x15, 0x62, 0xe7, 0x63, 0x3b, 0xe3, 0x37, 0x91, 0x07,
    0x04, 0xfb, 0xc0, 0xc2, 0xee, 0xa3, 0xd2, 0xd3, 0x61, 0xe5, 0xcb, 0x45,
    0xfa, 0x62, 0x95, 0xf9, 0x29, 0x7b, 0xb8, 0xe5, 0x1d, 0x8d, 0x36, 0x92,
    0xf1, 0x81, 0x39, 0x81, 0xa9, 0x17, 0x4c, 0xb1, 0x67, 0x9f, 0xd0, 0x19,
    0x08, 0x0a, 0x80, 0x87, 0xf2, 0xb3, 0x8c, 0xc4, 0x2f, 0x9d, 0xdf, 0x29,
    0x84, 0x5e, 0x24, 0x0c, 0x85, 0xef, 0x8a, 0x00, 0x9a, 0x4d, 0xc3, 0xab,
    0x51, 0xa5, 0x62, 0x9f, 0x9e, 0xfb, 0x1f, 0x3f, 0x39, 0x49, 0x60, 0x47,
    0xf7, 0xbd, 0x9c, 0x77, 0xaa, 0x50, 0x22, 0xb7, 0x42, 0xce, 0x1b, 0xa5,
    0xc9, 0xf1, 0x07, 0x09, 0xd3, 0xed, 0x8a, 0x6d, 0x5a, 0x73, 0xa7, 0xf0,
    0xee, 0x24, 0x13, 0x19, 0xb1, 0x04, 0xf5, 0x4a, 0xcd, 0xd9, 0x19, 0xf6,
    0x9b, 0x61, 0x9c, 0x7e, 0xaf, 0x18, 0xf7, 0xd6, 0x33, 0xd5, 0x8b, 0x2a,
    0xea, 0x5e, 0xe7, 0x85, 0xfe, 0xe2, 0x21, 0x0f, 0x5c, 0x06, 0x78, 0xc0,
    0x51, 0x23, 0x82, 0x7e, 0x38, 0x39, 0x2e, 0xe6, 0x3e, 0x09, 0x09, 0x62,
    0x2b, 0x2f, 0xf8, 0x02, 0xd0, 0x2f, 0x6a, 0x39, 0x0c, 0x28, 0x2b, 0xa1,
    0x7d, 0x10, 0x56, 0x6a, 0x5f, 0x82, 0x85, 0x77, 0x29, 0x34, 0xf5, 0x27,
    0x34, 0xe1, 0xd9, 0x9e, 0xf8, 0xab, 0xed, 0x50, 0x40, 0x51, 0xa3, 0x4a,
    0xa7, 0x28, 0x73, 0x6d, 0x8e, 0xe9, 0x02, 0x96, 0xd6, 0x2d, 0xcf, 0x28,
    0x20, 0x65, 0xd5, 0xb0, 0x28, 0x40, 0xef, 0x8a, 0x30, 0x7c, 0x25, 0x27,
    0xf8, 0x0b, 0x58, 0x7e, 0xfc, 0x2b, 0x84, 0x10, 0x7b, 0x10, 0x8e, 0xec,
    0x6a, 0x24, 0xac, 0x7b, 0xa1, 0xfa, 0x3a, 0x7c, 0x7d, 0xf7, 0xa5, 0xd2,
    0xe7, 0xf3, 0x7c, 0x65, 0x0a, 0x32, 0xdd, 0xc2, 0xd2, 0x90, 0x90, 0xe0,
    0x6c, 0xb9, 0x39, 0xd9, 0x5a, 0x24, 0x19, 0xbc, 0xcc, 0xba, 0x7e, 0x21,
    0x11, 0xb9, 0x78, 0xaa, 0xbc, 0x49, 0x20, 0x7e, 0xb2, 0xed, 0x3d, 0x20,
    0x4a, 0x42, 0xad, 0xb9, 0x9d, 0x64, 0x0c, 0xbe, 0xeb, 0x60, 0x02, 0xc3,
    0xa2, 0xe9, 0x00, 0xb9, 0x09, 0xed, 0x63, 0x8c, 0x74, 0xea, 0xea, 0x23,
    0x18, 0x4d, 0xcf, 0xd1, 0xe7, 0x1e, 0x32, 0xec, 0x80, 0x72, 0xc2, 0xa7,
    0xcd, 0x7b, 0xae, 0x21, 0xee, 0xf6, 0x16, 0x13, 0xec, 0x58, 0x2c, 0x08,
    0xcf, 0x18, 0x1d, 0x1d, 0x44, 0xb3, 0x99, 0xbd, 0x55, 0xc2, 0xe6, 0x34,
    0x76, 0xa8, 0xaf, 0xac, 0x57, 0x57, 0x09, 0xcb, 0x62, 0xe5, 0x07, 0xee,
    0x16, 0x00, 0xc8, 0x87, 0xfb, 0x61, 0xca, 0x22, 0x87, 0x1c, 0xb7, 0xa6,
    0xf2, 0x9e, 0x32, 0x9b, 0x99, 0xbe, 0xca, 0x50, 0x85, 0x93, 0x63, 0x74,
    0x6e, 0x7b, 0x7a, 0x8c, 0xc2, 0x57, 0x72, 0xd3, 0x30, 0xcf, 0x42, 0x49,
    0x93, 0x3c, 0xe7, 0x3d, 0xc7, 0x48, 0xd4, 0x3f, 0x0d, 0x9c, 0x63, 0xc0,
    0xe8, 0x26, 0x0d, 0x65, 0x62, 0xc1, 0x67, 0x64, 0x36, 0xd7, 0xcd, 0x37,
    0x2d, 0xfe, 0x91, 0x5d, 0x9e, 0x0e, 0xa0, 0x3a, 0x55, 0x38, 0x63, 0xb0,
    0x96, 0xf0, 0x68, 0x2f, 0x97, 0x82, 0xaf, 0xb8, 0xfa, 0x30, 0x85, 0x2e,
    0x8f, 0x65, 0xa3, 0x65, 0x17, 0x08, 0x03, 0xe0, 0xf8, 0xc5, 0x30, 0x9b,
    0x6a, 0xc1, 0x41, 0xeb, 0x70, 0x41, 0xdc, 0x72, 0xad, 0x64, 0x90, 0x7a,
    0x4f, 0x6b, 0x64, 0xeb, 0xd6, 0x9a, 0x2d, 0x66, 0x4d, 0x0b, 0xe6, 0xab,
    0x5c, 0xda, 0x59, 0x9c, 0xa8, 0x7d, 0x2b, 0x3e, 0xda, 0xab, 0xcb, 0x4c,
    0x0a, 0xae, 0xd1, 0x24, 0x54, 0x4c, 0x40, 0x02, 0x7e, 0x8d, 0xe2, 0xd9,
    0x7a, 0x9f, 0x42, 0xec, 0x65, 0xb8, 0xa7, 0x98, 0x2e, 0xfe, 0xb5, 0xf5,
    0x97, 0xa1, 0x8b, 0x6c, 0x6d, 0x45, 0x53, 0x53, 0x21, 0x97, 0x18, 0x53,
    0xa1, 0x22, 0x59, 0x1c, 0xb6, 0xd9, 0x74, 0x7b, 0x1c, 0x1a, 0x4b, 0xe4,
    0x67, 0x95, 0xd6, 0xa6, 0x9e, 0x9e, 0x56, 0xad, 0x25, 0x24, 0xc9, 0x52,
    0x43, 0xb3, 0xa9, 0x68, 0x5f, 0xf8, 0x0a, 0xcf, 0xf7, 0xcd, 0xfd, 0x3a,
    0xc6, 0x61, 0x79, 0x1f, 0xe9, 0x38, 0xf9, 0x62, 0x81, 0x53, 0x7a, 0x4b,
    0x9d, 0xa7, 0x7b, 0xda, 0x03, 0xda, 0x8c, 0xc2, 0xdb, 0x0f, 0xf3, 0x0d,
    0xad, 0xe9, 0xb7, 0xe1, 0xf9, 0x32, 0xfd, 0xc9, 0xd4, 0x2a, 0x7c, 0x09,
    0x53, 0x4f, 0x1f, 0xf0, 0x24, 0xe6, 0xa2, 0x09, 0x40, 0x63, 0xde, 0x2d,
    0x77, 0xa6, 0xe4, 0x34, 0xfa, 0x17, 0x37, 0xc0, 0x48, 0x74, 0xb0, 0x47,
    0xec, 0x90, 0xe4, 0xb5, 0x2f, 0x35, 0x8c, 0x8f, 0xe5, 0x4a, 0x4d, 0x45,
    0x1f, 0x09, 0x3b, 0x73, 0x60, 0xb6, 0xa5, 0xe1, 0x4e, 0xd9, 0x69, 0x84,
    0xdc, 0x95, 0xa2, 0x5a, 0x54, 0x0e, 0xb7, 0xad, 0x22, 0x30, 0x8d, 0x4d,
    0x9d, 0xbf, 0x3c, 0xb3, 0xb6, 0x00, 0xbf, 0xd7, 0x99, 0x72, 0xa6, 0xdf,
    0x70, 0x2e, 0xdc, 0x46, 0x16, 0x28, 0xe9, 0x6f, 0x23, 0x6f, 0x7e, 0xdc,
    0x86, 0x97, 0x30, 0xc5, 0xc9, 0x85, 0x05, 0x11, 0x11, 0xa1, 0x9d, 0x26,
    0x22, 0xdd, 0x31, 0xee, 0xee, 0x94, 0x28, 0x0d, 0x69, 0xda, 0x8f, 0x9c,
    0xcc, 0x42, 0xdf, 0xb0, 0x78, 0x8a, 0x2a, 0x49, 0x83, 0x6e, 0x50, 0x9b,
    0xb3, 0xcb, 0xde, 0xf3, 0xa3, 0x92, 0x52, 0x58, 0xf6, 0x68, 0xe1, 0xae,
    0x79, 0xea, 0xe4, 0xe8, 0x9d, 0xe3, 0xf9, 0xda, 0xa0, 0x41, 0x89, 0x34,
    0x67, 0x41, 0x7c, 0xec, 0x39, 0x1e, 0xb9, 0xd9, 0x1a, 0xbc, 0x4d, 0xa6,
    0xb1, 0x61, 0x3c, 0xc6, 0x38, 0x2b, 0x85, 0x24, 0x5d, 0xe7, 0xb6, 0x60,
    0x4c, 0xcb, 0x24, 0xd1, 0x5c, 0xe1, 0xb1, 0x1a, 0xcc, 0xb2, 0xa9, 0x5f,
    0x20, 0xc4, 0x1c, 0x4d, 0xa9, 0xa2, 0xc8, 0xed, 0xa9, 0x30, 0xa8, 0x53,
    0xec, 0x85, 0xd0, 0x7b, 0xfd, 0xe4, 0x3a, 0x05, 0x8a, 0x45, 0x35, 0x74,
    0xe5, 0xc6, 0x19, 0xfd, 0xd2, 0xb7, 0x66, 0x7d, 0x7e, 0x45, 0xbc, 0xde,
    0x70, 0x27, 0x7e, 0xb9, 0x3f, 0x51, 0xbf, 0xb3, 0x64, 0x8d, 0x35, 0xdb,
    0x33, 0x82, 0x5e, 0x30, 0x95, 0x67, 0x29, 0x61, 0xb5, 0x73, 0xb0, 0x4a,
    0x95, 0x48, 0x0b, 0x6a, 0xa0, 0x10, 0x5d, 0x26, 0xd2, 0x8f, 0x97, 0xb2,
    0xa6, 0x00, 0xbd, 0x68, 0x13, 0x7d, 0xc2, 0x11, 0xfc, 0x95, 0xa7, 0xae,
    0x5d, 0x99, 0xd0, 0x07, 0xd6, 0x50, 0x8f, 0x9a, 0x51, 0x66, 0x03, 0x5b,
    0x3a, 0x50, 0x82, 0xe3,
};
static std::uint8_t ct[1024] = {
    0x01, 0xff, 0xbb, 0x39, 0x33, 0x12, 0x9c, 0x96, 0x9b, 0xb9, 0x12, 0x7a,
    0x4d, 0xcc, 0x4b, 0xf2, 0x48, 0x2d, 0x8d, 0xad, 0xc7, 0x03, 0xa4, 0x5f,
    0x90, 0xd2, 0x42, 0x2b, 0x73, 0xc0, 0x90, 0x14, 0x2e, 0x5e, 0xbc, 0x8e,
    0x21, 0x8e, 0x46, 0x63, 0x3f, 0x46, 0x02, 0x8c, 0x21, 0x58, 0x86, 0x51,
    0x27, 0x79, 0x34, 0xed, 0x34, 0xf0, 0x2e, 0x2c, 0x42, 0x41, 0x9f, 0x45,
    0x2e, 0x5b, 0x00, 0x90, 0xce, 0x75, 0xec, 0x99, 0x03, 0x86, 0x27, 0x6c,
    0x86, 0xce, 0x28, 0x24, 0x5e, 0x38, 0x07, 0x97, 0x4f, 0xf8, 0x00, 0xd8,
    0x9c, 0x8c, 0x0a, 0xe3, 0x1f, 0x3a, 0xca, 0x67, 0x89, 0x80, 0x06, 0x4e,
    0xd3, 0xb7, 0x21, 0x69, 0xe7, 0xb8, 0xeb, 0xeb, 0x38, 0xba, 0x21, 0xa9,
    0x5a, 0xd2, 0x90, 0xdd, 0xe3, 0xe3, 0xfb, 0xe1, 0x70, 0xbc, 0x8e, 0xb6,
    0x54, 0xbb, 0x88, 0x08, 0x32, 0x43, 0x0b, 0x9a, 0x55, 0xc5, 0x81, 0xfb,
    0x9b, 0xa6, 0xbe, 0xf4, 0x17, 0x81, 0x83, 0x82, 0x04, 0x7d, 0xba, 0x78,
    0x5b, 0xbd, 0x0d, 0x59, 0xd6, 0xcd, 0x9c, 0xb8, 0x06, 0x99, 0x80, 0x5c,
    0xd1, 0x09, 0xef, 0xb6, 0x00, 0x01, 0x30, 0x96, 0xb3, 0x48, 0xf9, 0xd2,
    0xd3, 0x01, 0x57, 0xcf, 0x02, 0xf5, 0x97, 0x61, 0xf0, 0x98, 0x23, 0xc1,
    0xa1, 0xfb, 0x6e, 0xff, 0x76, 0xce, 0x7c, 0xa3, 0x20, 0x89, 0x75, 0x5b,
    0xe5, 0x17, 0xcc, 0x9d, 0xef, 0x44, 0x7a, 0x03, 0x80, 0x40, 0x0d, 0x33,
    0xc3, 0xb9, 0x2c, 0x51, 0xbc, 0x17, 0x18, 0x8d, 0x38, 0xc1, 0xc8, 0xf4,
    0x56, 0x5e, 0x31, 0xbc, 0x0f, 0xd9, 0xea, 0x60, 0x65, 0x6c, 0x71, 0x55,
    0x80, 0x36, 0xb4, 0xfa, 0x52, 0x8e, 0x82, 0xc0, 0x71, 0xf1, 0x92, 0x96,
    0x5a, 0xcc, 0x91, 0x22, 0xc0, 0xde, 0xf2, 0xa9, 0x6c, 0x85, 0x65, 0xb1,
    0x95, 0x37, 0x25, 0x6f, 0x9c, 0x3b, 0x40, 0xa0, 0x8b, 0x4a, 0xfd, 0x79,
    0x6b, 0xd3, 0x03, 0x43, 0x06, 0x30, 0x16, 0xaf, 0x24, 0x80, 0x49, 0x3c,
    0xeb, 0x03, 0x3f, 0x9a, 0xae, 0x8a, 0x1f, 0x12, 0x17, 0x17, 0x6b, 0xf3,
    0xea, 0xff, 0x25, 0xe0, 0x47, 0x04, 0x21, 0xa2, 0xd4, 0x11, 0x5f, 0x88,
    0xb6, 0xe2, 0xce, 0x40, 0x4a, 0xe8, 0xcd, 0x34, 0xa4, 0x80, 0x5c, 0x85,
    0x74, 0x0a, 0x94, 0x52, 0x5d, 0xb7, 0x3e, 0xa6, 0xd9, 0xb0, 0x79, 0x22,
    0x07, 0xb5, 0x21, 0x7b, 0xed, 0x6d, 0x45, 0xdd, 0x00, 0x59, 0xba, 0x76,
    0xdb, 0xc0, 0xa7, 0xfb, 0x4b, 0xb6, 0x19, 0xf0, 0x31, 0x62, 0xcd, 0x1e,
    0xe5, 0xd0, 0x29, 0xaf, 0xc2, 0x94, 0xf5, 0xd6, 0xca, 0x81, 0x25, 0x20,
    0x52, 0x3c, 0xe6, 0x2c, 0xeb, 0xcf, 0xf4, 0xc2, 0x39, 0xcb, 0x38, 0xc7,
    0xab, 0x97, 0x43, 0x41, 0x6e, 0xa5, 0x35, 0x06, 0x4e, 0xa8, 0xcc, 0xa4,
    0x7c, 0x5b, 0x0d, 0xab, 0x1e, 0xc5, 0x24, 0xbc, 0xb6, 0x2a, 0x52, 0x64,
    0x92, 0x30, 0x02, 0x68, 0xd4, 0x2f, 0x4d, 0xb6, 0xbb, 0xe5, 0xb7, 0xab,
    0xa0, 0x79, 0x76, 0x17, 0xcf, 0xfd, 0xe6, 0x92, 0x61, 0x24, 0xa7, 0x8a,
    0x41, 0x26, 0x3f, 0xb1, 0x76, 0x1d, 0x92, 0x62, 0xc8, 0x99, 0x62, 0x8f,
    0xb9, 0x32, 0xdd, 0x66, 0x34, 0x91, 0xa9, 0x61, 0xb5, 0x5d, 0xa3, 0x09,
    0x37, 0x62, 0x6e, 0x45, 0xae, 0x3e, 0x63, 0xa5, 0x74, 0xb8, 0x46, 0x72,
    0x31, 0x9f, 0x27, 0xbf, 0xe6, 0x7c, 0x36, 0x15, 0x05, 0x92, 0xfc, 0xd3,
    0x35, 0x6d, 0x14, 0xfe, 0xa3, 0x08, 0xc2, 0xae, 0x86, 0x17, 0x5d, 0x0d,
    0x34, 0x51, 0xc7, 0x98, 0x3b, 0x04, 0xea, 0xf7, 0xf9, 0x28, 0xde, 0xb4,
    0x0c, 0xc6, 0x61, 0x91, 0xab, 0x15, 0xbc, 0x3b, 0xc6, 0x91, 0x74, 0xea,
    0xfc, 0xd0, 0x7c, 0x94, 0x3f, 0xe0, 0xdf, 0x89, 0xe1, 0x7f, 0x7a, 0x09,
    0xa2, 0xd8, 0x7d, 0xc8, 0xbc, 0x53, 0xd3, 0x94, 0x19, 0x67, 0xd8, 0x78,
    0x6d, 0x31, 0x75, 0x5c, 0x49, 0xc9, 0x60, 0x26, 0xdc, 0x5b, 0x4e, 0xa6,
    0x89, 0xba, 0x3e, 0x0e, 0xb3, 0x13, 0xc0, 0x0d, 0x6b, 0x37, 0x77, 0x19,
    0x3a, 0xdc, 0x1d, 0x00, 0x8f, 0x09, 0x9d, 0x40, 0xbc, 0xa8, 0x91, 0xb4,
    0xf6, 0xa1, 0xc5, 0x81, 0xfd, 0xee, 0x38, 0x96, 0x51, 0x52, 0x19, 0x57,
    0x94, 0xa6, 0x5b, 0x80, 0xe5, 0x5d, 0xcc, 0xba, 0xc9, 0xc4, 0xc5, 0xa9,
    0x59, 0x31, 0xec, 0x06, 0xae, 0x6b, 0x1d, 0xe4, 0x27, 0x5d, 0x88, 0x34,
    0x2c, 0x80, 0xc0, 0xfc, 0x31, 0xa7, 0x89, 0xb3, 0x1f, 0x7f, 0x45, 0xa5,
    0xa3, 0x9c, 0xa5, 0xec, 0xcc, 0x3f, 0xfe, 0x06, 0x43, 0x6b, 0x99, 0x62,
    0xac, 0x6a, 0xd3, 0x45, 0xaa, 0xa0, 0xc0, 0xaa, 0x02, 0x04, 0xc6, 0xfe,
    0x52, 0x86, 0xcc, 0xc3, 0x62, 0x72, 0xd5, 0x44, 0x5f, 0x7e, 0xbb, 0xfd,
    0x89, 0xb6, 0xe5, 0x57, 0xfa, 0x0f, 0xde, 0x19, 0xea, 0x61, 0x98, 0x24,
    0xff, 0xae, 0x1b, 0x9e, 0xbb, 0xf4, 0xe2, 0x33, 0xd0, 0xf3, 0x21, 0xc0,
    0x9a, 0xf9, 0x62, 0xcb, 0xe6, 0x3e, 0xe4, 0x44, 0x61, 0xdd, 0xbf, 0xbc,
    0xd6, 0xc5, 0x59, 0x96, 0x48, 0xb6, 0xbd, 0xb2, 0x05, 0x6c, 0xe7, 0x03,
    0x10, 0xbb, 0x0d, 0x12, 0x91, 0xa7, 0xbc, 0xaf, 0x4a, 0x40, 0x29, 0x58,
    0xe8, 0xb5, 0xf7, 0x64, 0x71, 0x24, 0x9e, 0x43, 0x9c, 0x58, 0xb9, 0x24,
    0x65, 0xcd, 0xb9, 0x4b, 0x31, 0x0e, 0x61, 0xaf, 0xbd, 0x70, 0x99, 0xb6,
    0x03, 0xc8, 0xb4, 0x7a, 0xd0, 0xdd, 0x6b, 0xa6, 0x18, 0xb5, 0xca, 0x6c,
    0x55, 0x66, 0xfe, 0x61, 0x9b, 0x13, 0x27, 0xc7, 0x5c, 0xbb, 0xd1, 0xc1,
    0x06, 0xf2, 0x61, 0x4f, 0xf4, 0x76, 0x4c, 0x64, 0xb9, 0x4f, 0x89, 0x17,
    0x39, 0x02, 0x46, 0x0d, 0x3c, 0x27, 0x06, 0x80, 0xcf, 0x4b, 0x64, 0x4a,
    0xcc, 0xe6, 0xb1, 0x2c, 0x3b, 0x2c, 0x0e, 0x06, 0xf0, 0xa9, 0x2c, 0xdb,
    0xc6, 0xac, 0xea, 0x83, 0x06, 0xc2, 0xf6, 0x89, 0x6b, 0x50, 0x92, 0xf5,
    0x0f, 0x9f, 0x66, 0x06, 0xd5, 0xb8, 0x81, 0x5a, 0xf2, 0x0b, 0xc1, 0xb3,
    0xa3, 0xf0, 0xe6, 0x10, 0x3d, 0xf3, 0x7b, 0x75, 0xbc, 0x24, 0x94, 0x4e,
    0x0d, 0x83, 0x71, 0xd2, 0x78, 0x06, 0x80, 0xe3, 0xb4, 0xdc, 0xf9, 0xcb,
    0x85, 0xa0, 0x71, 0x4c, 0xba, 0x7a, 0xce, 0x14, 0x23, 0xbb, 0xbf, 0x55,
    0xbb, 0xc9, 0x60, 0xea, 0x3a, 0x6e, 0x8c, 0x97, 0x78, 0xe5, 0xaf, 0x06,
    0x95, 0x0d, 0x16, 0x4e, 0xd6, 0x17, 0x6a, 0x01, 0x81, 0x21, 0x8e, 0xee,
    0x7d, 0x16, 0x3d, 0x10, 0x48, 0xe0, 0xcc, 0xe3, 0xa9, 0xd5, 0x2d, 0x99,
    0xfe, 0xc5, 0x2f, 0xfb, 0x5c, 0xd1, 0x9d, 0x52, 0x22, 0x89, 0x20, 0x55,
    0x07, 0xee, 0xd8, 0xa1, 0xc1, 0x0a, 0x15, 0xc8, 0x93, 0x0f, 0xe4, 0xf6,
    0xe4, 0xa3, 0xf0, 0x3b, 0xdd, 0x5a, 0x7c, 0x1d, 0x52, 0x9a, 0x49, 0x5b,
    0xe9, 0x5e, 0xb7, 0x68, 0x9c, 0x09, 0xf3, 0x4c, 0x0a, 0x12, 0xc1, 0x86,
    0xee, 0xfc, 0x6e, 0x8d, 0xe5, 0x32, 0x04, 0xfc, 0x72, 0xd1, 0x1e, 0x43,
    0x39, 0xa8, 0x00, 0x21, 0x07, 0x53, 0x23, 0x73, 0xcd, 0x36, 0x8f, 0x44,
    0xcd, 0xf1, 0x12, 0xc1, 0xa7, 0xd5, 0x8d, 0x25, 0xd3, 0x3b, 0xbb, 0xb9,
    0x4f, 0x7e, 0x45, 0x74, 0x53, 0x58, 0xf4, 0x36, 0xd3, 0x72, 0xf9, 0xd1,
    0xeb, 0x1c, 0xd2, 0x6f, 0x86, 0x2c, 0x7c, 0xfb, 0x97, 0x22, 0x21, 0x76,
    0x77, 0x95, 0x9f, 0x63, 0xc2, 0x71, 0x76, 0x77, 0x6a, 0xaa, 0x05, 0xa4,
    0xa0, 0xd8, 0x42, 0x9e, 0xe1, 0xcd, 0xf7, 0x27, 0xcf, 0xab, 0xd0, 0x7f,
    0x90, 0xf6, 0x1d, 0x7f,
};

void test_ecb_mode()
{
    std::uint8_t buf[1024];
    std::size_t  size, n;

    auto e = SM4EcbEncryptor(user_key);
    e.do_final(buf, &size, pt, 1024);
    if (std::memcmp(buf, ct, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in ecb_mode");
    }
    e.reset();
    e.update(buf, &n, pt, 100);
    size = n;
    e.do_final(buf + size, &n, pt + 100, 1024 - 100);
    size += n;
    if (std::memcmp(buf, ct, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in ecb_mode");
    }
    e.reset();
    e.update(buf, &n, pt, 100);
    size = n;
    e.update(buf + size, &n, pt + 100, 1024 - 100);
    size += n;
    e.do_final(buf + size, &n, nullptr, 0);
    size += n;
    if (std::memcmp(buf, ct, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in ecb_mode");
    }

    auto d = SM4EcbDecryptor(user_key);
    d.do_final(buf, &size, ct, 1024);
    if (std::memcmp(buf, pt, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in ecb_mode");
    }
    d.reset();
    d.update(buf, &n, ct, 100);
    size = n;
    d.do_final(buf + size, &n, ct + 100, 1024 - 100);
    size += n;
    if (std::memcmp(buf, pt, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in ecb_mode");
    }
    d.reset();
    d.update(buf, &n, ct, 100);
    size = n;
    d.update(buf + size, &n, ct + 100, 1024 - 100);
    size += n;
    d.do_final(buf + size, &n, nullptr, 0);
    size += n;
    if (std::memcmp(buf, pt, 1024) != 0 || size != 1024)
    {
        throw std::runtime_error("err in ecb_mode");
    }
}