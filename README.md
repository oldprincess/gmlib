# GMLib

本项目使用MIT协议，如果您想要使用本项目，请仔细阅读MIT协议。

This software uses the MIT LICENSE. If you wish to use this software, please carefully read the text of the MIT LICENSE.

## 1 基本介绍

一句话介绍：GMLib是一个基于C++17的高性能国密算法库，支持国密SM2、SM3、SM4、SM9

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
|AES-128|104166 Mbps|:-:|SM2-SM3签名[64字节数据]|9140  opt/s|
|AES-192|87719  Mbps|:-:|SM2-SM3验签[64字节数据]|5668  opt/s|
|AES-256|73529  Mbps|:-:|SM2-SM3加密[64字节数据]|4878  opt/s|
|SM4    |6250   Mbps|:-:|SM2-SM3解密[64字节数据]|11876 opt/s|
|SM3    |2216   Mbps|:-:|SM9-SM3签名[64字节数据]|1116  opt/s|
|:-:|:-:|:-:|SM9-SM3验签[64字节数据]|444   opt/s|

#### b. 功能完备且易拓展

支持SM2、SM3、SM4、SM9国密标准

容易拓展到其它密码算法的工作模式（ECB、CBC、...）、消息认证码（HMAC）等，因为使用了C++的模板技术，并且仅依赖C++标准库

## 2 快速开始

本项目使用`cmake`构建，使用`python`作为脚本语言

#### step1：测试平台支持的优化

如果不想使用针对处理器平台的优化，可以跳过这一步

如果处理器平台是x86_64，可以使用`tools/cpuid.py`脚本测试平台支持的优化，运行下述命令

```
python tools/cpuid.py
```

将得到如下所示的输出

```
add_definitions(-DCPU_FLAG_SSE2)
add_definitions(-DCPU_FLAG_AVX2)
add_definitions(-DCPU_FLAG_AES)
add_definitions(-DCPU_FLAG_MOVBE)
add_definitions(-DCPU_FLAG_BMI2)
add_definitions(-DCPU_FLAG_RDSEED)
add_definitions(-DCPU_FLAG_RDRAND)
add_definitions(-DCPU_FLAG_PCLMUL)
add_definitions(-DSUPPORT_SM3_YANG15)
add_definitions(-DSUPPORT_SM4_LANG18)
set(PROJECT_COMPILE_OPTIONS -msse2 -mavx2 -maes -mmovbe -mbmi2 -mrdseed -mrdrnd -mpclmul)
```

将上述内容添加至`CMakeLists.txt`文件中，文件中有说明添加的具体位置

* x86_64平台相关宏定义如下

|宏定义|含义|
|:-:|:-:|
|CPU_FLAG_SSE2|SSE2指令集|
|CPU_FLAG_AVX2|AVX2指令集|
|CPU_FLAG_AES|AES指令集，AES算法加解密|
|CPU_FLAG_MOVBE|MOVBE指令集，大端读取数据|
|CPU_FLAG_BMI2|BMI2指令集|
|CPU_FLAG_RDSEED|RDSEED指令集，随机数生成|
|CPU_FLAG_RDRAND|RDRAND指令集，随机数生成|
|CPU_FLAG_PCLMUL|PCLMUL指令集|

* 优化方法相关宏定义如下

|宏定义|含义|
|:-:|:-:|
|SUPPORT_SM3_YANG15|支持YANG15的SM3优化|
|SUPPORT_SM4_LANG18|支持LANG18的SM4优化|

#### step2：编译

* Windows平台

```
cd gmlib
mkdir build
cd build
cmake ..
cmake --build . --config=Release
```

* Linux平台 

```
cd gmlib
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

#### step3：测试

以Windows平台为例，将在Release文件夹生成`sm2_test.exe`、`sm3_test.exe`、`sm4_test.exe`等多个测试文件

* 执行下述命令测试SM2算法正确性

```
Release/sm2_test.exe
```

* 执行下述命令测试SM2算法正确性和性能

```
Release/sm2_test.exe speed
```

## 3 声明

本软件是AS IS的( 不提供任何保证， ( 不管是显式的还是隐式的，包括但不限于适销性保证、适用性保证、非侵权性保证 ) ) ，在任何情况下， ( 对于任何的权益追索、损失赔偿或者任何追责 ) ，作者或者版权所有人都不会负责。( 无论这些追责产生自合同、侵权，还是直接或间接来自于本软件以及与本软件使用或经营有关的情形 )

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.