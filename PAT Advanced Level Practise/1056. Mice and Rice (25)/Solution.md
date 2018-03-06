# 1056. Mice and Rice (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1056)
* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue


Mice and Rice is the name of a programming contest in which each programmer must write a piece of code to 
control the movements of a mouse in a given map. The goal of each mouse is to eat as much rice as possible 
in order to become a FatMouse.

First the playing order is randomly decided for NP programmers. Then every NG programmers are grouped in a 
match. The fattest mouse in a group wins and enters the next turn. All the losers in this turn are ranked 
the same. Every NG winners are then grouped in the next match until a final winner is determined.

For the sake of simplicity, assume that the weight of each mouse is fixed once the programmer submits his/her 
code. Given the weights of all the mice and the initial playing order, you are supposed to output the ranks 
for the programmers.



## Input Specification: 

Each input file contains one test case. For each case, the first line contains 2 positive integers: NP and NG 
(<= 1000), the number of programmers and the maximum number of mice in a group, respectively. If there are less 
than NG mice at the end of the player's list, then all the mice left will be put into the last group. The second 
line contains NP distinct non-negative numbers Wi (i=0,...NP-1) where each Wi is the weight of the i-th mouse 
respectively. The third line gives the initial playing order which is a permutation of 0,...NP-1 (assume that 
the programmers are numbered from 0 to NP-1). All the numbers in a line are separated by a space.



## Output Specification: 

For each test case, print the final ranks in a line. The i-th number is the rank of the i-th programmer, and 
all the numbers must be separated by a space, with no extra space at the end of the line. 



## Sample Input:

11 3  
25 18 0 46 37 3 19 22 57 56 10  
6 0 8 7 10 5 9 1 4 2 3  

## Sample Output:

5 5 5 2 5 5 5 3 1 3 5  



## 题意：

输入Np只老鼠的重量，以及枚举顺序。每Ng只老鼠为一组，每组中最重的进入下一轮比赛，直到找出最重的。每一轮
被淘汰的老鼠排名相同。求每只老鼠的名次


## 思路：

vector存储枚举顺序，按此枚举顺序，每Ng只老鼠中找到最重的，存入另一个vector中。用vector<int>数组存储每一轮
被淘汰的老鼠序号，则这一组中不是最重的都在这一轮被淘汰。递归直到枚举vector中只有一个元素。根据每一轮被淘汰
的老鼠序号及总共的轮数，求每只老鼠的名次（见代码注释）

## 代码：
[1056. Mice and Rice (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1056.%20Mice%20and%20Rice%20(25)/1056.%20Mice%20and%20Rice%20(25).cpp)
```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>

int ng, *mice; 
vector<int> *level; //每一轮被淘汰的老鼠序号

int contest(vector<int> permutation, int l)
{
	if (permutation.size() == 1) { //只有一个元素
		level[l].push_back(permutation[0]);
		return l;
	}
	int index = 0;
	vector<int>next; //进入下一轮比赛的老鼠序号
	while (index < permutation.size()) { //分组
		int max = permutation[index]; //这一组中最重的老鼠序号，初始化为按枚举顺序的这一组的第一只老鼠序号
		int count = 0;
		for (int i = 0; i < ng; i++) {
			if (index + i > permutation.size() - 1) break; //若这一组分不到ng只
			if (mice[permutation[index + i]] > mice[max]) max = permutation[index + i];
			count++; //这一组实际分到的老鼠数（最后一组可能不到ng只）
		}
		for (int i = 0; i < count; i++) { //遍历这一组老鼠序号
			if (permutation[index + i] == max) next.push_back(permutation[index + i]); //最重的进入下一轮
			else level[l].push_back(permutation[index + i]); //在这一轮被淘汰的
		}
		index += count; 
	}
	return contest(next, l + 1); //递归下一轮比赛，轮数l增1
}

int main()
{
	int np;
	cin >> np >> ng;
	mice = new int[np];
	level = new vector<int>[np];
	vector<int> permutation(np); //枚举顺序
	for (int i = 0; i < np; i++) cin >> mice[i];
	for (int i = 0; i < np; i++) cin >> permutation[i];
	int l = contest(permutation, 0); //比赛
	int count = 1, tmp = 1;
	int *rank = new int[np]; //名次
	for (int i = l; i >= 0; i--) {//分层遍历
		for (auto it = level[i].begin(); it != level[i].end(); it++) {
			rank[*it] = tmp; //同一层的老鼠排名相同
			count++;
		}
		tmp = count;
	}
	for (int i = 0; i < np; i++) {
		if (i != 0) putchar(' ');
		cout << rank[i];
	}
    return 0;
}
```
