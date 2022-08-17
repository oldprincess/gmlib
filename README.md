# GMLib

支持国密 SM4/AES-ECB/CBC/GCM，SM3，SM2签名/加密，ZUC算法 的密码库，文档页面 https://oldprincess.github.io/gmlib/，项目地址 [gmlib](https://github.com/oldprincess/gmlib/)

开发这个库的时候参考了很多密码库，例如 [Crypto++](https://github.com/weidai11/cryptopp)，[openssl](https://github.com/openssl/openssl)，[GmSSL](https://github.com/guanzhi/GmSSL)，[Oryx Embedded](https://www.oryx-embedded.com/doc/) 以及 `JAVA JDK`，所以很多地方都能看到这些库的影子

## 一、快速开始

### 1.1 文件目录

整个项目主要分为4部分，`include` 目录为 `gmlib` 库向外暴露的接口， `src` 目录为实现的源代码，`test` 目录为测试函数，`demo` 目录为一些调用样例

### 1.2 通过CMake编译（推荐）

测试环境1：`Windows 10` 系统，`VS` 版本2019，`CMake` 版本3.15

测试环境2：`Ubuntu 18.04.6 LTS` 系统，`gcc` 版本7.5.0，`CMake` 版本3.10.2

若 `Windows` 电脑中没有配置 `CMake` 环境，则可从 https://cmake.org/download/ 处下载安装配置

* 拷贝 gmlib 项目至本机(也可以通过下载zip包的方式拷贝)

```bash
git clone https://github.com/oldprincess/gmlib.git
```

执行下述命令

```bash
# 进入 gmlib 目录
cd gmlib
# 创建 build 目录，避免污染源代码
mkdir build
cd build
```

* 执行cmake，以Release模式编译

```bash
# linux
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

```bash
# Windows(VS)
cmake ..
cmake --build . --config release
```

若编译成功，则应该在`build`目录下生成结果文件，在其下的`bin`和`lib`目录为生成的测试文件与lib文件

* 在控制台中执行 `bin` 目录下编译出的测试文件 `gmlib-test`

应当可在控制台中看到输出 `test finish!`，说明测试结果正确

**注**：在 linux 系统中编译流程同上

## 二、GMLib 库使用

以 1.2 中的 cmake 方式编译为例，编译完成后生成的库文件位于 `gmlib/build/lib` 目录，库的名称均为 `gmlib`。

* 错误信息输出至 `stderr`，例如如下代码：

```c
#include <gmlib/bint.h>
int main() {
    BINT x;  // 声明大整数变量
    // 从字符串中以10进制读入大整数
    bint_from_str(&x, "a", 10); 
    return 0;
}
```

* 控制台中将提示

```bash
[Error] Bad string input, need [0, 9], get a. File `..\src\bint\bint_cast.c`, line 68, in `bint_from_str`
```

该错误提示是由 `GMLIB_DEBUG` 宏控制，若想关闭该提示，可修改 CMakeLists.txt 文件，将该行注释

```bash
set(CMAKE_C_FLAGS -DGMLIB_DEBUG)
```

再重新编译工程

更多使用样例请参考docs文档和demo目录

## 三、其它

* **为什么要写这个密码库**：
想自己造个轮子，如果可以的话可以方便后人对密码学实现这块的学习。
我最初学习算法我是通过 `openssl` 库学习的，`openssl` 库代码风格对我而言过于晦涩复杂。之后找到了阅读起来更为易懂的 `oryx-embedded`（一个嵌入式的密码库）。在学习大整数运算时我是阅读 `Java JDK` 的源码学习的，虽然代码风格优秀，但 Java 中全部源码集中在一个文件中，函数调用关系不易捋清，而且英文文档和代码对我而言阅读起来远不及中文方便。

* **后续这个库的开发方向**：
后续主要随着自己的喜好开发，预计先将国密标准的算法全部写完，之后预计增加其它的工作模式和密码算法，再进行些效率上的优化。
