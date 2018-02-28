# 1011. World Cup Betting (20)

* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



With the 2010 FIFA World Cup running, football fans the world over were becoming increasingly excited as 
the best players from the best teams doing battles for the World Cup trophy in South Africa. Similarly, 
football betting fans were putting their money where their mouths were, by laying all manner of World Cup bets.

Chinese Football Lottery provided a "Triple Winning" game. The rule of winning was simple: first select any 
three of the games. Then for each selected game, bet on one of the three possible results -- namely W for win, 
T for tie, and L for lose. There was an odd assigned to each result. The winner's odd would be the product of 
the three odds times 65%.

For example, 3 games' odds are given as the following:
 W    T    L  
*1.1  2.5  1.7*  
*1.2  3.0  1.6*  
*4.1  1.2  1.1*  


To obtain the maximum profit, one must buy W for the 3rd game, T for the 2nd game, and T for the 1st game. 
If each bet takes 2 yuans, then the maximum profit would be 
(4.1*3.0*2.5*65%-1)*2 = 37.98 yuans (accurate up to 2 decimal places).




## Input

Each input file contains one test case. Each case contains the betting information of 3 games. 
Each game occupies a line with three distinct odds corresponding to W, T and L.



## Output

For each test case, print in one line the best bet of each game, and the maximum profit accurate 
up to 2 decimal places. The characters and the number must be separated by one space.




Sample Input
1.1 2.5 1.7
1.2 3.0 1.6
4.1 1.2 1.1

Sample Output
T T W 37.98



## 题意：

已知3场比赛每一场的W、T、L的赔率，3场比赛中，每场选出最大的赔率，（设为a、b、c），则最大收益为：
(a*b*c*0.65 - 1)*2，求每场比赛的最大赔率是W、T还是L，以及最大收益（精确到2位小数）

## 思路：

收益profit初始化为1，每输入一场比赛的W、T、L赔率，找出最大赔率与profit相乘，并输出最大赔率是W、T还是L，
3场比赛输入完毕后，用公式计算收益(profit*0.65 - 1)*2，用%.2f输出


## 代码：

[1011. World Cup Betting (20).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1011.%20World%20Cup%20Betting%20(20)/1011.%20World%20Cup%20Betting%20(20).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	float profit = 1;
	for (int i = 0; i < 3; i++) {
		float max = 0;
		int maxj = 0;
		for (int j = 0; j < 3; j++) {
			float odd;
			cin >> odd;
			if (odd > max) {
				max = odd;
				maxj = j;
			}
		}
		profit *= max;
		switch (maxj) {
		case 0: {cout << "W"; break; }
		case 1: {cout << "T"; break; }
		case 2: {cout << "L"; break; }
		}
		cout << " ";
	}
	printf("%.2f", (profit*0.65 - 1) * 2);
    return 0;
}


```


