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
