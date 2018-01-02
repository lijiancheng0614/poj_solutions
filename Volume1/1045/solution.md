# Bode Plot

## 题目

给定 V_2 = i * R

V_2 = V_R * cos(w * t + q)

V_1 = V_S * cos(w * t)

i = C * d(V_1 - V_2) / dt

d指求导

已知 V_S, R, C, w

求 V_R


## 方法

数学

把前三式代入第四式，并左右同乘 R，得

V_R * cos(w * t + q) = R * C * d(V_S * cos(w * t) - V_R * cos(w * t + q)) / dt

由 d(cos(x)) / dx = -sin(x) 得

V_R * cos(w * t + q) = R * C * w (-V_S * sin(w * t) + V_R * sin(w * t + q))

令 w * t = 0 得

cos(q) = R * C * w * sin(q)

又 sin^2(q) + cos^2(q) = 1，则

R^2 * C^2 * w^2 * sin^2(q) + sin^2(q) = 1

即 sin(q) = sqrt(1 / (R^2 * C^2 * w^2 + 1))

令 w * t + q = 0 得

V_R = R * C * w * (-V_S * sin(w * t)) = R * C * w * V_S * sin(q)

则 V_R = R * C * w * V_S * sqrt(1 / (R^2 * C^2 * w^2 + 1))
