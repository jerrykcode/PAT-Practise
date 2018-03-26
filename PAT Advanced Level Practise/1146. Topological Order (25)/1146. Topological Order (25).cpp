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