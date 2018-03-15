# 1132. Cut Integer (20)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1132)

* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard

* 题目作者 CHEN, Yue


Cutting an integer means to cut a K digits long integer Z into two integers of (K/2) digits long integers A and B. For example, after cutting Z = 167334, we have A = 167 and B = 334. It is interesting to see that Z can be devided by the product of A and B, as 167334 / (167 x 334) = 3. Given an integer Z, you are supposed to test if it is such an integer.

## Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N (<= 20). Then N lines follow, each gives an integer Z (10<=Z<=2^31). It is guaranteed that the number of digits of Z is an even number.

## Output Specification:

For each case, print a single line "Yes" if it is such a number, or "No" if not.

## Sample Input:

3  
167334  
2333  
12345678  


## Sample Output:

Yes  
No  
No  

## 题意: 

正整数Z (10<=Z<=2^31) 有K(为偶数)个字符，前K/2个字符组成正整数a,后K/2个字符组成正整数b,若K % (a * b) == 0，则输出"Yes"，否则"No"。

## 代码：


[1132. Cut Integer (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1132.%20Cut%20Integer%20(20)/1132.%20Cut%20Integer%20(20).cpp)



```cpp
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
```