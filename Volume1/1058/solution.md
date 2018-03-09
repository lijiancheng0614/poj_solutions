# The Gourmet Club

## 题目

给定 16 个点，平均分成 4 组，每组内点两两连边

已知 3 种分组方案，方案的并集不存在重边

求是否再增加 2 种分组方案能使得所有方案的并集不存在重边且构成完全图（任意两点相连）


## 方法

模拟

显然存在则每个点还与 6 个点没相连

设与点 A 不相连的点集为 S(A)，点 B 属于 S(A)

则 S(A) 与 S(B) 的交集恰好为 2 时合法且 A, B, S(A) 与 S(B) 的交集为一个分组

此时该分组内恰好有 3 个点没相连时合法，显然每个点与相应的 3 个占点为另一种分组方案

判断两个分组方案是否相容即可