# Cipher

## 题目

给定 1 ~ n 的序列 a[i]，一些字符串 s[j] 及置换次数 k[j]

置换一次即把第 i 个位置上的字符变成第 a[i] 个位置上的字符，长度小于 n 则用空格补齐

求所有字符串置换 k 次后的字符串


## 方法

数学

设某个位置上的置换的阶为 len，则进行 k 次置换的结果与进行 k % len 次置换的结果相同

故求出每个位置上的阶 len[i]：不断进行 i' = a[i'] 直到 i' = i，len 为进行操作的次数

然后对每个位置进行 k % len[i] 次置换即可
