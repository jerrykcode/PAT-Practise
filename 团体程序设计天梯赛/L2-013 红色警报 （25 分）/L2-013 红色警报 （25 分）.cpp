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