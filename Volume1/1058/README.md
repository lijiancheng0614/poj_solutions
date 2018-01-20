# The Gourmet Club

Time Limit: 1000MS

Memory Limit: 65536K

Special Judge


## Description

The gourmet club of ACM City has 16 members. They contracted the proprietor of the local French restaurant Chateau Java to arrange dinner parties for 5 consecutive evenings. They asked to be seated around 4 tables, 4 persons per table. They also stipulated that during the 5 evenings, every member of the club will share a table exactly once with each member of the club. Mr. I.B. Emm, the restaurateur, assigned his Maitre D' the task of scheduling the seating for the 5 evenings. On the first evening, the Maitre D' seated the members as they arrived and recorded their seating. Each subsequent evening, he carefully planned the seating to match the requirement that no member will be dining twice with some other member. Unfortunately, the Maitre D' disappeared on the morning of the fourth evening. Mr. Emm was left only with his notes which included the recorded seating arrangements during the previous 3 evenings. As he was trying to schedule the seating for the remaining evenings, it dawned on him that this task may not be that easy. He is asking for your help to try and see whether the remaining two evenings can be scheduled. The following is a sample of the Maitre D's seating arrangements during the first 3 evenings:

ABCD    EFGH    IJKL    MNOP
AEIM    BFJN    CGKO    DHLP
AFKP    BGLM    CHIN    DEJO

The members of the gourmet club were identified by the letters A,B,C,...,P.

Each line represents one evening of seating with each set of four letters a single table. Thus on the first evening A dines with B, C and D etc. Write a program that will read from the input the seating arrangement of the first three evenings and will either complete the schedule or determine that the Maitre D' screwed up.


## Input

Each data set will be 3 lines. Each line will consist of four blocks, each 4 letters long. All letters will be in upper case. Blocks will be separated by "white space". Data sets will be separated by blank lines.


## Output

For a successful schedule, echo the input and add two lines showing the successful schedule. If it is not possible to complete the schedule, do not echo the input, but print "It is not possible to complete this schedule." Separate output for each data set with a blank line.


## Sample Input

```
ABCD EFGH IJKL MNOP
AEIM BFJN CGKO DHLP
AFKP BGLM CHIN DEJO
```


## Sample Output

```
It is not possible to complete this schedule.
```


## Hint

If there are several solutions, any one is ok.


## Source

Pacific Northwest 1998
