SM2 算法
====================

SM2 官方文档可从 http://www.gmbz.org.cn/main/bzlb.html 处查询

.. c:var:: extern EC_CTX SM2_Fp256_CTX;

    SM2 标准文档中给定的 Fp256 椭圆曲线(256bit有限域)

####################
一、SM2 签名验签
####################

.. note:: 

    SM2 签名的大小与所使用的椭圆曲线中的素域有关，例如使用 256bit 有限域时，
    签名大小为 512bit(512/8字节)

====================
1.1 SM2 签名
====================

.. c:struct:: SM2_SIGN_CTX

    SM2 签名 Context

.. c:function:: int sm2_sign_init(uint8_t* ENTL, uint8_t* ID, EC_CTX* ec_ctx, \
                                  BINT* da, ECPoint* P, SM2_SIGN_CTX* sm2_sign_ctx);
    
    :param ENTL:    ID 的比特长度，共 2 字节
    :param ID:      签名者可辩别标识
    :param ec_ctx:  椭圆曲线
    :param da:      签名者私钥
    :param P:       签名者公钥
    :param sm2_sign_ctx:    SM2 签名 Context
                        
    SM2 签名初始化

.. c:function:: void sm2_sign_reset(SM2_SIGN_CTX* sm2_sign_ctx);

    SM2 签名重置

.. note::

    利用 ``sm2_sign_reset`` 可实现一个签名者对多条消息签名，避免频繁地初始化

.. code-block:: c
    :caption: example

    SM2_SIGN_CTX sm2_sign_ctx;
    sm2_sign_init(..., &sm2_sign_ctx);
    // 对消息1签名 ...
    sm2_sign_update(msg1, ...);
    sm2_sign_final(...)
    // 对消息2签名
    sm2_sign_reset(&sm2_sign_ctx);
    sm2_sign_update(msg2, ...);
    sm2_sign_final(...)

.. c:function:: void sm2_sign_update(uint8_t* in, int inl, SM2_SIGN_CTX* sm2_sign_ctx);

    SM2 签名 Update

.. c:function:: int sm2_sign_final(uint8_t* out, int* outl, SM2_SIGN_CTX* sm2_sign_ctx);

    SM2 签名 Final

====================
1.2 SM2 验签
====================

.. c:struct:: SM2_VERIFY_CTX

    SM2 验签 Context

.. c:function:: int sm2_verify_init(uint8_t* ENTL, uint8_t* ID, EC_CTX* ec_ctx, ECPoint* P, \
                                    SM2_VERIFY_CTX* sm2_verify_ctx);
                        
    SM2 验签初始化

.. c:function:: void sm2_verify_reset(SM2_VERIFY_CTX* sm2_verify_ctx);

    SM2 验签重置

.. c:function:: void sm2_verify_update(uint8_t* in, int inl, SM2_VERIFY_CTX* sm2_verify_ctx);

    SM2 验签 Update

.. c:function:: int sm2_verify_final(int* status, uint8_t* signature, SM2_VERIFY_CTX* sm2_verify_ctx);

    SM2 验签 Final

.. code-block:: c
    :caption: example

    #include <gmlib/publickey/sm2.h>
    #include <stdio.h>

    static uint8_t ID_A[] = {
        0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,  //
        0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,  //
    };

    static uint8_t ENTL_A[] = {0x00, 0x80};

    // 签名方私钥
    static char* da_hex =
        "3945208F_7B2144B1_3F36E38A_C6D39F95_88939369_2860B51A_42FB81EF_4DF7C5B8";

    // 待签名消息
    static uint8_t msg[] = {
        'm', 'e', 's', 's', 'a', 'g', 'e', ' ', 'd', 'i', 'g', 'e', 's', 't',
    };

    // signature=(r,s)
    static uint8_t signature[2 * (GMLIB_BINT_BITS / 8)];
    static int outl;

    int main() {
        BINT da;    // 私钥
        ECPoint P;  // 公钥

        // 载入私钥
        bint_from_str(&da, da_hex, 16);
        // 计算公钥 P = [da]G
        ec_mul(&P, &da, &SM2_Fp256_CTX.G, &SM2_Fp256_CTX);

        // sm2 签名
        SM2_SIGN_CTX sm2_sign_ctx;
        sm2_sign_init(ENTL_A, ID_A, &SM2_Fp256_CTX, &da, &P, &sm2_sign_ctx);
        sm2_sign_update(msg, sizeof(msg), &sm2_sign_ctx);
        sm2_sign_final(signature, &outl, &sm2_sign_ctx);

        // sm2 验签
        SM2_VERIFY_CTX sm2_verify_ctx;
        int status = 0;  // 签名正确性
        sm2_verify_init(ENTL_A, ID_A, &SM2_Fp256_CTX, &P, &sm2_verify_ctx);
        sm2_verify_update(msg, sizeof(msg), &sm2_verify_ctx);
        sm2_verify_final(&status, signature, &sm2_verify_ctx);
        if (status != 1) {
            puts("check fail!");
            return -1;
        }
        puts("check ok!");
        return 0;
    }
