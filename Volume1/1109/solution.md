# Index Generation

## 题目

给定若干文档，文档间用 `*` 隔开

文档内不同页用 `&` 隔开

文档内索引用 `{text%primary$secondary}` 表示，`primary` 和 `secondary` 可选

若有 `primary` 则索引关键字为 `primary`，否则为 `text`

若有 `secondary` 则增加一行，并把页码写在这一行，否则把页码写在主关键字那一行

求每个文档大小写不敏感排序后的索引及其对应页码


## 方法

模拟
