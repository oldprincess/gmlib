# AES

## 1. 基本介绍

翻译自英文维基。 [点击此链接跳转至原文](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard)

> 高级加密标准（AES），也称为Rijndael（荷兰语发音：[ˈrɛindaːl]），是美国国家标准与技术研究所（NIST）于2001年制定的电子数据加密规范。

下方是AES的相关文档资料。

> FIPS 197. Advanced Encryption Standard (AES).
> https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf

> ISO/IEC 18033-3: Block ciphers
> https://www.iso.org/standard/54531.html

## 2. 接口说明

### 2.1 使用AES加密单个分组数据（gmlib/aes/aes.h）

AES算法包括AES128、AES192和AES256，分别对应16字节、24字节和32字节长度的密钥。

下方代码是一个简单的示例，采用AES128加密一个分组（16字节）的数据。

- 首先，需要定义`aes::AES128`类型的变量，下方代码中对应`aes128_ctx`。下方代码的这种构造方式会调用默认构造函数，实际上，默认构造函数将不会执行任何初始化操作，之后必须通过`set_key`函数来初始化密钥。
- 接着，调用`set_key`函数，输入16字节的用户密钥`user_key`，并将`aes::AES128::ENCRYPTION`传入，意为初始化加密密钥。
- 之后，调用`encrypt_block`函数，加密单个分组（16字节）的数据

```c++
#include <gmlib/aes/aes.h>

void aes128_enc_single_block(const std::uint8_t user_key[16],
                             std::uint8_t       out[16],
                             const std::uint8_t in[16])
{
    aes::AES128 aes128_ctx;
    aes128_ctx.set_key(user_key, aes::AES128::ENCRYPTION);
    aes128_ctx.encrypt_block(out, in);
}
```

下方代码是一个简单的示例，采用AES128解密一个分组（16字节）的数据。

```c++
#include <gmlib/aes/aes.h>

void aes128_dec_single_block(const std::uint8_t user_key[16],
                             std::uint8_t       out[16],
                             const std::uint8_t in[16])
{
    aes::AES128 aes128_ctx;
    aes128_ctx.set_key(user_key, aes::AES128::DECRYPTION);
    aes128_ctx.decrypt_block(out, in);
}
```

### 2.2 使用AES加密多个分组数据（gmlib/aes/aes_mode.h）

当加密多个分组数据的时候，需要结合工作模式使用。工作模式（Block Cipher Mode）的具体介绍位于block_cipher_mode模块中。

下方代码是一个简单的示例，采用AES128的ECB模式加密一段数据。

- 首先，定义`aes::AES128EcbEncryptor`类型的变量，下方代码中对应`aes128_enc_ctx`。
- 接着，调用`init`函数进行初始化，传入16字节的用户密钥
- 之后，调用`do_final`函数进行加密，并输出结果。`in`是输入数据的内存地址，长度为`inl`字节，`out`是输出数据的内存地址，长度为`*outl`字节。为了以防万一，`in`和`out`尽量不要出现内存重叠，否则可能会发生无法预知的错误。

```c++
#include <gmlib/aes/aes_mode.h>

void aes128_enc_ecb(const std::uint8_t  user_key[16],
                    std::uint8_t*       out,
                    size_t*             outl,
                    const std::uint8_t* in,
                    size_t              inl)
{
    aes::AES128EcbEncryptor aes128_enc_ctx;
    aes128_enc_ctx.init(user_key);
    aes128_enc_ctx.do_final(out, outl, in, inl);
}
```

上方代码假定需要加密的数据位于一段连续的内存中，可以直接调用`do_final`一次性加密。而有时，需要加密的数据会被分成多段，例如加密一个大文件时，不一定能一次性全部加载至内存中，因而需要分批次输入数据。

下方代码是一个简单的示例，采用AES128的ECB模式加密数据。假设需要加密的数据长度为`inl_part1 + inl_part2`，分成了两段，此时可以通过调用`update`函数来实现加密。加密的过程相比于上方的代码更为繁琐，需要不断更新`out`指针。

```c++
#include <gmlib/aes/aes_mode.h>

void aes128_enc_ecb(const std::uint8_t  user_key[16],
                    std::uint8_t*       out,
                    size_t*             outl,
                    const std::uint8_t* in_part1,
                    size_t              inl_part1,
                    const std::uint8_t* in_part2,
                    size_t              inl_part2)
{
    std::size_t             tmp_outl;
    aes::AES128EcbEncryptor aes128_enc_ctx;
    *outl = 0;
    aes128_enc_ctx.init(user_key);
    aes128_enc_ctx.update(out, &tmp_outl, in_part1, inl_part1);
    out += tmp_outl, *outl += tmp_outl;
    aes128_enc_ctx.update(out, &tmp_outl, in_part2, inl_part2);
    out += tmp_outl, *outl += tmp_outl;
    aes128_enc_ctx.do_final(out, &tmp_outl);
    out += tmp_outl, *outl += tmp_outl;
}
```

## 3. 权利与说明

针对AES算法的实现采用了多种优化方案，在本节中进行具体说明。

* aes_lut

采用查表优化，出自Rijndael算法设计文档。

> J.Daemen, V.Rijmen. The Design of Rijndael[M]. Berlin: Springer, 2020: 53-63. 
> https://csrc.nist.gov/csrc/media/projects/cryptographic-standards-and-guidelines/documents/aes-development/rijndael-ammended.pdf

* aes_aesni

采用AES-NI指令集加速。针对AES-NI指令集的相关资料可以在网上查到。

> https://www.intel.cn/content/www/cn/zh/developer/articles/tool/intel-advanced-encryption-standard-aes-instructions-set.html

在实现时，部分代码借用了Jubal Mordecai Velasco的开源代码。下方是其代码链接和开源协议。

>  MIT License, Copyright (c) 2023 Jubal Mordecai Velasco, https://github.com/mrdcvlsc/AES/blob/main/AES.hpp

```
MIT License

Copyright (c) 2023 Jubal Mordecai Velasco

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```