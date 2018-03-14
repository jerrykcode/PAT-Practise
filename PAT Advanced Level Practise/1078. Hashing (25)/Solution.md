# 1078. Hashing (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1078)
* 时间限制 100 ms
* 内存限制 65536 kB
* 代码长度限制 16000 B
* 判题程序 Standard
* 题目作者 CHEN, Yue
The task of this problem is simple: insert a sequence of distinct positive integers into a hash table, and output the positions of the input numbers. The hash function is defined to be "H(key) = key % TSize" where TSize is the maximum size of the hash table. Quadratic probing (with positive increments only) is used to solve the collisions.

Note that the table size is better to be prime. If the maximum size given by the user is not prime, you must re-define the table size to be the smallest prime number which is larger than the size given by the user.

## Input Specification:

Each input file contains one test case. For each case, the first line contains two positive numbers: MSize (<=104) and N (<=MSize) which are the user-defined table size and the number of input numbers, respectively. Then N distinct positive integers are given in the next line. All the numbers in a line are separated by a space.

## Output Specification:

For each test case, print the corresponding positions (index starts from 0) of the input numbers in one line. All the numbers in a line are separated by a space, and there must be no extra space at the end of the line. In case it is impossible to insert the number, print "-" instead.

## Sample Input:
4 4  
10 6 4 15  
## Sample Output:
0 1 4 -  

## 题意与思路: 

散列表,平方探测法

## 代码: 
[1078. Hashing (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1078.%20Hashing%20(25)/1078.%20Hashing%20(25).cpp)
```cpp
#include <iostream>
using namespace std;
#include <math.h>

int nextPrime(int n)
{
	if (n <= 2) return 2;
	if (n == 3) return 3;
	int p = (n % 2) ? n : n + 1;
	while (1) {
		int i;
		for (i = (int)sqrt(p); i > 2; i --)
			if (!(p % i))
				break;
		if (i == 2)
			return p;
		else
			p += 2;
	}
}


int main()
{
	int m, n;
	cin >> m >> n;
	int size = nextPrime(m);
	int *hashTable = new int[size];
	fill(hashTable, hashTable + size, 0);
	for (int i = 0; i < n; i++) {
		int key;
		cin >> key;
		int flag = 0;
		for (int increment = 0; increment < size; increment++) {
			int pos = key + pow(increment, 2);
			pos %= size;
			if (hashTable[pos] == 0) {
				hashTable[pos] = 1;
				if (i != 0) putchar(' ');
				cout << pos;
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			if (i != 0) putchar(' ');
			cout << "-";
		}
	}
	return 0;
}
```