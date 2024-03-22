# 样例

利用脚本文件`make.py`编译样例代码

需要位于路径`gmlib/demo`，需要`python`和`g++`环境

## sm2

sm2签名

```
python make.py sm2\sm2_sign.cpp  demo.exe
```

sm2加密

```
python make.py sm2\sm2_cipher.cpp  demo.exe
```

## sm3

* 哈希

```
python make.py sm3\sm3_hash.cpp  demo.exe
```

* 消息认证码

```
python make.py sm3\sm3_hmac.cpp  demo.exe
```

## sm4

* 加密解密

```
python make.py sm4\sm4_cipher.cpp  demo.exe
```

* 工作模式

```
python make.py sm4\sm4_cbc.cpp  demo.exe
```

```
python make.py sm4\sm4_gcm.cpp  demo.exe
```

## sm9

```
python make.py sm9\sm9_sign.cpp  demo.exe
```