# GMLib

支持国密 SM4-ECB/CBC/CTR，SM3，SM2签名/加密 的密码库，文档页面 https://oldprincess.github.io/gmlib/

## 一、快速开始

### 1.1 文件目录

整个项目主要分为4部分，`include` 目录为 `gmlib` 库向外暴露的接口， `src` 目录为实现的源代码，`test` 目录为测试函数，`demo` 目录为一些调用样例

```tree
├─include               # include 文件
│  └─gmlib              # gmlib 库头文件
│      ├─cipher             # 分组密码
│      ├─hash               # 哈希函数
│      └─publickey          # 公钥密码
|
├─src                   # gmlib 源代码
│  ├─bint                   # 大整数运算
│  ├─cipher                 # 分组密码
│  │  ├─cipher_mode             # 分组密码工作模式
│  │  └─sm4                     # SM4 算法
│  ├─ec                     # 椭圆曲线运算
│  ├─hash                   # 哈希算法
│  │  └─sm3                     # SM3 算法
│  ├─math                   # 数学函数
│  └─publickey              # 公钥密码
│      └─sm2                    # SM2 算法
|
├─test                  # 测试文件
|   ├─bint
|   ├─cipher
|   │  └─sm4
|   ├─ec
|   ├─hash
|   │  └─sm3
|   ├─math
|   └─publickey
|       └─sm2
├─demo                  # 样例
```

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
# 执行cmake 以 Debug 模式编译
cmake .. -DCMAKE_BUILD_TYPE="Debug"
cmake --build .
```

若编译成功，则应该在`build/output`目录下生成结果文件，在其下的`exe`和`lib`目录为生成的测试文件与lib文件

* 在控制台中输入下述命令，执行编译出的测试文件 `gmlib-test`

```bash
./output/exe/DEBUG/gmlib-test
```

应当可在控制台中看到输出 `test finish!`，说明测试结果正确

上述编译流程默认编译 DEBUG 项目，以 DEBUG 模式编译将开启 `GMLib` 库的错误 log 功能。若需要关闭该功能，或是想使用 RELEASE 版本，则应当以 RELEASE 模式编译。将 cmake 命令改为

```bash
cmake .. -DCMAKE_BUILD_TYPE="Release"
```

**注**：在 linux 系统中编译流程同上

### 1.3 通过VS编译

若不想下载 `CMake`，则可使用 VS 创建工程，并在工程中添加 `src` 和 `test` 中的源文件，并添加外部 include_path 为 `gmlib/include` 目录。

为了测试程序能正常运行，需要在编译时添加 `GMLIB_TEST` 宏，使算法中与随机数生成相关的代码生成固定的随机数，否则测试程序将不通过。若无需测试，仅需要使用库中的代码，`test` 目录中的源文件可排除在项目之外，且无需添加 `GMLIB_TEST` 宏。

## 二、GMLib 库使用

以 1.2 中的 cmake 方式编译为例，编译完成后生成的库文件位于 `gmlib/build/output/lib` 目录，其中的 `DEBUG` 和 `RELEASE` 子目录分别对应 DEBUG 和 RELEASE 模式的编译输出，库的名称均为 `gmlib.lib`。

* DEBUG 模式下会将错误信息输出至 `stderr`，例如如下代码：

```c
#include <gmlib/bint.h>
int main() {
    BINT x;  // 声明大整数变量
    // 从字符串中以10进制读入大整数
    bint_from_str(&x, "a", 10); 
    return 0;
}
```

* 若使用 DEBUG 模式编译输出的库，则控制台中将提示

```bash
[Error] Bad string input, need [0, 9], get a. File `..\src\bint\bint_cast.c`, line 68, in `bint_from_str`
```

而若使用 RELEASE 模式编译的库，则不会有上述提示

该错误提示是由 `GMLIB_DEBUG` 宏控制，若想在 RELEASE 模式中也输出错误 log，可修改 CMakeLists.txt 文件，将 `# set(CMAKE_C_FLAGS_RELEASE -DGMLIB_DEBUG)` 该注释消去再重新编译工程

更多使用样例请参考docs文档和demo目录

## 三、其它

* **为什么要写这个密码库**：
想自己造个轮子，如果可以的话可以方便后人对密码学实现这块的学习。
我最初学习算法我是通过 `openssl` 库学习的，`openssl` 库代码风格对我而言过于晦涩复杂。之后找到了阅读起来更为易懂的 `oryx-embedded`（一个嵌入式的密码库）。在学习大整数运算时我是阅读 `Java JDK` 的源码学习的，虽然代码风格优秀，但 Java 中全部源码集中在一个文件中，函数调用关系不易捋清，而且英文文档和代码对我而言阅读起来远不及中文方便。

* **后续这个库的开发方向**：
后续主要随着自己的喜好开发，预计先将国密标准的算法全部写完，之后预计增加其它的工作模式和密码算法，再进行些效率上的优化。
