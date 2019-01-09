# L3-003 社交集群 （30 分）

[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805053141925888)

> 作者: 陈越  
> 单位: 浙江大学  
> 时间限制: 1200 ms  
> 内存限制: 64 MB  
> 代码长度限制: 16 KB  

当你在社交网络平台注册时，一般总是被要求填写你的个人兴趣爱好，以便找到具有相同兴趣爱好的潜在的朋友。一个“社交集群”是指部分兴趣爱好相同的人的集合。你需要找出所有的社交集群。

## 输入格式：

输入在第一行给出一个正整数 N（≤1000），为社交网络平台注册的所有用户的人数。于是这些人从 1 到 N 编号。随后 N 行，每行按以下格式给出一个人的兴趣爱好列表：

> Ki: hi[1] hi[2] ... hi[Ki]

其中Ki(>0)是兴趣爱好的个数，hi[j]是第j个兴趣爱好的编号，为区间 [1, 1000] 内的整数。

## 输出格式：

首先在一行中输出不同的社交集群的个数。随后第二行按非增序输出每个集群中的人数。数字间以一个空格分隔，行末不得有多余空格。

## 输入样例：

> 8  
> 3: 2 7 10  
> 1: 4  
> 2: 5 3  
> 1: 4  
> 1: 3  
> 1: 4  
> 4: 6 8 1 5  
> 1: 4  


## 输出样例：

> 3  
> 4 3 1 

## 思路

并查集。用数组标记每个hobby所属的人，初始为-1。输入一个人的爱好时，若该爱好已经有人有了，就将这两人所属的集合合并。

## 代码

[L3-003 社交集群 （30 分）.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L3-003%20%E7%A4%BE%E4%BA%A4%E9%9B%86%E7%BE%A4%20%EF%BC%8830%20%E5%88%86%EF%BC%89/L3-003%20%E7%A4%BE%E4%BA%A4%E9%9B%86%E7%BE%A4%20%EF%BC%8830%20%E5%88%86%EF%BC%89.cpp)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef short ID;
bool compare(ID a, ID b) {
	return a > b;
}
class USet {
public:
	USet(int n) : n(n) {
		_set = new ID[n];
		fill(_set, _set + n, -1);
	}
	~USet() { free(_set); }
	
	void unionSets(ID a, ID b);
	void getSets(vector<ID>& sets);

private:
	ID findRoot(ID a);

	int n;
	ID *_set;
};

ID USet::findRoot(ID a) {
	if (_set[(int)a] < 0) return a;
	return _set[(int)a] = findRoot(_set[(int)a]);
}

void USet::unionSets(ID a, ID b) {
	ID root_a = findRoot(a);
	ID root_b = findRoot(b);
	if (root_a == root_b) return;
	if (_set[root_a] < _set[root_b]) {
		_set[root_a] += _set[root_b];
		_set[root_b] = root_a;
	}
	else {
		_set[root_b] += _set[root_a];
		_set[root_a] = root_b;
	}
}

void USet::getSets(vector<ID>& sets) {
	for (int i = 0; i < n; i++)
		if (_set[i] < 0) {
			sets.push_back(_set[i] * (-1));		
		}	
	sort(sets.begin(), sets.end(), compare);
}

int main() {
	int n;
	scanf("%d", &n);
	USet uset(n);
	ID hobbies[1000];
	for (int i = 0; i < 1000; i++) hobbies[i] = -1;
	int k, hobby;
	for (int i = 0; i < n; i++) {
		scanf("%d:", &k);	
		for (int j = 0; j < k; j++) {
			scanf("%d", &hobby);
			hobby--;
			if (hobbies[hobby] == -1)
				hobbies[hobby] = (ID)i;
			else {
				uset.unionSets(hobbies[hobby], (ID)i);
			}
		}
	}
	vector<ID> sets;
	uset.getSets(sets);
	printf("%d\n", sets.size());
	for (auto it = sets.begin(); it != sets.end(); it++) {
		if (it != sets.begin()) putchar(' ');
		printf("%hd", *it);
	}
	sets.clear();
	vector<ID>().swap(sets);
	return 0;
}

```

