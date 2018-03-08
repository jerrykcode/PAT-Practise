# 1033. To Fill or Not to Fill (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1033)

* 时间限制 100 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 ZHANG, Guochuan



With highways available, driving a car from Hangzhou to any other city is easy. But since the tank capacity of a car is limited, we have to find gas stations on the way from time to time. Different gas station may give different price. You are asked to carefully design the cheapest route to go.

## Input Specification: 

Each input file contains one test case. For each case, the first line contains 4 positive numbers: Cmax (<= 100), the maximum capacity of the tank; D (<=30000), the distance between Hangzhou and the destination city; Davg (<=20), the average distance per unit gas that the car can run; and N (<= 500), the total number of gas stations. Then N lines follow, each contains a pair of non-negative numbers: Pi, the unit gas price, and Di (<=D), the distance between this station and Hangzhou, for i=1,...N. All the numbers in a line are separated by a space.

## Output Specification: 

For each test case, print the cheapest price in a line, accurate up to 2 decimal places. It is assumed that the tank is empty at the beginning. If it is impossible to reach the destination, print "The maximum travel distance = X" where X is the maximum possible distance the car can run, accurate up to 2 decimal places.
## Sample Input 1:
50 1300 12 8  
6.00 1250  
7.00 600  
7.00 150  
7.10 0  
7.20 200  
7.50 400  
7.30 1000  
6.85 300  

## Sample Output 1:

749.17

## Sample Input 2:

50 1300 12 2  
7.10 0  
7.00 600  

## Sample Output 2:

The maximum travel distance = 1200.00  

## 题意：

已知杭州到某城市的距离，路上的加油站数量，汽车油箱容积，每单位汽油能行驶的距离。输入每个加油站与杭州的距离及该加油站每单位油的价格。初始时汽车没有油，求从杭州到此城市所需的最低油费，若无法到达，则输出最远可行驶的距离。

## 思路：

用结构体存储加油站的距离与油价，结构体数组存储所有加油站，终点也作为一个油价为0的加油站存储在数组中，按距离非递减排序，若第0个加油站的距离不是0，则无法到达，最远行驶距离为0。否则在此加油。在这里加满油能行驶的距离是当前最大距离maxDist，若下一个加油站的距离大于maxDist，则不能到达终点，否则若在maxDist距离内有比当前加油站的油价低的，就正好加到那个更低的去加。若没有更低的则加满，然后到maxDist距离内最低的去加。用availableDist表示当前能够走到的距离。


## 代码：

[1033. To Fill or Not to Fill (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1033.%20To%20Fill%20or%20Not%20to%20Fill%20(25)/1033.%20To%20Fill%20or%20Not%20to%20Fill%20(25).cpp)
```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <algorithm>

struct node {
	double price, dist;
};

bool compare(node a, node b)
{
	return a.dist < b.dist;
}

int main()
{
	double cmax, d, davg;
	int n;
	cin >> cmax >> d >> davg >> n;
	node *stations = new node[n + 1];
	for (int i = 0; i < n; i++) 
		cin >> stations[i].price >> stations[i].dist;
	stations[n] = {0.0, d};
	sort(stations, stations + n + 1, compare);
	if (stations[0].dist != 0) {
		printf("The maximum travel distance = 0.00\n");
		return 0;
	}
	double availableDist = 0, totalPrice = 0;
	int currentStation = 0;
	while (1) {
		double maxDist = stations[currentStation].dist + cmax * davg;
		if (currentStation + 1 < n + 1 && stations[currentStation + 1].dist > maxDist) {
			printf("The maximum travel distance = %.2f\n", maxDist);
			return 0;
		}
		int min = currentStation + 1, flag = 0;
		for (int i = currentStation + 1; i < n; i++) {
			if (stations[i].dist > maxDist) break;
			if (stations[i].price < stations[currentStation].price) {
				min = i;
				flag = 1;
				break;
			}
			if (stations[i].price < stations[min].price) 
				min = i;
		}
		if (flag) {
			totalPrice += (stations[min].dist - availableDist) * stations[currentStation].price/davg;
			availableDist = stations[min].dist;
			currentStation = min;
		}
		else {
			if (maxDist >= d) {
				totalPrice += (d - availableDist)*stations[currentStation].price/davg;
				break;
			}
			totalPrice += (maxDist - availableDist)*stations[currentStation].price/davg;
			availableDist = maxDist;
			currentStation = min;
		}
	}//while
	printf("%.2f\n", totalPrice);
    return 0;
}
```