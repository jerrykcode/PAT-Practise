# 1114. Family Property (25)



* 时间限制 150 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B


* 判题程序 Standard 

* 作者 CHEN, Yue



This time, you are supposed to help us collect the data for family-owned property. Given each person's family members, and the estate（房产）info under his/her own name, we need to know the size of each family, and the average area and number of sets of their real estate.

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N (<=1000). Then N lines follow, each gives the infomation of a person who owns estate in the format:

*ID Father Mother k Child1 ... Childk M_estate Area*

where ID is a unique 4-digit identification number for each person; Father and Mother are the ID's of this person's parents (if a parent has passed away, -1 will be given instead); k (0<=k<=5) is the number of children of this person; Childi's are the ID's of his/her children; M_estate is the total number of sets of the real estate under his/her name; and Area is the total area of his/her estate. 

## Output Specification: 

For each case, first print in a line the number of families (all the people that are related directly or indirectly are considered in the same family). Then output the family info in the format: 

*ID M AVG_sets AVG_area*

where ID is the smallest ID in the family; M is the total number of family members; AVG_sets is the average number of sets of their real estate; and AVG_area is the average area. The average numbers must be accurate up to 3 decimal places. The families must be given in descending order of their average areas, and in ascending order of the ID's if there is a tie. 




## Sample Input:

10
6666 5551 5552 1 7777 1 100
1234 5678 9012 1 0002 2 300
8888 -1 -1 0 1 1000
2468 0001 0004 1 2222 1 500
7777 6666 -1 0 2 300
3721 -1 -1 1 2333 2 150
9012 -1 -1 3 1236 1235 1234 1 100
1235 5678 9012 0 1 50
2222 1236 2468 2 6661 6662 1 300
2333 -1 3721 3 6661 6662 6663 1 100

## Sample Output:

3
8888 1 1.000 1000.000
0001 15 0.600 100.000
5551 4 0.750 100.000


## 题意：

N个人，输入每个人的id、父母id及所有子女的id，以及此人的房产数量和房产总面积。有亲属关系的人组成一个家庭，每个家庭的id为其成员中id最小的人的id。家庭的相关信息有：id、成员数量、成员人均房产数量和人均面积。输出家庭数量。家庭按成员人均面积递减排序，有相同则按id递增排序。输出所有家庭。所有id不超过4个数字，所有人的id均不相同

## 思路：


*BFS求连通分量*

长度10000的结构体数组存储N个人。数组的下标为该人的id。结构体中用vector存储此人的直接亲属（父母及子女）。这些直接亲属即是与该人直接相邻的顶点（看作图）。BFS求连通分量。一个连通分量即一个家庭。对每个连通分量求出其中最小的id，所有顶点的总房产数量、总面积，从而得到这个家庭的信息。家庭用另一个结构体存储。所有家庭存储在一个vector中，排序后输出


## 代码：

[1114. Family Property (25).cpp ](https://github.com/jerrykcode/PAT-Advanced-Level-Practise/blob/master/1114.%20Family%20Property%20(25)/1114.%20Family%20Property%20(25).cpp)