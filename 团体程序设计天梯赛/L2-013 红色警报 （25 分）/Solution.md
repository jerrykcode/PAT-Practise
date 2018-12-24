# L2-013 红色警报 （25 分）

[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805063963230208)

> 作者: 陈越  
> 单位: 浙江大学  
> 时间限制: 400 ms  
> 内存限制: 64 MB  
> 代码长度限制: 16 KB  

战争中保持各个城市间的连通性非常重要。本题要求你编写一个报警程序，当失去一个城市导致国家被分裂为多个无法连通的区域时，就发出红色警报。注意：若该国本来就不完全连通，是分裂的k个区域，而失去一个城市并不改变其他城市之间的连通性，则不要发出警报。

## 输入格式：

输入在第一行给出两个整数N（0 < N ≤ 500）和M（≤ 5000），分别为城市个数（于是默认城市从0到N-1编号）和连接两城市的通路条数。随后M行，每行给出一条通路所连接的两个城市的编号，其间以1个空格分隔。在城市信息之后给出被攻占的信息，即一个正整数K和随后的K个被攻占的城市的编号。

*注意：输入保证给出的被攻占的城市编号都是合法的且无重复，但并不保证给出的通路没有重复。*

## 输出格式：

对每个被攻占的城市，如果它会改变整个国家的连通性，则输出Red Alert: City k is lost!，其中k是该城市的编号；否则只输出City k is lost.即可。如果该国失去了最后一个城市，则增加一行输出Game Over.。

## 输入样例：

> 5 4  
> 0 1  
> 1 3  
> 3 0  
> 0 4  
> 5  
> 1 2 0 4 3  


## 输出样例：

> City 1 is lost.  
> City 2 is lost.  
> Red Alert: City 0 is lost!  
> City 4 is lost.  
> City 3 is lost.  
> Game Over.  

## 思路

先求图的连通分量，对每个连通分量编号，用数组记录每个顶点所属的连通分量，及每个连通分量的顶点数量。对于每个被攻占的
城市，删除这个城市的所有边，然后再遍历该城市所属的连通分量，若顶点数量为原连通分量的顶点数量-1，则该连通分量还是连
通的；否则该连通分量因删除一个顶点而被分成了多个连通分量，此时需要警报，在这种情况下，需要遍历新产生的连通分量，记
录它们的顶点数量。

## 代码

[L2-013 红色警报 （25 分）.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L2-013%20%E7%BA%A2%E8%89%B2%E8%AD%A6%E6%8A%A5%20%EF%BC%8825%20%E5%88%86%EF%BC%89/L2-013%20%E7%BA%A2%E8%89%B2%E8%AD%A6%E6%8A%A5%20%EF%BC%8825%20%E5%88%86%EF%BC%89.cpp)

```cpp
#include <iostream>
#include <vector>
using namespace std;

int n; //城市数量，即图的顶点数量
bool **graph; //以城市为顶点的图，graph[v][w]为true若v,w之间存在边
bool *collected; //collected[v]为true，若v被遍历
short *componentId; //componentId[v]表示顶点v所属的连通分量的id
vector<short> idNum; //idNum[i]表示id为i的连通分量的顶点数量

//从src开始dfs深搜遍历第id个连通分量，返回遍历的连通分量内的顶点数量
short dfs(int src, short id) {
	collected[src] = true;
	componentId[src] = id;
	short size = 1;
	for (int v = 0; v < n; v++)
		if (!collected[v] && graph[src][v]) {
			size += dfs(v, id);
		}
	return size;
}

int main()
{
	scanf("%d", &n);
	//初始化
	graph = new bool *[n];
	for (int i = 0; i < n; i++) {
		graph[i] = new bool[n];
		fill(graph[i], graph[i] + n, false);
	}
	collected = new bool[n];
	fill(collected, collected + n, false);
	componentId = new short[n];
	//根据输入插入边
	int m, c1, c2;
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &c1, &c2);
		graph[c1][c2] = graph[c2][c1] = true;
	}
	//求连通分量
	short id = 0;
	for (int v = 0; v < n; v++)
		if (!collected[v]) idNum.push_back(dfs(v, id++)); //记录每个连通分量的顶点数量
	//
	int k;
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		int v;
		scanf("%d", &v); //城市v被攻占
		int vid = componentId[v]; //被攻占城市所属的连通分量
		componentId[v] = -1; //删除该城市
		for (int w = 0; w < n; w++)
			graph[v][w] = graph[w][v] = false; //删除边
		bool isRedAlert = false; //是否需要警报
		if (idNum[vid] == 1) //若该城市单独为一个连通分量，则不需警报
			idNum[vid] = 0;
		else { //该连通分量不止1个城市
			//寻找一个相同连通分量内的城市
			//并把该连通分量的顶点的collected设为false
			int sameIdCity = -1;
			for (int w = 0; w < n; w++)
				if (componentId[w] == vid) {
					collected[w] = false;
					if (sameIdCity == -1) sameIdCity = w;
				}
			//从相同连通分量内的一个城市开始遍历,若得到的顶点数量等于原来该连通分量的顶点数量-1，
			//则该连通分量除删除v外没有改变；否则该连通分量因删除v而被分成了多个连通分量
			short size = dfs(sameIdCity, vid);
			if (size == idNum[vid] - 1) 
				idNum[vid]--;
			else { //size < idNum[vid] - 1				
				if (i != k - 1) { 
					//遍历原连通分量分割出的新连通分量
					idNum[vid] = size;
					while (1) {
						sameIdCity = -1;
						for (int w = 0; w < n; w++) //寻找在原连通分量中，且没有被之前遍历到的顶点
							if (!collected[w] && componentId[w] == vid) {
								sameIdCity = w;
								break;
							}
						if (sameIdCity == -1) break; //所有顶点均被遍历到，新的连通分量已记录，break
						idNum.push_back(dfs(sameIdCity, id++)); //记录新的连通分量的顶点数量
					}
				}
				printf("Red Alert: "); //需要警报
				isRedAlert = true;
			}
		}
		printf("City %d is lost", v);
		printf(isRedAlert ? "!" : ".");
		printf("\n");
	}
	if (k == n) printf("Game Over."); //若k==n，则所有城市均被攻占
	for (int i = 0; i < n; i++)
		free(graph[i]);
	free(graph);
	free(collected);
	free(componentId);
	idNum.clear();
	vector<short>().swap(idNum);
	return 0;
}
```
