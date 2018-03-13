# 1029. Median (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1029)
* 时间限制 1000 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Given an increasing sequence S of N integers, the median is the number at the middle position. 
For example, the median of S1={11, 12, 13, 14} is 12, and the median of S2={9, 10, 15, 16, 17} 
is 15. The median of two sequences is defined to be the median of the nondecreasing sequence 
which contains all the elements of both sequences. For example, the median of S1 and S2 is 13.

Given two increasing sequences of integers, you are asked to find their median.



## Input

Each input file contains one test case. Each case occupies 2 lines, each gives the information 
of a sequence. For each sequence, the first positive integer N (<=1000000) is the size of that 
sequence. Then N integers follow, separated by a space. It is guaranteed that all the integers 
are in the range of long int.



## Output

For each test case you should output the median of the two given sequences in a line.



## Sample Input: 

4 11 12 13 14  
5 9 10 15 16 17  

## Sample Output:  

13  


## 题意：

对于一个递增序列，其中间位置的元素即为中位数，如S1={11, 12, 13, 14}的中位数为12，S2={9, 10, 15, 16, 17} 
的中位数为15，定义两个序列的中位数为包含这两个序列的所有元素的非递减序列的中位数，如S1与S2的中位数为13，

输入两个递增序列(序列的元素数量分别为N1，N2)，求这两个序列的中位数


## 思路：

用两个数组分别存储两个序列，归并到另一个数组中，在归并时当第(N1 + N2 - 1)/2个元素确定时即可输出中位数


## 代码：

[1029. Median (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1029.%20Median%20(25)/1029.%20Median%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int n1, n2, *s1, *s2;
	cin >> n1;
	s1 = new int[n1];
	for (int i = 0; i < n1; i++) //Inputs s1
		cin >> s1[i];
	cin >> n2;
	s2 = new int[n2];
	for (int i = 0; i < n2; i++) //Inputs s2
		cin >> s2[i];
	int i = 0, j = 0, *s = new int[n1 + n2];
	int index = 0;
	while (i < n1 && j < n2) { //归并s1、s2到s中
		if (s1[i] < s2[j])
			s[index] = s1[i++];
		else
			s[index] = s2[j++];
		if (index == (n1 + n2 - 1) / 2) { //index到达中位
			cout << s[index];
			return 0;
		}
		index++;
	}
	//s1或s2的剩余部分
	while (i < n1) { 
		s[index] = s1[i++];
		if (index == (n1 + n2 - 1) / 2) { //index到达中位
			cout << s[index];
			return 0;
		}
		index++;
	}
	while (j < n2) {
		s[index] = s2[j++];
		if (index == (n1 + n2 - 1) / 2) { //index到达中位
			cout << s[index];
			return 0;
		}
		index++;
	}

    return 0;
}

```
