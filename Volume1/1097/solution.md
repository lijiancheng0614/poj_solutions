# Roads Scholar

## 题目

给定 n 个点 m 条边的带点权带边权无向图

要在边上某个位置加路牌显示从边的起始点到远方某个必经过该边的点的距离

求所有远方点并按距离和点权顺序输出


## 方法

图论 - 最短路

用 floyd 求出任意两点间的最短路，并求出任意两点间最短路最先经过的边

按边保存所有远方点

查询时取出远方点及其距离按要求排序即可
