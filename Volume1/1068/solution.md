# Parencodings

## 题目

给定一个合法括号序列

已知其 P 序列：每个右括号前的左括号个数

求 W 序列：当前右括号包含的括号对数


## 方法

模拟

遍历 P 序列算出原括号序列：不断插入 p[i] - p[i - 1] 个左括号即可

遍历括号序列，用计数器记录当前位置未匹配的左括号数，遇左括号 + 1，遇右括号 - 1

遇左括号时还需更新计数器对应的位置 i

遇右括号时则找到计数器相同值时左括号的位置 j，并把 (i - j + 1) / 2 加入到 W 中