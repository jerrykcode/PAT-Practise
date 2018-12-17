# L3-015 球队“食物链” （30 分）

[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805048175869952)


>作者: 李文新
单位: 北京大学
时间限制: 2000 ms
内存限制: 128 MB
代码长度限制: 16 KB


某国的足球联赛中有N支参赛球队，编号从1至N。联赛采用主客场双循环赛制，参赛球队两两之间在双方主场各赛一场。 
联赛战罢，结果已经尘埃落定。此时，联赛主席突发奇想，希望从中找出一条包含所有球队的“食物链”，来说明联赛的精彩程度。“食物链”为一个1至N的排列{T1 T2 T3 … Tn}，满足：球队T1战胜过球队T2，球队T2战胜过球队T3，… ，球队T(N-1)战胜过球队TN，球队TN战胜过球队T1。 
现在主席请你从联赛结果中找出“食物链”。若存在多条“食物链”，请找出字典序最小的。 
注：排列{ a1 a2 … an }在字典序上小于排列{ b1 b2 … bn }，当且仅当存在整数K（1≤K≤N），满足: ak < bk且对于任意小于K的正整数i, ai = bi。 
## 输入格式： 
输入第一行给出一个整数N（2≤N≤20），为参赛球队数。随后N行，每行N个字符，给出了N×N的联赛结果表，其中第i行第j列的字符为球队i在主场对阵球队j的比赛结果：W表示球队i战胜球队j，L表示球队i负于球队j，D表示两队打平，- 表示无效（当i=j时）。输入中无多余空格。 
## 输出格式： 
按题目要求找到“食物链” T1 T2 … TN ，将这N个数依次输出在一行上，数字间以1个空格分隔，行的首尾不得有多余空格。若不存在“食物链”，输出“No Solution”。 
## 输入样例1： 
5   
-LWDW   
W-LDW   
WW-LW   
DWW-W   
DDLW-   
## 输出样例1： 
1 3 5 4 2   
## 输入样例2： 
5   
-WDDW   
D-DWL   
DD-DW   
DDW-D   
DDDD-   
## 输出样例2： 
No Solution  


## 思路

DFS + 剪枝

DFS中，若"食物链"外未选取的球队，没有一个赢过食物链中的第1个球队，则剪枝。

## 代码

[L3-015 球队“食物链” （30 分）.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L3-015%20%E7%90%83%E9%98%9F%E2%80%9C%E9%A3%9F%E7%89%A9%E9%93%BE%E2%80%9D%20%EF%BC%8830%20%E5%88%86%EF%BC%89/L3-015%20%E7%90%83%E9%98%9F%E2%80%9C%E9%A3%9F%E7%89%A9%E9%93%BE%E2%80%9D%20%EF%BC%8830%20%E5%88%86%EF%BC%89.cpp)


```cpp
#include <iostream>
using namespace std;
#include <vector>

#define WIN(Ti, Tj) (graph[Ti][Tj] == 'W' || graph[Tj][Ti] == 'L')

char **graph;

bool dfs(int start, vector<int>& chain, bool *collected, int n) {
	int size = (int)chain.size();
	int chainLastTeam = chain[size - 1]; //chain is never empty in this function
	if (size == n) {
		if (WIN(chainLastTeam, start)) return true;
	}
	bool flag = true;
	for (int team = 0; team < n; team++)
		if (!collected[team])
			if (WIN(team, start)) {
				flag = false;
				break;
			}
	if (flag) return false;
	for (int team = 0; team < n; team++) {
		if (!collected[team] && WIN(chainLastTeam, team)) {
			chain.push_back(team);
			collected[team] = true;
			if (dfs(start, chain, collected, n)) return true;
			chain.pop_back();
			collected[team] = false;
		}
	}
	return false;
}

int main()
{
	int n;
	cin >> n;
	graph = new char *[n];
	for (int i = 0; i < n; i++) {
		graph[i] = new char[n];
		for (int j = 0; j < n; j++)
			cin >> graph[i][j];
	}
	vector<int> chain;
	bool *collected = new bool[n];
	fill(collected, collected + n, false);
	for (int team = 0; team < n; team++) {
		chain.push_back(team);
		collected[team] = true;
		if (dfs(team, chain, collected, n)) break;
		chain.pop_back();
		collected[team] = false;
	}
	free(collected);
	for (int i = 0; i < n; i++) {
		free(graph[i]);
	}
	free(graph);
	if (chain.empty()) {
		cout << "No Solution" << endl;
	}
	else {
		for (auto it = chain.begin(); it != chain.end(); it++) {
			if (it != chain.begin()) putchar(' ');
			cout << (*it) + 1;
		}
		cout << endl;
	}
	return 0;
}

```