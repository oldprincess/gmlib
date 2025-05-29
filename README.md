# GMLib

本项目使用MIT协议，如果您想要使用本项目，请仔细阅读MIT协议。

如果有任何疑问，请发 email 至 <zirui.gong@foxmail.com> ，或者提交issue。

This software uses the MIT LICENSE. If you wish to use this software, please carefully read the text of the MIT LICENSE.

If you have any questions, please send an email to <zirui.gong@foxmail.com>, or submit an issue.

本项目的将在 github 平台更新，并随机同步至 gitee 平台。如果您的ip地址位于中国，可以使用 gitee 克隆本项目（ [点击链接跳转](https://gitee.com/oldprincess/gmlib) ），否则更推荐您使用 github 克隆本项目（ [点击链接跳转](https://github.com/oldprincess/gmlib) ）。

This project will be updated on the GitHub platform and randomly synchronized to the Gitee platform. If your IP address is located in China, you can use Gitee to clone this project ( [click link to jump](https://gitee.com/oldprincess/gmlib) ). Otherwise, I recommend that you use GitHub to clone this project ( [click link to jump](https://github.com/oldprincess/gmlib) ).

## 1 基本介绍

一句话介绍：GMLib是一个基于C++17的高性能国密算法库，支持国密SM2、SM3、SM4、SM9

目前支持的密码算法为：

* 对称密码：AES、Ballet、DES、SM4、uBlock
* 哈希算法：MD5、SHA1、SM3、GHASH
* 公钥密码：SM2、SM9

### 1.1 开发密码库GMLib的初衷

娱乐，just for fun

### 1.2 密码库GMLib的优点

性能高效且跨平台、功能完备且易拓展

#### a. 性能高效且跨平台

为AES、SM2、SM3、SM4、SM9进行了x86_64平台的优化实现

在Windows平台和Linux平台均通过测试

* 测试CPU平台：12th Gen Intel(R) Core(TM) i5-12500H

* 测试OS平台：Windows 11

|算法|性能|:-:|算法|性能|
|:-:|:-:|:-:|:-:|:-:|
|AES-128|104166 Mbps|:-:|SM2-SM3签名[64字节数据]|34722 opt/s|
|AES-192|87719  Mbps|:-:|SM2-SM3验签[64字节数据]|10548 opt/s|
|AES-256|73529  Mbps|:-:|SM2-SM3加密[64字节数据]|7987  opt/s|
|SM4    |6250   Mbps|:-:|SM2-SM3解密[64字节数据]|11876 opt/s|
|SM3    |2216   Mbps|:-:|SM9-SM3签名[64字节数据]|1116  opt/s|
|:-:|:-:|:-:|SM9-SM3验签[64字节数据]|444   opt/s|
|:-:|:-:|:-:|SM9-SM3加密[64字节数据]|1014  opt/s|
|:-:|:-:|:-:|SM9-SM3解密[64字节数据]|904   opt/s|

#### b. 功能完备且易拓展

支持SM2、SM3、SM4、SM9国密标准

容易拓展到其它密码算法的工作模式（ECB、CBC、...）、消息认证码（HMAC）等，因为使用了C++的模板技术，并且仅依赖C++标准库

## 2 快速开始

本项目在 Windows 11 和 WSL-Ubuntu 22.04.3 TLS 平台上通过测试。

|平台|处理器|编译器|
|:-:|:-:|:-:|
|Windows 11|12th Gen Intel(R) Core(TM) i5-12500H|Microsoft (R) C/C++ 优化编译器 19.40.33811 版|
|WSL-Ubuntu 22.04.3 TLS|12th Gen Intel(R) Core(TM) i5-12500H|gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0|

### 2.1 快速构建

本项目使用`cmake`构建

#### step1：测试平台支持的优化

如果不想使用针对处理器平台的优化，可以跳过这一步

如果处理器平台是x86_64，可以使用`tools/cpuid.py`脚本测试平台支持的优化，运行下述命令来编译并执行脚本

```bash
python cpuid.py
```

将得到如下所示的输出（部分输出结果省略）

```text
add_definitions(-DCPU_FLAG_CPU_FLAG_AES)
add_definitions(-DCPU_FLAG_CPU_FLAG_AVX2)
add_definitions(-DCPU_FLAG_CPU_FLAG_BMI2)
...
set(PROJECT_COMPILE_OPTIONS -maes -mavx2 ...)
```

将上述内容添加至`CMakeLists.txt`文件中，文件中有说明添加的具体位置

#### step2：编译

* Windows平台

```bash
cd gmlib
mkdir build
cd build
cmake ..
cmake --build . --config=Release
```

* Linux平台

```bash
cd gmlib
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

#### step3：测试

以Windows平台为例，将在Release文件夹生成`sm2_test.exe`、`sm3_test.exe`、`sm4_test.exe`等多个测试文件

* 执行下述命令测试SM2算法正确性

```bash
Release/sm2_test.exe
```

* 执行下述命令测试SM2算法正确性和性能

```bash
Release/sm2_test.exe speed
```

### 2.2 使用

很遗憾，目前本项目只能采用静态库的方式进行使用，后续会支持通过动态库的调用。

* Windows平台：按照2.1的流程，将在`build\Release`文件夹下得到名为`gmlib_static.lib`的静态库文件
* Linux平台：按照2.1的流程，将在`build`文件夹下得到名为`libgmlib_static.a`的静态库文件

#### step1：作为教程，创建如下的目录结构

目录包含`include`、`lib`和`src`三个目录：`include`目录中存放gmlib库的头文件，直接从该项目源码中拷贝即可；`lib`目录中存放gmlib库的静态库文件；`src`目录存放教程项目的源代码。

```text
+---include
|   \---gmlib
|
+---lib
|       gmlib_static.lib  [in windows]
|       libgmlib_static.a [in linux]
|
\---src
        main.cpp
```

#### step2：正式使用gmlib库

接着，修改`src/main.cpp`，以`gmlib/demo/sm2/sm2_cipher.cpp`为例。

```c++
#include <gmlib/memory_utils/memdump.h>
#include <gmlib/rng/std_rng.h>
#include <gmlib/sm2/sm2.h>
#include <gmlib/sm3/sm3.h>

#include <iostream>
#include <memory>

#define log(msg) std::printf("[%d]: %s\n", __LINE__, msg)

constexpr int MSG_SIZE = 64;

int main()
{
    log("sm2-sm3 sign demo begin");

    sm2::SM2PrivateKey<sm3::SM3> priv_key;
    sm2::SM2PublicKey<sm3::SM3>  pub_key;
    rng::StdRng                  rng;

    std::uint8_t msg[MSG_SIZE];
    std::uint8_t ct[1024], pt[1024];
    std::size_t  ct_len, pt_len;
    std::uint8_t data_pub_x[32], data_pub_y[32], data_priv[32];

    log("generate random private key");
    priv_key.gen_priv(rng);
    priv_key.get_priv(data_priv);
    memory_utils::memdump(data_priv, sizeof(data_priv));

    log("fetch public key");
    pub_key = priv_key.fetch_pub();
    pub_key.get_pub(data_pub_x, data_pub_y);
    log("public key - x");
    memory_utils::memdump(data_pub_x, sizeof(data_pub_x));
    log("public key - y");
    memory_utils::memdump(data_pub_y, sizeof(data_pub_y));

    log("rand msg");
    rng.gen(msg, MSG_SIZE);
    memory_utils::memdump(msg, MSG_SIZE);

    // store data_pub_x[32], data_pub_y[32], data_priv[32] to some place

    log("encrypt");
    pub_key.set_pub(data_pub_x, data_pub_y);
    if (sizeof(ct) < pub_key.ciphertext_len(msg, sizeof(msg)))
    {
        log("err");
        return -1;
    }
    pub_key.encrypt(ct, &ct_len, msg, sizeof(msg), rng);
    memory_utils::memdump(ct, ct_len);

    log("decrypt");
    priv_key.set_priv(data_priv);
    if (sizeof(pt) < priv_key.plaintext_len(ct, ct_len))
    {
        log("err");
        return -1;
    }
    priv_key.decrypt(pt, &pt_len, ct, ct_len);
    memory_utils::memdump(pt, pt_len);

    log("sm2-sm3 sign demo end");
    return 0;
}
```

之后执行编译命令

* Windows 平台

使用MSVC的 [CL](https://learn.microsoft.com/zh-cn/cpp/build/reference/compiler-command-line-syntax?view=msvc-170) 工具，`/I`表示添加头文件路径，`/Zl`表示省略默认库名，`/std:c++17`表示使用c++17，`/MD`表示多线程使用Release版本的动态链接库

```bash
CL src\main.cpp  lib\gmlib_static.lib /I include /Zl /std:c++17 /MD
```

```bash
.\main.exe
```

* Linux 平台

```bash
g++ src/main.cpp lib/libgmlib_static.a -I include -std=c++17 -o main.x
```

```bash
./main.x
```

将会输出计算结果，下面是一个例子

```text
[19]: sm2-sm3 sign demo begin
[30]: generate random private key
82 91 75 1d 3e cf 97 57 27 a0 f8 1b 1b b7 77 11    ..u.>..W'.....w.
2f 6f 30 91 4b 24 bb cc 75 b7 be 8d 41 7d 92 a1    /o0.K$..u...A}..
[35]: fetch public key
[38]: public key - x
26 f8 fe ab 8b 27 64 38 d4 86 13 fc f0 bd a1 97    &....'d8........
1c 47 61 a3 8c 14 3b a5 da 0a f4 da 16 21 fb 8a    .Ga...;......!..
[40]: public key - y
a2 57 31 df e4 aa c9 56 80 8a 39 d9 c8 14 23 f7    .W1....V..9...#.
a2 0d b2 ad c8 18 75 9f 5b 7d 82 1f 9b 36 d2 32    ......u.[}...6.2
[43]: rand msg
4d 5b 2d 42 b0 4b d1 e4 1a c9 11 28 90 40 c4 d9    M[-B.K.....(.@..
eb 49 17 5e ac 2d 41 20 17 b8 76 a4 ec 17 10 f3    .I.^.-A ..v.....
de d3 27 01 c0 7f b4 85 3d 0a 2a 3e f4 31 24 65    ..'.....=.*>.1$e
8e 8f 5e 71 a9 78 85 bd 78 58 c7 b4 bd 26 32 fc    ..^q.x..xX...&2.
[49]: encrypt
04 62 e2 95 9b db 46 25 40 29 3f cb 84 4a 43 f2    .b....F%@)?..JC.
9b 5d 0f 0e 5a 3a e0 32 bf 01 27 3a 74 30 bb 66    .]..Z:.2..':t0.f
e6 68 46 e3 19 55 d5 5b 52 6a e1 89 35 99 12 91    .hF..U.[Rj..5...
00 89 b3 d2 26 43 5d e9 35 f5 de ef 60 96 aa 95    ....&C].5...`...
5d 3d 64 54 55 87 28 19 d9 68 a7 51 5b 5a c6 da    ]=dTU.(..h.Q[Z..
e5 ef db a6 26 ed a3 e4 a6 73 7e 36 ac 5b 2a 93    ....&....s~6.[*.
1e 73 4a 05 75 0e d5 44 81 62 1c c8 c2 7b b7 67    .sJ.u..D.b...{.g
0c f3 ff 5f df 5b 14 5f f5 50 ef 17 2c 29 62 5b    ..._.[._.P..,)b[
de ae 57 a5 95 09 87 a0 72 e6 ea 5a 09 a2 c9 f4    ..W.....r..Z....
6e b6 9c 15 88 f8 d8 81 25 13 d8 29 e1 a0 9b 87    n.......%..)....
09                                                 .
[59]: decrypt
4d 5b 2d 42 b0 4b d1 e4 1a c9 11 28 90 40 c4 d9    M[-B.K.....(.@..
eb 49 17 5e ac 2d 41 20 17 b8 76 a4 ec 17 10 f3    .I.^.-A ..v.....
de d3 27 01 c0 7f b4 85 3d 0a 2a 3e f4 31 24 65    ..'.....=.*>.1$e
8e 8f 5e 71 a9 78 85 bd 78 58 c7 b4 bd 26 32 fc    ..^q.x..xX...&2.
[69]: sm2-sm3 sign demo end
```

## 3 声明

本软件是AS IS的( 不提供任何保证， ( 不管是显式的还是隐式的，包括但不限于适销性保证、适用性保证、非侵权性保证 ) ) ，在任何情况下， ( 对于任何的权益追索、损失赔偿或者任何追责 ) ，作者或者版权所有人都不会负责。( 无论这些追责产生自合同、侵权，还是直接或间接来自于本软件以及与本软件使用或经营有关的情形 )

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
