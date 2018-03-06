# 1058. A+B in Hogwarts (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1058)
* 时间限制 50 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



If you are a fan of Harry Potter, you would know the world of magic has its own currency system 
-- as Hagrid explained it to Harry, "Seventeen silver Sickles to a Galleon and twenty-nine Knuts 
to a Sickle, it's easy enough." Your job is to write a program to compute A+B where A and B are 
given in the standard form of "Galleon.Sickle.Knut" (Galleon is an integer in [0, 107], Sickle is 
an integer in [0, 17), and Knut is an integer in [0, 29)).



## Input Specification: 

Each input file contains one test case which occupies a line with A and B in the standard form, 
separated by one space. 



## Output Specification: 

For each test case you should output the sum of A and B in one line, with the same format as the input.



## Sample Input:

3.2.1 10.16.27  

## Sample Output:

14.1.28  


## 题意：

个位到29进位，十位到17进位，给出两个数的百位、十位、个位，求和的百位、十位、个位

## 思路：

按规则进位

## 代码：
[1058. A+B in Hogwarts (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1058.%20A+B%20in%20Hogwarts%20(20)/1058.%20A+B%20in%20Hogwarts%20(20).cpp)

```cpp
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int g1, s1, k1, g2, s2, k2, g, s, k;
	scanf("%d.%d.%d %d.%d.%d", &g1, &s1, &k1, &g2, &s2, &k2);
	k = (k1 + k2) % 29;
	int temp = (k1 + k2) / 29;
	s = (s1 + s2 + temp) % 17;
	temp = (s1 + s2 + temp) / 17;
	g = g1 + g2 + temp;
	printf("%d.%d.%d", g, s, k);
	return 0;
}
```
