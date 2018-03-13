# 1101. Quick Sort (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1101)

* 时间限制 200 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 作者 CAO, Peng



There is a classical process named partition in the famous quick sort algorithm. In this process we typically choose one element as the pivot. Then the elements less than the pivot are moved to its left and those larger than the pivot to its right. Given N distinct positive integers after a run of partition, could you tell how many elements could be the selected pivot for this partition?

For example, given N = 5 and the numbers 1, 3, 2, 4, and 5. We have:


* 1 could be the pivot since there is no element to its left and all the elements to its right are larger than it;

* 3 must not be the pivot since although all the elements to its left are smaller, the number 2 to its right is less than it as well;

* 2 must not be the pivot since although all the elements to its right are larger, the number 3 to its left is larger than it as well;

* and for the similar reason, 4 and 5 could also be the pivot.

Hence in total there are 3 pivot candidates.

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N (<= 105). Then the next line contains N distinct positive integers no larger than 109. The numbers in a line are separated by spaces.

## Output Specification: 

For each test case, output in the first line the number of pivot candidates. Then in the next line print these candidates in increasing order. There must be exactly 1 space between two adjacent numbers, and no extra space at the end of each line.
## Sample Input: 
5  
1 3 2 4 5  

## Sample Output:
3  
1 4 5  

## 题意：


快速排序选取主元需要：主元之前的元素比主元小，之后的元素比主元大。输入N个互不相同的整数，构成一个序列，求序列中的那些元素可以作为主元？


## 思路：

int 数组 list 存储序列。若 list[0] ~ list[i - 1] 均小于 list[i] 而 list[i + 1] ~ list[n - 1] 均大于 list[i]，则 list[i] 为一个主元。

用 int 数组 max、min，max[i] 表示从 list[0] 到 list[i] 中最大的元素，min[i] 表示从 list[i] 到 list[n - 1] 中最小的元素，则有：

* ##### max[i] = 
    * list[0] , i = 0
    * list[i] > max[i - 1] ? list[i] : max[i - 1] , i > 0
* ##### min[i] = 
    * list[n - 1] , i = n - 1
    * list[i] < min[i + 1] ? list[i] : min[i + 1] , i < n - 1

求出 max 与 min 之后，遍历 list，对于list[i]，若 i == 0 或者 list[i] > max[i - 1]，则 list[i] 比其之前的元素都大；若 i == n - 1 或者 list[i] < min[i + 1]，则 list[i] 比其之后的元素都小。满足上述两条件的 list[i] 为一个主元，将他放入vector中

最后输出 vector 的 size() 并遍历输出 vector

##### 注意：
测试点2一直格式错误，参考了[柳婼 の blog 1101. Quick Sort (25)-PAT甲级真题](https://www.liuchuo.net/archives/1917)
>格式错误。。（好像可以说明那个第2个测试点是0个主元？。。）然后——加了最后一句printf(“\n”);才正确。。（大部分测试用例结尾不输出换行符都可以通过。只有一个出现格式错误，是由于该测试点为特例，其结果为0。没有换行符其结果只有一行～）


所有输出后换行，然后答案正确

## 参考：
[柳婼 の blog 1101. Quick Sort (25)-PAT甲级真题](https://www.liuchuo.net/archives/1917)


## 代码：

[1101. Quick Sort (25)_2.cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1101.%20Quick%20Sort%20(25)/1101.%20Quick%20Sort%20(25)_2.cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>

int main()
{
	int n;
	cin >> n;
	int *list = new int[n];
	for (int i = 0; i < n; i++)
		cin >> list[i];
	int *max = new int[n]; //max[i] is the max number in [list[0], list[i]]
	max[0] = list[0];
	for (int i = 1; i < n; i++)
		max[i] = list[i] > max[i - 1] ? list[i] : max[i - 1];
	int *min = new int[n];
	min[n - 1] = list[n - 1]; //min[i] is the minmum number in [list[i], list[n - 1]]
	for (int i = n - 2; i >= 0; i--)
		min[i] = list[i] < min[i + 1] ? list[i] : min[i + 1];
	vector<int> pivots;
	for (int i = 0; i < n; i++) {
		if (i == 0 || list[i] > max[i - 1]) {
			if ( i == n - 1 || list[i] < min[i + 1])
				pivots.push_back(list[i]);
		}
	}
	cout << pivots.size() << endl;
	for (auto it = pivots.begin(); it != pivots.end(); it++) {
		if (it != pivots.begin()) putchar(' ');
		printf("%d", *it);
	}
	cout << endl;
    return 0;
}
```

 