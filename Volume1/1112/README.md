# Team Them Up!

Time Limit: 1000MS

Memory Limit: 10000K

Special Judge


## Description

Your task is to divide a number of persons into two teams, in such a way, that:

everyone belongs to one of the teams;

every team has at least one member;

every person in the team knows every other person in his team;

teams are as close in their sizes as possible.

This task may have many solutions. You are to find and output any solution, or to report that the solution does not exist.


## Input

For simplicity, all persons are assigned a unique integer identifier from 1 to N.

The first line in the input file contains a single integer number N (2 <= N <= 100) - the total number of persons to divide into teams, followed by N lines - one line per person in ascending order of their identifiers. Each line contains the list of distinct numbers Aij (1 <= Aij <= N, Aij != i) separated by spaces. The list represents identifiers of persons that ith person knows. The list is terminated by 0.


## Output

If the solution to the problem does not exist, then write a single message "No solution" (without quotes) to the output file. Otherwise write a solution on two lines. On the first line of the output file write the number of persons in the first team, followed by the identifiers of persons in the first team, placing one space before each identifier. On the second line describe the second team in the same way. You may write teams and identifiers of persons in a team in any order.


## Sample Input

```
5
2 3 5 0
1 4 5 3 0
1 2 5 0
1 2 3 0
4 3 2 1 0
```


## Sample Output

```
3 1 3 5
2 2 4
```


## Source

Northeastern Europe 2001
