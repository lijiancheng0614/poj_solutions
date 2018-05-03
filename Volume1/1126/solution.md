# Simply Syntax

## 题目

给定一个字符串

求是否符合以下条件：

0. 字母仅为 p 到 z 和 N, C, D, E, I

1. 每一个 p 到 z 的字母是一个正确句子

2. 若 s 是一个正确句子，那么 Ns 也是

3. 若 s 和 t 是正确句子，那么 Cst, Dst, Est, Ist 也是

4. 不符合上述的句子不正确


## 方法

模拟

从后往前遍历字符串，设 tot 为正确句子数量

若为 p ~ z，tot += 1

若为 N，若 tot < 1 则不符合

若为 C D E I，若 tot < 2 则不符合；反之 tot -= 1

若为其它字符，则不符合

最后若 tot 为 1，则符合