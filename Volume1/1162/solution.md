# Building with Blocks

## 题目

给定 12 种由若干 1 x 1 x 1 正方体相连组成的积木，积木可旋转、位移且体积不超过 4

求某个实心物体最少由几块积木组成，要求积木不能重合


## 方法

搜索

显然对于体积为 V 的物体，至少需要 V / 4 块

按积木从大到小搜索，若某一步所需块数 + 剩下体积 / 4 不小于当前答案，则剪枝


## 注意

此方法是 [IOI 2000](http://www.ioinformatics.org/locations/ioi00/contest/) 时的参考方法，但也依然 Time Limit Exceeded
