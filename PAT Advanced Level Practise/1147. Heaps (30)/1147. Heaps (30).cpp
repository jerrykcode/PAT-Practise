#include <iostream>
using namespace std;
typedef int h_type;
#define MAX 1
#define MIN 0

bool isHeap(int *tree, int root, int n, h_type flag)
{
	int left = root * 2 + 1, right = left + 1;
	if (left < n) {
		if (flag == MAX && tree[root] < tree[left]) return false;
		if (flag == MIN && tree[root] > tree[left]) return false;
		if (!isHeap(tree, left, n, flag))return false;
	}
	if (right < n) {
		if (flag == MAX && tree[root] < tree[right]) return false;
		if (flag == MIN && tree[root] > tree[right]) return false;
		if (!isHeap(tree, right, n, flag))return false;
	}
	return true;
}

void post(int *tree, int root, int n)
{
	int left = root * 2 + 1, right = left + 1;
	if (left < n) {
		post(tree, left, n);
		putchar(' ');
	}
	if (right < n) {
		post(tree, right, n);
		putchar(' ');
	}
	printf("%d", tree[root]);
}

int main()
{
	int m, n;
	cin >> m >> n;
	int *tree = new int[n];
	for (int i = 0; i < m; i++) {
		for (int i = 0; i < n; i++) cin >> tree[i];
		if (isHeap(tree, 0, n, MAX)) printf("Max Heap\n");
		else if (isHeap(tree, 0, n, MIN)) printf("Min Heap\n");
		else printf("Not Heap\n");
		post(tree, 0, n);
		cout << endl;
	}
    return 0;
}

