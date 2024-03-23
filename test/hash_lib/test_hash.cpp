#include "test.h"
#include "sm3.h"
#include <cstring>

static std::uint8_t data[1124] = {
    0x10, 0x01, 0x09, 0x5f, 0xd9, 0xdb, 0x69, 0xd8, 0x48, 0x52, 0x28, 0x10,
    0x9b, 0x91, 0x32, 0x50, 0x47, 0xcf, 0x75, 0x0a, 0xee, 0x41, 0x40, 0x57,
    0x41, 0xbf, 0xe5, 0x39, 0xd7, 0x99, 0x73, 0xb6, 0x7d, 0xb9, 0xa6, 0xa8,
    0x5d, 0x54, 0x65, 0x94, 0x8a, 0xe0, 0x65, 0x5b, 0x8b, 0xa7, 0x91, 0x53,
    0x69, 0x14, 0x6d, 0x7a, 0x7d, 0x3f, 0xfc, 0xca, 0x60, 0xf7, 0x14, 0xfa,
    0x97, 0x7c, 0xd9, 0x54, 0x77, 0x30, 0x60, 0x45, 0xa3, 0x32, 0xf7, 0x45,
    0x78, 0x00, 0x0d, 0x38, 0x89, 0x55, 0x05, 0xdd, 0xf9, 0x02, 0x1d, 0xcf,
    0xd3, 0x40, 0xd0, 0xac, 0xaf, 0x18, 0x1b, 0x61, 0xee, 0x19, 0x7f, 0x1a,
    0x28, 0xb3, 0x51, 0xa7, 0x56, 0xe5, 0x0a, 0x47, 0x44, 0x9d, 0x2b, 0xb2,
    0xd1, 0xea, 0x6f, 0xc0, 0xc3, 0x6f, 0xa0, 0xfe, 0x63, 0xa0, 0x46, 0x43,
    0x27, 0x08, 0xc9, 0x45, 0xde, 0x9f, 0x6d, 0x2c, 0x5f, 0xe8, 0x39, 0x0c,
    0x62, 0x6e, 0x8e, 0xc3, 0x9c, 0xd6, 0x25, 0xaf, 0x76, 0x7f, 0x2f, 0xb3,
    0x7a, 0x48, 0x5d, 0x95, 0xbd, 0x6a, 0x6c, 0x2f, 0x44, 0xc7, 0xcb, 0xc2,
    0x19, 0x59, 0x52, 0x51, 0xb9, 0xc9, 0xe1, 0x67, 0x85, 0xf6, 0x95, 0xa6,
    0x62, 0x9c, 0x44, 0x2d, 0xe3, 0xe6, 0xcf, 0xe5, 0x81, 0x2f, 0xca, 0x1f,
    0x6a, 0x5a, 0xfd, 0x9b, 0x0c, 0x1f, 0xfc, 0xd5, 0x85, 0x30, 0xc2, 0xfe,
    0xaf, 0x03, 0x93, 0xc2, 0x09, 0x1b, 0x22, 0x1a, 0x94, 0x68, 0xfe, 0x8b,
    0xc2, 0x17, 0x72, 0x43, 0x72, 0x03, 0x8a, 0x97, 0xba, 0x89, 0xde, 0x72,
    0x0e, 0x9b, 0x1a, 0xcd, 0x69, 0x1b, 0x01, 0x0d, 0x3c, 0xf7, 0xaa, 0x73,
    0xe9, 0x3d, 0xef, 0xc9, 0x72, 0x88, 0xed, 0x80, 0x11, 0x15, 0x0e, 0x4c,
    0xde, 0x09, 0xf7, 0x1b, 0xb0, 0x78, 0x21, 0x8b, 0x4b, 0x2f, 0x8a, 0x4b,
    0xc8, 0xac, 0xf6, 0x92, 0x1a, 0xba, 0xfd, 0x72, 0x14, 0xb7, 0xe3, 0xa9,
    0x4f, 0xdb, 0x48, 0x45, 0x43, 0x05, 0x75, 0x0a, 0x44, 0x92, 0x3f, 0x44,
    0x4d, 0x0c, 0x65, 0x71, 0x16, 0x8a, 0xa0, 0xaa, 0xe7, 0x36, 0x82, 0x2f,
    0x2d, 0xa7, 0xc3, 0x59, 0x8a, 0xb7, 0x71, 0x03, 0xce, 0x4e, 0x94, 0x69,
    0xb0, 0x58, 0x0f, 0xd6, 0x70, 0x39, 0x22, 0x03, 0x5d, 0x51, 0x0f, 0xc1,
    0x29, 0xe7, 0xb1, 0xf5, 0xa3, 0xdc, 0x76, 0x09, 0x1a, 0x4f, 0x06, 0x30,
    0x8a, 0xba, 0xf2, 0xc7, 0x7f, 0x34, 0x21, 0x06, 0xc8, 0x64, 0xc4, 0x32,
    0x47, 0x89, 0x40, 0xe9, 0x42, 0x6e, 0x47, 0xdd, 0xd1, 0x20, 0x84, 0x41,
    0x7e, 0xa8, 0x48, 0x8e, 0xf8, 0xc2, 0xb2, 0x3c, 0x85, 0x85, 0x6d, 0xe2,
    0x81, 0x6b, 0xb0, 0xf3, 0x22, 0x1b, 0x33, 0xa4, 0x7a, 0xbb, 0x49, 0xf9,
    0xba, 0x70, 0x54, 0x7b, 0x2f, 0xd9, 0xb5, 0xec, 0x27, 0x00, 0xc6, 0x03,
    0x54, 0x20, 0x35, 0x9b, 0x94, 0x0d, 0x78, 0xc0, 0xd9, 0xb5, 0x80, 0x64,
    0x08, 0xe0, 0x38, 0x20, 0xff, 0x7f, 0xf2, 0x03, 0xc5, 0xf2, 0x2b, 0x0c,
    0x4b, 0xd2, 0xdb, 0x8e, 0xe7, 0x7f, 0xe2, 0xac, 0x9a, 0x01, 0xbb, 0x9e,
    0x89, 0x66, 0x96, 0xd4, 0x62, 0x1a, 0x00, 0xa8, 0xb4, 0xbd, 0x3f, 0xa1,
    0x19, 0x6d, 0xa3, 0x38, 0x78, 0xf6, 0x90, 0x25, 0x83, 0x52, 0xc1, 0xc7,
    0xa8, 0xeb, 0xd1, 0xa2, 0x62, 0x82, 0xfd, 0x79, 0x65, 0x3b, 0x30, 0xf4,
    0x30, 0x09, 0xc3, 0x41, 0xd8, 0x45, 0xe6, 0x75, 0x3f, 0xa9, 0x76, 0x4e,
    0x44, 0x56, 0x6e, 0x1e, 0x6b, 0x13, 0x11, 0x4e, 0x5f, 0x06, 0xf8, 0xc6,
    0x85, 0x9d, 0xb5, 0x7e, 0x08, 0x9b, 0xeb, 0x69, 0x50, 0xd1, 0x4b, 0xed,
    0x9c, 0x89, 0xa2, 0x8c, 0x69, 0x16, 0xbc, 0xac, 0x93, 0xe0, 0x36, 0x62,
    0x56, 0x51, 0xd3, 0xbd, 0x35, 0x28, 0x8f, 0xe0, 0x00, 0x59, 0x38, 0x01,
    0xa8, 0xba, 0x23, 0x29, 0xe9, 0x2f, 0x63, 0x66, 0x4a, 0x3a, 0x24, 0x35,
    0x07, 0x2c, 0x4c, 0xd7, 0x59, 0xda, 0x91, 0x8a, 0x0a, 0x32, 0x50, 0x1b,
    0x09, 0xa1, 0xcf, 0x19, 0x88, 0x0b, 0x44, 0x82, 0xad, 0x5e, 0xaa, 0x62,
    0xd9, 0x04, 0xd4, 0xac, 0x0c, 0xf2, 0x66, 0x88, 0x5c, 0x41, 0x46, 0xe8,
    0x05, 0xcb, 0xe3, 0xf3, 0xf5, 0x24, 0xc0, 0x27, 0x65, 0x9b, 0x52, 0x66,
    0x6c, 0x76, 0x28, 0xa0, 0xc1, 0xf9, 0x92, 0xc2, 0xdd, 0x3f, 0xcf, 0x9c,
    0x28, 0x2d, 0x83, 0x75, 0x37, 0xdd, 0x1f, 0xed, 0x26, 0x81, 0x1c, 0x97,
    0x8b, 0x48, 0x13, 0x96, 0x0f, 0x5d, 0x4e, 0xdf, 0xb0, 0xfa, 0xb5, 0xef,
    0xe2, 0x0d, 0xf2, 0xd9, 0x2b, 0x3f, 0x15, 0xb6, 0xcc, 0xa8, 0x61, 0x71,
    0x66, 0x07, 0x70, 0xab, 0xbd, 0x1e, 0xa8, 0x35, 0x36, 0x92, 0x83, 0xf9,
    0xf6, 0xeb, 0x60, 0xe1, 0x95, 0x54, 0xc3, 0x21, 0x1a, 0xb5, 0xef, 0x38,
    0x04, 0xc1, 0x97, 0x9e, 0xcc, 0x06, 0xf7, 0xab, 0x8e, 0x0a, 0xfc, 0x1a,
    0x31, 0xa5, 0x10, 0xc4, 0x82, 0x43, 0xa5, 0xe9, 0xe2, 0x8e, 0x1f, 0xda,
    0x32, 0x52, 0x6d, 0x83, 0x10, 0x3f, 0xaa, 0x61, 0xff, 0x43, 0x02, 0xa3,
    0x3d, 0x62, 0x67, 0xd7, 0x2d, 0xe9, 0x02, 0xb8, 0xf4, 0x13, 0x36, 0xf0,
    0xe6, 0xa4, 0xd6, 0xaf, 0x08, 0x13, 0xdb, 0x09, 0x83, 0xf4, 0x1e, 0xae,
    0xca, 0x62, 0x1a, 0xd2, 0x75, 0x31, 0x0e, 0x6d, 0x5f, 0x9c, 0xd7, 0x65,
    0x84, 0x7c, 0x70, 0x76, 0x4b, 0x14, 0xb4, 0x71, 0x99, 0x65, 0xf6, 0x9f,
    0xfd, 0x70, 0xfc, 0x61, 0x71, 0xf2, 0x77, 0x1c, 0xde, 0x29, 0x0b, 0x70,
    0x1f, 0x83, 0x12, 0xde, 0xe6, 0x11, 0xc8, 0x5f, 0xfd, 0xc8, 0x54, 0x75,
    0x11, 0x07, 0xf2, 0xb9, 0xa2, 0xe8, 0x2d, 0x5a, 0x18, 0x00, 0x4d, 0x3f,
    0x3f, 0xe0, 0x56, 0x7b, 0x64, 0x20, 0xec, 0xd5, 0xfd, 0xae, 0xb3, 0x86,
    0xc4, 0xab, 0x09, 0x3f, 0x96, 0x42, 0x03, 0x13, 0xfd, 0x58, 0x89, 0x71,
    0xbc, 0x47, 0x30, 0x97, 0xba, 0xff, 0x5c, 0xa9, 0x06, 0x77, 0x2a, 0x5e,
    0xc4, 0x0a, 0xe9, 0x1b, 0xd6, 0x05, 0x37, 0x1c, 0x5a, 0x99, 0xbe, 0x6f,
    0x93, 0xe2, 0x78, 0xbf, 0x10, 0x36, 0x42, 0x54, 0x1b, 0xb0, 0xca, 0x6d,
    0x3a, 0x21, 0xdf, 0x25, 0x9f, 0xe8, 0xd2, 0x58, 0xfc, 0x00, 0x68, 0xf8,
    0x20, 0xb4, 0x8b, 0x5a, 0xbd, 0xce, 0xa7, 0x63, 0x07, 0x89, 0x23, 0xc5,
    0x30, 0xe9, 0xce, 0x4a, 0xc5, 0x03, 0xdb, 0x17, 0xa0, 0xd4, 0xcc, 0x25,
    0x47, 0xb2, 0xb6, 0x2a, 0xcd, 0xe5, 0xf1, 0x58, 0xaf, 0x17, 0xd4, 0x59,
    0x15, 0x00, 0x35, 0xbd, 0x91, 0x12, 0xc1, 0xbf, 0x9c, 0xa8, 0x9b, 0x61,
    0x2c, 0x73, 0xfc, 0xf8, 0xed, 0xe5, 0x73, 0xfa, 0x63, 0xd3, 0x92, 0xfa,
    0x09, 0x62, 0xa9, 0x4a, 0x86, 0x83, 0x8a, 0x7e, 0x03, 0x4b, 0xea, 0xfe,
    0xfa, 0x71, 0xba, 0x28, 0x3b, 0xe6, 0x9c, 0xe1, 0xf9, 0x02, 0xf5, 0x1b,
    0xce, 0x50, 0xcf, 0xe7, 0x39, 0x82, 0x58, 0xd8, 0xac, 0x30, 0x4a, 0x67,
    0xb2, 0x79, 0xa7, 0xe3, 0xdb, 0x42, 0x79, 0xc0, 0x3e, 0x97, 0x5c, 0x48,
    0x73, 0x62, 0xe6, 0xe2, 0xd3, 0xc8, 0xdc, 0x57, 0x86, 0x90, 0x98, 0xcd,
    0x47, 0xff, 0xfd, 0xb1, 0x35, 0x9d, 0x44, 0xfc, 0x89, 0x37, 0x90, 0xd1,
    0x9d, 0x6a, 0x8a, 0x82, 0x2b, 0x43, 0x4d, 0xd8, 0x0e, 0x2a, 0x39, 0x1b,
    0x6a, 0x12, 0xeb, 0xee, 0x56, 0xb3, 0x37, 0x03, 0x82, 0x79, 0x8c, 0xd8,
    0x40, 0xdd, 0x12, 0xea, 0xfe, 0xca, 0xd8, 0x6e, 0x39, 0xe6, 0x5e, 0x83,
    0x4a, 0x1f, 0x71, 0xad, 0x13, 0xae, 0xb1, 0x29, 0xfe, 0x47, 0x62, 0xed,
    0x46, 0xed, 0xb6, 0x00, 0x03, 0xae, 0x6a, 0xe3, 0xf0, 0xc4, 0x0a, 0x00,
    0xb4, 0x71, 0x41, 0x51, 0x68, 0xaf, 0x42, 0x45, 0x94, 0x8f, 0xb2, 0x59,
    0x0f, 0xfd, 0x42, 0xe2, 0xb2, 0xb8, 0xf9, 0x13, 0x45, 0x8a, 0xe0, 0xb6,
    0x07, 0x69, 0xb4, 0xeb, 0x82, 0xe1, 0x1a, 0x38, 0xad, 0x73, 0x9e, 0xf8,
    0xe1, 0x08, 0x9a, 0x67, 0xe2, 0x8b, 0xa7, 0x8c, 0x99, 0x1e, 0x85, 0x91,
    0xf5, 0x11, 0x42, 0x9e, 0x37, 0x5e, 0x59, 0xf5, 0xb2, 0x45, 0xcf, 0x6d,
    0xc6, 0xfd, 0x27, 0x1b, 0xed, 0x20, 0x3d, 0x38, 0xa3, 0x88, 0xb2, 0x99,
    0x31, 0x50, 0x3d, 0x91, 0x7f, 0x18, 0x07, 0xbb, 0x1d, 0x07, 0x99, 0x75,
    0x78, 0x0a, 0x5d, 0xa9, 0xca, 0xb5, 0x32, 0x02,
};
static std::uint8_t digest[32] = {
    0x18, 0x59, 0x25, 0x2d, 0xea, 0xac, 0xef, 0xd6, 0x61, 0x92, 0x97,
    0x53, 0x06, 0x61, 0x0b, 0xc1, 0x67, 0x1b, 0x82, 0xd4, 0xf8, 0x4d,
    0x0b, 0x3e, 0x19, 0xe1, 0x4e, 0xcc, 0xf2, 0x1c, 0x51, 0x2f,
};

void test_hash()
{
    auto         sm3 = SM3();
    std::uint8_t out[32];
    sm3.do_final(out, data, 1124);
    if (std::memcmp(out, digest, 32) != 0)
    {
        std::runtime_error("err in hash do_final");
    }
    sm3.reset();
    sm3.update(data, 1024);
    sm3.do_final(out, data + 1024, 100);
    if (std::memcmp(out, digest, 32) != 0)
    {
        std::runtime_error("err in hash do_final");
    }
    sm3.reset();
    sm3.update(data, 1024);
    sm3.update(data + 1024, 100);
    sm3.do_final(out, nullptr, 0);
    if (std::memcmp(out, digest, 32) != 0)
    {
        std::runtime_error("err in hash do_final");
    }
}