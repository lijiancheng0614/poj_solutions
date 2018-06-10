# SAFE

## 题目

给定 n 个数，每个数可在模 10000000 下加 1 或减 1

求把所有数变成同一个数的步数


## 方法

模拟

最后的数必为 n 个数之一

枚举该数 x，步数为 sum{min{(a[i] - x + N) % N, (x - a[i] + N) % N}}

可先排序再根据 x - N / 2 与 x + N / 2 的移动而快速从当前步数更新到新的步数