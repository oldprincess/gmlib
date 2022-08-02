错误处理
====================

在 ``err.h`` 中定义了2个常量

==================  =====   =========
名称                值      含义
==================  =====   ========= 
ERR_NOERROR         0       无错误
ERR_RUNTIME_ERROR   1       发生错误
==================  =====   =========

且定义了宏函数 ``ERR_LOG`` 以及 ``try_goto``

* 宏函数 ``ERR_LOG`` 接收格式化字符串与参数，将错误信息输出至 ``stderr`` 中，
  输出的错误信息包括文件名、代码位置以及函数名称

.. code-block:: c

    #define ERR_LOG(_fmt, ...)                     \
        fprintf(stderr,                            \
                "[Error] "_fmt                     \
                ". File `%s`, line %d, in `%s`\n", \
                __VA_ARGS__, __FILE__, __LINE__, __FUNCTION__)


调用方式例如 ``ERR_LOG("Err Happen")`` 或是 ``ERR_LOG("Err Happen, get %d", 2)``

.. note::

    ``ERR_LOG`` 仅在定义了 ``GMLIB_DEBUG`` 宏时才会打印错误信息，当 ``GMLIB_DEBUG``
    宏未定义时等价于空语句

* 宏函数 ``try_goto`` 必须搭配 C 语言的标签 ``error`` 使用，例如

.. code-block:: c

    #include <gmlib/bint.h>
    #include <gmlib/err.h>

    int main() {
        BINT x;
        // try_goto
        try_goto(bint_from_str(&x, "a", 10));
        // same expression
        if (bint_from_str(&x, "a", 10) != ERR_NOERROR) {
            ERR_LOG("Err Happen");
            goto error;
        }

        return 0;
    error:
        return -1;
    }

使用 ``try_goto`` 宏可以使得错误处理更为方便，源代码中将大量采用这种表达方式
