# 1118. Birds in Forest (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1118)

* 时间限制 150 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



Some scientists took pictures of thousands of birds in a forest. Assume that all the birds appear in the same picture belong to the same tree. You are supposed to help the scientists to count the maximum number of trees in the forest, and for any pair of birds, tell if they are on the same tree. 

## Input Specification: 

Each input file contains one test case. For each case, the first line contains a positive number N (<= 10^4) which is the number of pictures. Then N lines follow, each describes a picture in the format:
 *K B1 B2 ... BK*
 where K is the number of birds in this picture, and Bi's are the indices of birds. It is guaranteed that the birds in all the pictures are numbered continuously from 1 to some number that is no more than 10^4.

After the pictures there is a positive number Q (<= 10^4) which is the number of queries. Then Q lines follow, each contains the indices of two birds. 

## Output Specification: 

For each test case, first output in a line the maximum possible number of trees and the number of birds. Then for each query, print in a line "Yes" if the two birds belong to the same tree, or "No" if not.
## Sample Input:
4  
3 10 1 2  
2 3 4  
4 1 5 7 8  
3 9 6 4  
2  
10 5  
3 7  

## Sample Output:  
2 10  
Yes  
No  

## 题意：

N张照片，每张输入上面的鸟的数量与每只鸟的id（1到不超过10^4的数），假设每张照片上的鸟在同一棵树上。求有多少棵树，多少只鸟。然后输入Q个查询，每个查询输入两只鸟的id，输出它们是否在同一棵树上。


## 思路：
用并查集。  
思路与[1107. Social Clusters (30)](https://github.com/jerrykcode/PAT-Advanced-Level-Practise/blob/master/PAT%20Advanced%20Level%20Practice/1107.%20Social%20Clusters%20(30)/Solution.md)类似。集合存储的是同一棵树的照片，用一个数组存储每只鸟所在的任意一张照片。输入照片时，若一只鸟在其他照片上未出现过，则计数器增1，否则现在正在输入的这一张照片与鸟所在的照片属同一棵树，把这两张照片的集合并在一起。并查集中的集合数即树的数量。最后输入的每对查询，若两只鸟所在的照片的集合的根相同，则在同一棵树上。

## 代码：

[1118. Birds in Forest (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1118.%20Birds%20in%20Forest%20(25)/1118.%20Birds%20in%20Forest%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

int S[10001];

int findRoot(int x)
{
	if (S[x] < 0)
		return x;
	else return S[x] = findRoot(S[x]);
}

void unionSets(int s1, int s2)
{
	int r1 = findRoot(s1);
	int r2 = findRoot(s2);
	if (S[r1] < S[r2]) {
		S[r1] += S[r2];
		S[r2] = r1;
	}
	else {
		S[r2] += S[r1];
		S[r1] = r2;
	}
}

int main()
{
	fill(S, S + 10001, -1);
	int n, k, bi, q;
	cin >> n;
	int pic[10001];
	fill(pic, pic + 10001, 0);
	int count = 0;
	for (int i = 1; i <= n; i++) {
		cin >> k;
		for (int j = 0; j < k; j++) {
			cin >> bi;
			if (pic[bi] == 0) {
				pic[bi] = i;
				count++;
			}
			else {
				unionSets(i, pic[bi]);
			}
		}
	}
	int nTree = 0;
	for (int i = 1; i <= n; i++)
		if (S[i] < 0) nTree++;
	printf("%d %d\n", nTree, count);
	cin >> q;
	for (int i = 0; i < q; i++) {
		int b1, b2;
		cin >> b1 >> b2;
		cout << (findRoot(pic[b1]) == findRoot(pic[b2]) ? "Yes" : "No") << endl;
	}
    return 0;
}
```

