# Farmland

## 题目

给定 n 个点相连关系的平面图

设简单多边形为任意两条不相邻的边不相交不重合的多边形

求有 k 条边且内部不包含其它点的简单多边形的个数


## 方法

数学 - 几何

枚举起始点搜索所有能构成 k 条边的多边形

再判断多边形是否符合条件：

1. 多边形有向面积为正

2. 剩下点不在多边形内：剩下点与无穷远点相连，判断该线与多边形相交的边数是否为奇数，是则在里面

3. 多边形不相邻两点不相连
