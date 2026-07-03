# SM4

## 1. 基本介绍

摘抄自百度百科。 [点击此链接跳转至原文](https://baike.baidu.com/item/SM4.0)

> SM4.0（原名SMS4.0）是中华人民共和国政府采用的一种分组密码标准，由国家密码管理局于2012年3月21日发布。相关标准为“GM/T 0002-2012《SM4分组密码算法》（原SMS4分组密码算法）”。

## 2. 接口说明

### 2.1 使用SM4对消息进行加解密

见demo/sm4目录

## 3. 权利与说明

* sm4_lang18

使用郎等人的优化方法加速. [链接](https://html.rhhz.net/ZGKXYDXXB/20180205.htm)

> 郎欢, 张蕾, 吴文玲. SM4的快速软件实现技术. 中国科学院大学学报, 2018, 35(2): 180-187.

* sm4_gong23

使用龚等人的优化方法加速. [链接](https://www.journalofcybersec.com/CN/Y2023/V1/I3/86)

> 龚子睿, 郭华, 陈晨, 等. SM4字节切片高性能实现[J]. 网络空间安全科学学报, 2023, 1(3): 86-96.

> 一种基于字节切片的SM4快速软件实现方法:202310025457.7[P].2023-06-13.

* sm4_sm4ni

使用 Markku-Juhani O. Saarinen 的实现, 利用 AESNI 加速 SM4 算法. [链接](https://github.com/mjosaarinen/sm4ni)

```text
MIT License

Copyright (c) 2018 Markku-Juhani O. Saarinen

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
