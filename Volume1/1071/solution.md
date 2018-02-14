# Illusive Chase

## 题目

给定 m * n 的 01 矩阵和第 i 步往 d[i] 方向走 a[i] 至 b[i] 步的路径

矩阵中 1 表示不能通过该位置，d[i] 为上下左右四个方向之一

求有多少个初始位置，使得满足该路径且不走出矩阵


## 方法

动态规划

设 f[k][i][j] 表示第 k 步是否能走到 (i, j)，则

f[k][i][j] |= f[k - 1][x][y]

其中 (x, y) + direction * step = (i, j), steps_min[k] <= step <= steps_max[k] 且 (x, y) 到 (i, j) 的路径上不存在 1

初始时 f[0] 即 01 矩阵取反

答案为 f[steps] 中能走到的元素个数
