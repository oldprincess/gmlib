# 将GMLib接入至OpenSSL

## 1. 系统要求

* OpenSSL 3.5.0以上
* CMake

### 1.1 安装OpenSSL

教程撰写日期：2025-6-13

* Windows平台

在 [Shining Light Productions](https://slproweb.com/products/Win32OpenSSL.html) 网站中下载 v3.5.0 以上的OpenSSL，并安装。

* Linux平台

克隆 [OpenSSL](https://github.com/openssl/openssl) 的Github仓库，根据教程编译安装。

```bash
# 克隆3.5.0版本的仓库
git clone https://github.com/openssl/openssl.git --depth 1 -b openssl-3.5.0
# 进入仓库路径并配置安装路径/usr/local/ssl
cd openssl
./Configure --prefix=/usr/local/ssl --openssldir=/usr/local/ssl '-Wl,-rpath,$(LIBRPATH)'
# 编译
make
# 安装
sudo make install
```

## 2. 编译

首先需要编译好gmlib库，将编译生成的静态库（在Windows下名为gmlib_static.lib，Linux下名为libgmlib_static.a）复制到该路径下。编译方法见项目 [README](../../README.md) 。

之后编译gmlib针对OpenSSL的Provider，可以指定OpenSSL的安装路径。

* Windows（OpenSSL的头文件和库路径不在环境变量中）

```bash
mkdir build
cd build
cmake .. -DOPENSSL_BASE_DIR=<your OpenSSL path>
cmake --build . --config=Release
```

* Linux（OpenSSL的头文件和库路径不在环境变量中）

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DOPENSSL_BASE_DIR=<your OpenSSL path> 
cmake --build .
```

* Linux（OpenSSL的头文件和库路径已经在环境变量中）

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

## 3. 使用

### 3.1 运行测试脚本

编译会自动生成测试样例程序，可先将OpenSSL的动态库路径临时添加到环境变量中

* Windows（使用Powershell终端）

```powershell
$env:PATH += ";<your OpenSSL dll path>"
# 例如
$env:PATH += ";C:/Programming/OpenSSL-Win64/bin"
```

* Linux

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<your OpenSSL dll path>
# 例如
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/ssl/lib64
```

运行编译出的测试程序，例如

```bash
# Linux
./evp_sm4_ecb
```

输出

```text
[228] Provider loaded
[240] EVP Cipher SM4 ECB start
[332] EVP CIPHER SM4 ECB PASS
```

### 3.2 接入OpenSSL命令行

```text
kentle@KENTLE-ASUS:/usr/local/ssl/lib64$ ../bin/openssl list -provider-path /mnt/e/code/git_repo/gmlib/extention/openssl-binding/ -provider libgmlibprov -providers
Providers:
  libgmlibprov
    name: gmlib
    version: 1.0.0
    status: active
```

```text
kentle@KENTLE-ASUS:/usr/local/ssl/lib64$ echo "0123456789abcde" | ../bin/openssl enc -e -K 00112233445566777766554433221100 -sm4-ecb -provider-path /mnt/e/code/git_repo/gmlib/extention/openssl-binding/ -provider libgmlibprov | ../bin/openssl enc -d -K 00112233445566777766554433221100 -sm4-ecb -provider-path /mnt/e/code/git_repo/gmlib/extention/openssl-binding/ -provider libgmlibprov -v -p
bufsize=8192
salt=00000000C9570000
key=00112233445566777766554433221100
0123456789abcde
bytes read   :       16
bytes written:       16
```

### 3.3 接入OpenSSL库

参考 test/*.c 中的测试代码
