# Hexagon

## 题目

给定如图所示 19 个六边形，每个方向由 5 行组成

5 行分别由 3 个不同的数字覆盖

每行分数为覆盖数字与该行格子数的乘积

总分数为 3 个方向共 15 行的分数之和

求分数最大值


## 方法

模拟

三个方向上的构成只可能是以下这一种可能性：

一个方向上三个数分别乘 5, 6, 8

另外两个方向上三个数分别乘 5, 7, 7

对三个方向的三个数排序，再依次相乘求和，求最大值即可