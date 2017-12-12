# Fence

## 题目

给定一个高为 h 的多边形栅栏和一个位于 (0, 0) 的光源

距光源 r 处的光强度为 I_0 = k / r，k 为常数

一块无穷小的宽度为 dl 高为 h 的栅栏受到的照度为 dI = I_0 * |cos a| * dl * h

其中 I_0 为该点光强，a 为法线与该点到光源连线的夹角

求栅栏的总照度 sum{dI}


## 方法

几何

对宽度为 dl 的线段 AB，设光源 O 垂直于 AB 于点 D

设 OA = r, 角 AOD = a, OA 与 OB 的夹角为 da

OD = r * cos a

dl = AB = BD - AD

   = OD * (tan a - tan(a - da))

   = r * cos a * (sin a / cos a - sin(a - da) / cos(a - da))

   = r * (sin a * cos(a - da) - cos a * sin(a - da)) / cos(a - da)

   = r * (sin a * cos a * cos da + sin a * sin a * sin da - cos a * sin a cos da + cos a * cos a sin da)  / cos(a - da)

   = r * sin da / cos(a - da)

   ~= r * da / cos a

dI = I_0 * |cos a| * dl * h

   = k / r * |cos a| * r * da / cos a * h

   = k * h * da

sum{dI} = k * h * sum{da}

sum{da} 即光源点对该多边形的张角

对光源点对多边形每条有向边的张角 a (-pi <= a <= pi) 求和

若包含光源点，则张角为 2 * pi，否则为求和过程中最大值与最小值之差
