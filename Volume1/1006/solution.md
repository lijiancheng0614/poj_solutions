# Biorhythms

## 题目

给定非负整数 p, e, i, d

求最小的 ans 使得存在正整数 a, b, c 满足 ans = p + 23 * a = e + 28 * b = i + 33 * c 且 ans > d


## 方法

数学

中国剩余定理

由于 23, 28, 33 素质，故由剩余定理有

设 s1 = p + 23 * a, s2 = e + 28 * b, s3 = i + 33 * c

令 ans = s1 + s2 + s3 除以 23 余 p, 除以 28 余 e, 除以 33 余 i

则 s2, s3 为 23 的倍数，s3, s1 为 28 的倍数， s1, s2 为 33 的倍数

又根据 (k * a) % b = k * (a % b) (k > 0)

则 s1 = p * s1', s2 = e * s2', s3 = i * s3'

s1' = 28 * 33 * a 且 s1' % 23 == 1 => 最小的正整数 s1' = 5544, a = 6

s2' = 23 * 33 * b 且 s2' % 28 == 1 => 最小的正整数 s2' = 14421, b = 19

s3' = 23 * 28 * c 且 s3' % 33 == 1 => 最小的正整数 s3' = 1288, c = 2

故 ans = (s1' * p + s2' * e + s3' * i) % (23 * 28 * 33)