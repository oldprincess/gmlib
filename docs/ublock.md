# uBlock

## 1. 基本介绍

> 吴文玲, 张蕾, 郑雅菲, 李灵琛. 分组密码 uBlock[J]. 密码学报, 2019, 6(6): 690–703.
>
> WU W L, ZHANG L, ZHENG Y F, LI L C. The block cipher uBlock[J]. Journal of Cryptologic Research, 2019, 6(6): 690–703.

## 2. 接口说明

略

## 3. 权利与说明

针对uBlock算法的实现采用了多种优化方案，在本节中进行具体说明。

- ublock common

普通实现。

- ublock standard

核心代码复用"全国密码算法设计竞赛"中uBlock密码算法的提交代码，需要处理器平台支持SSSE3指令集。

> <https://sfjs.cacrnet.org.cn/site/term/list_76_1.html>

- ublock gong25

使用龚等人的优化方法加速. [链接](https://jos.org.cn/jos/article/abstract/7316)

> 龚子睿, 郭华, 陈晨, 等. FBS-uBlock: 灵活的 uBlock 算法比特切片优化方法[J]. 软件学报, 2025, 36(10): 4827-4845.

```bibtex
@Article{20254827,
  title   = {FBS-uBlock: 灵活的uBlock算法比特切片优化方法},
  author  = {龚子睿,郭华,陈晨,张宇轩,陈俊鑫,关振宇},
  journal = {软件学报},
  volume  = {36},
  number  = {10},
  pages   = {4827},
  numpages= {19.0000},
  year    = {2025},
  month   = {10},
  doi     = {10.13328/j.cnki.jos.007316},
  publisher = {科学出版社}
}
```