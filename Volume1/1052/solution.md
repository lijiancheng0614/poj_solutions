# Plato's Blocks

## 题目

给定由若干 1 * 1 * 1 个小立方体粘连而成的大立方体 3 个不同方向投影的结果

求是否合理


## 方法

模拟

投影结果从不同角度看有 8 种情况，分别通过旋转（4 种）和镜像（2 种）得到

枚举每个方向的投影结果，根据光线去掉立方体的某一个通道

再判断构造的立方体是否能得到投影结果以及是否连通


## 注意

避免对象过多赋值导致超时
