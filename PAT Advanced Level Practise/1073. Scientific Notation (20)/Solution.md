# 1073. Scientific Notation (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1073)
* 时间限制 100 ms
* 内存限制 65536 kB
* 代码长度限制 16000 B
* 判题程序 Standard
* 题目作者 HOU, Qiming
Scientific notation is the way that scientists easily handle very large numbers or very small numbers. The notation matches the regular expression [+-][1-9]"."[0-9]+E[+-][0-9]+ which means that the integer portion has exactly one digit, there is at least one digit in the fractional portion, and the number and its exponent's signs are always provided even when they are positive.

Now given a real number A in scientific notation, you are supposed to print A in the conventional notation while keeping all the significant figures.

## Input Specification:

Each input file contains one test case. For each case, there is one line containing the real number A in scientific notation. The number is no more than 9999 bytes in length and the exponent's absolute value is no more than 9999.

## Output Specification:

For each test case, print in one line the input number A in the conventional notation, with all the significant figures kept, including trailing zeros,

## Sample Input 1:
+1.23400E-03  
## Sample Output 1:
0.00123400  
## Sample Input 2:
-1.2E+10  
## Sample Output 2:
-12000000000  

## 代码：

[1073. Scientific Notation (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1073.%20Scientific%20Notation%20(20)/1073.%20Scientific%20Notation%20(20).cpp)

```cpp
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
```