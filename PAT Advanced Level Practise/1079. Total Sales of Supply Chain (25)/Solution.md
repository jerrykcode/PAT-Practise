# 1079. Total Sales of Supply Chain (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1079)
* 时间限制 250 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



A supply chain is a network of retailers（零售商）, distributors（经销商）, and suppliers（供应商）-- everyone 
involved in moving a product from supplier to customer.

Starting from one root supplier, everyone on the chain buys products from one's supplier in a price P and sell or 
distribute them in a price that is r% higher than P. Only the retailers will face the customers. It is assumed that 
each member in the supply chain has exactly one supplier except the root supplier, and there is no supply cycle.

Now given a supply chain, you are supposed to tell the total sales from all the retailers.



## Input Specification: 

Each input file contains one test case. For each case, the first line contains three positive numbers: N (<=10^5), 
the total number of the members in the supply chain (and hence their ID's are numbered from 0 to N-1, and the root 
supplier's ID is 0); P, the unit price given by the root supplier; and r, the percentage rate of price increment 
for each distributor or retailer. Then N lines follow, each describes a distributor or retailer in the following format:

*Ki ID[1] ID[2] ... ID[Ki]*

where in the i-th line, Ki is the total number of distributors or retailers who receive products from supplier i, and is 
then followed by the ID's of these distributors or retailers. Kj being 0 means that the j-th member is a retailer, then 
instead the total amount of the product will be given after Kj. All the numbers in a line are separated by a space.



## Output Specification: 

For each test case, print in one line the total sales we can expect from all the retailers, accurate up to 1 decimal place. 
It is guaranteed that the number will not exceed 10^10.



## Sample Input:

10 1.80 1.00  
3 2 3 5  
1 9  
1 4  
1 7  
0 7  
2 6 1  
1 8  
0 9  
0 4  
0 3  

## Sample Output:

42.4  



## 题意：

供应商为根结点，经过若干层经销商，到达零售商（叶子结点）。已知供应商、经销商、零售商总数N（结点总数，编号0~N - 1，供
应商编号为0），供应商商品价格，每一层售价增加百分比。输入供应商和零售商（非叶结点）的子结点编号，以及零售商（叶子结点）
的商品数量。若顾客只能从零售商购买商品，求所有零售商销售价值总和


## 思路：

BFS层序遍历，对每一层的叶子结点计算其销售价值


## 代码：


[1079. Total Sales of Supply Chain (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1079.%20Total%20Sales%20of%20Supply%20Chain%20(25)/1079.%20Total%20Sales%20of%20Supply%20Chain%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <queue>
#include <math.h>

typedef struct node {
	int id, nChild, *children, flag;
} treeNode;

int main()
{
	int n;
	double p, r;
	cin >> n >> p >> r;
	treeNode * tree = new treeNode[n];
	for (int i = 0; i < n; i++) {
		int ki, flag = 0;
		cin >> ki;
		int *children = new int[ki];
		if (ki == 0) cin >> flag;
		else
		{
			for (int j = 0; j < ki; j++)
				cin >> children[j];
		}
		tree[i] = {i, ki, children, flag};
	}
	int last = 0, tail = 0, level = 0; //last是当前最后进队列的，tail是一层中最后一个，level是层数
	double total = 0;
	queue<int>q;
	q.push(0);
	while (!q.empty()) {
		int node = q.front();
		q.pop();
		if (tree[node].flag) //叶子
			total += tree[node].flag * p * pow((1 + r * 0.01), level);
		else {
			for (int i = 0; i < tree[node].nChild; i++) {//孩子入队
				q.push(tree[node].children[i]);
				last = tree[node].children[i];
			}
		}
		if (node == tail) { //出队列的是一层的最后一个，进入下一层
			tail = last;
			level++;
		}
	}
	printf("%.1f", total);
    return 0;
}
```
