大整数数学运算函数
====================

.. warning::

    为了简便，示例代码中并未进行错误处理，
    实际情况下应当检查函数返回值，防止发生异常

####################
一、一般函数
####################

.. c:function:: int bint_rand_bits(BINT* r, int bits);

    随机生成bits比特大整数

.. c:function:: int bint_rand_range(BINT* r, BINT* left, BINT* right);

    随机生成[left, right)范围大整数

.. c:function:: int bint_prime_bits(BINT* r, int bits);

    随机生成bits比特大素数

.. c:function:: int bint_is_prime(BINT* n, int* status);

    素数判断(无视符号位)

.. code-block:: c
    :caption: example

    BINT p;
    int status = 0;
    bint_prime_bits(&p, 256);    // 256 比特素数
    bint_is_prime(&p, &status);  // 素性检测
    // is prime
    if (status == 1) {
        puts("is prime");
    } else {
        puts("not prime");
    }

.. c:function:: int bint_gcd(BINT* gcd, BINT* n1, BINT* n2);

    最大公约数

####################
二、有限域 Fp 运算
####################

.. c:function:: int fp_add(BINT* r, BINT* n1, BINT* n2, BINT* p);

    有限域加法

.. c:function:: int fp_sub(BINT* r, BINT* n1, BINT* n2, BINT* p);

    有限域减法

.. c:function:: int fp_mul(BINT* r, BINT* n1, BINT* n2, BINT* p);

    有限域乘法

.. c:function:: int fp_mul_u32(BINT* r, BINT* n1, uint32_t n2, BINT* p);

    有限域乘法

.. c:function:: int fp_sqr(BINT* r, BINT* n, BINT* p);

    有限域二次幂

.. c:function:: int fp_pow(BINT* r, BINT* n, BINT* e, BINT* p);

    有限域求幂

.. c:function:: int fp_inverse(BINT* r, BINT* n, BINT* p);

    有限域求逆

.. c:function:: int fp_neg(BINT* r, BINT* n, BINT* p);

    有限域取负

.. note:: 

    有限域算法要求输入的 ``p`` 为正素数，会保证输出的值为非负数