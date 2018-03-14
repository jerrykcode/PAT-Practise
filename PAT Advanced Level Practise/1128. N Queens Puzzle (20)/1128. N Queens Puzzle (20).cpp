# include <iostream>
using namespace std;

int main()
{
	int k, n;
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> n;
		int *queensRow = new int[n];
		int flag = 0;
		for (int j = 0; j < n; j++) {
			cin >> queensRow[j];
			if (flag) continue;
			for (int m = 0; m < j; m++) {
				if (queensRow[m] == queensRow[j]) {
					flag = 1;
					break;
				}
				if (abs(queensRow[j] - queensRow[m]) == abs(j - m)) {
					flag = 1;
					break;
				}
			}
		}
		cout << (flag ? "NO" : "YES") << endl;
	}
	return 0;
}