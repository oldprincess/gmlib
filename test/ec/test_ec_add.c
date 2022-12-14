#include <gmlib/ec.h>
#include <gmlib/err.h>
#include <stdlib.h>

static char* dot1_fp192[][2] = {
    {
        "2012187664930809898563739307392552636339705069190310174083",  // x
        "2225010555505614815134241691356875658190680180564480028995",  // y
    },
    // [3]G
    {
        "3241959689206761204426342363111981661731043446758629854182",
        "3191151435493273541483981135250496819258126892831569605521",
    },
    // [51]G
    {
        "2399386719223234245175543692342806846188738807029355132631",
        "1691263994663933672006298336903549213479262517589054591671",
    },
};

static char* dot2_fp192[][2] = {
    {
        "3241959689206761204426342363111981661731043446758629854182",  // x
        "3191151435493273541483981135250496819258126892831569605521",  // y
    },
    // [3]G
    {
        "3241959689206761204426342363111981661731043446758629854182",
        "3191151435493273541483981135250496819258126892831569605521",
    },
    // [33]G
    {
        "4647192170443755668019242104543510714810683387177116247718",
        "4068274243832424116510632981428006682351374416458153442555",
    },
};

static char* dot3_fp192[][2] = {
    {
        "19913958154514119588348167140624588539541593114363382577",    // x
        "1419714424967879194955196042037612660983569533331937020705",  // y
    },
    // [6]G
    {
        "63857857110780534288982087356131627420682355233083239",
        "4352024559017642589010166816279446848827667889089777588782",
    },
    // [84]G
    {
        "3199098669917067527173795944498389261996111238934698925020",
        "3429006222664411811484459911433211800447425802196970924761",
    },
};

void test_ec_add() {
    EC_CTX* ec_fp192 = &EC_Fp192_CTX;
    ECPoint d1, d2, d3, t;
    BINT x, y;
    for (int i = 0; i < sizeof(dot1_fp192) / sizeof(dot1_fp192[0]); i++) {
        try_goto(bint_from_str(&x, dot1_fp192[i][0], 10));
        try_goto(bint_from_str(&y, dot1_fp192[i][1], 10));
        ec_construct(&d1, &x, &y);

        try_goto(bint_from_str(&x, dot2_fp192[i][0], 10));
        try_goto(bint_from_str(&y, dot2_fp192[i][1], 10));
        ec_construct(&d2, &x, &y);

        try_goto(bint_from_str(&x, dot3_fp192[i][0], 10));
        try_goto(bint_from_str(&y, dot3_fp192[i][1], 10));
        ec_construct(&d3, &x, &y);

        try_goto(ec_add(&t, &d1, &d2, ec_fp192));
        if (ec_equal(&d3, &t) != 1) {
            ERR_LOG("Err in ec_add");
            goto error;
        }
    }

    return;
error:
    exit(-1);
}
