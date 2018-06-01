# LITTLE SHOP OF FLOWERS

## 题目

给定一个 n * m 的矩阵 a[][]

求 max{sum{a[i][p[i]]}}, 1 <= i <= n, p[i] < p[i + 1]


## 方法

动态规划

设 f[i][j] 为 i * j 矩阵的最大值

则 f[i][j] = max{f[i][j - 1], f[i - 1][j - 1] + a[i][j]}

答案为 f[n][m]
