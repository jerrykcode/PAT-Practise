# 1106. Lowest Price in Supply Chain (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1106)


* 时间限制 200 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 作者 CHEN, Yue



A supply chain is a network of *`retailers（零售商）`*, *`distributors（经销商）`*, and *`suppliers（供应商）`*-- everyone involved in moving a product from supplier to customer.

Starting from one root supplier, everyone on the chain buys products from one's supplier in a price P and sell or distribute them in a price that is r% higher than P. Only the retailers will face the customers. It is assumed that each member in the supply chain has exactly one supplier except the root supplier, and there is no supply cycle.

Now given a supply chain, you are supposed to tell the lowest price a customer can expect from some retailers.

## Input Specification: 

Each input file contains one test case. For each case, The first line contains three positive numbers: N (<=105), the total number of the members in the supply chain (and hence their ID's are numbered from 0 to N-1, and the root supplier's ID is 0); P, the price given by the root supplier; and r, the percentage rate of price increment for each distributor or retailer. Then N lines follow, each describes a distributor or retailer in the following format:

*Ki ID[1] ID[2] ... ID[Ki]*

where in the i-th line, Ki is the total number of distributors or retailers who receive products from supplier i, and is then followed by the ID's of these distributors or retailers. Kj being 0 means that the j-th member is a retailer. All the numbers in a line are separated by a space.

## Output Specification: 

For each test case, print in one line the lowest price we can expect from some retailers, accurate up to 4 decimal places, and the number of retailers that sell at the lowest price. There must be one space between the two numbers. It is guaranteed that the all the prices will not exceed 1010.
Sample Input:  
10 1.80 1.00  
3 2 3 5  
1 9  
1 4  
1 7  
0  
2 6 1  
1 8  
0  
0  
0  

## Sample Output:  
1.8362 2  

## 题意：


供应商为根结点，经销商为中间结点，零售商为叶结点。商品在供应商的售价为p，往下每经过一层售价增加 r%。输入供应链上每个结点（共N个，编号0~N - 1）的子结点个数与所有子节点编号。若顾客只能在零售商处购买商品，求顾客可以得到的最低售价与能提供此最低售价的零售商个数 :)


## 思路：


结构体存储一个树结点的子结点个数与存储子结点编号的数组，结构体数组存储树，BFS分层遍历树，最先遇到的叶结点是所在层数最低的零售商（供应商根结点在第0层），这里的售价最低。求出此最低售价。遍历完这一层，记录这一层叶结点个数，进入下一层时结束程序:)

## 代码：

[1106. Lowest Price in Supply Chain (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1106.%20Lowest%20Price%20in%20Supply%20Chain%20(25)/1106.%20Lowest%20Price%20in%20Supply%20Chain%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <queue>

struct node {
	int k, *children;
};

void bfs(node *tree, int n, double p, double r)
{
	queue<int>q;
	int *collected = new int[n];
	int last = 0, tail = 0, level = 0, count = 0, flag = 0;
	double min = 0.0;
	q.push(0);
	collected[0] = 1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		if (tree[v].k == 0) {
			min = p * pow((1 + r / 100.0), level);
			count++;
			flag = 1;
		}
		for (int i = 0; i < tree[v].k; i++) {
			if (collected[tree[v].children[i]] != 1) {
				q.push(tree[v].children[i]);
				collected[tree[v].children[i]] = 1;
				last = tree[v].children[i];
			}
		}
		if (v == tail) {
			tail = last;
			level++;
			if (flag == 1) {
				printf("%.4f %d", min, count);
				return;
			}
		}
	}
}

int main()
{
	int n;
	double p, r;
	cin >> n >> p >> r;
	node *tree = new node[n];
	for (int i = 0; i < n; i++) {
		int k, *children;
		cin >> k;
		children = new int[k];
		for (int j = 0; j < k; j++)
			cin >> children[j];
		tree[i] = { k, children };
	}
	bfs(tree, n, p, r);
    return 0;
}
```

