# Octal Fractions

Time Limit: 1000MS

Memory Limit: 10000K


## Description

Fractions in octal (base 8) notation can be expressed exactly in decimal notation. For example, 0.75 in octal is 0.953125 (7/8 + 5/64) in decimal. All octal numbers of n digits to the right of the octal point can be expressed in no more than 3n decimal digits to the right of the decimal point.

Write a program to convert octal numerals between 0 and 1, inclusive, into equivalent decimal numerals.


## Input

The input to your program will consist of octal numbers, one per line, to be converted. Each input number has the form 0.d1d2d3 ... dk, where the di are octal digits (0..7). There is no limit on k.


## Output

Your output will consist of a sequence of lines of the form

0.d1d2d3 ... dk [8] = 0.D1D2D3 ... Dm [10]


where the left side is the input (in octal), and the right hand side the decimal (base 10) equivalent. There must be no trailing zeros, i.e. Dm is not equal to 0.


## Sample Input

```
0.75
0.0001
0.01234567
```


## Sample Output

```
0.75 [8] = 0.953125 [10]
0.0001 [8] = 0.000244140625 [10]
0.01234567 [8] = 0.020408093929290771484375 [10]
```


## Source

Southern African 2001
