# GHash

GHash用于GCM工作模式

翻译自英文维基。 [点击此链接跳转至原文](https://en.wikipedia.org/wiki/Galois/Counter_Mode)

在密码学中，Galois/Counter Mode（GCM）是一种对称密钥加密分组密码的作模式，因其性能而被广泛采用。使用廉价的硬件资源，可以实现最先进的高速通信通道的GCM吞吐率。

下方是GHash的相关文档资料。

> Dworkin M. Recommendation for block cipher modes of operation: Galois/Counter Mode (GCM) and GMAC [R]. National Institute of Standards and Technology, 2007.
> <https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38d.pdf>

## 2. 接口说明

略

## 3. 权利与说明

- ghash common

普通实现

- ghash lut256

使用查表加速

> McGrew D, Viega J. The Galois/counter mode of operation (GCM) [J]. submission to NIST Modes of Operation Process, 2004, 20: 0278-0070.
> <https://csrc.nist.rip/groups/ST/toolkit/BCM/documents/proposedmodes/gcm/gcm-spec.pdf>

- ghash pclmul

使用PCLMUL指令加速

> Intel Carry-Less Multiplication Instruction and its Usage for Computing the GCM Mode.
> <https://www.intel.com/content/dam/develop/external/us/en/documents/clmul-wp-rev-2-02-2014-04-20.pdf>

> Copyright (c) 2010 Intel Corporation. All rights reserved.
