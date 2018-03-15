# 1112. Stucked Keyboard (20)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1112)

* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard

* 题目作者 CHEN, Yue


On a broken keyboard, some of the keys are always stucked. So when you type some sentences, the characters corresponding to those keys will appear repeatedly on screen for k times.

Now given a resulting string on screen, you are supposed to list all the possible stucked keys, and the original string.

Notice that there might be some characters that are typed repeatedly. The stucked key will always repeat output for a fixed k times whenever it is pressed. For example, when k=3, from the string "thiiis iiisss a teeeeeest" we know that the keys "i" and "e" might be stucked, but "s" is not even though it appears repeatedly sometimes. The original string could be "this isss a teest".

## Input Specification:

Each input file contains one test case. For each case, the 1st line gives a positive integer k ( 1<k<=100 ) which is the output repeating times of a stucked key. The 2nd line contains the resulting string on screen, which consists of no more than 1000 characters from {a-z}, {0-9} and "_". It is guaranteed that the string is non-empty.

## Output Specification:

For each test case, print in one line the possible stucked keys, in the order of being detected. Make sure that each key is printed once only. Then in the next line print the original string. It is guaranteed that there is at least one stucked key.

## Sample Input:

3  
caseee1__thiiis_iiisss_a_teeeeeest  

## Sample Output:

ei  
case1__this_isss_a_teest  


## 题意: 

一个键盘有一些卡住(Stucked)的键，按它们的时候，对应的值会重复K次，输入K与一个显示出的字符串，求可能被卡住的键，并输出原来不卡住时的字符串。

## 思路：

遍历字符串时无法确定卡住的键，但可以确定一定没有卡住的键。用数组 int flag[256] 标记每一个字符，初始化为1，遍历字符串时，若一个字符的后K个字符中有与它不相同的，则此字符一定没有卡住，设此字符后K个字符中第j个字符与它不相同，则 i += j(对于后面K个字符都与它相同的，则 j = K，相当于 i += K)，若一个字符后面没有K个字符了，则也一定没有卡住，对于一定没有卡住的字符，flag标记为0，再次遍历字符串，输出flag标记为1的(可能卡住的)，并更新其flag标记为2，以避免重复，最后再遍历字符串，输出字符，对于flag标记为2的，则跳过后面K个字符。


## 代码：

[1112. Stucked Keyboard (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1112.%20Stucked%20Keyboard%20(20)/1112.%20Stucked%20Keyboard%20(20).cpp)

```cpp
#include <iostream>
using namespace std;
#include <string>

int main()
{
	int k;
	string input;
	cin >> k >> input;
	int flag[256];
	fill(flag, flag + 256, 1);
	int j;
	for (int i = 0; i < input.length(); i += j) {
		if (i + k > input.length()) {
			flag[(int)input[i]] = 0;
			j = 1;
			continue;
		}
		for (j = 1; j < k; j++)
			if (input[i + j] != input[i]) {
				flag[(int)input[i]] = 0;
				break;
			}
	}
	for (int i = 0; i < input.length(); i++) 
		if (flag[(int)input[i]] == 1) {
			cout << input[i];
			flag[(int)input[i]] = 2;
		}
	cout << endl;
	for (int i = 0; i < input.length(); i++) {
		cout << input[i];
		if (flag[(int)input[i]] == 2) i += k - 1;
	}
	return 0;
}
```