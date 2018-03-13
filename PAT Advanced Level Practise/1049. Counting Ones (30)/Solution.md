# 1049. Counting Ones (30)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1049)
* 时间限制 100 ms
* 内存限制 65536 kB
* 代码长度限制 16000 B
* 判题程序 Standard
* 题目作者 CHEN, Yue
The task is simple: given any positive integer N, you are supposed to count the total number of 1's in the decimal form of the integers from 1 to N. For example, given N being 12, there are five 1's in 1, 10, 11, and 12.

## Input Specification:

Each input file contains one test case which gives the positive N (<=230).

## Output Specification:

For each test case, print the number of 1's in one line.

## Sample Input:
12
## Sample Output:
5

## 思路：

本题参考：[1049. Counting Ones (30) (柳婼 の blog)](https://www.liuchuo.net/archives/2305)

## 代码：

[1049. Counting Ones (30)](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1049.%20Counting%20Ones%20(30)/1049.%20Counting%20Ones%20(30).cpp)

```cpp
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
```