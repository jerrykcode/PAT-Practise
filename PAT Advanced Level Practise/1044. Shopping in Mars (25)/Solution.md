# 1044. Shopping in Mars (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1044)
* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Shopping in Mars is quite a different experience. The Mars people pay by chained diamonds. 
Each diamond has a value (in Mars dollars M$). When making the payment, the chain can be 
cut at any position for only once and some of the diamonds are taken off the chain one by 
one. Once a diamond is off the chain, it cannot be taken back. For example, if we have a 
chain of 8 diamonds with values M$3, 2, 1, 5, 4, 6, 8, 7, and we must pay M$15. We may have 
3 options:

* 1\. Cut the chain between 4 and 6, and take off the diamonds from the position 1 to 5 (with values 3+2+1+5+4=15).
	
* 2\. Cut before 5 or after 6, and take off the diamonds from the position 4 to 6 (with values 5+4+6=15).
	
* 3\. Cut before 8, and take off the diamonds from the position 7 to 8 (with values 8+7=15).

Now given the chain of diamond values and the amount that a customer has to pay, you are 
supposed to list all the paying options for the customer.

If it is impossible to pay the exact amount, you must suggest solutions with minimum lost. 




## Input Specification: 

Each input file contains one test case. For each case, the first line contains 2 numbers: N (<=10^5), 
the total number of diamonds on the chain, and M (<=10^8), the amount that the customer has to pay. 
Then the next line contains N positive numbers D1 ... DN (Di<=10^3 for all i=1, ..., N) which are the 
values of the diamonds. All the numbers in a line are separated by a space.




## Output Specification: 

For each test case, print "i-j" in a line for each pair of i <= j such that Di + ... + Dj = M. Note 
that if there are more than one solution, all the solutions must be printed in increasing order of i.

If there is no solution, output "i-j" for pairs of i <= j such that Di + ... + Dj > M with (Di + ... + Dj - M) 
minimized. Again all the solutions must be printed in increasing order of i.

It is guaranteed that the total value of diamonds is sufficient to pay the given amount. 


## Sample Input 1:

16 15  
3 2 1 5 4 6 8 7 16 10 15 11 9 12 14 13  

## Sample Output 1:

1-5  
4-6  
7-8  
11-11  


## Sample Input 2:

5 13  
2 4 5 7 9  

## Sample Output 2:

2-4  
4-5  



## 题意：

火星上用一串钻石购买物品，每颗钻石有其价值，可截取一段钻石购买相应价值的物品，若没有一个子串
的价值正好与物品相等，则截取一段损失最小的串

输入一串钻石的个数与每颗钻石的价值，以及购买物品的价值，输出所有可选择的钻石字串

## 思路：

钻石串中的钻石价值存储在数组中，动态处理(具体实现见代码)

## 代码：
[1044. Shopping in Mars (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1044.%20Shopping%20in%20Mars%20(25)/1044.%20Shopping%20in%20Mars%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>

typedef struct node {
	int start;
	int end;
}chain;

int main()
{
	int n, m;
	cin >> n >> m;
	int *diamonds = new int[n];
	for (int i = 0; i < n; i++)
		cin >> diamonds[i];
	vector<chain> chains;
	int i ,j, sum, flag, minLost; //i, j指针，sum字串和，flag是否有相等的价值，minLost在无相等价值情况下最小损失
	i = j = flag = 0;
	sum = diamonds[0];
	minLost = 1000;
	while (j < n) {
		if (sum == m) { 
			printf("%d-%d\n", i + 1, j + 1);
			sum -= diamonds[i];
			i++;
			if (i > j) {
				j++;
				sum += diamonds[j];
			}
			flag = 1;
		}
		else if (sum > m) {
			if (!flag) { //还没有相等价值
				if (sum - m < minLost) {
					chains.clear();
					chains.push_back({ i, j });
					minLost = sum - m;
				}
				else if (sum - m == minLost)
					chains.push_back({ i, j });
			}
			sum -= diamonds[i];
			i++;
			if (i > j) {
				j++;
				sum += diamonds[j];
			}
		}
		else if (sum < m) {
			j++;
			sum += diamonds[j];
		}
	}
	if (!flag) {
		for (auto it = chains.begin(); it != chains.end(); it++)
			printf("%d-%d\n", it->start + 1, it->end + 1);
	}
    return 0;
}

```
