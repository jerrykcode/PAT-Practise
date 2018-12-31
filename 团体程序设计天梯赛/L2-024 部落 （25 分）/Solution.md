# L2-024 部落 （25 分）
[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805056736444416)

> 作者: 陈越  
> 单位: 浙江大学  
> 时间限制: 150 ms  
> 内存限制: 64 MB  
> 代码长度限制: 16 KB  

在一个社区里，每个人都有自己的小圈子，还可能同时属于很多不同的朋友圈。我们认为朋友的朋友都算在一个部落里，于是要请你统计一下，在一个给定社区中，到底有多少个互不相交的部落？并且检查任意两个人是否属于同一个部落。

## 输入格式：

输入在第一行给出一个正整数N（≤10^4），是已知小圈子的个数。随后N行，每行按下列格式给出一个小圈子里的人：

`K P[1] P[2] ... P[K]`

其中K是小圈子里的人数，P[i]（i=1, ... ,K）是小圈子里每个人的编号。这里所有人的编号从1开始连续编号，最大编号不会超过10^4。

之后一行给出一个非负整数Q（≤10^4），是查询次数。随后Q行，每行给出一对被查询的人的编号。

## 输出格式：

首先在一行中输出这个社区的总人数、以及互不相交的部落的个数。随后对每一次查询，如果他们属于同一个部落，则在一行中输出Y，否则输出N。

## 输入样例：

> 4  
> 3 10 1 2  
> 2 3 4  
> 4 1 5 7 8  
> 3 9 6 4  
> 2  
> 10 5  
> 3 7  


## 输出样例：

> 10 2  
> Y  
> N  

## 思路

并查集存储圈子。输入时记录每个人所属的圈子，若此人之前不属于任何一个圈子，则人数增1，否则当前圈子与此人之前所属的圈子合并。
对于每一次查询，判断两人是否属于同一个圈子，若圈子不同，判断两个圈子是否在并查集中属于同一个集合。

## 代码

```cpp

#include <iostream>
using namespace std;

typedef int Set;
class USet {
public:
	USet(int n) : n(n) {
		s = new Set[n];
		fill(s, s + n, -1);
	}
	~USet() { free(s); }
	bool isSameSet(Set a, Set b);
	void unionSets(Set a, Set b);
	int numSets();
private:
	Set findRoot(Set a);
	int n;
	Set *s;
};

Set USet::findRoot(Set a) {
	if (s[a] < 0) return a;
	return s[a] = findRoot(s[a]);
}

bool USet::isSameSet(Set a, Set b) {
	return findRoot(a) == findRoot(b);
}

void USet::unionSets(Set a, Set b) {
	Set a_root = findRoot(a);
	Set b_root = findRoot(b);
	if (a_root == b_root) return;
	if (s[a_root] < s[b_root]) {
		s[a_root] += s[b_root];
		s[b_root] = a_root;
	}
	else {
		s[b_root] += s[a_root];
		s[a_root] = b_root;
	}
}

int USet::numSets() {
	int size = 0;
	for (int i = 0; i < n; i++)
		if (s[i] < 0) size++;
	return size;
}

int main()
{
	int n;
	cin >> n;
	USet uset(n);	
	int *circle = new int[10001];
	fill(circle, circle + 10001, -1);
	int num = 0;
	int k, id;
	for (int i = 0; i < n; i++) {
		cin >> k;
		for (int j = 0; j < k; j++) {
			cin >> id;
			if (circle[id] == -1) {
				circle[id] = i;
				num++;
			}
			else
				uset.unionSets(i, circle[id]);
		}	
	}
	cout << num << " " << uset.numSets() << endl;
	int q, id1, id2;
	cin >> q;
	for (int i = 0; i < q; i++) {
		cin >> id1 >> id2;
		cout << ((circle[id1] == circle[id2] || uset.isSameSet(circle[id1], circle[id2])) ? "Y" : "N") << endl;
	}
	free(circle);
	return 0;
}

```
