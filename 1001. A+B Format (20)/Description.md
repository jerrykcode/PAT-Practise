# 1001. A+B Format (20)

* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue


Calculate a + b and output the sum in standard format -- that is, the digits must be separated into 
groups of three by commas (unless there are less than four digits).



## Input

Each input file contains one test case. Each case contains a pair of integers a and b where -1000000 <= a, 
b <= 1000000. The numbers are separated by a space.



## Output

For each test case, you should output the sum of a and b in one line. 
The sum must be written in the standard format. 



## Sample Input
-1000000 9


## Sample Output
-999,991



## 题意：

输入两个整数a、b，将a + b的值按标准格式输出(如a = 1003，b = -2，输出1,001)

## 思路：

用字符串存储a + b的结果，从末尾每隔3个数插入逗号(具体实现方法见代码)

## 代码

[1001. A+B Format (20).cpp ](https://github.com/jerrykcode/PAT-Advanced-Level-Practise/blob/master/1001.%20A%2BB%20Format%20(20)/1001.%20A%2BB%20Format%20(20).cpp)

[AplusBFormat1001.java](https://github.com/jerrykcode/PAT-Advanced-Level-Practise/blob/master/1001.%20A%2BB%20Format%20(20)/AplusBFormat1001.java)
