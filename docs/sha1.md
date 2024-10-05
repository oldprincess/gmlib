# SHA1

## 1. 基本介绍

翻译自英文维基。 [点击此链接跳转至原文](https://en.wikipedia.org/wiki/SHA-1)

> 在密码学中，SHA-1（安全哈希算法1）是一种哈希函数，它接受输入并产生一个160位（20字节）的哈希值，称为消息摘要，通常表示为40个十六进制数字。它由美国国家安全局设计，是美国联邦信息处理标准。该算法已被破解，但仍被广泛使用。

## 2. 接口说明

### 2.1 使用SHA1对消息进行摘要

略。

## 3. 权利与说明

* sha1_sha

使用x86_64的SHA指令集加速

> cite: https://github.com/noloader/SHA-Intrinsics/blob/master/sha1-x86.c

```
/**
 * part of the code is "derived from miTLS project. sha1-x86.c"
 *
 * https://github.com/noloader/SHA-Intrinsics/blob/master/sha1-x86.c
 *
 * sha1-x86.c - Intel SHA extensions using C intrinsics
 * Written and place in public domain by Jeffrey Walton
 * Based on code from Intel, and by Sean Gulley for
 * the miTLS project.
 */
```