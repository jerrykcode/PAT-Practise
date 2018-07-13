# 1016 Uniqueness of MST（35 point(s)）

[原题地址](https://pintia.cn/problem-sets/994805148990160896/problems/994805150751768576)

* Author: CHEN, Yue
* Organization: 浙江大学
* Time Limit: 400ms
* Memory Limit: 64MB
* Code Size Limit: 16KB


Given any weighted undirected graph, there exists at least one minimum spanning tree (MST) if the graph is connected. Sometimes the MST may not be unique though. Here you are supposed to calculate the minimum total weight of the MST, and also tell if it is unique or not.

## Input Specification:
Each input file contains one test case. Each case starts with a line containing 2 numbers N (≤ 500), and M, which are the total number of vertices, and the number of edges, respectively. Then M lines follow, each describes an edge by 3 integers:

*V1 V2 Weight*

where V1 and V2 are the two ends of the edge (the vertices are numbered from 1 to N), and Weight is the positive weight on that edge. It is guaranteed that the total weight of the graph will not exceed 2^30.


## Output Specification:
For each test case, first print in a line the total weight of the minimum spanning tree if there exists one, or else print No MST instead. Then if the MST exists, print in the next line Yes if the tree is unique, or No otherwise. There there is no MST, print the number of connected components instead.

## Sample Input 1:
5 7  
1 2 6  
5 1 1  
2 3 4  
3 4 3  
4 1 7  
2 4 2  
4 5 5  
## Sample Output 1:
11  
Yes  
## Sample Input 2:
4 5  
1 2 1  
2 3 1  
3 4 2  
4 1 2  
3 1 3  

## Sample Output 2:
4  
No  
## Sample Input 3:
5 5  
1 2 1  
2 3 1  
3 4 2  
4 1 2  
3 1 3  
## Sample Output 3:
No MST  
2  


## 题意

给出一个图，若图连通，则输出最小生成树MST的权重并判断该图的MST是否唯一，若图不连通则输出 "No MST"，并输出图的连通分量的个数。

## 思路

本题需要求解：
* 最小生成树：Prim算法
* 判断图是否连通：Prim算法过程中，记录收录顶点的数量，若Prim结束后收录顶点数量等于图的总顶点数量，则连通
* 判断MST是否唯一：Prim算法后，若图连通，对于MST中所有存在与其他边权重相同的边，删除此边，并对此时的图求最小生成树，若权重仍然相等，则不唯一
* 求连通分量个数：若图不连通，用bfs求连通分量

## 代码

[Uniqueness of MST(35).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Top%20Level%20Practice/1016/Uniqueness%20of%20MST(35).cpp)

```cpp
#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

#define INFINITE 1000000

typedef struct enode{ //edge 边
    int v, w;
    int weight;
} * edge;

/* functions of MST. */
class MST {
public:  
    /** Returns the weight of the MST. If flag == 1, then it also checks whether the graph
        is connected, as well as push all the edges with weight equals other edges into the
        repeatedEdges vector. 
        返回最小生成树权重，若flag == 1，则同时判断图是否连通，并将有与其他边权重相等的边
        存入repeatedEdges vector 中。*/
    int prim(int **graph, int nv, int flag);
    
    /** Returns the number of the connected components */
    int nConnectedComponents(int **graph, int nv);
    
    /** Returns true if MST is unique. */
    bool unique_MST(int **graph, int nv);
    
    /** Input. */
    void input(int **graph, int nv, int ne);
    
    /** 题目入口函数 */
    void PAT_T_1016(int **graph, int nv);
private:
    map<int, int> edgeWeightRepeatedTime; //边权重出现次数
    vector<edge> repeatedEdges; //Weight repeated edges 权重重复的边
    bool isConnected; //是否连通
    int mstWeight; //Weight of the MST 
    int findMin(int *dist, int nv);
    void bfs(int **graph, bool *collected, int s, int nv);
};

int MST::prim(int **graph, int nv, int flag) {
    int s = 0;
    int *dist = new int[nv]; //Distance between the vertex and the MST
    int *pre = new int[nv]; //The previous vertex
    for (int v = 0; v < nv; v ++) {
        dist[v] = graph[s][v];
        pre[v] = dist[v] < INFINITE ? s : -1;
    }
    dist[s] = 0;
    int MST_weight = 0;    
    int nvCollected = 1; //s is collected, so the number of vertexes collected now is 1
    while (1) {
        int minV = findMin(dist, nv);
        if (minV == -1)
            break;
        if (flag) {
            nvCollected++;
            if (edgeWeightRepeatedTime[dist[minV]] > 1) { //The edge has repeated weight 边的权重重复
                edge e = new enode;
                e->v = pre[minV];
                e->w = minV;
                e->weight = dist[minV];
                repeatedEdges.push_back(e);
            }
        }
        MST_weight += dist[minV];
        dist[minV] = 0;
        for (int v = 0; v < nv; v ++)
            if (dist[v] != 0 && graph[minV][v] < INFINITE) 
                if (graph[minV][v] < dist[v]) {
                    dist[v] = graph[minV][v];
                    pre[v] = minV;
                }        
    }
    if (flag) 
        isConnected = nvCollected == nv; //If the vertexes collected equals to the number of total vertexes in the graph,
                                          // then the graph is connected
    free(dist);
    free(pre);
    return MST_weight;
}

int MST::findMin(int *dist, int nv) {
    int min = INFINITE, minV = -1;
    for (int v = 0; v < nv; v ++) 
        if (dist[v] != 0 && dist[v] < min) {
            min = dist[v];
            minV = v;
        }
    return minV;
}

int MST::nConnectedComponents(int **graph, int nv) {
    int num = 0;
    bool *collected = new bool[nv];
    fill(collected, collected + nv, false);
    for (int s = 0; s < nv; s++) {
        if (collected[s]) continue;
        bfs(graph, collected, s, nv);
        num++;
    }
    free(collected);
    return num;
}

void MST::bfs(int **graph, bool *collected, int s, int nv) {
    queue<int> q;
    q.push(s);
    collected[s] = true;
    while (!q.empty()) {
        int v = q.back();
        q.pop();
        for (int w = 0; w < nv; w ++) 
            if (!collected[w] && graph[v][w] < INFINITE) {
                collected[w] = true;
                q.push(w);
            }        
    }
}

bool MST::unique_MST(int **graph, int nv) {
    for (auto it = repeatedEdges.begin(); it != repeatedEdges.end(); it ++) {
        edge e = *it;
        int v = e->v, w = e->w;
        graph[v][w] = graph[w][v] = INFINITE; //Remove the repeated weight edge
        int currentWeight = prim(graph, nv, 0); //Prim
        graph[v][w] = graph[w][v] = e->weight; //Add the edge back
        if (currentWeight == mstWeight) {//If the weight of MST of the graph with the edge removed
                                          // is same as the origin weight of MST, then MST is not unique.
                                          // 若删除权重重复边，此时图的MST的权重不变，则MST不唯一
            return false;
        }
    }
    return true;
}

void MST::input(int **graph, int nv, int ne) {
    for (int i = 0; i < ne; i ++) {
        int v, w, weight;
        cin >> v >> w >> weight;
        v--; w--;
        graph[v][w] = graph[w][v] = weight;
        edgeWeightRepeatedTime[weight] ++;
    }
}
    
void MST::PAT_T_1016(int **graph, int nv) {
    mstWeight = prim(graph, nv, 1);
    if (isConnected) {
        cout << mstWeight << endl;
        cout << (unique_MST(graph, nv) ? "Yes" : "No") << endl;
    } else {
        cout << "No MST" << endl;
        cout << nConnectedComponents(graph, nv) << endl;
    }
}

int main() 
{
    MST mst;
    int nv, ne;
    cin >> nv >> ne;
    int **graph = new int*[nv];
    for (int i = 0; i < nv; i ++) {
        graph[i] = new int[nv];
        for (int j = 0; j < nv; j ++)
            graph[i][j] = INFINITE;
    }
    mst.input(graph, nv, ne);
    mst.PAT_T_1016(graph, nv);
    free(graph);
    return 0;
}
```
