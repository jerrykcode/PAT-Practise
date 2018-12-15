#include <iostream>
using namespace std;
#include <string>

int main()
{
	int d, n;
	cin >> d >> n;
	string result = to_string(d);
	for (int i = 1; i < n; i++)
	{
		string tmp = "";
		for (int j = 0; j < result.length();)
		{
			tmp += result[j];
			int k;
			for ( k = j + 1; k < result.length() && result[k] == result[j]; k++);
			tmp += to_string(k - j);
			j = k;
		}
		result = tmp;
	}
	cout << result << endl;
	return 0;
}