# 1023. Have Fun with Numbers (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1023)
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



Notice that the number 123456789 is a 9-digit number consisting exactly the numbers from 1 to 9, with 
no duplication. Double it we will obtain 246913578, which happens to be another 9-digit number consisting 
exactly the numbers from 1 to 9, only in a different permutation. Check to see the result if we double it 
again! 

Now you are suppose to check if there are more numbers with this property. That is, double a given number 
with k digits, you are to tell if the resulting number consists of only a permutation of the digits in the 
original number.



## Input Specification: 

Each input file contains one test case. Each case contains one positive integer with no more than 20 digits.



## Output Specification: 

For each test case, first print in a line "Yes" if doubling the input number gives a number that consists of 
only a permutation of the digits in the original number, or "No" if not. Then in the next line, print the 
doubled number.



## Sample Input:
1234567899  

## Sample Output:
Yes  
2469135798  


## 题意：

输入一个整数，判断其乘2后的值的所有字符是否都是原数中的字符的不同组合(整数的字符数不超过20)


## 思路：

用string number存储原数，vector<char> digits存储number中的每一个字符，string result存储乘2后的值，循环result
中每一个字符，若在digits中存在相同的字符则erase掉digits中的该字符，若digits中不存在相同的字符则输出"No\n"并
跳出循环，最后输出result

## 代码：
[1023. Have Fun with Numbers (20).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1023.%20Have%20Fun%20with%20Numbers%20(20)/1023.%20Have%20Fun%20with%20Numbers%20(20).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	string number, result= "";
	vector<char> digits;
	cin >> number;
	int k = 0;//进位
	for (int i = number.length() - 1; i >= 0; i--) {
		digits.push_back(number[i]);
		int n = ((int)number[i] - 48) * 2 + k;
		result = std::to_string(n % 10) + result;
		k = n / 10;
	}
	int flag = 0;
	if (k > 0) {
		cout << "No\n";
		result = std::to_string(k) + result;
		goto end;
	}
	for (int i = 0; i < result.length(); i++) {//判断result中的每一个字符是否为digits中的元素（无重复）
		flag = 0;
		for (vector<char>::iterator it = digits.begin(); it != digits.end(); it++) 
			if (result[i] == *it) {
				flag = 1;
				it = digits.erase(it);
				break;
			}
		if (!flag) {
			cout << "No\n";
			break;
		}
	}
	if (flag) cout << "Yes\n";
end:cout << result;
    return 0;
}
```
