# SAFE

Time Limit: 1000MS

Memory Limit: 10000K


## Description

Mirko has decided to rob mini-safe owned by his son so that he could take away some football stickers which are missing in his big sticker collection.

Lock on the safe consists of N equal discs, each of them being divided in 10,000,000 equal segments numbered from 1 to 10,000,000 clockwise. In the begining, segments on discs having the same number are placed one above (beneath) the other. Discs are layed one on the other such that the segments are overlaping and each disc is missing exactly one segment that is called hole.

In order to unlock the lock, all holes must be one above (beneath) the other.In one second, Mirko can turn one disc in one direction (clockwise or counterclockwise) for one segment.

Write a program which will find the minimal time that Mirko needs to open the safe.


## Input

The first line of the input contains an integer N, 2 <= N <= 100,000, the number of discs.

The next N lines contain data describing the initial positions of the holes on each disc.

The (i + 1)-th line contains an integer Pi, 1 <= Pi <= 10000000, the initial position of the hole on the i-th disc.


## Output

The first and only line of the output should contain the minimal time (in seconds).

Note: take care of the size of that number.


## Sample Input

```
4
9999999
7
16
9999995
```


## Sample Output

```
29
```


## Source

Croatia OI 2002 Final Exam - First day
