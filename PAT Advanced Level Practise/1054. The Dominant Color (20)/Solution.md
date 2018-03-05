# 1054. The Dominant Color (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1054)
* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue


Behind the scenes in the computer's memory, color is always talked about as a series of 24 bits 
of information for each pixel. In an image, the color with the largest proportional area is called 
the dominant color. A strictly dominant color takes more than half of the total area. Now given an 
image of resolution M by N (for example, 800x600), you are supposed to point out the strictly 
dominant color.



## Input Specification: 

Each input file contains one test case. For each case, the first line contains 2 positive numbers: 
M (<=800) and N (<=600) which are the resolutions of the image. Then N lines follow, each contains 
M digital colors in the range [0, 224). It is guaranteed that the strictly dominant color exists for 
each input image. All the numbers in a line are separated by a space.



## Output Specification: 

For each test case, simply print the dominant color in a line.



## Sample Input:

5 3  
0 0 255 16777215 24  
24 24 0 0 24  
24 0 24 24 24  

## Sample Output:

24  


## 题意：

求M*N个整数中出现频率大于50%，即出现次数大于M*N/2的数

## 思路：

用map存储整数与出现次数的对应关系，每输入一个数，其对应的map值加1，若大于M*N/2则程序结束


## 代码：

[1054. The Dominant Color (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1054.%20The%20Dominant%20Color%20(20)/1054.%20The%20Dominant%20Color%20(20).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <map>

int main()
{
	int m, n, half, color;
	map<int, int> fre; //出现次数
	scanf("%d %d", &m, &n);
	half = n * m / 2;
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < m; j++) {
			scanf("%d", &color);
			fre[color]++;
			if (fre[color] > half) {
				printf("%d", color);
				return 0;
			}
		}
    return 0;
}
```
