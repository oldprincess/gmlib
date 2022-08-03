SM3 算法
====================

SM3 官方文档参考 http://www.gmbz.org.cn/main/viewfile/20180108023812835219.html

================== ==== ====================
宏定义              值  含义
================== ==== ====================
SM3_DIGEST_SIZE     16  SM3 摘要字节数
SM3_BLOCK_SIZE      16  SM3 压缩函数分组数
================== ==== ====================

.. c:struct:: SM3_CTX

    SM3 算法 Context

.. c:function:: void sm3_init(SM3_CTX* ctx);

    SM3 初始化

.. c:function:: void sm3_update(uint8_t* in, int inl, SM3_CTX* ctx);

    SM3 更新消息


.. note:: 

    ``update`` 函数可让待哈希的消息分段多次输入，能在对大文件/数据进行 Hash 时提供便利

.. code-block:: c
    :caption: example

    // Z = X || Y
    sm3_update(Z, Z.len, ctx);
    // 等价于
    sm3_update(X, X.len, ctx);
    sm3_update(Y, Y.len, ctx);

.. c:function:: void sm3_final(uint8_t* out, SM3_CTX* ctx);

    SM3 Final 并输出摘要

.. code-block:: c
    :caption: example

    #include <gmlib/hash/sm3.h>
    #include <gmlib/utils.h>

    int main() {
        SM3_CTX sm3_ctx;
        uint8_t msg[] = {'a', 'b', 'c'};  // 原始消息
        uint8_t digest[SM3_DIGEST_SIZE];  // 消息摘要

        // 初始化 SM3
        sm3_init(&sm3_ctx);
        // 输入消息
        sm3_update(msg, sizeof(msg), &sm3_ctx);
        // 结束 SM3 并输出摘要 digest
        sm3_final(digest, &sm3_ctx);

        dump_data(digest, sizeof(digest));
        /*  SM3 摘要结果
            66 c7 f0 f4 62 ee ed d9 d1 f2 d4 6b dc 10 e4 e2
            41 67 c4 87 5c f2 f7 a2 29 7d a0 2b 8f 4b a8 e0
        */
        return 0;
    }

