功能函数
====================

.. c:function:: uint32_t loadu32_be(uint8_t* src);

    以大端形式读取32比特数

.. c:function:: void storeu32_be(uint8_t* dst, uint32_t n);

    以大端形式存储32比特数

.. c:function:: void storeu64_be(uint8_t* dst, uint64_t n);

    以大端形式存储64比特数

.. code-block:: c
    :caption: example

    uint8_t b[4] = {0x12, 0x34, 0x56, 0x78};
    uint32_t n = loadu32_be(b);
    printf("n=0x%08x\n", n);  // n=0x12345678
    storeu32_be(b, 0x87654321);
    // 87 65 43 21
    for (int i = 0; i < 4; i++) {
        printf("%02x ", b[i]);
    }
    puts("");


.. c:function:: void dump_data(uint8_t* d, int len);

    打印内存数据

.. code-block:: c

    uint8_t b[] = {'1', '2', '3', '4'};
    dump_data(b, sizeof(b));
    // dump data: size = 4
    // 0000 - 	31 32 33 34                                     	1234

.. c:function:: void memxor(uint8_t* dst, uint8_t* a, uint8_t* b, int size);

    字节异或

.. c:function:: void rand_mem(uint8_t* mem, int size);

    内存随机化

.. note:: 
    
    在调用 ``rand_mem`` 函数前应该设置一个随机数种子 ``srand`` 

.. code-block:: c
    :caption: example

    srand((unsigned)time(NULL));  // 设置随机数种子
    rand_mem(b, sizeof(b));       // 随机内存

.. code-block:: c
    :caption: source code

    void rand_mem(uint8_t* mem, int size) {
        for (int i = 0; i < size; i++) {
            mem[i] = rand() % 256;
        }
    }
