# 1069. The Black Hole of Numbers (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1069)
* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



For any 4-digit integer except the ones with all the digits being the same, if we sort the digits 
in non-increasing order first, and then in non-decreasing order, a new number can be obtained by 
taking the second number from the first one. Repeat in this manner we will soon end up at the number 
6174 -- the "black hole" of 4-digit numbers. This number is named Kaprekar Constant.

For example, start from 6767, we'll get:

	7766 - 6677 = 1089
	9810 - 0189 = 9621
	9621 - 1269 = 8352
	8532 - 2358 = 6174
	7641 - 1467 = 6174
		... ...

Given any 4-digit number, you are supposed to illustrate the way it gets into the black hole.



## Input Specification: 

Each input file contains one test case which gives a positive integer N in the range (0, 10000).


## Output Specification: 

If all the 4 digits of N are the same, print in one line the equation "N - N = 0000". Else print each 
step of calculation in a line until 6174 comes out as the difference. All the numbers must be printed 
as 4-digit numbers.



## Sample Input 1:

6767

## Sample Output 1:

7766 - 6677 = 1089  
9810 - 0189 = 9621  
9621 - 1269 = 8352  
8532 - 2358 = 6174  


## Sample Input 2:

2222

## Sample Output 2:

2222 - 2222 = 0000


## 代码：

[1069. The Black Hole of Numbers (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1069.%20The%20Black%20Hole%20of%20Numbers%20(20)/1069.%20The%20Black%20Hole%20of%20Numbers%20(20).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <algorithm>

int compare(char a, char b)
{
	return a > b;
}

int main()
{
	string number;
	cin >> number;
	while (1) {
		while (number.length() < 4) number = "0" + number;
		sort(number.begin(), number.end(), compare);
		int n1 = stoi(number);
		sort(number.begin(), number.end());
		int n2 = stoi(number);
		int sub = n1 - n2;
		printf("%04d - %04d = %04d\n", n1, n2, sub);
		if (sub == 6174 || sub == 0) break;
		number = std::to_string(sub);
	}
    return 0;
}
```
