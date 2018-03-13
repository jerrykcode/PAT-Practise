# 1124. Raffle for Weibo Followers (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1124)


* 时间限制 400 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



John got a full mark on PAT. He was so happy that he decided to hold a raffle（抽奖） for his followers on Weibo -- that is, he would select winners from every N followers who forwarded his post, and give away gifts. Now you are supposed to help him generate the list of winners.

## Input Specification: 

Each input file contains one test case. For each case, the first line gives three positive integers M (<= 1000), N and S, being the total number of forwards, the skip number of winners, and the index of the first winner (the indices start from 1). Then M lines follow, each gives the nickname (a nonempty string of no more than 20 characters, with no white space or return) of a follower who has forwarded John's post.

Note: it is possible that someone would forward more than once, but no one can win more than once. Hence if the current candidate of a winner has won before, we must skip him/her and consider the next one.

## Output Specification: 

For each case, print the list of winners in the same order as in the input, each nickname occupies a line. If there is no winner yet, print "Keep going..." instead. 
## Sample Input 1:  
9 3 2  
Imgonnawin!  
PickMe  
PickMeMeMeee  
LookHere  
Imgonnawin!  
TryAgainAgain  
TryAgainAgain  
Imgonnawin!  
TryAgainAgain  

## Sample Output 1:  
PickMe  
Imgonnawin!  
TryAgainAgain  

## Sample Input 2:  
2 3 5  
Imgonnawin!  
PickMe  

## Sample Output 2:  
Keep going...  

## 题意：

微博抽奖，在M个转发中，每N个中的第S个为中奖者，但每人不管转发了几次最多只能中奖一次，所以若一个人已中过奖，则应跳过他。输入M、N、S，与所有转发的人的昵称，输出所有中奖的人的昵称，若没有人中奖，则输出"Keep going...  "。

## 思路：

用map<string, int>判断一个人是否中过奖，i从1开始遍历输入昵称，当 i >= S && (i - S)%N == 0 时，第i个人即为某个N个人中的第S个，若此人没有中过奖，则输出他，否则i--,m-- ，跳过此人。


## 代码：


[1124. Raffle for Weibo Followers (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1124.%20Raffle%20for%20Weibo%20Followers%20(20)/1124.%20Raffle%20for%20Weibo%20Followers%20(20).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <map>

int main()
{
	int m, n, s;
	cin >> m >> n >> s;
	map<string, int>flag;
	int tag = 0;
	for (int i = 1; i <= m; i++) {
		string name;
		cin >> name;
		if (i >= s && (i - s) % n == 0) {
			if (flag[name] == 0) {
				cout << name << endl;
				tag = 1;
				flag[name] = 1;
			}
			else {
				i--;
				m--;
			}
		}
	}
	if (tag == 0) cout << "Keep going..." << endl;
    return 0;
}
```
