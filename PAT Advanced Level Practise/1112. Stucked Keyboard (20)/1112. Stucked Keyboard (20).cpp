#include <iostream>
using namespace std;
#include <string>

int main()
{
	int k;
	string input;
	cin >> k >> input;
	int flag[256];
	fill(flag, flag + 256, 1);
	int j;
	for (int i = 0; i < input.length(); i += j) {
		if (i + k > input.length()) {
			flag[(int)input[i]] = 0;
			j = 1;
			continue;
		}
		for (j = 1; j < k; j++)
			if (input[i + j] != input[i]) {
				flag[(int)input[i]] = 0;
				break;
			}
	}
	for (int i = 0; i < input.length(); i++) 
		if (flag[(int)input[i]] == 1) {
			cout << input[i];
			flag[(int)input[i]] = 2;
		}
	cout << endl;
	for (int i = 0; i < input.length(); i++) {
		cout << input[i];
		if (flag[(int)input[i]] == 2) i += k - 1;
	}
	return 0;
}