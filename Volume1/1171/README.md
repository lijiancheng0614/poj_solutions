# Letter Game

Time Limit: 1000MS

Memory Limit: 10000K


## Description

![1171_1.gif]
 
Figure 1:Each of the 26 lowercase letters and its value

Letter games are popular at home and on television. In one version of the game, every letter has a value, and you collect letters to form one or more words giving the highest possible score. Unless you have 'a way with words', you will try all the words you know, sometimes looking up the spelling, and then compute the scores. Obviously, this can be done more accurately by computer.

Given the values in Figure 1, a list of English words, and the letters collected: find the highest scoring words or pairs of words that can be formed,in which a letter must not occur more often than in the collected letters.


## Input

Your program is to read from standard input. The first line contains a string of lowercase letters (from 'a' to 'z'): the letters collected. The string consists of at least 3 and at most 7 letters in arbitrary order.

From the second line, there is a dictionary consisting of at most 40,000 lines. At the end of the dictionary is a line with a single period ('.'). Each of the other lines contains a string of at least 3 and at most 7 lowercase letters. The dictionary is sorted alphabetically and contains no duplicates.


## Output

Your program is to write to standard output. You should output one line with the highest score.


## Sample Input

```
prmgroa
profile
program
prom
rag
ram
rom
.
```


## Sample Output

```
24
```


## Hint

Huge input,scanf is recommended.


## Source

IOI 1995
