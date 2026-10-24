# GMLib

GMLib 是一个基于 C++17 的密码算法库，提供 SM2、SM3、SM4、SM9，以及 AES、SHA 等算法实现。项目包含通用实现和针对 CPU 指令集优化的实现，支持运行时选择可用的实现

源码托管于 [GitHub](https://github.com/oldprincess/gmlib)，并同步至 [Gitee](https://gitee.com/oldprincess/gmlib)

## 主要特性

- 提供分组密码、哈希、公钥密码及相关工具
- 包含 AES-NI、AVX2、AVX-512/GFNI、Intel SHA 和 ARM 加密扩展等优化实现，具体支持情况取决于算法、编译器和目标架构
- 根据当前 CPU 的指令集支持情况进行运行时的实现方案选择
- 使用 CMake 构建，核心库依赖 C++ 标准库，当前提供静态库
- 提供 [OpenSSL Provider 扩展](extention/openssl-binding/README.md)，可通过 OpenSSL 调用部分算法实现

## 支持的功能

| 类别 | 算法与功能 |
| --- | --- |
| 分组密码 | AES、Ballet、DES、SM4、uBlock |
| 分组密码模式 | ECB、CBC、CFB、OFB、CTR、GCM；可用模式取决于算法和实现 |
| 哈希与认证 | MD5、SHA-1、SHA-2、SM3、GHASH、HMAC |
| 公钥密码 | SM2、SM9 |
| 工具 | ASN.1、Base64、大数运算、随机数接口、CPU 指令集检测 |

## 快速开始

### 环境要求

- 支持 C++17 的编译器
- CMake 3.18 或更新版本

### 构建与测试

获取源码：

```sh
git clone https://github.com/oldprincess/gmlib.git
cd gmlib
```

Linux：

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

Windows：

```sh
cmake -S . -B build
cmake --build build --config Release --parallel
ctest --test-dir build -C Release --output-on-failure
```

默认构建测试程序。仅构建库时，可添加 `-DPROJECT_BUILD_TEST=OFF`

### 最小示例：SM3 摘要

```c++
#include <gmlib/sm3/sm3.h>

#include <cstdint>
#include <cstdio>

int main()
{
    std::uint8_t message[] = {'a', 'b', 'c'};
    std::uint8_t digest[sm3::SM3::DIGEST_SIZE];
    sm3::SM3 hash;
    hash.do_final(digest, message, sizeof(message));

    for (std::uint8_t byte : digest)
    {
        std::printf("%02x", (unsigned int)byte);
    }
    std::puts("");
}
```

更多示例见 [demo/](demo/)

## 在自己的项目中使用

将源码放在 `external/gmlib/`，通过 CMake 引入：

```cmake
cmake_minimum_required(VERSION 3.18)
project(example LANGUAGES CXX)

set(PROJECT_BUILD_TEST OFF CACHE BOOL "Build GMLib tests")
add_subdirectory(external/gmlib)

add_executable(example main.cpp)
target_compile_features(example PRIVATE cxx_std_17)
target_include_directories(example PRIVATE external/gmlib/include)
target_link_libraries(example PRIVATE gmlib_static)
```

也可以直接使用 `include/` 中的头文件并链接构建产物：Windows 下为 `build/Release/gmlib_static.lib`，Linux 下为 `build/libgmlib_static.a`。路径可能随生成器和构建配置变化

## 实现选择与构建选项

默认配置会启用适合目标架构的实现，并在运行时选择当前 CPU 支持的 provider。自动选择时可回退到可用的通用实现；显式请求不可用的 provider 会抛出异常

可以关闭不需要的实现以减小构建产物，例如：

```sh
cmake -S . -B build -DSUPPORT_SM4_GONG23_GFNI=OFF
```

完整选项见 [CMakeLists.txt](CMakeLists.txt)。运行时调度适用于相同操作系统、ABI 和 CPU 架构下的不同指令集配置

## 文档

- 算法说明：[SM2](docs/sm2.md)、[SM3](docs/sm3.md)、[SM4](docs/sm4.md)、[AES](docs/aes.md)、[Ballet](docs/ballet.md)、[uBlock](docs/ublock.md)
- 其它模块和参考资料：[docs/](docs/)
- 使用示例：[demo/](demo/)
- OpenSSL 接入：[扩展说明](extention/openssl-binding/README.md)

## 性能测试记录

[benchmark/](benchmark/) 保存最近一次测试版本在不同平台上的原始输出，按 Git hash 管理，不按日期归档。每个平台目录包含 `_platform.txt`、`_ctest.txt` 和按算法命名的输出文件

使用 Python 3.9 或更新版本采集结果：

```sh
# Linux
python3 benchmark/run.py build
```

```sh
# Windows
python benchmark/run.py build/Release
```

脚本会先运行 CTest，再依次执行目录中的 `*_test speed`。使用方法、平台信息和记录覆盖规则见 [benchmark/README.md](benchmark/README.md)。

## 反馈与贡献

欢迎通过 [GitHub Issues](https://github.com/oldprincess/gmlib/issues) 报告问题、讨论功能。报告问题时请附上代码版本、平台、编译器、构建命令及最小复现。

也可以通过邮件联系：<zirui.gong@foxmail.com>。

## License

本项目采用 [MIT License](LICENSE)，按许可证中的 “AS IS” 条款提供。

本软件是AS IS的( 不提供任何保证， ( 不管是显式的还是隐式的，包括但不限于适销性保证、适用性保证、非侵权性保证 ) ) ，在任何情况下， ( 对于任何的权益追索、损失赔偿或者任何追责 ) ，作者或者版权所有人都不会负责。( 无论这些追责产生自合同、侵权，还是直接或间接来自于本软件以及与本软件使用或经营有关的情形 )

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
