# 1116. Come on! Let's C (20)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1116)

* 时间限制 200 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



"Let's C" is a popular and fun programming contest hosted by the College of Computer Science and Technology, Zhejiang University. Since the idea of the contest is for fun, the award rules are funny as the following:

* 0.The Champion will receive a "Mystery Award" (such as a BIG collection of students' research papers...).
* 1.Those who ranked as a prime number will receive the best award -- the Minions (小黄人)!
* 2.Everyone else will receive chocolates. 

Given the final ranklist and a sequence of contestant ID's, you are supposed to tell the corresponding awards. 

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N (<=10000), the total number of contestants. Then N lines of the ranklist follow, each in order gives a contestant's ID (a 4-digit number). After the ranklist, there is a positive integer K followed by K query ID's.

## Output Specification: 

For each query, print in a line "ID: award" where the award is "Mystery Award", or "Minion", or "Chocolate". If the ID is not in the ranklist, print "Are you kidding?" instead. If the ID has been checked before, print "ID: Checked". 
##Sample Input:  
6  
1111  
6666  
8888  
1234  
5555  
0001  
6  
8888  
0001  
1111  
2222  
8888  
2222  

## Sample Output:  
8888: Minion  
0001: Chocolate  
1111: Mystery Award  
2222: Are you kidding?  
8888: Checked  
2222: Are you kidding?  

## 题意：

N个参赛的人，输入N行，第i行为第i名的id（i从1开始，id有4个数字）。输入K个询问id，若这个id的名次是1，则输出`Mystery Award`，名次是素数则输出`Minion`，否则输出`Chocolate`，若id不存在则输出`Are you kidding?`，id在之前已查询过则输出`Checked`。


## 思路：

用数组下标表示id，存储id对应的名次。id不存在的其对应的值为0。具体情况见代码。


## 代码：


[1116. Come on! Let's C (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1116.%20Come%20on!%20Let's%20C%20(20)/1116.%20Come%20on!%20Let's%20C%20(20).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
#include <math.h>
using namespace std;

int isPrime(int n)
{
	if (n == 1) return 0;
	if (n <= 3) return 1;
	for (int i = 2; i <= sqrt(n); i++) 
		if (n % i == 0) return 0;
	return 1;
}

int main()
{
	int flag[10000];
	fill(flag, flag + 10000, 0);
	int n, id, k;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> id;
		flag[id] = i;
	}
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> id;
		printf("%04d: ", id);
		switch (flag[id]) {
		case 0: {printf("Are you kidding?\n"); break; }
		case -1: { printf("Checked\n"); break; }
		case 1: {printf("Mystery Award\n"); flag[id] = -1; break; }
		default : {
			cout << (isPrime(flag[id]) == 1 ? "Minion\n" : "Chocolate\n");
			flag[id] = -1;
		}
		}
	}
    return 0;
}
```