# L3-008 喊山 （30 分）

[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805050709229568)

> 作者: 陈越
单位: 浙江大学
时间限制: 150 ms
内存限制: 64 MB
代码长度限制: 16 KB


喊山，是人双手围在嘴边成喇叭状，对着远方高山发出“喂—喂喂—喂喂喂……”的呼唤。呼唤声通过空气的传递，回荡于深谷之间，传送到人们耳中，发出约定俗成的“讯号”，达到声讯传递交流的目的。原来它是彝族先民用来求援呼救的“讯号”，慢慢地人们在生活实践中发现了它的实用价值，便把它作为一种交流工具世代传袭使用。（图文摘自：http://news.xrxxw.com/newsshow-8018.html）



一个山头呼喊的声音可以被临近的山头同时听到。题目假设每个山头最多有两个能听到它的临近山头。给定任意一个发出原始信号的山头，本题请你找出这个信号最远能传达到的地方。

## 输入格式：

输入第一行给出3个正整数n、m和k，其中n（≤10000）是总的山头数（于是假设每个山头从1到n编号）。接下来的m行，每行给出2个不超过n的正整数，数字间用空格分开，分别代表可以听到彼此的两个山头的编号。这里保证每一对山头只被输入一次，不会有重复的关系输入。最后一行给出k（≤10）个不超过n的正整数，数字间用空格分开，代表需要查询的山头的编号。

## 输出格式：

依次对于输入中的每个被查询的山头，在一行中输出其发出的呼喊能够连锁传达到的最远的那个山头。注意：被输出的首先必须是被查询的个山头能连锁传到的。若这样的山头不只一个，则输出编号最小的那个。若此山头的呼喊无法传到任何其他山头，则输出0。

## 输入样例：
7 5 4  
1 2  
2 3  
3 1  
4 5  
5 6  
1 4 5 7  


## 输出样例：

2  
6  
4  
0  

## 思路：

BFS广度优先搜索

山头为顶点，可以彼此听到的两个山头之间有一条边。用邻接表表示图，以查询的山头为源，BFS分层遍历，求最后一层(最远能传到的一层)中最小编号的山头。

## 代码

[L3-008 喊山 （30 分）.cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L3-008%20%E5%96%8A%E5%B1%B1%20%EF%BC%8830%20%E5%88%86%EF%BC%89/L3-008%20%E5%96%8A%E5%B1%B1%20%EF%BC%8830%20%E5%88%86%EF%BC%89.cpp)

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> *Graph;

int bfs(Graph graph, int src, int n) {
	queue<int>q;
	int last = src, tail = src;
	bool *collected = new bool[n];
	fill(collected, collected + n, false);
	q.push(src);
	collected[src] = true;
	int minV = -1;
	bool newLevel = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int w : graph[v]) {
			if (!collected[w]) {
				collected[w] = true;
				q.push(w);
				if (newLevel || w < minV) {
					if (newLevel) newLevel = false;
					minV = w;
				}
				last = w;
			}
		}
		if (v == tail) {
			tail = last;
			newLevel = true;
		}
	}
	free(collected);
	return minV;
}

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	Graph graph = new vector<int>[n];
	for (int i = 0; i < m; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		v1--; v2--;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	for (int i = 0; i < k; i++) {
		int v;
		cin >> v;
		int minV = bfs(graph, v - 1, n);
		cout << (minV + 1) << endl;
	}
	return 0;
}

```

