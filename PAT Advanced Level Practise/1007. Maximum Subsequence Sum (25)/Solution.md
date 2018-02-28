# 1007. Maximum Subsequence Sum (25)

* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue


Given a sequence of K integers { N1, N2, ..., NK }. A continuous subsequence is defined to be { Ni, Ni+1, ..., Nj } 
where 1 <= i <= j <= K. The Maximum Subsequence is the continuous subsequence which has the largest sum of its 
elements. For example, given sequence { -2, 11, -4, 13, -5, -2 }, its maximum subsequence is { 11, -4, 13 } with 
the largest sum being 20.
Now you are supposed to find the largest sum, together with the first and the last numbers of the maximum subsequence. 



## Input Specification: 

Each input file contains one test case. Each case occupies two lines. The first line contains a positive integer K (<= 10000). 
The second line contains K numbers, separated by a space. 


## Output Specification: 

For each test case, output in one line the largest sum, together with the first and the last numbers of the maximum subsequence. 
The numbers must be separated by one space, but there must be no extra space at the end of a line. In case that the maximum 
subsequence is not unique, output the one with the smallest indices i and j (as shown by the sample case). If all the K numbers 
are negative, then its maximum sum is defined to be 0, and you are supposed to output the first and the last numbers of the 
whole sequence.


 
## Sample Input:
10
-10 1 2 3 4 -5 -23 3 7 -21

## Sample Output:
10 1 4




## 题意：

已知K个整数，{N1，N2，... ，Nk}，定义{Ni， N(i+1)，... ，Nj}为子列，Ni + N(i+1) + ... + Nj为子列和，求最大子列和，及该子列的起始
数字Ni及结尾数字Nj

## 思路：

初始化最大子列和max = -1，当前子列和current = 0，最大子列和起始下标maxi = 结束下标maxj = 0，当前子列和起始下标i = 结束下标j = 0，
输入整数存储在数组arr中，对每一个整数arr[m]，current += arr[m]，若current < 0，则current更新为0，i = j = m + 1，若current > max，
则max更新为current，maxi和maxj更新为i和j，只要current >= 0便j++，循环每个整数后，若max == -1，输出0，arr[0]，arr[K - 1]，否则输出
max，arr[maxi]，arr[maxj]


## 代码：

[1007. Maximum Subsequence Sum (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1007.%20Maximum%20Subsequence%20Sum%20(25)/1007.%20Maximum%20Subsequence%20Sum%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int K;
	cin >> K;
	int *arr = new int[K];
	int max = -1, current = 0, maxi = 0, maxj = 0, i = 0, j = 0;/* initialize */
	for (int m = 0; m < K; m++) {
		cin >> arr[m];
		current += arr[m];
		if (current < 0) {
			current = 0;
			i = j = m + 1;
			continue;//j will not increase
		}
		else if (current > max) {
			max = current;
			maxi = i;
			maxj = j;
		}
		j++;
	}
	if (max == -1)
		cout << "0 " << arr[0] << " " << arr[K - 1];
	else
		cout << max << " " << arr[maxi] << " " << arr[maxj];
    return 0;
}
```