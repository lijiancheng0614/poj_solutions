# You Who?

## 题目

给定一个不完全连通的无向图，将其分成点数最多相差 1 的两个子图

求如何分使得两个子图中度最小的点的度尽可能大，输出两个子图中点数减去该度的值的较大者


## 方法

枚举

用二进制表示每个点的不连通情况

枚举其中一个子图选哪些点，统计每个点与子图的交集后二进制下 1 的位数即为该子图的答案

答案为两个子图答案较大者的最小值
