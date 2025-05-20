# hash lib

## 1. 基本介绍

引用自百度百科. [点击链接跳转原文](https://baike.baidu.com/item/HASH/)

> Hash，一般翻译做散列、杂凑，或音译为哈希，是把任意长度的输入（又叫做预映射pre-image）通过散列算法变换成固定长度的输出，该输出就是散列值。

引用自百度百科. [点击链接跳转原文](https://baike.baidu.com/item/hmac)

> HMAC是密钥相关的哈希运算消息认证码（Hash-based Message Authentication Code）的缩写

## 2. 接口说明

### 2.1 Hash 接口（gmlib/hash_lib/abc.h）

`Hash` 类型是所有Hash算法的基类，任何派生类都需要实现下述接口函数。

1 算法参数获取，包括：算法名称、算法名称的字符串长度、分组长度、摘要长度、安全强度

* 获取当前对象对应的哈希算法名称

```c++
    virtual const char* fetch_name() const noexcept = 0;
```

* 获取当前对象对应的哈希算法的分组长度（以字节为单位）

```c++
    virtual std::size_t fetch_block_size() const noexcept = 0;
```

* 获取当前对象对应的哈希算法的摘要长度（以字节为单位）

```c++
    virtual std::size_t fetch_digest_size() const noexcept = 0;
```

* 获取当前对象对应的哈希算法的安全强度

```c++
    virtual std::size_t fetch_security_strength() const noexcept = 0;
```

2 哈希处理，包括：重置、更新输入、输出摘要

* 重置对象

```c++
    virtual void reset() = 0;
```

* 更新对象的输入数据

```c++
    virtual void update(const std::uint8_t* in, std::size_t inl) = 0;
```

* 处理对象最后的输入，并输出摘要

```c++
    virtual void do_final(std::uint8_t*       digest,
                          const std::uint8_t* in  = nullptr,
                          std::size_t         inl = 0) = 0;
```

### 2.2 HashImpl 接口（gmlib/hash_lib/hash.h）

`HashImpl` 类型是对 `Hash` 类型的初步包装，定义了一个哈希算法所需要具备的基本接口。任何哈希算法都应该继承 `HashImpl` 类型。

`HashImpl` 类型实现了 `Hash` 类型中的 `reset`、`update` 和 `do_final` 函数，但需要依赖于下方两个函数，需要通过具体的哈希算法来实例化。

* 更新多分组数据

```c++
private:
    virtual void update_blocks(const std::uint8_t* in,
                               std::size_t         block_num) = 0;
```

* 处理最后一组数据

```c++
    virtual void final_block(std::uint8_t*       digest,
                             const std::uint8_t* in,
                             std::size_t         inl) = 0;
```

### 2.3 HMac（gmlib/hash_lib/hmac.h）

* 设置密钥

```c++
    void set_key(const std::uint8_t* key, std::size_t key_len);
```

* 更新数据

```c++
    void update(const std::uint8_t* msg, std::size_t msg_len);
```

* 输出摘要

```c++
    void do_final(std::uint8_t*       digest,
                  const std::uint8_t* msg     = nullptr,
                  std::size_t         msg_len = 0);
```

## 3. 权利与说明

无