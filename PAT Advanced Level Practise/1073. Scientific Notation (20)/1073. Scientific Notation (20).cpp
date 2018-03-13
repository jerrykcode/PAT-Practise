#include <iostream>
using namespace std;
#include <string>

int main()
{
	string input;
	cin >> input;
	if (input[0] == '-') cout << "-";
	string digit = "";
	int a = 0, flag = 0, pos = 0;
	int i;
	for (i = 1; i < input.length(); i++) {
		if (input[i] == 'E') break;
		if (input[i] == '.') {
			pos = i;
			flag = 1;
			continue;
		}
		digit += input[i];
		if (flag == 1) a++;
	}
	flag = 0;
	for (int j = 0; j < digit.length(); j++)
		if (digit[j] != '0') {
			flag = 1;
			break;
		}
	if (flag == 0) {
		cout << "0" << endl;
		return 0;
	}
	int e = atoi(input.substr(i + 1, input.length() - i - 1).c_str());
	if (e == 0) {
		for (int i = 1; i < input.length() && input[i] != 'E'; i++) 
			cout << input[i];
		return 0;
	}
	else if (e < 0) {
		for (int j = 0; j < -1 * (e + 1); j++)
			digit = "0" + digit;
		digit = "0." + digit;
	}
	else {
		for (int j = 0; j < e - a; j++)
			digit = digit + "0";
		if (e - a < 0) {
			flag = 0;
			for (int j = 0; j < digit.length(); j++) {
				if (j == pos - 1 + e && flag == 0) {
					cout << ".";
					j--;
					flag = 1;
				}
				else cout << digit[j];
			}
			return 0;
		}
	}
	cout << digit << endl;
	return 0;
}