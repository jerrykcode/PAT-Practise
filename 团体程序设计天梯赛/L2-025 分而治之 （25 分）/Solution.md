L2-025 分而治之 （25 分）

[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805056195379200)

> 作者: 陈越  
> 单位: 浙江大学  
> 时间限制: 600 ms  
> 内存限制: 64 MB  
> 代码长度限制: 16 KB  

分而治之，各个击破是兵家常用的策略之一。在战争中，我们希望首先攻下敌方的部分城市，使其剩余的城市变成孤立无援，然后再分头各个击破。为此参谋部提供了若干打击方案。本题就请你编写程序，判断每个方案的可行性。

## 输入格式：

输入在第一行给出两个正整数 N 和 M（均不超过10 000），分别为敌方城市个数（于是默认城市从 1 到 N 编号）和连接两城市的通路条数。随后 M 行，每行给出一条通路所连接的两个城市的编号，其间以一个空格分隔。在城市信息之后给出参谋部的系列方案，即一个正整数 K （≤ 100）和随后的 K 行方案，每行按以下格式给出：

> Np v[1] v[2] ... v[Np]


其中 Np 是该方案中计划攻下的城市数量，后面的系列 v[i] 是计划攻下的城市编号。

## 输出格式：

对每一套方案，如果可行就输出YES，否则输出NO。

## 输入样例：

> 10 11  
> 8 7  
> 6 8  
> 4 5  
> 8 4  
> 8 1  
> 1 2  
> 1 4 
> 9 8  
> 9 1  
> 1 10  
> 2 4  
> 5  
> 4 10 3 8 4  
> 6 6 1 7 5 4 9  
> 3 1 8 4  
> 2 2 8  
> 7 9 8 7 6 5 4 2  


## 输出样例：

NO  
YES  
YES  
NO  
NO  

## 思路

邻接表表示的图存储城市。对每一个方案，标记被攻下的城市，遍历所有未被攻下的城市，若它的邻接点中还存在未被攻下的城市，则不可行。

## 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector<int> *graph = new vector<int>[n];
	for (int i = 0; i < m; i++) {
		int city1, city2;
		scanf("%d %d", &city1, &city2);
		city1--;
		city2--;
		graph[city1].push_back(city2);
		graph[city2].push_back(city1);
	}
	int k, nv, destroyedCity;
	scanf("%d", &k);
	bool *hasDestroyed = new bool[n];
	for (int i = 0; i < k; i++) {
		fill(hasDestroyed, hasDestroyed + n, false);
		scanf("%d", &nv);
		for (int j = 0; j < nv; j++) {
			scanf("%d", &destroyedCity);
			destroyedCity--;
			hasDestroyed[destroyedCity] = true;
		}
		bool flag = true;	
		for (int city = 0; city < n; city++) {
			if (hasDestroyed[city]) continue;
			if (graph[city].empty()) continue;
			for (int neighborCity : graph[city])
				if (!hasDestroyed[neighborCity]) {
					flag = false;
					break;
				}
			if (flag == false) break;
		}
		cout << (flag ? "YES" : "NO") << endl;
	}
	free(hasDestroyed);
	for (int i = 0; i < n; i++) {
		graph[i].clear();
		vector<int>().swap(graph[i]);
	}
	//free(graph); //pat提交runtime error 
	return 0;
}

```

