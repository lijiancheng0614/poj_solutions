# Ships

## 题目

给定 h x w 的字符矩阵

有 7 个不同形状可以旋转不能翻转的船

x 表示船的一部分，o 表示空，. 表示未知

点击 . 可以翻开该位置看是船还是空

求最多翻出一次 o 的情况下能否翻出所有的船


## 方法

搜索

用 dfs 搜索每个船，枚举每个位置看是否能放下当前船

记录所有解，并去掉重复解

若只有一个解或无解则确定答案

若有多解，则枚举原图中未知且解中为空的位置，若只有一个位置则去掉该解

直至最后只有一个解或无解则答案为能