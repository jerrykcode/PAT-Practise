#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define ID_INF 10000 //id是4位数，最大的id为9999
typedef short ID; //用short存储id
typedef struct Node { //图顶点
	ID id; //顶点表示的人的id
	vector<ID> neighbors; //相邻的顶点的id
	double nHouse; //房屋数
	double area; //面积
	Node(ID id) : id(id), nHouse(0.0), area(0.0) {}
} *PNode;
//数组存储图顶点指针
PNode list[ID_INF] = { NULL };

struct Family {
	ID min_id; //最小id
	int size; //人数
	double average_nHouse; //平均房屋数
	double average_area; //平均面积
	Family(ID min_id, int size, double nHouse, double area) : min_id(min_id), size(size), average_nHouse(nHouse), average_area(area) {}
};

bool compare(Family a, Family b) {
	return a.average_area != b.average_area ? a.average_area > b.average_area : a.min_id < b.min_id;
}

void bfs(vector<Family>& families) {
	bool collected[ID_INF] = { false };
	queue<ID> q;
	for (ID id = 0; id < ID_INF; id++) { //遍历所有可能的id
		if (list[(int)id] == NULL) continue; //该id不存在
		if (collected[(int)id]) continue; //该id已收录
		//BFS求连通分量
		q.push(id);
		collected[(int)id] = true;
		ID min_id = id; //连通分量中的最小id
		int size = 1; //连通分量的顶点数量，已收录id，故size为1
		double nHouse = list[(int)id]->nHouse, area = list[(int)id]->area; //连通分量的总房屋数，总面积
		while (!q.empty()) {
			ID v = q.front();
			q.pop();
			for (ID w : list[(int)v]->neighbors) //遍历邻接点 
				if (!collected[(int)w]) { //若未被收录	
					if (w < min_id) min_id = w;
					size++;
					collected[(int)w] = true; //收录w，若v的邻接点有重复，则再次出现w时，w已收录，不会重复计数
					q.push(w);
					nHouse += list[(int)w]->nHouse;
					area += list[(int)w]->area;
				}
		}
		//将连通分量的信息存储在Family结构体中，并把结构体存入families中
		families.push_back(Family(min_id, size, nHouse / size, area / size));
	}
	//排序
	sort(families.begin(), families.end(), compare);
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		ID id, father_id, mother_id, child_id;
		int k;
		double nHouse, area;
		scanf("%hd %hd %hd %d", &id, &father_id, &mother_id, &k);
		list[(int)id] = new Node(id);
		//父母及孩子作为相邻的顶点
		if (father_id != -1) list[(int)id]->neighbors.push_back(father_id);
		if (mother_id != -1) list[(int)id]->neighbors.push_back(mother_id);
		for (int j = 0; j < k; j++) {
			scanf("%hd", &child_id);
			list[(int)id]->neighbors.push_back(child_id);
		}
		for (ID neighbor_id : list[(int)id]->neighbors) {
			//反向边。之后若输入neighbor_id的信息，则neighbor_id的邻接点中会重复出现id，BFS遍历时需注意
			if (list[(int)neighbor_id] == NULL) list[(int)neighbor_id] = new Node(neighbor_id);
			list[(int)neighbor_id]->neighbors.push_back(id);
		}
		scanf("%lf %lf", &nHouse, &area);
		list[(int)id]->nHouse = nHouse;
		list[(int)id]->area = area;
	}
	vector<Family> families;
	//BFS求连通分量，每个连通分量为一个Family结构，存储在families中
	bfs(families);
	//输出
	printf("%d\n", families.size());
	for (auto it = families.begin(); it != families.end(); it++)
		printf("%04hd %d %.3f %.3f\n", it->min_id, it->size, it->average_nHouse, it->average_area);
	//释放内存
	vector<Family>().swap(families);
	for (int i = 0; i < ID_INF; i++)
		if (list[i] != NULL) {
			delete list[i];
			list[i] = NULL;
		}
	return 0;
}
