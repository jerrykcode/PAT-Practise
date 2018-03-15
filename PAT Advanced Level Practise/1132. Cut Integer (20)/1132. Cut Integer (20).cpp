#include <iostream>
using namespace std;
#include <string>

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string input;
		cin >> input;
		string s1 = "", s2 = "";
		int k = input.length() / 2;
		for (int i = 0; i < k; i++)
			s1 += input[i];
		for (int i = k; i < input.length(); i++)
			s2 += input[i];
		int z = atoi(input.c_str());
		int a = atoi(s1.c_str());
		int b = atoi(s2.c_str());
		if (a * b == 0) {
			cout << "No";
		}
		else cout << (z % (a*b) == 0 ? "Yes" : "No");
		cout << endl;
	}
	return 0;
}