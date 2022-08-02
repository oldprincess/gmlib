大整数运算 BINT 模块
====================

.. warning::

    为了简便，示例代码中并未进行错误处理，
    实际情况下应当检查函数返回值，防止发生异常

==================  ================================
宏定义              含义
==================  ================================
GMLIB_BINT_BITS     大整数BINT最大比特数
GMLIB_BINT_SIZE     大整数BINT最大字数(32bit为一个字)
==================  ================================

大整数 ``BINT`` 将使用栈空间，默认是 GMLIB_BINT_BITS = 512 比特长度

.. c:struct:: BINT
    
    .. c:var:: uint32_t d[GMLIB_BINT_SIZE]

        GMLIB_BINT_BITS 大小内存空间，单位为32比特字，长度为 GMLIB_BINT_SIZE
    
    .. c:var:: int sign

        BINT 符号位
    
    .. c:var:: int dsize

        BINT 占用32比特字的内存长度

.. note::

    不要自行改动 `BINT` 结构体的成员数据，除非你确定知道这么做的后果。

.. c:var:: BINT BINT_ONE

    大整数常量1

.. c:var:: BINT BINT_TWO

    大整数常量2

.. c:var:: BINT BINT_THREE

    大整数常量3

.. warning::

    不要改变 ``BINT_ONE``， ``BINT_TWO`` 和 ``BINT_THREE`` 这三个常量的值，否则会发生错误。


####################
一、大整数读入与输出
####################

====================
1.1 字符串转化
====================

============ ====== ============
相关宏定义      值      含义
============ ====== ============
BINT_HEX        16      16进制
BINT_DEC        10      10进制
BINT_BIN        2       2进制
============ ====== ============

.. c:function:: int bint_from_str(BINT* n, char* str, int radix);

    从字符串中加载大整数

字符串忽略大小写，且可以使用 ``_`` 作为分隔符以便阅读

.. code-block:: c
    :caption: example

    BINT x;
    bint_from_str(&x, "123456", 10);         // x = 123456
    bint_from_str(&x, "-123456", 10);        // x = -123456
    bint_from_str(&x, "ABCDEF", 16);         // x = 0xABCDEF
    bint_from_str(&x, "abcd_EFGH", 16);      // x = 0xABCDEFGH

.. c:function:: int bint_to_str(BINT* n, char* str, int radix);

    大整数转字符串

.. code-block:: c
    :caption: example

    BINT x;
    char s[GMLIB_BINT_BITS + 2];
    bint_from_str(&x, "123456", 10);  // x = 123456
    bint_to_str(&x, s, 10);           // s = "123456"
    printf("x=%s\n", s);              // x = 123456
    bint_to_str(&x, s, 16);           // s = "1E240"
    printf("x=0x%s\n", s);            // x = 0x1E240

.. c:function:: char* bint_fast_to_str(BINT* n, int radix);

    大整数转字符串（非线程安全，用于打印输出）

.. code-block:: c
    :caption: example

    BINT x;
    bint_from_str(&x, "123456", 10);             // x=123456
    printf("x=%s\n", bint_fast_to_str(&x, 10));  // x=123456

.. note::

    函数 ``bint_fast_to_str`` 应当只用于输出数据，且一个 ``printf`` 中仅能调用一次该函数，
    像如下的代码将会产生错误的输出结果

.. code-block:: c
    :caption: error code

    // error output
    printf("x=%s, y=%s\n", bint_fast_to_str(&x, 10), bint_fast_to_str(&y, 10));


====================
1.2 整数转化
====================

.. c:function:: void bint_from_u32(BINT* n, uint32_t u);

    从整数中读入大整数

.. c:function:: int bint_to_u32(uint32_t* u, BINT* n);

    大整数转32位整数

.. code-block:: c
    :caption: example

    BINT x;
    uint32_t u1 = 123456, u2 = 0;
    bint_from_u32(&x, u1);  // x=123456
    bint_to_u32(&u2, &x);   // u2=123456
    // u1=123456, u2=123456, x=123456
    printf("u1=%d, u2=%d, x=%s\n", u1, u2, bint_fast_to_str(&x, 10));


====================
1.3 字节串转化
====================

==================== ====== =========
相关宏定义              值      含义
==================== ====== =========
BINT_BIG_ENDIAN         1   大端模式
BINT_LITTLE_ENDIAN      0   小端模式
==================== ====== =========

.. c:function:: int bint_from_bytes(BINT* n, uint8_t* b, int bsize, int endian);

    从字节串中读取大整数

.. code-block:: c
    :caption: example

    BINT x;
    uint8_t b[] = {0x12, 0x34, 0x56, 0x78};
    // x=0x12345678
    bint_from_bytes(&x, b, sizeof(b), BINT_BIG_ENDIAN);
    printf("x=0x%s\n", bint_fast_to_str(&x, 16));
    // x=0x78563412
    bint_from_bytes(&x, b, sizeof(b), BINT_LITTLE_ENDIAN);
    printf("x=0x%s\n", bint_fast_to_str(&x, 16));
    
.. c:function:: int bint_to_bytes(BINT* n, uint8_t* b, int bsize, int endian);

    大整数转字节串

.. code-block:: c
    :caption: example

    BINT x;
    uint8_t b[10];
    bint_from_str(&x, "01_23_45_67", 16);  // x=0x01234567
    bint_to_bytes(&x, b, 4, BINT_BIG_ENDIAN);
    dump_data(b, 4);  // 01 23 45 67
    bint_to_bytes(&x, b, 6, BINT_BIG_ENDIAN);
    dump_data(b, 6);  // 00 00 01 23 45 67

.. note::

    | 像上面的代码那样，当字节串长度超过表示大整数 ``BINT`` 所需要的大小时，会默认补0
    | 建议采用 ``bint_bytes_len`` 函数获取大整数所需要的字节大小，如下所示

.. code-block:: c
    :caption: example

    int bsize = bint_bytes_len(&x);  // 4
    bint_to_bytes(&x, b, bsize, BINT_BIG_ENDIAN);
    dump_data(b, bsize);  // 01 23 45 67


####################
二、大整数运算
####################

====================
2.1 加减法
====================

.. c:function:: int bint_add(BINT* r, BINT* n1, BINT* n2);

    大整数加法

.. c:function:: int bint_sub(BINT* r, BINT* n1, BINT* n2);

    大整数减法

.. code-block:: c
    :caption: example

    BINT x, y, z1, z2;
    bint_from_str(&x, "1000", 10);  // x=1000
    bint_from_str(&y, "2000", 10);  // y=2000
    bint_add(&z1, &x, &y);          // z1=x+y
    bint_sub(&z2, &x, &y);          // z2=x-y
    // x+y=3000
    // x-y=-1000
    printf("x+y=%s\n", bint_fast_to_str(&z1, 10));
    printf("x-y=%s\n", bint_fast_to_str(&z2, 10));


====================
2.2 乘法
====================

.. c:function:: int bint_mul(BINT* r, BINT* n1, BINT* n2);

    大整数乘法

.. c:function:: int bint_sqr(BINT* r, BINT* n);

    大整数二次幂

.. c:function:: int bint_mul_u32(BINT* r, BINT* n1, uint32_t n2);

    大整数乘法

.. code-block:: c
    :caption: example

    BINT x, z1, z2, z3;
    bint_from_str(&x, "1000", 10);  // x=1000
    bint_mul(&z1, &x, &x);          // z1=x*x
    bint_sqr(&z2, &x);              // z2=x^2
    bint_mul_u32(&z3, &x, 1000);    // z3=x*1000
    // x*x   =  1000000
    // x^2   =  1000000
    // x*1000=  1000000
    printf("x*x=%s\n", bint_fast_to_str(&z1, 10));
    printf("x^2=%s\n", bint_fast_to_str(&z2, 10));
    printf("x*1000=%s\n", bint_fast_to_str(&z3, 10));


====================
2.3 除法
====================

.. c:function:: int bint_divmod(BINT* q, BINT* r, BINT* n1, BINT* n2);

    大整数除法

.. c:function:: int bint_divmod_u32(BINT* q, uint32_t* r, BINT* n1, uint32_t n2);

    大整数除法

.. code-block:: c
    :caption: example

    BINT x, y, z1, z2;
    uint32_t rem;
    bint_from_str(&x, "1001", 10);  // x=1001
    bint_from_str(&y, "50", 10);    // y=50

    bint_divmod(&z1, &z2, &x, &y);
    // x div y = 20, x mod y = 1
    printf("x div y=%s\n", bint_fast_to_str(&z1, 10));
    printf("x mod y=%s\n", bint_fast_to_str(&z2, 10));
    // same
    bint_divmod(&z1, NULL, &x, &y);  // 丢弃余数
    bint_divmod(NULL, &z2, &x, &y);  // 丢弃商
    // also like
    bint_divmod_u32(&z1, &rem, &x, 50);


====================
2.4 幂
====================

.. c:function:: int bint_pow(BINT* r, BINT* n, BINT* e, BINT* mod);

    大整数求幂

.. c:function:: int bint_pow_u32(BINT* r, BINT* n, uint32_t e, BINT* mod);

    大整数求幂

.. code-block:: c
    :caption: example

    BINT x, mod, z1, z2;
    bint_from_str(&x, "1001", 10);  // x=1001
    // x^3
    bint_pow(&z1, &x, &BINT_THREE, NULL);
    bint_pow_u32(&z2, &x, 3, NULL);
    // z1=1003003001, z2=1003003001
    printf("z1=%s\n", bint_fast_to_str(&z1, 10));
    printf("z2=%s\n", bint_fast_to_str(&z2, 10));

    bint_from_str(&mod, "1000", 10);  // mod=1000
    bint_pow_u32(&z1, &x, 3, &mod);   // x^3 mod 1000
    // z1=1
    printf("z1=%s\n", bint_fast_to_str(&z1, 10));

====================
2.5 算数移位
====================

.. c:function:: int bint_sll(BINT* r, BINT* n, int bits);

    大整数逻辑（算数）左移

.. c:function:: int bint_sra(BINT* r, BINT* n, int bits);

    大整数算数右移

.. code-block:: c
    :caption: example

    BINT x, z;
    bint_from_str(&x, "1110", 2);  // x=0b1110

    bint_sll(&z, &x, 3);  // z=0b1110000
    printf("z=%s\n", bint_fast_to_str(&z, 2));
    bint_sra(&z, &x, 2);  // z=11
    printf("z=%s\n", bint_fast_to_str(&z, 2));


####################
三、功能函数
####################

====================
3.1 比较函数
====================

.. c:function:: int bint_cmp(BINT* n1, BINT* n2);

    大整数比较

.. c:function:: inline int bint_is_zero(BINT* n);

    是否为零

.. c:function:: inline int bint_is_neg(BINT* n);

    是否为负

.. c:function:: inline int bint_is_pos(BINT* n);

    是否为正

.. c:function:: inline int bint_is_odd(BINT* n);

    是否是奇数

====================
3.2 设置/拷贝函数
====================

.. c:function:: inline void bint_set_zero(BINT* n);

    设置大整数为零

.. c:function:: void bint_copy(BINT* r, BINT* n);

    大整数拷贝

.. c:function:: void bint_neg(BINT* r, BINT* n);

    大整数取负

.. c:function:: void bint_abs(BINT* r, BINT* n);

    大整数取绝对值

====================
3.3 杂项/辅助函数
====================

.. c:function:: int bint_bytes_len(BINT* n);

    大整数的字节数

.. c:function:: int bint_bits_len(BINT* n);

    大整数的比特数

.. c:function:: int bint_bits_at(BINT* n, int index);

    大整数某一比特位数值

.. code-block:: c
    :caption: example

    BINT x;
    bint_from_str(&x, "11100", 2);  // x=0b11100
    int bits = bint_bits_len(&x);   // bits=5
    for (int i = bits - 1; i >= 0; i--) {
        // 1 1 1 0 0
        printf("%d ", bint_bits_at(&x, i));
    }
    puts("");
