# The Circle

Time Limit: 1000MS

Memory Limit: 10000K


## Description

You have a circle, divided into sectors. You are given three positive numbers: n (n <= 6), m (m <= 20) and k (k <= 20). n is the number of sectors. Choose integers to place in each sector. All integers have to be greater or equal to k. When the circle is filled you can use the integer in a single sector or add the integers in two or more adjacent sectors to make a new number. Using these new numbers you can create an unbroken sequence of all integers between m and i (m,m+1,m+2 ... i).

Your task is to choose integers for the sectors such that the largest number (i) in the sequence is as high as possible. Figure 1 below shows how to generate all numbers from 2 to 21 (for n=5, m=2, k=1). The ^-sign below the sectors shows which sectors to add together to make numbers in the sequence.


## Input

Your program is to read from standard input. The input contains three integers (n, m and k).


## Output

Your program is to write to standard output. The output must contain:
The highest number (i) that can be generated with the list of numbers.
All arrangements of numbers in a circle that produce a sequence from m to i. (One per line.) Each arrangement is a list of numbers starting with the smallest number (which is not necessarily unique). The arrangements are sorted in ascending order.

(2 10 3 1 5) is NOT a valid solution, since it does not start with the smallest number. (1 3 10 2 5) and (1 5 2 10 3) must both be included in the output. Note that (1 1 2 3), (1 3 2 1), (1 2 3 1) and (1 1 3 2) should all be output.


## Sample Input

```
5
2
1
```


## Sample Output

```
21
1 3 10 2 5
1 5 2 10 3
2 4 9 3 5
2 5 3 9 4
```


## Hint

FIGURE 1 (all circles have been cut open as indicated by arrow):

```
   |----------|      |----------|     |----------|     |----------|
.->|1|3|10|2|5|-.    |1|3|10|2|5|     |1|3|10|2|5|     |1|3|10|2|5|
|  |----------| |    |----------|     |----------|     |----------|
|          ^    |       ^              ^ ^                       ^
"---------------"

   |----------|      |----------|     |----------|     |----------|
.->|1|3|10|2|5|-.    |1|3|10|2|5|     |1|3|10|2|5|     |1|3|10|2|5|
|  |----------| |    |----------|     |----------|     |----------|
|   ^        ^  |            ^ ^       ^      ^ ^       ^ ^      ^
"---------------"

   |----------|      |----------|     |----------|     |----------|
.->|1|3|10|2|5|-.    |1|3|10|2|5|     |1|3|10|2|5|     |1|3|10|2|5|
|  |----------| |    |----------|     |----------|     |----------|
|        ^      |     ^ ^    ^ ^            ^           ^ ^    ^ ^
"---------------"

   |----------|      |----------|     |----------|     |----------|
.->|1|3|10|2|5|-.    |1|3|10|2|5|     |1|3|10|2|5|     |1|3|10|2|5|
|  |----------| |    |----------|     |----------|     |----------|
|        ^ ^    |       ^  ^           ^ ^  ^             ^  ^ ^
"---------------"

   |----------|      |----------|     |----------|     |----------|
.->|1|3|10|2|5|-.    |1|3|10|2|5|     |1|3|10|2|5|     |1|3|10|2|5|
|  |----------| |    |----------|     |----------|     |----------|
|   ^ ^ ^  ^    |          ^ ^ ^       ^    ^ ^ ^       ^ ^  ^   ^
"---------------"

   |----------|      |----------|
.->|1|3|10|2|5|-.    |1|3|10|2|5|
|  |----------| |    |----------|
|     ^ ^  ^ ^  |     ^ ^ ^  ^ ^
"---------------"
```


## Source

IOI 1994
