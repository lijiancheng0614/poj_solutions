# Joseph

## 题目

给定 k 个 0 和 k 个 1 依次组成的环

从第 1 个数开始数，数到第 m 个数时删掉这个数并从头开始数

求最小的正整数 m 使得 k 个 1 被删掉，剩下 k 个 0


## 方法

数学

设 n = 2k，把这些数编号为 0, 1, ..., n - 1

则第 i 轮删掉的数在这轮的编号为 f[i] = (f[i - 1] + m - 1) % (n - i + 1), f[0] = 0

由题意知，f[i] >= k, 0 < i <= k

那么 f[k] = k + 1

f[k - 1] = k + 2 或 f[k - 1] = k + 1

代入得 m = (k + 1) * t 或 m = (k + 1) * t + 1，其中 t >= 1


## 注意
