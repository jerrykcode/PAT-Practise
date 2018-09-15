#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

int main() 
{
	int n;
	scanf("%d", &n);
	int *statements = new int[n + 1];
	for (int i = 1; i <= n; i++)
		scanf("%d", statements + i);
	vector<int> liars;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++) {
			liars.clear();
			for (int k = 1; k <= n; k++) {
				if (statements[k] < 0) {
					if (0-statements[k] != i && 0-statements[k] != j) liars.push_back(k);
				} else {
					if (statements[k] == i || statements[k] == j) liars.push_back(k);
				}
			}
			if (liars.size() != 2) continue;
			if ((liars[0] == i || liars[0] == j) && (liars[1] != i && liars[1] != j)) {
				printf("%d %d\n", i, j);
				goto END;
			}
			else if ((liars[0] != i && liars[0] != j) && (liars[1] == i || liars[1] == j)) {
				printf("%d %d\n", i, j);
				goto END;
			}
		}
  printf("No Solution\n");
END:
	free(statements);
	return 0;
}
