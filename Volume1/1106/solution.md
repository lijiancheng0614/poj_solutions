# Transmitters

## 题目

给定一个点、半径和一个点集

求以该点为圆心的半圆最多能覆盖点集中点的个数


## 方法

几何

筛选出与定点距离不大于半径的点

显然最优解存在至少有一个点在半圆直径上的情况

枚举在直径上的点，用叉积判断同侧的点的数量，取最大值即可