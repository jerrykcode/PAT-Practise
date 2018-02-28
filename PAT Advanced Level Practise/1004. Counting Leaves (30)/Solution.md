# 1004. Counting Leaves (30)



* 时间限制 400 ms


* 内存限制 65536 kB


* 代码长度限制 16000 B


* 判题程序 Standard 

* 作者 CHEN, Yue


A family hierarchy is usually presented by a pedigree tree. 
Your job is to count those family members who have no child.



## Input

Each input file contains one test case. Each case starts with a line containing 0 < N < 100, 
the number of nodes in a tree, and M (< N), the number of non-leaf nodes. Then M lines follow, each in the format:
*ID K ID[1] ID[2] ... ID[K]*

where ID is a two-digit number representing a given non-leaf node, K is the number of its children, 
followed by a sequence of two-digit ID's of its children. 
For the sake of simplicity, let us fix the root ID to be 01.




## Output

For each test case, you are supposed to count those family members who have no child 
for every seniority level starting from the root. The numbers must be printed in a line, 
separated by a space, and there must be no extra space at the end of each line.

The sample case represents a tree with only 2 nodes, where 01 is the root and 02 is its only child. 
Hence on the root 01 level, there is 0 leaf node; 
and on the next level, there is 1 leaf node. Then we should output "0 1" in a line.



## Sample Input
2 1
01 1 02

## Sample Output
0 1




## 题意:
一颗树有N个结点，M个非叶结点，已知每个非叶结点的编号（根为01），子结点个数以及每个子结点的编号，求树的每层的叶结点个数

## 思路：
用链表存储非叶结点的子结点，M个链表存储在数组中，
层序遍历树，用Last记录每层最后元素编号（初始化为根结点编号），Tail记录当前进队列的结点编号（初始不赋值），
count记录每层叶结点数量（初始为0）

根结点进队列，while队列不空，队列头元素出队列（设为n），若n无孩子，count++，否则其所有子结点进队列，并将
当前进队列的子结点赋值给Tail，所有子结点进队列后，若n==Last，说明n是一层的最后元素，此时输出count，并将
count归0，Tail赋值给Last（即下一层的最后元素）

## 代码：

[1004. Counting Leaves (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1004.%20Counting%20Leaves%20(30)/1004.%20Counting%20Leaves%20(30).cpp)

```cpp
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;

typedef struct Node *Position;
struct Node {
	int Data;
	Position Next;
};
typedef Position List;

void CountLeaves(List *Vector)
{
	int Root = 1;/* Root of the tree */
	int count = 0;
	int Tail, Last;
	queue<int> Q;
	Q.push(Root);
	Last = Root;
	while (!Q.empty()) {
		int n = Q.front();
		Q.pop();
		if (Vector[n]->Next == NULL) 
			count++;
		else {
			Position P = (Position)malloc(sizeof(struct Node));
			for (P = Vector[n]->Next; P; P = P->Next) {
				Q.push(P->Data);
				Tail = P->Data;
			}
		}
		if (n == Last) {
			if (n != Root)
				putchar(' ');
			printf("%d", count);
			count = 0;
			Last = Tail;
		}
	}
}

int main()
{
	int N, M; /* 0 < N < 100, the number of nodes in a tree, and M (< N), the number of non-leaf nodes */
	scanf("%d %d", &N, &M);
	List *Vector = (List *)malloc((N + 1) * sizeof(List)); /* 链表存储非叶子结点的子结点，叶子结点的链表为NULL */
	for (int i = 1; i <= N; i++) {
		Vector[i] = (List)malloc(sizeof(struct Node));
		Vector[i]->Next = NULL;
	}
	for (int i = 0; i < M; i++) {
		int id, K;
		scanf("%d %d", &id, &K);
		for (int j = 0; j < K; j++) {
			int idk;
			scanf("%d", &idk);
			Position P = (Position)malloc(sizeof(struct Node));
			P->Data = idk;
			P->Next = Vector[id]->Next;
			Vector[id]->Next = P;
		}
	}
	CountLeaves(Vector);
	return 0;
}
```
