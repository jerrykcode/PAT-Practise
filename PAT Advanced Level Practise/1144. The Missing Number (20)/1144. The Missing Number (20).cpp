#include <iostream>
using namespace std;
#include <map>

int main()
{
  int n, m;
  cin >> n;
  map<int, int> list;
  for (int i = 0; i < n; i++) {
    cin >> m;
    if (m > 0)list[m] = 1;
  }
  int index = 0;
  while ( ++ index)
    if (list[index] == 0) {
      cout << index;
      return 0;
    }
  return 0;
}