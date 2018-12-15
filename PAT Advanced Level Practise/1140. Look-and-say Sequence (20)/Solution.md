# 1140. Look-and-say Sequence (20)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1140)

* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard

* 题目作者 CHEN, Yue

Look-and-say sequence is a sequence of integers as the following:

D, D1, D111, D113, D11231, D112213111, ...
where D is in [0, 9] except 1. The (n+1)st number is a kind of description of the nth number. For example, the 2nd number means that there is one D in the 1st number, and hence it is D1; the 2nd number consists of one D (corresponding to D1) and one 1 (corresponding to 11), therefore the 3rd number is D111; or since the 4th number is D113, it consists of one D, two 1's, and one 3, so the next number must be D11231. This definition works for D = 1 as well. Now you are supposed to calculate the Nth number in a look-and-say sequence of a given digit D.

## Input Specification:

Each input file contains one test case, which gives D (in [0, 9]) and a positive integer N (<=40), separated by a space.

## Output Specification:

Print in a line the Nth number in a look-and-say sequence of D.

## Sample Input:

1 8  

## Sample Output:

1123123111  

## 题意：

Look-and-say sequence:

eg:  

1为初始值，8次后的Look-and-say sequence: 

1  
1出现1次：  
11  
1出现2次：  
12  
1出现1次，2出现1次：  
1121  
1出现2次，2出现1次，1出现1次：  
122111  
1出现1次，2出现2次，1出现3次：  
112213  
1出现2次，2出现2次，1出现1次，3出现1次：  
12221131  
1出现1次，2出现3次，1出现2次，3出现1次，1出现1次：
1123123111  

输入D和N，求以D为初始值，N次后的"Look-and-say sequence"

## 思路：

string result存储结果，初始化为D的字符串形式，循环N - 1次，每次将result[j](j初始为0)存入另一个string tmp中，然后result往后，记录有多少个连续与result[j]相同的，将此数加到tmp后面，然后j更新为j之后第一个与result[j]不同的。

## 代码：

[1140. Look-and-say Sequence (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1140.%20Look-and-say%20Sequence%20(20)/1140.%20Look-and-say%20Sequence%20(20).cpp)

```cpp
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
```
