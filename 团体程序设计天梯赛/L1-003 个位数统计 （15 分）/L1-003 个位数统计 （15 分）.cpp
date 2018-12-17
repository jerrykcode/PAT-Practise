#include <iostream>
#include <string>
using namespace std;

int main()
{
	string str;
	cin >> str;
	int num[10] = { 0 }; //0 ~ 9
	for (int i = 0; i < str.length(); i++)
		num[(int)str[i] - (int)('0')]++;
	for (int i = 0; i < 10; i++)
		if (num[i]) {
			cout << i << ":" << num[i] << endl;
		}
	return 0;
}