# Eight

## 题目

给定 3 * 3 的棋盘上，其中 8 个位置上放了 1 ~ 8 这 8 个数

求移动剩余的空位，使棋盘上的数字有序


## 方法

搜索

这是经典的八数码问题，每个状态恰好是一个全排列，使用康托展开可对状态进行压缩

使用 bfs 搜索初始状态不断往 4 个方向移动，直至到达目标状态


## 注意

过多地新建 vector 对象会导致超时
