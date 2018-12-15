# 1013 Image Segmentation（35 point(s)）

[原题地址](https://pintia.cn/problem-sets/994805148990160896/problems/994805151670321152)

* Author: ZHU, Jianke
* Organization: 浙江大学
* Time Limit: 200ms
* Memory Limit: 64MB
* Code Size Limit: 16KB


Image segmentation is usually formulated as a graph partition problem, where each segment corresponds to a connected component. Moreover, each pixel is the vertex of the graph. Each edge has a weight, which is a non-negative dissimilarity between neighboring pixels. So, the goal of image segmentation is to decompose the image graph into several disconnected components, where the elements in a component are similar and the elements in the different components are dissimilar.

The components are defined as follows:

* A component is made of a set of connected vertices;
* Any two components have no shared vertices;
* The dissimilarity D(C1,C2) of any two components C1 and C2 is larger than the confidence H of any of C1 and C2.
* The dissimilarity D(C1,C2) is defined to be the minimum edge weight of all the edges connecting C1 and C2, or infinity if no such edge exists;
* The confidence of a component C, H(C), is defined to be the maximum edge weight of the minimum spanning tree of C, plus a function f(C)=c/∣C∣ where c is a positive constant and ∣C∣ is the size of the component C;
* A set of vertices must not be treated as a component if they can be partitioned into two or more components.

Your job is to write a program to list all the components.

## Input Specification:

Each input file contains one test case. For each case, the first line contains three integers: N​v​​  (0<N​v​​ ≤1000), the total number of vertices (and hence the vertices are numbered from 0 to N​v​​ −1); N​e​​ , the total number of edges; and c, the constant in the function f(C). Then N​e​​  lines follow, each gives an adge in the format:

*V1 V2 Weight*

Note: it is guaranteed that each pixel has no more than 8 neighboring pixels. The constant and all the weights are positive and are no more than 1000.

## Output Specification:
For each case, list each component in a line. The vertices in a component must be printed in increasing order, separated by one space with no extra space at the beginning or the end of the line. The components must be listed in increasing order of their first vertex.

## Sample Input 1:

10 21 100  
0 1 10  
0 3 60  
0 4 90  
1 2 90  
1 3 50  
1 4 200  
1 5 86  
2 4 95  
2 5 5  
3 4 95  
3 6 15  
3 7 101  
4 5 500  
4 6 100  
4 7 101  
4 8 101  
5 7 300  
5 8 50  
6 7 90  
7 8 84  
7 9 34  

## Sample Output 1:

0 1 3 6  
2 5 8  
4  
7 9  

## Sample Input 2:

7 7 100  
0 1 10  
1 2 61  
2 3 50  
3 4 200  
4 5 82  
5 0 200  
3 6 90  

## Sample Output 2:

0 1  
2 3 6  
4 5  

## 题意

已知：

* 一个 *component* 由相连的顶点组成。
* 两个 *component* 没有共享的顶点。
* 两个 *component* 的差距比其中一个的 *confidence* 大。
* 两个 *component* C1、C2的差距是连接C1、C2的最小边的权重。
* 一个 *component* 的 *confidence* 是该 *component* 的最小生成树的最大边的权重 + f(C); f(C) = c / (C的顶点数)，c为一常数。
* 若一个 *component* 可以分为多个 *component* ，则应分开。


求一个图的所有 *component* 。

## 思路

求最小生成树MST，记录当前MST中的最大边，在收录顶点时，若顶点与MST的距离小于等于当前MST的confidence, 则收录该顶点并更新最大边与confidence，否则当前MST为一个 *component* ，然后以其他顶点为源计算MST。对顶点计算MST的次序，应先计算与之相连的边的权重小的顶点。


## 代码

[1013 Image Segmentation.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Top%20Level%20Practice/1013/1013%20Image%20Segmentation.cpp)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INFINITE 100000000

int c; //Constant in the function f(C), 常量
int * shortest_edge; //Length of the shortest edge a vertex connected to. 与一顶点相连的最短边长度

/* Calculates the confidence. */
int calc_confidence(int max_weight, int nv_mst) {
    return max_weight + (int)(c/nv_mst + 0.5);
}

/* MST. */
void prim(int **graph, bool * collected, int nv, int s, vector<int>& mst) {
    int *dist = new int[nv]; //Distance between a vertex and the MST
    for (int v = 0; v < nv; v ++) {
        if (collected[v]) continue;
        dist[v] = graph[s][v];
    }   
    collected[s] = true;// Collects the source
    mst.push_back(s);
    dist[s] = 0;
    int max_weight = 0; //Maximum edge weight of the MST
    int nv_mst = 1;
    int confidence = calc_confidence(max_weight, nv_mst); //Calculates the confidence
    while (1) {
        int minV = -1, min = INFINITE;
        for (int v = 0; v < nv; v ++)
            if (!collected[v] && dist[v] < min) {
                min = dist[v];
                minV = v;
            }
        if (minV == -1) break; //无顶点，MST连通分量计算结束
        if (min <= confidence) {
            collected[minV] = true; //Collects minV
            mst.push_back(minV);
            nv_mst++;
            dist[minV] = 0; //Distance between minV and the MST is 0
            for (int v = 0; v < nv; v ++) {
                if (collected[v]) continue;
                if (graph[minV][v] < dist[v])
                    dist[v] = graph[minV][v];
            }
            if (min > max_weight) 
                max_weight = min; //Updates max_weight         
            confidence = calc_confidence(max_weight, nv_mst); //Updates confidence
        }
        else break; //min > confidence, MST连通分量计算结束
    }
    free(dist);
}

bool compare0(int a, int b) {
    return shortest_edge[a] < shortest_edge[b];
}

void mst_components (int **graph, int nv, vector<vector<int>>& msts) {
    bool * collected = new bool[nv];
    fill(collected, collected + nv, false);
    int * sequence = new int [nv]; //Sequence. 顶点调用prim的次序
    for (int i = 0; i < nv; i ++) sequence[i] = i;
    sort(sequence, sequence + nv, compare0); //Sorts according to the length of the minimum edge they connected to
    for (int i = 0; i < nv; i ++) {
        int v = sequence[i];
        if (collected[v]) continue;
        vector<int> mst;
        prim(graph, collected, nv, v, mst);
        sort(mst.begin(), mst.end());
        msts.push_back(mst);
    }
    free(collected);
    free(sequence);
}

bool compare1(vector<int>& a, vector<int>& b) {
    return *(a.begin()) < *(b.begin());
}

int main()
{
    int nv, ne;
    //Input
    cin >> nv >> ne >> c;
    int ** graph = new int *[nv];   
    for (int i = 0; i < nv; i ++) {
        graph[i] = new int[nv];
        fill(graph[i], graph[i] + nv, INFINITE);
    }
    shortest_edge = new int[nv];
    fill(shortest_edge, shortest_edge + nv, INFINITE);
    for (int i = 0; i < ne; i ++) {
        int v1, v2, weight;
        cin >> v1 >> v2 >> weight;
        graph[v1][v2] = graph[v2][v1] = weight;
        if (weight < shortest_edge[v1]) shortest_edge[v1] = weight;
        if (weight < shortest_edge[v2]) shortest_edge[v2] = weight;
    }
    //Calculate
    vector<vector<int>> msts;
    mst_components(graph, nv, msts);
    sort(msts.begin(), msts.end(), compare1);
    //Output
    for (auto i = msts.begin(); i != msts.end(); i ++) {
        for (auto j = i->begin(); j != i->end(); j ++) {
            if (j != i->begin()) putchar(' ');
            cout << *j;
        }
        cout << endl;
    }
    free(graph);
    free(shortest_edge);
    return 0;
}
```


