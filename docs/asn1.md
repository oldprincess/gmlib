# ASN1

## 1. 基本介绍

ASN.1语法的入门可以参考微软的文档。

> ASN.1 语法和编码简介. 
> https://learn.microsoft.com/zh-cn/windows/win32/seccertenroll/about-introduction-to-asn-1-syntax-and-encoding

更为详细的ASN.1编码规则可以从下方文档中查询。

> X.680-X.693 : Information Technology - Abstract Syntax Notation One (ASN.1) & ASN.1 encoding rules. 
> https://www.itu.int/rec/T-REC-X.680-X.693-202102-I/en

## 2. 接口说明

ASN.1语法的使用可辨别编码规则 (DER) 进行编码，本节关于ASN.1语法的函数均是对DER格式的数据进行解析和处理。

### 2.1 打印ASN.1数据（asn1_dump.h）

下方的例子展示了将DER格式的sm2签名数据`SM2_SIGNATURE_DER`解码成ASN.1格式，并打印至控制台的方法。

```c++
#include <gmlib/asn1/asn1_dump.h>

#include <cstdio>

static const unsigned char SM2_SIGNATURE_DER[] = {
    0x30, 0x45, 0x02, 0x21, 0x00, 0xa2, 0x43, 0x86, 0x41, 0x7d, 0x79, 0x60,
    0xe7, 0x94, 0x74, 0xb6, 0xca, 0xfa, 0x77, 0x20, 0x09, 0x8d, 0x79, 0x1c,
    0x94, 0x7e, 0x96, 0xc0, 0x67, 0x0f, 0xa6, 0x00, 0x32, 0xf4, 0xc6, 0x87,
    0xd8, 0x02, 0x20, 0x15, 0x01, 0x0a, 0x81, 0xb5, 0xd2, 0x27, 0x87, 0xcf,
    0x52, 0x06, 0xaf, 0xba, 0xae, 0xd0, 0x9f, 0x51, 0xc9, 0xe0, 0xf1, 0xbe,
    0x29, 0xe6, 0xa9, 0xc6, 0xf1, 0x36, 0xae, 0xc2, 0x87, 0x23, 0x05,
};

int main()
{
    int ret;
    ret = asn1::asn1_dump(SM2_SIGNATURE_DER, sizeof(SM2_SIGNATURE_DER));
    if (ret)
    {
        std::puts("err happened");
        return -1;
    }
    return 0;
}
```

程序的预期输出如下。

```
30 45                      ;  SEQUENCE(length = 69 Bytes,UNIVERSAL,CONSTRUCTED)
   02 21                      ;  INTEGER(length = 33 Bytes,UNIVERSAL,PRIMITIVE)
      00 a2 43 86 41 7d 79 60 
      e7 94 74 b6 ca fa 77 20
      09 8d 79 1c 94 7e 96 c0
      67 0f a6 00 32 f4 c6 87
      d8
   02 20                      ;  INTEGER(length = 32 Bytes,UNIVERSAL,PRIMITIVE)
      15 01 0a 81 b5 d2 27 87
      cf 52 06 af ba ae d0 9f
      51 c9 e0 f1 be 29 e6 a9
      c6 f1 36 ae c2 87 23 05
```

### 2.2 ASN.1编码与解码（asn1.h）

略，目前仅作为内部函数使用。