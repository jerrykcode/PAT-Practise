# 1107. Social Clusters (30)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1107)

* 时间限制 1000 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



When register on a social network, you are always asked to specify your hobbies in order to find some potential friends with the same hobbies. A "social cluster" is a set of people who have some of their hobbies in common. You are supposed to find all the clusters.

## Input Specification: 

Each input file contains one test case. For each test case, the first line contains a positive integer N (<=1000), the total number of people in a social network. Hence the people are numbered from 1 to N. Then N lines follow, each gives the hobby list of a person in the format:

*Ki: hi[1] hi[2] ... hi[Ki]*

where Ki (>0) is the number of hobbies, and hi[j] is the index of the j-th hobby, which is an integer in [1, 1000].

## Output Specification: 

For each case, print in one line the total number of clusters in the network. Then in the second line, print the numbers of people in the clusters in non-increasing order. The numbers must be separated by exactly one space, and there must be no extra space at the end of the line. 

## Sample Input:
8  
3: 2 7 10  
1: 4  
2: 5 3  
1: 4  
1: 3  
1: 4  
4: 6 8 1 5  
1: 4  

## Sample Output:
3  
4 3 1  

## 题意：

N个人id编号1\~N，输入每个人的爱好（爱好编号1\~1000）。有相同爱好的人聚在一起，求有多少个聚在一起的人群，及每个群体的人数（非递增输出）。

## 思路：

用并查集。

int数组S，下标表示人的id，存储的值为并查集中此人的父结点。根结点的S值为该集合的人数乘以-1，（S值为负数的一定是一个集合的根结点）。S中的值初始化为-1。int数组hobbies[1001]的下标表示爱好的编号，值表示有这个爱好的一个人，初始化为0。边输入边处理。若一个爱好已经有人有了（hobbies值大于0），则正在输入的这个人和有此爱好的人并到一个集合中。合并两个集合时先找到它们的根（递归找根时[压缩路径](http://www.icourse163.org/learn/ZJU-93001?tid=1002261004#/learn/content?type=detail&id=1003011847&cid=1003525114)），然后将较小的并到较大的上。输入结束后，遍历数组S，将小于0的值（根的S值，即集合大小的相反数）存入vector中，输出vector的size，对vector的值排序（sort函数自动非递减排序，但这些根的S值是负数，乘-1后变为非递增）输出。


## 代码：

[1107. Social Clusters (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1107.%20Social%20Clusters%20(30)/1107.%20Social%20Clusters%20(30).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

int *S;

int findRoot(int x)
{
	if (S[x] < 0)
		return x;
	return S[x] = findRoot(S[x]);
}

void unionSets(int x1, int x2)
{
	int root1 = findRoot(x1);
	int root2 = findRoot(x2);
	if (root1 == root2) return;
	if (S[root1] > S[root2]) {
		S[root2] += S[root1];
		S[root1] = root2;
	}
	else {
		S[root1] += S[root2];
		S[root2] = root1;
	}
}

int main()
{
	int n;
	cin >> n;
	S = new int[n + 1];
	int hobbies[1001] = { 0 };
	fill(S, S + n + 1, -1);
	for (int i = 1; i <= n; i++) {
		int k, h;
		scanf("%d:", &k);
		for (int j = 0; j < k; j++) {
			scanf("%d", &h);
			if (hobbies[h] > 0)
				unionSets(i, hobbies[h]);
			hobbies[h] = i;
		}
	}
	vector<int> clusters;
	for (int i = 1; i <= n; i++) 
		if (S[i] < 0) clusters.push_back(S[i]);
	sort(clusters.begin(), clusters.end());
	printf("%d\n", clusters.size());
	for (auto it = clusters.begin(); it != clusters.end(); it++) {
		if (it != clusters.begin()) putchar(' ');
		printf("%d", -1*(*it));
	}
    return 0;
}
```
