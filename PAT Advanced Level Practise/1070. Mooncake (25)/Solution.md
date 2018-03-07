# 1070. Mooncake (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1070)
* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Mooncake is a Chinese bakery product traditionally eaten during the Mid-Autumn Festival. Many types of fillings and 
crusts can be found in traditional mooncakes according to the region's culture. Now given the inventory amounts and 
the prices of all kinds of the mooncakes, together with the maximum total demand of the market, you are supposed to 
tell the maximum profit that can be made.



Note: partial inventory storage can be taken. The sample shows the following situation: given three kinds of mooncakes 
with inventory amounts being 180, 150, and 100 thousand tons, and the prices being 7.5, 7.2, and 4.5 billion yuans. If 
the market demand can be at most 200 thousand tons, the best we can do is to sell 150 thousand tons of the second kind 
of mooncake, and 50 thousand tons of the third kind. Hence the total profit is 7.2 + 4.5/2 = 9.45 (billion yuans).



## Input Specification: 

Each input file contains one test case. For each case, the first line contains 2 positive integers N (<=1000), the number 
of different kinds of mooncakes, and D (<=500 thousand tons), the maximum total demand of the market. Then the second line 
gives the positive inventory amounts (in thousand tons), and the third line gives the positive prices (in billion yuans) 
of N kinds of mooncakes. All the numbers in a line are separated by a space.



## Output Specification: 

For each test case, print the maximum profit (in billion yuans) in one line, accurate up to 2 decimal places.



## Sample Input:

3 200  
180 150 100  
7.5 7.2 4.5  

## Sample Output:

9.45  



## 题意：

输入月饼可能的种类，市场需求，以及每种月饼的可以生产的最大数量，和这种月饼生产最大数量能得到的利润。选择若干种月饼，
每种月饼的数量在其生产范围内，求最大的利润。

## 思路：

结构体存储一种月饼的最大产量，最大产量下的利润及单价(最大产量下的利润/最大产量)，结构体存储在数组中，对数组按单价非
递增排序，求出最大利润。


## 代码：

[1070. Mooncake (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1070.%20Mooncake%20(25)/1070.%20Mooncake%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <algorithm>

typedef struct node {
	double amount, price, unit;
}cake;

bool compare(cake a, cake b)
{
	return a.unit > b.unit;
}

int main()
{
	int n, demand;
	cin >> n >> demand;
	if (n == 0 || demand == 0) { cout << 0; return 0; }
	cake *cakes = new cake[n];
	for (int i = 0; i < n; i++) 
		cin >> cakes[i].amount;
	for (int i = 0; i < n; i++) {
		cin >> cakes[i].price;
		cakes[i].unit = cakes[i].price / cakes[i].amount;
	}
	sort(cakes, cakes + n, compare);
	double profit = 0;
	int index = 0;
	while (demand >= cakes[index].amount) {
		profit += cakes[index].price;
		demand -= cakes[index].amount;
		if (index == n - 1) goto end;
		index++;
	}
	profit += demand * cakes[index].unit;
	end:printf("%.2f\n", profit);
    return 0;
}
```