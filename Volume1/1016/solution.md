# Numbers That Count

## 题目

给定非负整数 n

它的 inventory 是另一个整数：由 c1 d1 c2 d2 ... ck dk 拼接而成

表示 n 中有 ci 个 di，ci 是正整数，0 <= d1 < d2 < ... < dk <= 9

求 n 属于以下哪一类：

1. self-inventorying: n 的 inventory 等于 n

2. self-inventorying after j steps: n 经过 j 次 inventory 转换后满足第一类

3. n enters an inventory loop of length k: n 经过 j 次 inventory 转换后得到 n_j，经过 k 次 inventory 转换后又得到 n_j，以此循环

4. n can not be classified after 15 iterations: n  经过 15 次 inventory 转换后不满足上述三类


## 方法

模拟
