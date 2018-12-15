#include <iostream>
using namespace std;
#include <math.h>

int nextPrime(int n)
{
	if (n <= 2) return 2;
	if (n == 3) return 3;
	int p = (n % 2) ? n : n + 1;
	while (1) {
		int i;
		for (i = (int)sqrt(p); i > 2; i --)
			if (!(p % i))
				break;
		if (i == 2)
			return p;
		else
			p += 2;
	}
}


int main()
{
	int m, n;
	cin >> m >> n;
	int size = nextPrime(m);
	int *hashTable = new int[size];
	fill(hashTable, hashTable + size, 0);
	for (int i = 0; i < n; i++) {
		int key;
		cin >> key;
		int flag = 0;
		for (int increment = 0; increment < size; increment++) {
			int pos = key + pow(increment, 2);
			pos %= size;
			if (hashTable[pos] == 0) {
				hashTable[pos] = 1;
				if (i != 0) putchar(' ');
				cout << pos;
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			if (i != 0) putchar(' ');
			cout << "-";
		}
	}
	return 0;
}
