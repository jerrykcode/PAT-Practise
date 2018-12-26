#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 100
#define MIN 0

int main()
{
  int n, k, m;
  cin >> n >> k >> m;
  float *score = new float[n];
  for (int i = 0; i < n; i++) {
    int sum = 0, min = MAX + 1, max = MIN - 1, sc;
    for (int j = 0; j < k; j++) {
      cin >> sc;
      sum += sc;
      if (sc > max) max = sc;
      if (sc < min) min = sc;
    }
    score[i] = ((float)sum - (float)max - (float)min) / (k - 2);
  }
  sort(score, score + n);
  for (int i = n - m; i < n; i++) {
    if (i != n - m) putchar(' ');
    printf("%.3f", score[i]);
  }
  free(score);
  return 0;
}