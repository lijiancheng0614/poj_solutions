# Dividing

## 题目

给定 a[i] 个 i, i 为 1 到 6 间的整数

求是否存在非负数数列 b，使得 sum{b[i] * i} = sum{a[i] * i} / 2


## 方法

动态规划

设 f[i][j] 为使用前 i 种数，和为 j 时第 i 种数剩余的个数

```
f[i][j] = a[i],            if f[i - 1][j] >= 0

          -1,              if j < i or f[i - 1][j - i] <= 0

          f[i][j - i] - 1, else

f[0][0] = 0
```

若 f[n][sum / 2] >= 0 则存在该数列
