# 1013. Battle Over Cities (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1013)
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



It is vitally important to have all the cities connected by highways in a war. If a city is occupied by the enemy, 
all the highways from/toward that city are closed. We must know immediately if we need to repair any other highways 
to keep the rest of the cities connected. Given the map of cities which have all the remaining highways marked, you 
are supposed to tell the number of highways need to be repaired, quickly.

For example, if we have 3 cities and 2 highways connecting city1-city2 and city1-city3. Then if city1 is occupied by 
the enemy, we must have 1 highway repaired, that is the highway city2-city3.




## Input

Each input file contains one test case. Each case starts with a line containing 3 numbers N (<1000), M and K, 
which are the total number of cities, the number of remaining highways, and the number of cities to be checked, 
respectively. Then M lines follow, each describes a highway by 2 integers, which are the numbers of the cities 
the highway connects. The cities are numbered from 1 to N. Finally there is a line containing K numbers, which 
represent the cities we concern.




## Output

For each of the K cities, output in a line the number of highways need to be repaired if that city is lost.




## Sample Input
3 2 3  
1 2  
1 3  
1 2 3  

## Sample Output
1  
0  
0  



## 题意：

已知N个城市，M条路及每条路的两个顶点，当一个城市被敌方占领，所有从此城市发出及通往此城市的公路均关闭，此时必须修建公路以
连通所有剩余的城市，输入K个城市，对于每一个城市，求若该城市被敌方占领，需要修建多少条公路才能连通剩余所有城市

## 思路：

图的连通分量的数量减1即为需要修建的公路数量

建立用N\*N的邻接矩阵表示的图G（二维数组），顶点表示城市，边表示公路，若城市i、j之间有公路连通，则G[i][j] = 1，否则G[i][j] = -1，
对于K个城市中的每一个c，（c为被占领的城市）建立N\*N的图temp（二维数组），表示c被占领后的情况，对于每一对顶点<i，j\>，若i==c\|\|j==c，
即这条公路经过c，则temp[i][j] = -1，否则temp[i][j] = G[i][j]，此时计算temp的连通分量数量：

用collected数组存储每一个顶点是否被收录过，对于除c外的每个顶点v，若v未被收录，从v开始遍历图，遍历过程中与v连通的顶点均被收录，遍历结束后连通分量数量+1


## 代码：

[1013. Battle Over Cities(25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1013.%20Battle%20Over%20Cities%20(25)/1013.%20Battle%20Over%20Cities%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
#include <queue>
using namespace std;

void bfs(int **G, int n)
{
	int c;
	cin >> c;
	c--;
	int **temp = new int *[n]; //临时图，存储删除结点c后的图
	for (int i = 0; i < n; i++) {
		temp[i] = new int[n];
		for (int j = 0; j < n; j++) {
			if (i != c && j != c) //边的两个顶点均不是c
				temp[i][j] = G[i][j];
			else
				temp[i][j] = -1; //删除含有c的边
		}
	}
	int count = 0; //连通分量的个数（c除外）
	int *collected = new int[n];
	for (int i = 0; i < n; i++) collected[i] = 0;
	for (int i = 0; i < n; i++) { //每个顶点
		if (collected[i]) //已收录
			continue;
		queue<int> q; //BFS遍历图中与i连通的顶点
		collected[i] = 1;
		q.push(i);
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (int w = 0; w < n; w++)
				if (temp[v][w] == 1 && !collected[w]) {
					collected[w] = 1;
					q.push(w);
				}
		}
		if (i != c) //i不是被删除的顶点c
			count++;
	}//for N
	cout << count - 1 << "\n";
	for (int j = 0; j < n; j++)
		free(temp[j]);
	free(temp);
}

int main()
{
	int n, m, k;
	cin >> n >> m >> k;
	int **G = new int*[n]; //初始化图
	for (int i = 0; i < n; i++) {
		G[i] = new int[n];
		for (int j = 0; j < n; j++)
			G[i][j] = -1;
	}
	for (int i = 0; i < m; i++) {
		int c1, c2;
		cin >> c1 >> c2;
		c1--;
		c2--;
		G[c1][c2] = 1; //插入边<c1, c2>
		G[c2][c1] = 1; //插入边<c2, c1>
	}
	for (int i = 0; i < k; i++) {
		bfs(G, n);
	}
    return 0;
}
```
