# MD5

## 1. 基本介绍

翻译自英文维基。 [点击此链接跳转至原文](https://en.wikipedia.org/wiki/MD5)

> MD5消息摘要算法是一种广泛使用的哈希函数，可产生128位哈希值。MD5由Ronald Rivest于1991年设计，用以替换早期的哈希函数MD4，并于1992年被指定为RFC 1321。

## 2. 接口说明

### 2.1 使用MD5对消息进行摘要

```c++
#include <gmlib/md5/md5.h>

#include <cstdio>
#include <cstring>

int main()
{
    const char*  msg = "hello world";
    std::uint8_t digest[md5::MD5::DIGEST_SIZE];
    md5::MD5     md5_ctx;

    md5_ctx.do_final(digest, (const std::uint8_t*)msg, std::strlen(msg));

    // 5eb63bbbe01eeed093cb22bb8f5acdc3
    for (std::size_t i = 0; i < sizeof(digest); i++)
    {
        std::printf("%02x", digest[i]);
    }
    std::printf("\n");

    return 0;
}
```

## 3. 权利与说明

* md5 common

部分代码源自RSA Data Security

> cite: https://www.rfc-editor.org/rfc/rfc1321

```
Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.
```