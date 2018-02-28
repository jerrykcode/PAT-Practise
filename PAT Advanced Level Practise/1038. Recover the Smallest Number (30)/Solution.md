# 1038. Recover the Smallest Number (30)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1038)
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Given a collection of number segments, you are supposed to recover the smallest number from them. For 
example, given {32, 321, 3214, 0229, 87}, we can recover many numbers such like 32-321-3214-0229-87 or 
0229-32-87-321-3214 with respect to different orders of combinations of these segments, and the smallest 
number is 0229-321-3214-32-87.



## Input Specification: 

Each input file contains one test case. Each case gives a positive integer N (<=10000) followed by N 
number segments. Each segment contains a non-negative integer of no more than 8 digits. All the numbers 
in a line are separated by a space.


## Output Specification: 

For each test case, print the smallest number in one line. Do not output leading zeros. 



## Sample Input:

5 32 321 3214 0229 87  

## Sample Output:

22932132143287  

## 题意与思路参考：

本题参考 [1038. Recover the Smallest Number (30) 柳婼 の blog]( https://www.liuchuo.net/archives/2303)


以下引用自 https://www.liuchuo.net/archives/2303 :

>“题目大意：给一些字符串，求它们拼接起来构成最小数字的方式
分析：贪心算法。让我们一起来见证cmp函数的强大之处！！\~\~\~\~不是按照字典序排列就可以的，必须保证两个字符串
构成的数字是最小的才行，所以cmp函数写成return a + b < b + a;的形式，保证它排列按照能够组成的最小数字的
形式排列。因为字符串可能前面有0，这些要移除掉（用s.erase(s.begin())就可以了\~\~嗯\~\~string如此神奇\~\~\~）。
输出拼接后的字符串即可。
注意：如果移出了0之后发现s.length() == 0了，说明这个数是0，那么要特别地输出这个0，否则会什么都不输出。”



## 代码：

[1038. Recover the Smallest Number (30).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1038.%20Recover%20the%20Smallest%20Number%20(30)/1038.%20Recover%20the%20Smallest%20Number%20(30).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <algorithm>

bool compare(string a, string b)
{
	return a + b < b + a;
}

int main()
{
	int n;
	cin >> n;
	string  *str = new string[n];
	for (int i = 0; i < n; i++)
		cin >> str[i];
	sort(str, str + n, compare);
	string result = "";
	for (int i = 0; i < n; i++)
		result += str[i];
	while (result.length() != 0 && result[0] == '0')
		result.erase(result.begin());
	if (result.length() == 0)
		cout << 0;
	else cout << result;
    return 0;
}
```
