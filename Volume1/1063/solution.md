# Flip and Shift

## 题目

给定 01 循环串，每次可交换相邻 3 个元素的首尾 2 个元素

求是否可以经过若干次交换使得所有 0 相邻


## 方法

数学

若串长为奇数，则每个位置上的数可交换至任意位置，答案显然为是

若串长为偶数，则奇/偶数位置上的数可交换至奇/偶数位置上。所求问题转化为奇数位置上的 0 的个数与偶数位置上的 0 的个数之差不大于 1
