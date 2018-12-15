#include <iostream>
using namespace std;
int main() {
	int n, left = 0, right = 0, a = 1, current = 1, result = 0;
	cin >> n;
	while (n / a) {
		left = n / (a * 10);
		current = (n / a) % 10;
		right = n % a;
		if (current == 0) result += left * a;
		else if (current == 1) result += left * a + right + 1;
		else result += (left + 1) * a;
		a *= 10;
	}
	cout << result;
	return 0;
}