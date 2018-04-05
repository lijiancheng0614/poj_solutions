# Double Vision

## 题目

给定 n 个 r * c 大小的 01 矩阵，要求找出每个矩阵中不超过两个点使得其为 1 而其它矩阵不全为 1

求是否能找到及找到的结果


## 方法

模拟

枚举每个每个矩阵的每个 1 位置，判断其它矩阵是否不全为 1

先判断 1 个点，再判断 2 个点的情况即可