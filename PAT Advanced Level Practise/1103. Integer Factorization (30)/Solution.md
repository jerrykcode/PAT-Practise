# 1103. Integer Factorization (30)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1103)

* 时间限制 1200 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B


* 判题程序 Standard 

* 作者 CHEN, Yue



The K-P factorization of a positive integer N is to write N as the sum of the P-th power of K positive integers. You are supposed to write a program to find the K-P factorization of N for any positive integers N, K and P.

## Input Specification: 

Each input file contains one test case which gives in a line the three positive integers N (<=400), K (<=N) and P (1<P<=7). The numbers in a line are separated by a space.

## Output Specification: 

For each case, if the solution exists, output in the format:

N = n1^P + ... nK^P 

where ni (i=1, ... K) is the i-th factor. All the factors must be printed in non-increasing order.

Note: the solution may not be unique. For example, the 5-2 factorization of 169 has 9 solutions, such as 122 + 42 + 22 + 22 + 12, or 112 + 62 + 22 + 22 + 22, or more. You must output the one with the maximum sum of the factors. If there is a tie, the largest factor sequence must be chosen -- sequence { a1, a2, ... aK } is said to be larger than { b1, b2, ... bK } if there exists 1<=L<=K such that ai=bi for i<L and aL>bL 

If there is no solution, simple output "Impossible". 
## Sample Input 1:  
169 5 2  

## Sample Output 1:

169 = 6^2 + 6^2 + 6^2 + 6^2 + 5^2  

## Sample Input 2:

169 167 3  

## Sample Output 2:  

Impossible    

## 题意：


输入正整数N、K、P，求N分解成K个整数的P次方相加的因式，多个答案则取K个因子之和最大的，仍有多个答案则取因数字典序最大的


## 思路1: 

N由K个因数的P次方组成，故因数不可能大于N/K，从N/K开始试探，试探时确定一个因数之后，组合中剩下的因数只能小于等于它，在因数和相同时先试探到的组合字典序更大。



## 代码1：

[1103. Integer Factorization (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1103.%20Integer%20Factorization%20(30)/1103.%20Integer%20Factorization%20(30).cpp)

```cpp
#include <iostream>
using namespace std;
#include <vector>
#include <math.h>

vector<int> best;
int max_factor_sum = 0;
vector<int> tmp;
int n, k, p;

void dfs(int factor, int factor_sum,int sum, int level) {
	if (sum > n) return;
	if (level == k) {
		if (sum != n) return;
		if (factor_sum > max_factor_sum) {
			best = tmp;
			max_factor_sum = factor_sum;
		}
		return;
	}
	for (int i = factor; i >= 1; i--) {
		tmp.push_back(i);
		dfs(i, factor_sum + i,sum + pow(i, p),  level + 1);
		tmp.pop_back();
	}
}

int main()
{
	cin >> n >> k >> p;
	dfs(n/k, 0, 0, 0);
	if (best.size() == 0) {
		cout << "Impossible";
		return 0;
	}
	printf("%d = ", n);
	for (auto it = best.begin(); it != best.end(); it++) {
		if (it != best.begin()) printf(" + ");
		printf("%d^%d", *it, p);
	}
}
```


## 思路2：

本思路参考[柳婼 の blog Integer Factorization (30)-PAT甲级真题](https://www.liuchuo.net/archives/2451)

从0开始，把整数i的p次方存储在vector中，i递增直到i的p次方大于n，这些i的p次方（除0外）都是可能的因子的p次方。DFS深度优先试探每种K个因子的组合方式，对于组合起来因子的p次方之和等于n的，则这是一个可能的组合，若这些因子之和更大，则更新此组合为最佳组合（最佳组合初始化为空vector，最大的因子和初始化为0）。DFS时先试探最大的因子，这样先得到的组合的字典序更大。确定一个因子，试探下一个时只考虑小于等于此因子的，以避免重复（eg：因子为1，2，3，K = 2，先试探3\^p + 3\^p，然后3\^p + 2\^p，... ，到2时开始试探2\^p +2\^p，不要重复2\^p + 3\^p）


## 参考：

[柳婼 の blog Integer Factorization (30)-PAT甲级真题](https://www.liuchuo.net/archives/2451)


## 代码2：


[1103. Integer Factorization (30)_2.cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1103.%20Integer%20Factorization%20(30)/1103.%20Integer%20Factorization%20(30)_2.cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>
#include <math.h>

vector<int> factors;
vector<int> bestPath;
vector<int> currentPath;
int n, k, p, maxFace = 0;

void init()
{
	for (int i = 0; i <= n; i++) {
		int factor = pow(i, p);
		if (factor > n) break;
		factors.push_back(factor);
	}
}

void dfs(int index, int level, int sum, int face)
{
	if (level == k) {
		if (sum == n && face > maxFace) {
			bestPath = currentPath;
			maxFace = face;
		}
		return;
	}
	if (sum >= n) return;
	for (int i = 0; index - i > 0; i++) {
		currentPath.push_back(index - i);
		dfs(index - i, level + 1, sum + factors[index - i], face + index - i);
		currentPath.pop_back();
	}
}

int main()
{
	cin >> n >> k >> p;
	init();
	dfs(factors.size() - 1, 0, 0, 0);
	if (maxFace == 0) {
		printf("Impossible\n");
		return 0;
	}
	printf("%d = ", n);
	for (auto it = bestPath.begin(); it != bestPath.end(); it++) {
		if (it != bestPath.begin()) printf(" + ");
		printf("%d^%d", *it, p);
	}
    return 0;
}
```