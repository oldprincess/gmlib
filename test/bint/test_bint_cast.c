#include <gmlib/bint.h>
#include <gmlib/err.h>
#include <stdlib.h>
#include <string.h>

static void test_str_cast_pos();
static void test_str_cast_neg();
static void test_str_cast_ex();

static void test_bytes_cast();
static void test_u32_cast();

void test_bint_cast() {
    test_str_cast_pos();
    test_str_cast_neg();
    test_str_cast_ex();
    test_bytes_cast();
    test_u32_cast();
}

static void test_str_cast_pos() {
    static char str[GMLIB_BINT_SIZE + 1];
    char* x_hex =
        "27FAF5836081C7E80E05BE4346DAB656C98CC5D2A037D776B04CFF82F4E08B36";
    char* x_dec =
        "1808360733071333107327453929757789680712341810427204572506184105511076"
        "9183542";
    char* x_oct =
        "2377275301540403437500340267620643332554533114314272250033727355301147"
        "770136470105466";
    char* x_bin =
        "1001111111101011110101100000110110000010000001110001111110100000001110"
        "0000010110111110010000110100011011011010101101100101011011001001100011"
        "0011000101110100101010000000110111110101110111011010110000010011001111"
        "11111000001011110100111000001000101100110110";
    BINT x, y;
    char* lst[] = {x_hex, x_dec, x_oct, x_bin};       // 测试数据List
    int radix[] = {16, 10, 8, 2};                     // 数据对应进制
    int test_size = 4;                                // 测试数据量
    // 测试 from_str
    for (int i = 0; i < test_size; i++) {
        for (int j = 0; j < test_size; j++) {
            try_goto(bint_from_str(&x, lst[i], radix[i]));
            try_goto(bint_from_str(&y, lst[j], radix[j]));
            if (bint_cmp(&x, &y) != 0) {
                ERR_LOG("Err in bint_from_str");
                goto error;
            }
        }
    }

    // 测试 to_str
    try_goto(bint_from_str(&x, x_hex, 16));
    for (int i = 0; i < test_size; i++) {
        try_goto(bint_to_str(&x, str, radix[i]));
        if (strcmp(str, lst[i]) != 0) {
            ERR_LOG("Err in bint_to_str");
            goto error;
        }
    }

    // 测试 to_str + from_str
    try_goto(bint_from_str(&x, x_hex, 16));
    for (int i = 2; i <= 36; i++) {
        try_goto(bint_to_str(&x, str, i));
        try_goto(bint_from_str(&y, str, i));
        if (bint_cmp(&x, &y) != 0) {
            ERR_LOG("");
            goto error;
        }
    }

    return;
error:
    exit(-1);
}

static void test_str_cast_neg() {
    static char str[GMLIB_BINT_SIZE + 1];
    char* x_hex =
        "-27FAF5836081C7E80E05BE4346DAB656C98CC5D2A037D776B04CFF82F4E08B36";
    char* x_dec =
        "-180836073307133310732745392975778968071234181042720457250618410551107"
        "69183542";
    char* x_oct =
        "-237727530154040343750034026762064333255453311431427225003372735530114"
        "7770136470105466";
    char* x_bin =
        "-100111111110101111010110000011011000001000000111000111111010000000111"
        "0000001011011111001000011010001101101101010110110010101101100100110001"
        "1001100010111010010101000000011011111010111011101101011000001001100111"
        "111111000001011110100111000001000101100110110";
    BINT x, y;
    char* lst[] = {x_hex, x_dec, x_oct, x_bin};       // 测试数据List
    int radix[] = {16, 10, 8, 2};                     // 数据对应进制
    int test_size = 4;                                // 测试数据量
    // 测试 from_str
    for (int i = 0; i < test_size; i++) {
        for (int j = 0; j < test_size; j++) {
            try_goto(bint_from_str(&x, lst[i], radix[i]));
            try_goto(bint_from_str(&y, lst[j], radix[j]));
            if (bint_cmp(&x, &y) != 0) {
                ERR_LOG("Err in bint_from_str");
                goto error;
            }
        }
    }

    // 测试 to_str
    try_goto(bint_from_str(&x, x_hex, 16));
    for (int i = 0; i < test_size; i++) {
        try_goto(bint_to_str(&x, str, radix[i]));
        if (strcmp(str, lst[i]) != 0) {
            ERR_LOG("Err in bint_to_str");
            goto error;
        }
    }

    // 测试 to_str + from_str
    try_goto(bint_from_str(&x, x_hex, 16));
    for (int i = 2; i <= 36; i++) {
        try_goto(bint_to_str(&x, str, i));
        try_goto(bint_from_str(&y, str, i));
        if (bint_cmp(&x, &y) != 0) {
            ERR_LOG("");
            goto error;
        }
    }

    return;
error:
    exit(-1);
}

static void test_bytes_cast() {
    static uint8_t b_be[] = {
        0xfa, 0x32, 0x61, 0xf3, 0x5c, 0xce, 0xdb, 0xa9, 0xa9, 0xf1, 0x39,
        0xa5, 0xca, 0x0c, 0x9e, 0x87, 0x7e, 0x32, 0x00, 0xae, 0x0a, 0x79,
        0xfb, 0x17, 0x83, 0x78, 0x64, 0x27, 0x8e, 0x0f, 0x6d,
    };
    static uint8_t b_le[] = {
        0x6d, 0x0f, 0x8e, 0x27, 0x64, 0x78, 0x83, 0x17, 0xfb, 0x79, 0x0a,
        0xae, 0x00, 0x32, 0x7e, 0x87, 0x9e, 0x0c, 0xca, 0xa5, 0x39, 0xf1,
        0xa9, 0xa9, 0xdb, 0xce, 0x5c, 0xf3, 0x61, 0x32, 0xfa,
    };
    static uint8_t b[GMLIB_BINT_BITS / 8];
    char* x_hex =
        "FA3261F35CCEDBA9A9F139A5CA0C9E877E3200AE0A79FB17837864278E0F6D";

    BINT x, y;
    // 测试 from_bytes
    try_goto(bint_from_str(&y, x_hex, 16));
    try_goto(bint_from_bytes(&x, b_be, sizeof(b_be), BINT_BIG_ENDIAN));
    if (bint_cmp(&x, &y) != 0) {
        ERR_LOG("Err in bint_from_bytes");
        printf("%s\n", bint_fast_to_str(&x, 16));
        printf("%s\n", bint_fast_to_str(&y, 16));
        goto error;
    }
    try_goto(bint_from_bytes(&x, b_le, sizeof(b_le), BINT_LITTLE_ENDIAN));
    if (bint_cmp(&x, &y) != 0) {
        ERR_LOG("Err in bint_from_bytes");
        goto error;
    }
    // 测试 to_bytes
    try_goto(bint_to_bytes(&x, b, sizeof(b_be), BINT_BIG_ENDIAN));
    if (memcmp(b_be, b, sizeof(b_be)) != 0) {
        ERR_LOG("Err in bint_to_bytes");
        goto error;
    }
    try_goto(bint_to_bytes(&x, b, sizeof(b_le), BINT_LITTLE_ENDIAN));
    if (memcmp(b_le, b, sizeof(b_le)) != 0) {
        ERR_LOG("Err in bint_to_bytes");
        goto error;
    }

    return;
error:
    exit(-1);
}

void test_u32_cast() {
    uint32_t u = 0x11223344;
    char* x_hex = "11223344";
    BINT x, y;
    // test from_u32
    try_goto(bint_from_str(&y, x_hex, 16));
    bint_from_u32(&x, u);
    if (bint_cmp(&x, &y) != 0) {
        ERR_LOG("Err in bint_from_u32");
        goto error;
    }
    // test to_u32
    uint32_t a;
    try_goto(bint_from_str(&y, x_hex, 16));
    try_goto(bint_to_u32(&a, &y));
    if (a != u) {
        ERR_LOG("Err in bint_to_u32");
        goto error;
    }

    return;
error:
    exit(-1);
}

static void test_str_cast_ex() {
    BINT x;
    // 测试 0
    bint_from_str(&x, "0", 10);
    if (!bint_is_zero(&x)) {
        ERR_LOG("Err in bint_from_str");
        goto error;
    }
    // 测试 -0
    bint_from_str(&x, "-0", 10);
    if (!bint_is_zero(&x)) {
        ERR_LOG("Err in bint_from_str");
        goto error;
    }
    // 测试 +0
    bint_from_str(&x, "+0", 10);
    if (!bint_is_zero(&x)) {
        ERR_LOG("Err in bint_from_str");
        goto error;
    }

    return;
error:
    exit(-1);
}
