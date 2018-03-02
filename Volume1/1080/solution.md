# Human Gene Functions

## 题目

给定只包含ACGT的两个字符串，两个字符串可插入空格

再给定任意两个字符的分数

求两个字符串对应位置的分数之和的最大值


## 方法

动态规划、最长公共子序列

设 f[i][j] 表示串 1 前 i 位和串 2 前 j 位的最大值，则

f[i][j] = max{ f[i - 1][j - 1] + score[i][j],
    f[i - 1][j] + score[i][space],
    f[i][j - 1] + score[space][j] }

score[i][j] 表示串 1 第 i 位和串 2 第 j 位的分数

答案为 f[n][m]
