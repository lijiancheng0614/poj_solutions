# Pairs of Integers

Time Limit: 1000MS

Memory Limit: 10000K


## Description

You are to find all pairs of integers such that their sum is equal to the given integer number N and the second number results from the first one by striking out one of its digits. The first integer always has at least two digits and starts with a non-zero digit. The second integer always has one digit less than the first integer and may start with a zero digit.


## Input

The input file consists of a single integer N (10 <= N <= 10^9).


## Output

On the first line of the output file write the total number of different pairs of integers that satisfy the problem statement. On the following lines write all those pairs. Write one pair on a line in ascending order of the first integer in the pair. Each pair must be written in the following format:

X + Y = N

Here X, Y, and N, must be replaced with the corresponding integer numbers. There should be exactly one space on both sides of '+' and '=' characters.


## Sample Input

```
302
```


## Sample Output

```
5
251 + 51 = 302
275 + 27 = 302
276 + 26 = 302
281 + 21 = 302
301 + 01 = 302
```


## Source

Northeastern Europe 2001
