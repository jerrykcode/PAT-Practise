# 1090. Highest Price in Supply Chain (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1089)
* 时间限制 200 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



A supply chain is a network of retailers（零售商）, distributors（经销商）, and suppliers（供应商）-- everyone 
involved in moving a product from supplier to customer.

Starting from one root supplier, everyone on the chain buys products from one's supplier in a price P and sell 
or distribute them in a price that is r% higher than P. It is assumed that each member in the supply chain has 
exactly one supplier except the root supplier, and there is no supply cycle.

Now given a supply chain, you are supposed to tell the highest price we can expect from some retailers.



## Input Specification: 

Each input file contains one test case. For each case, The first line contains three positive numbers: N (<=105), 
the total number of the members in the supply chain (and hence they are numbered from 0 to N-1); P, the price 
given by the root supplier; and r, the percentage rate of price increment for each distributor or retailer. Then 
the next line contains N numbers, each number Si is the index of the supplier for the i-th member. Sroot for the 
root supplier is defined to be -1. All the numbers in a line are separated by a space.



## Output Specification: 

For each test case, print in one line the highest price we can expect from some retailers, accurate up to 2 decimal 
places, and the number of retailers that sell at the highest price. There must be one space between the two numbers. 
It is guaranteed that the price will not exceed 1010.



## Sample Input:

9 1.80 1.00  
1 5 4 4 -1 4 5 3 6  

## Sample Output:

1.85 2  



## 题意：

与 [1079. Total Sales of Supply Chain (25)](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1079.%20Total%20Sales%20of%20Supply%20Chain%20(25)/Solution.md) 类似：

供应商、经销商与零售商为树的结点，供应商为根，输入供应商与经销商与零售商的供应他们的人，即每个叶结点的父结点。供应商的
父结点为-1。顺供应链往下每深一层售价增百分之r，求最大的售价及此按售价销售的零售商个数


## 思路：

DFS/BFS 求最高层数与最高一层的结点数


## 代码： 

## [DFS](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1090.%20Highest%20Price%20in%20Supply%20Chain%20(25)/1090.%20Highest%20Price%20in%20Supply%20Chain%20(25)_DFS.cpp)

```cpp
#include <iostream>
using namespace std;
#include <vector>
#include <math.h>

int max_height = 0, n_max = 0;

void dfs(vector<int> *tree, int t, int count)
{
	if (tree[t].size() == 0) {
		if (count > max_height) {
			max_height = count;
			n_max = 1;
		}
		else if (count == max_height)
			n_max++;
		return;
	}
	for (auto it = tree[t].begin(); it != tree[t].end(); it++)
		dfs(tree, *it, count + 1);
}

int  main()
{
	int n, root;
	double p, r;
	cin >> n >> p >> r;
	vector<int> * tree = new vector<int>[n];
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		if (t == -1) root = i;
		else tree[t].push_back(i);
	}
	dfs(tree, root, 0);
	printf("%.2f %d\n", p * pow((1 + r/100), max_height), n_max);
	return 0;
}
```


##[BFS](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1090.%20Highest%20Price%20in%20Supply%20Chain%20(25)/1090.%20Highest%20Price%20in%20Supply%20Chain%20(25)_BFS.cpp)


```cpp
#include <iostream>
using namespace std;
#include <vector>
#include <queue>
#include <math.h>

int main()
{
	int n;
	double p, r;
	cin >> n >> p >> r;
	vector<int> *tree = new vector<int>[n]; //存储每个结点的子结点编号
	int root;
	for (int i = 0; i < n; i++) {
		int parent;
		cin >> parent;
		if (parent == -1) root = i;
		else tree[parent].push_back(i);
	}
	queue<int>q;
	q.push(root); //根入队
	int last, tail = root, level = 0, total = 1, tmp = 0;
	while (1) {
		int v = q.front();
		q.pop();
		tmp += tree[v].size();
		for (auto it = tree[v].begin(); it != tree[v].end(); it++) {
			q.push(*it); //孩子入队
			last = *it; //last为当前最后一个进队列的
		}
		if (v == tail) { //出队列的是tail（一层中的最后一个），进入下一层
			if (q.empty()) break; //此时break，total，level不变化
			tail = last;
			total = tmp;
			tmp = 0;
			level++;
		}
	}
	printf("%.2f %d\n", p * pow((1 + r/100), level), total);
    return 0;
}
```