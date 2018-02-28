# 1008. Elevator (20)

* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



The highest building in our city has only one elevator. A request list is made up with N positive numbers. 
The numbers denote at which floors the elevator will stop, in specified order. It costs 6 seconds to move 
the elevator up one floor, and 4 seconds to move down one floor. The elevator will stay for 5 seconds at each stop.

For a given request list, you are to compute the total time spent to fulfill the requests on the list. The 
elevator is on the 0th floor at the beginning and does not have to return to the ground floor when the 
requests are fulfilled.



## Input Specification: 

Each input file contains one test case. Each case contains a positive integer N, followed by N positive numbers. 
All the numbers in the input are less than 100.



## Output Specification: 

For each test case, print the total time on a single line. 



## Sample Input:
3 2 3 1

## Sample Output:
41


## 题意：

电梯上升一层需要6秒钟，下降一层需要4秒，在一层停留有5秒，电梯初始在第0层，输入电梯将要停留的楼层，求电梯到达最后
输入的楼层并停留后的总时间（电梯最后不用回到第0层）

## 思路：

初始化总时间total为0，电梯当前楼层current为0，对于将要停留的每一层f，若f > current（即f比current高），则total加上
（f - current）*6 + 5 （上升层数*6 + 停留时间），若f < current则total加上（current - f*4 + 5）（下降层数*4 + 停留时间）
若f == current，即电梯不上升也不下降，total加上停留时间5，最后current更新为f

## 代码：

[1008. Elevator (20).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1008.%20Elevator%20(20)/1008.%20Elevator%20(20).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;
	int current = 0;
	int totalTime = 0;
	for (int i = 0; i < N; i++) {
		int f;
		cin >> f;
		if (f > current) 
			totalTime += (f - current) * 6;
		else if (f < current) 
			totalTime += (current - f) * 4;
		totalTime += 5;
		current = f;
	}
	cout << totalTime;
    return 0;
}
```
