# Image Perimeters

## 题目

给定一个 01 矩阵

求某个 1 位置所在连通块的周长


## 方法

搜索

floodfill 求出所在连通块，搜索时计算周围 0 的个数即可
