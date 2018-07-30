# 1014 Circles of Friends(35)

[原题地址](https://pintia.cn/problem-sets/994805148990160896/problems/994805151343165440)

* Author: CHEN, Yue
* Organization: 浙江大学
* Time Limit: 1000ms
* Memory Limit: 64MB
* Code Size Limit: 16KB

A circle of friends is a network of friend relationships. If A is a friend of B, then B is considered a friend of A no matter B admits or not, and they are said to belong to the same circle. Here we assume that friendship is transitive, that is, if A is a friend of B, and B is a friend of C, then A is a friend of C and the three of them all belong to the same circle.

On the other hand, A is not so close to C as B is. We define the distance D(X, Y) between two friends X and Y as the minimum number of friends between them. For example, D(A, B) = 0, and D(C, A) = 1. The diameter of a friends circle is the maximum distance between any pair of friends in the circle.

Now given some people's relationships, you are supposed to find the number of friends circles and the circle with the largest diameter.

## Input Specification:
Each input file contains one test case. For each case, the first line gives an integer N (2≤N≤1000), which is the total number of people involved, and hence they are numbered from 1 to N. Then N lines follow, each in the format:

*k  p1  ... pk *

where k (0 ≤ k < min(10,N)) is the number of friends and p1  to pk  (if k>0) are the friends' indices. The i-th line corresponds to the i-th person. All the numbers in a line are separated by spaces. It is guaranteed that no one is given as a friend of oneself.

## Output Specification:
For each case, print in a line the number of friends circles, and the largest diameter, separated by exactly one space.

## Sample Input:
17  
2 15 12  
1 17  
2 16 9  
1 8  
4 10 13 15 14  
0  
2 11 14  
1 4  
2 2 3  
2 13 11  
2 15 7  
2 1 14  
2 5 15  
0  
0  
1 3  
1 2  
## Sample Output:
4 3  

## 题意：

已知图中，对顶点X，Y，D(X, Y)表示X与Y之间相隔的最少顶点数。一个连通图中最大的D为图的直径。给出由朋友关系组成的图，求连通分量的个数，及所有连通分量中的最大直径。

## 思路：

对每个顶点，以其作为源，进行BFS分层遍历，求出最深层数。对连通分量中每个顶点BFS后，最大的最深层数 - 2 即该连通分量的直径。

## 代码：
[1014 Circles of Friends(35).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Top%20Level%20Practice/1014/1014%20Circles%20of%20Friends(35).cpp)


```cpp
#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

int bfs(vector<int> * graph, int s, int * components_index, int index, int n) {
    queue<int> q;
    bool *tmp_collected = new bool[n];
    fill(tmp_collected, tmp_collected + n, false);
    q.push(s);
    if (components_index[s] == -1)
        components_index[s] = index;
    tmp_collected[s] = true;
    int last = s, tail = s, level = 0;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (int w : graph[v]) {
            if (!tmp_collected[w]) {
                q.push(w);
                if (components_index[w] == -1)
                    components_index[w] = index;
                tmp_collected[w] = true;
                last = w;
            }
        }
        if (v == tail) {
            level++;
            tail = last;
        }
    }
    free(tmp_collected);
    return level - 2;
}

int main ()
{
    int n;
    cin >> n;
    vector<int> * graph = new vector<int>[n];
    int k, p;
    for (int i = 0; i < n; i++) {
        cin >> k;
        for (int j = 0; j < k; j++) {
            cin >> p;
            p--;
            graph[i].push_back(p);
            graph[p].push_back(i);
        }
    }
    int * components_index = new int[n];
    fill(components_index, components_index + n, -1);
    map<int, int> diameter;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (components_index[i] == -1)
            index++;
        int level = bfs(graph, i, components_index, index, n);
        if (level > diameter[index])
            diameter[index] = level;
    }
    int max_dia = 0;
    for (auto it = diameter.begin(); it != diameter.end(); it++)
        if (it->second > max_dia)
            max_dia = it->second;
    cout << index + 1 << " " << max_dia;
    free(components_index);
    return 0;
}
```
