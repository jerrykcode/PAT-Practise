# 1146. Topological Order (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1146)

* 时间限制 200 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



This is a problem given in the Graduate Entrance Exam in 2018: Which of the following is NOT a topological order obtained from the given directed graph? Now you are supposed to write a program to test each of the options. 



## Input Specification: 

Each input file contains one test case. For each case, the first line gives two positive integers N (<= 1,000), the number of vertices in the graph, and M (<= 10,000), the number of directed edges. Then M lines follow, each gives the start and the end vertices of an edge. The vertices are numbered from 1 to N. After the graph, there is another positive integer K (<= 100). Then K lines of query follow, each gives a permutation of all the vertices. All the numbers in a line are separated by a space. 

## Output Specification: 

Print in a line all the indices of queries which correspond to "NOT a topological order". The indices start from zero. All the numbers are separated by a space, and there must no extra space at the beginning or the end of the line. It is graranteed that there is at least one answer.

## Sample Input:

6 8  
1 2  
1 3  
5 2  
5 4  
2 3  
2 6  
3 4  
6 4  
5  
1 5 2 3 6 4  
5 1 2 6 3 4  
5 1 2 3 6 4  
5 2 1 6 3 4  
1 2 3 4 5 6  

## Sample Output:

3 4  

## 思路：

邻接表存储图。用数组存储每个顶点的入度，对每组枚举序列，将入度数组复制到另一个临时数组上用于判断，每个顶点的入度应为0，然后此顶点相邻的每个顶点入度减1。

## 代码：

[1146. Topological Order (25)](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1146.%20Topological%20Order%20(25)/1146.%20Topological%20Order%20(25).cpp)

```cpp
#include <iostream>
using namespace std;
#include <vector>

int main()
{
  int n, m, k;
  cin >> n >> m;
  vector<int> *graph = new vector<int>[n];
  int *inDegree = new int[n], *temp = new int[n];
  fill(inDegree, inDegree + n, 0);
  for (int i = 0; i < m; i++) {
    int v1, v2;
    cin >> v1 >> v2;
    v1--; v2--;
    graph[v1].push_back(v2);
    inDegree[v2]++;
  }
  cin >> k;
  vector<int> nonTop;
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < n; j ++)temp[j] = inDegree[j];
    int v, flag = 0;
    for (int j = 0; j < n; j++) {
      cin >> v;
      if (flag) continue;
      v--;
      if (temp[v]) flag = 1;
      for (int w : graph[v]) temp[w]--;
    }
    if (flag) nonTop.push_back(i);
  }
  for (auto it = nonTop.begin(); it != nonTop.end(); it++) {
    if (it != nonTop.begin()) putchar(' ');
    cout << *it;
  }
}
```