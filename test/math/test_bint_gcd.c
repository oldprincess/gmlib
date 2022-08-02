#include <gmlib/err.h>
#include <gmlib/math.h>
#include <stdlib.h>

static char* data[][4] = {
    // 1
    {
        "166789811366126112595551916998898333809",  // x
        "788909145863734881819021027231640327833",  // y
        "9",                                        // gcd
        NULL,                                       // x^-1 mod y
    },
    // 2
    {"299277955107914672678914088885573237887",  //
     "935820670686964551522781836859742385050",  //
     "7",                                        //
     NULL},
    // 3
    {"145114668370772337676058100675133674212809",  //
     "354813863521386165788046518764400609924",     //
     "1",                                           //
     "198974993800317833716397444274910704365"},
    // 4
    {"-39916842112313100950203827644746028685687",  //
     "322927903989453944524046893008552971692",     //
     "1",                                           //
     "186831173306260854840093260858619891969"},
};

void test_bint_gcd() {
    BINT x, y, gcd, t, inverse;
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
        try_goto(bint_from_str(&x, data[i][0], 10));
        try_goto(bint_from_str(&y, data[i][1], 10));
        // gcd
        try_goto(bint_from_str(&t, data[i][2], 10));
        try_goto(bint_gcd(&gcd, &x, &y));
        if (bint_cmp(&gcd, &t) != 0) {
            ERR_LOG("Err in bint_gcd");
            goto error;
        }
        // inverse
        if (data[i][3] != NULL) {
            try_goto(fp_inverse(&inverse, &x, &y));
            try_goto(bint_from_str(&t, data[i][3], 10));
            if (bint_cmp(&inverse, &t) != 0) {
                ERR_LOG("Err in bint_inverse");
                printf("%s\n", data[i][0]);
                printf("%s\n", bint_fast_to_str(&inverse, 10));
                goto error;
            }
        }
    }

    return;
error:
    exit(-1);
}
