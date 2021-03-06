# Binary codes

Time Limit: 1000MS

Memory Limit: 65536K


## Description

Consider a binary string (b1...bN) with N binary digits. Given such a string, the matrix of Figure 1 is formed from the rotated versions of the string.

```
b1   b2 ... bN−1 bN
b2   b3 ... bN   b1
...
bN−1 bN ... bN−3 bN−2
bN   b1 ... bN−2 bN−1
```

Figure 1. The rotated matrix

Then rows of the matrix are sorted in alphabetical order, where ‘0’ is before ‘1’. You are to write a program which, given the last column of the sorted matrix, finds the first row of the sorted matrix.

As an example, consider the string (00110). The sorted matrix is

```
0 0 0 1 1
0 0 1 1 0
0 1 1 0 0
1 0 0 0 1
1 1 0 0 0
```

and the corresponding last column is (1 0 0 1 0). Given this last column your program should determine the first row, which is (0 0 0 1 1).


## Input

The first line contains one integer N ≤ 3000, the number of binary digits in the binary string. The second line contains N integers, the binary digits in the last column from top to bottom.


## Output

The first line contains N integers: the binary digits in the first row from left to right.


##Sample Input

```
5
1 0 0 1 0
```


## Sample Output

```
0 0 0 1 1
```


## Source

IOI 2001 (back-up task)
