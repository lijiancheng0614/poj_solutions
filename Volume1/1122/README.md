# FDNY to the Rescue!

Time Limit: 1000MS

Memory Limit: 10000K


## Description

The Fire Department of New York (FDNY) has always been proud of their response time to fires in New York City, but they want to make their response time even better. To help them with their response time, they want to make sure that the dispatchers know the closest firehouse to any address in the city. You have been hired to write this software and are entrusted with maintaining the proud tradition of FDNY. Conceptually, the software will be given the address of the fire, the locations of the firehouses, street intersections, and the time it takes to cover the distance between each intersection. It will then use this information to calculate how long it takes to reach an address from each firehouse.

Given a specific fire location in the city, the software will calculate the time taken from all the fire stations located in the city to reach the fire location. The list of fire stations will be sorted from shortest time to longest time. The dispatcher can then pick the closest firestation with available firefighters and equipment to dispatch to the fire.


## Input

Line 1:

\# of intersections in the city, a single integer (henceforth referred to as N) N<20

Lines 2 to N+1:

A table (square matrix of integer values separated by one or more spaces) representing the time taken in minutes between every pair of intersections in the city. In the sample input shown below the value "3" on the 1st row and the 2nd column represents the time taken from intersection #1 to reach intersection #2.

Similarly the value "9" on the 4th row and the 2nd column represents the time taken from intersection #4 to reach intersection #2.

A value of -1 for time means that it is not possible to go directly from the origin intersection (row #) to the destination intersection (column #). All other values in the table are non-negative.

Line N+2:

An integer value n (<= N) indicating the intersection closest to the fire location followed by one or more integer values for the intersections closest to the fire stations (all on one line, separated by one or more spaces) will follow the input matrix.

Notes on input format:

1. The rows and columns are numbered from 1 to N.
2. All input values are integers
3. All fire locations are guaranteed reachable from all firehouses.
4. All distance calculations are made from the intersection closest to each firehouse to the intersection closest to the fire.


## Output

Line 1:

A label line with the headings for each column, exactly as shown in the example.

Line 2 onwards (one line for each fire station):

A sorted list (based on time) showing the fire station (origin), the destination site, time taken and a complete shortest path of nodes from the originating fire station to the fire location.

Notes on output format:

1. Columns are tab separated.
2. If two or more firehouses are tied in time they can be printed in any order.
3. If more than one path exists that has the same minimal time for a given location & firehouse, either one can be printed on the output.
4. If the fire location and the fire station locations happen to be the same intersection, the output will indicate that the origin and destination have the same intersection number, the time will be "0" and the nodes in the shortest path will show just one number, the fire location.
Next is the picture for the sample input data.

![](1122_1.gif)


## Sample Input

```
6
0  3  4 -1 -1 -1
-1 0  4  5 -1 -1
2  3  0 -1 -1  2
8  9  5  0  1 -1
7  2  1 -1  0 -1
5 -1  4  5  4  0
2  4  5  6
```

In the above input the last line indicates that "2" is the location of the fire and "4", "5" and "6" are the intersections where fire stations are located.


## Sample Output

```
Org	Dest	Time	Path
5	2	2	5	2
4	2	3	4	5	2
6	2	6	6	5	2
```


## Source

Mid-Atlantic 2001
