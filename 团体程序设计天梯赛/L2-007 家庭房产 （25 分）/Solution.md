# L2-007 家庭房产 （25 分）

[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805068539215872)

> 作者: 陈越  
> 单位: 浙江大学  
> 时间限制: 400 ms  
> 内存限制: 64 MB  
> 代码长度限制: 16 KB  


给定每个人的家庭成员和其自己名下的房产，请你统计出每个家庭的人口数、人均房产面积及房产套数。

## 输入格式：

输入第一行给出一个正整数N（≤1000），随后N行，每行按下列格式给出一个人的房产：

> 编号 父 母 k 孩子1 ... 孩子k 房产套数 总面积


其中编号是每个人独有的一个4位数的编号；父和母分别是该编号对应的这个人的父母的编号（如果已经过世，则显示-1）；k（0≤k≤5）是该人的子女的个数；孩子i是其子女的编号。

## 输出格式：

首先在第一行输出家庭个数（所有有亲属关系的人都属于同一个家庭）。随后按下列格式输出每个家庭的信息：
家庭成员的最小编号 家庭人口数 人均房产套数 人均房产面积


其中人均值要求保留小数点后3位。家庭信息首先按人均面积降序输出，若有并列，则按成员编号的升序输出。

##　输入样例：

> 10  
> 6666 5551 5552 1 7777 1 100  
> 1234 5678 9012 1 0002 2 300  
> 8888 -1 -1 0 1 1000  
> 2468 0001 0004 1 2222 1 500  
> 7777 6666 -1 0 2 300  
> 3721 -1 -1 1 2333 2 150  
> 9012 -1 -1 3 1236 1235 1234 1 100  
> 1235 5678 9012 0 1 50  
> 2222 1236 2468 2 6661 6662 1 300  
> 2333 -1 3721 3 6661 6662 6663 1 100  

## 输出样例：

> 3  
> 8888 1 1.000 1000.000  
> 0001 15 0.600 100.000  
> 5551 4 0.750 100.000  


## 思路1 求图的连通分量

用图顶点表示每个人，其父母及孩子是相邻的顶点。BFS求连通分量。


## 代码1

[L2-007 家庭房产 （25 分）_BFS.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L2-007%20%E5%AE%B6%E5%BA%AD%E6%88%BF%E4%BA%A7%20%EF%BC%8825%20%E5%88%86%EF%BC%89/L2-007%20%E5%AE%B6%E5%BA%AD%E6%88%BF%E4%BA%A7%20%EF%BC%8825%20%E5%88%86%EF%BC%89_BFS.cpp)

```cpp

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
PNode list[ID_INF] = {NULL};

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
	bool collected[ID_INF] = {false};
	queue<ID> q;
	for (ID id = 0; id < ID_INF; id++) { //遍历所有可能的id
		if (list[(int)id] == NULL) continue; //该id不存在
		if (collected[(int)id]) continue; //该id已收录
		//BFS求连通分量
		q.push(id);
		collected[(int)id] = true;
		ID min_id = id; //连通分量中的最小id
		int size= 1; //连通分量的顶点数量，已收录id，故size为1
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
		families.push_back(Family(min_id, size, nHouse/size, area/size));
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

```

## 思路2 并查集

并查集封装在一个类中，用_set数组存储SetData结构体。SetData结构体如下：

```cpp
struct SetData { 
	ID parent;
	PFamily pFamily;
};
```

_set[id].parent即id的父结点在数组中的下标，为负表示id为根结点，负数的绝对值表示集合的大小。
_set[id].pFamily为Family结构体的指针，若id不是根结点则为NULL，若id是根结点，则指向一个存储
该集合信息的结构体。
合并集合时，将小的集合合并到大的集合上；_set数组中相应的pFamily指向的信息需合并，被合并的
集合，删除其原来根结点的pFamily指向的结构体

输入时，将输入id与其父母及孩子的集合合并。对它们所在的集合，增加输入的房屋数和面积

_set数组中pFamily非NULL的元素数量即集合数量。输出集合数量，对_set排序，pFamily非NUll的排在
前，pFamily均非NULL，则按pFamily指向的信息排序。输出排序后pFamily非NULL的指向的信息。

## 代码2

[L2-007 家庭房产 （25 分）_并查集.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L2-007%20%E5%AE%B6%E5%BA%AD%E6%88%BF%E4%BA%A7%20%EF%BC%8825%20%E5%88%86%EF%BC%89/L2-007%20%E5%AE%B6%E5%BA%AD%E6%88%BF%E4%BA%A7%20%EF%BC%8825%20%E5%88%86%EF%BC%89_%E5%B9%B6%E6%9F%A5%E9%9B%86.cpp)

```cpp


#include <iostream>
#include <algorithm>
using namespace std;

#define MIN(a, b) (a < b ? a : b)
#define ID_INF 10000
typedef short ID;
typedef struct Family {
	ID min_id;
	short size;
	double nHouse;
	double area;
	Family() {}
	Family(ID min_id, double nHouse, double area) : min_id(min_id), nHouse(nHouse), area(area) {}
} *PFamily;

struct SetData {
	ID parent;
	PFamily pFamily;
};
bool compare(SetData a, SetData b) {
	if (a.pFamily != NULL && b.pFamily != NULL) {
		return (a.pFamily->area != b.pFamily->area ? (a.pFamily->area > b.pFamily->area) : (a.pFamily->min_id < b.pFamily->min_id));
	}
	else if (a.pFamily != NULL || b.pFamily != NULL) { //非NULL的排在前
		return a.pFamily != NULL;		
	}	
	else return a.parent < b.parent; //均为NULL时并列即可，a.parent < b.parent可以改为任意判断句
}

class USet {
public:
	USet() {
		_set = new SetData[ID_INF];
		for (int i = 0; i < ID_INF; i++) {
			_set[i].parent = -1;
			_set[i].pFamily = NULL;
		}
	}
	~USet() { 
		for (int i = 0; i < ID_INF; i++) 
			if (_set[i].pFamily != NULL) {
				delete _set[i].pFamily;
				_set[i].pFamily = NULL;
			}
		free(_set);
	}

	void unionSet(ID a, ID b); //合并a，b
	void add(ID a, double nHouse, double area); //对a所属的集合增加nHouse, area
	int size(); //集合数量
	void printSetData(); //输出
private:
	ID findRoot(ID a);
	SetData *_set;
};

ID USet::findRoot(ID a) {
	if (_set[a].parent < 0) return a;
	return _set[a].parent = findRoot(_set[a].parent);	
}

void USet::unionSet(ID a, ID b) {
	if (a == -1 || b == -1) return;
	ID root_a = findRoot(a);
	ID root_b = findRoot(b);
	if (root_a == root_b) return;
	ID root_x, root_y;
	//小集合并到大集合上
	if (_set[root_a].parent < _set[root_b].parent) {
		root_x = root_a;
		root_y = root_b;
	}
	else {
		root_x = root_b;
		root_y = root_a;
	}
	_set[root_x].parent += _set[root_y].parent;
	_set[root_y].parent = root_x;
	if (_set[root_x].pFamily == NULL)
		_set[root_x].pFamily = new Family(root_x, 0.0, 0.0);
	if (_set[root_y].pFamily == NULL)
		_set[root_y].pFamily = new Family(root_y, 0.0, 0.0);
	if (_set[root_x].pFamily->min_id > _set[root_y].pFamily->min_id)
		_set[root_x].pFamily->min_id = _set[root_y].pFamily->min_id;
	_set[root_x].pFamily->nHouse += _set[root_y].pFamily->nHouse;
	_set[root_x].pFamily->area += _set[root_y].pFamily->area;
	delete _set[root_y].pFamily;
	_set[root_y].pFamily = NULL;
}

void USet::add(ID a, double nHouse, double area) {
	ID root = findRoot(a);
	if (_set[root].pFamily == NULL)
		_set[root].pFamily = new Family(root, 0.0, 0.0);
	_set[root].pFamily->nHouse += nHouse;
	_set[root].pFamily->area += area;
}

int USet::size() {
	int _size = 0;
	for (int i = 0; i < ID_INF; i++)
		if (_set[i].pFamily != NULL)
			_size++;
	return _size;
}

void USet::printSetData() {
	for (ID id = 0; id < ID_INF; id++) {
		if (_set[id].pFamily == NULL) continue;
		int size = _set[id].parent * (-1);
		_set[id].pFamily->nHouse /= size; //平均值
		_set[id].pFamily->area /= size;
	}
	sort(_set, _set + ID_INF, compare);
	for (ID id = 0; id < ID_INF; id++) {
		if (_set[(int)id].pFamily == NULL)continue;
		int size = _set[id].parent * (-1);
		printf("%04hd %d %.3f %.3f\n", _set[id].pFamily->min_id, size, _set[id].pFamily->nHouse, _set[id].pFamily->area);
	}	
}


int main()
{
	USet uset;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		ID id, father_id, mother_id, child_id;
		scanf("%hd %hd %hd", &id, &father_id, &mother_id);	
		uset.unionSet(id, father_id);
		uset.unionSet(id, mother_id);
		int k;
		scanf("%d", &k);
		for (int i = 0; i < k; i++) {
			scanf("%hd", &child_id);
			uset.unionSet(id, child_id);
		}
		double nHouse, area;
		scanf("%lf %lf", &nHouse, &area);
		uset.add(id, nHouse, area);
	}
	printf("%d\n", uset.size());
	uset.printSetData();
	return 0;
}
```

