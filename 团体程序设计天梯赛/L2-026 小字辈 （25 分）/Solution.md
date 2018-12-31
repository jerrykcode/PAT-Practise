# L2-026 小字辈 （25 分）
[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805055679479808)

> 作者: 陈越  
> 单位: 浙江大学  
> 时间限制: 400 ms  
> 内存限制: 64 MB  
> 代码长度限制: 16 KB  


本题给定一个庞大家族的家谱，要请你给出最小一辈的名单。

## 输入格式：

输入在第一行给出家族人口总数 N（不超过 100 000 的正整数） —— 简单起见，我们把家族成员从 1 到 N 编号。随后第二行给出 N 个编号，其中第 i 个编号对应第 i 位成员的父/母。家谱中辈分最高的老祖宗对应的父母编号为 -1。一行中的数字间以空格分隔。

## 输出格式：

首先输出最小的辈分（老祖宗的辈分为 1，以下逐级递增）。然后在第二行按递增顺序输出辈分最小的成员的编号。编号间以一个空格分隔，行首尾不得有多余空格。

## 输入样例：

> 9  
> 2 6 5 5 -1 5 6 4 7  


## 输出样例：
> 4  
> 1 9  

## 思路

BFS分层遍历，求出层数及最后一层的顶点

## 代码

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct TNode{
	int id;
	vector<int> children;
	TNode(int id) : id(id) {}
} *Tree;

int main()
{
	int n;
	cin >> n;
	Tree *list = new Tree[n];
	for (int i = 0; i < n; i++)
		list[i] = new TNode(i);
	int parent_id, root_id;
	for (int i = 0; i < n; i++) {
		cin >> parent_id;
		if (parent_id == -1) {
			root_id = i;
			continue;
		}
		parent_id--;
		list[parent_id]->children.push_back(i);	
	}
	Tree root = list[root_id];
	queue<Tree> q;
	q.push(root);
	Tree last = root, tail = root;
	int level = 0;
	vector<int> lastLevel;		
	while (!q.empty()) {
		Tree t = q.front();
		q.pop();
		lastLevel.push_back(t->id);
		for (int child_id : t->children) {				
			Tree tree = list[child_id];
			q.push(tree);
			last = tree;
		}
		if (t == tail) {
			level++;
			tail = last;
			if (!q.empty()) lastLevel.clear();
		}
	}
	cout << level << endl;
	for (auto it = lastLevel.begin(); it != lastLevel.end(); it++) {
		if (it != lastLevel.begin()) putchar(' ');
		cout << (*it + 1);
	}
	for (int i = 0; i < n; i++)
		if (list[i] != NULL)
			delete list[i];
	free(list);	
	return 0;
}

```