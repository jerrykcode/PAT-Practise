# 1145. Hashing - Average Search Time (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1145)

* 时间限制 200 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



The task of this problem is simple: insert a sequence of distinct positive integers into a hash table first. Then try to find another sequence of integer keys from the table and output the average search time (the number of comparisons made to find whether or not the key is in the table). The hash function is defined to be "H(key) = key % TSize" where TSize is the maximum size of the hash table. Quadratic probing (with positive increments only) is used to solve the collisions.

Note that the table size is better to be prime. If the maximum size given by the user is not prime, you must re-define the table size to be the smallest prime number which is larger than the size given by the user.

## Input Specification: 

Each input file contains one test case. For each case, the first line contains two positive numbers: MSize, N, and M, which are the user-defined table size, the number of input numbers, and the number of keys to be found, respectively. All the three numbers are no more than 104. Then N distinct positive integers are given in the next line. All the numbers in a line are separated by a space and are no more than 105.

## Output Specification: 

For each test case, in case it is impossible to insert some number, print in a line "X cannot be inserted." where X is the input number. Finally print in a line the average search time for all the M keys, accurate up to 1 decimal place. 
## Sample Input:

4 5 4  
10 6 4 15 11  
11 4 15 2  

## Sample Output:

15 cannot be inserted.  
2.8  

## 思路：

散列表平方探测法


## 代码：

[1145. Hashing - Average Search Time (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1145.%20Hashing%20-%20Average%20Search%20Time%20(25)/1145.%20Hashing%20-%20Average%20Search%20Time%20(25).cpp)

```cpp
#include <iostream>
using namespace std;
#include <math.h>

int nextPrime(int n)
{
	if (n == 1) return 2;
	if (n <= 3) return n;
	int p = n % 2 ? n : n + 1;
	while (1) {
		int i;
		for (i = sqrt(p); i > 2; i--)
			if (p % i == 0) break;
		if (i == 2) return p;
		p += 2;
	}
}

int main()
{
	int msize, n, m, key;
	cin >> msize >> n >> m;
	int tsize = nextPrime(msize);
	int *hashtable = new int[tsize];
	fill(hashtable, hashtable + tsize, -1);
	for (int i = 0; i < n; i++) {
		cin >> key;
		int flag = 0, increment;
		for (increment = 0; increment < tsize; increment++) {
			int pos = key % tsize + increment * increment;
			if (pos >= tsize) pos %= tsize;
			if (hashtable[pos] == -1) {
				hashtable[pos] = key;
				flag = 1;
				break;
			}
		}
		if (!flag) printf("%d cannot be inserted.\n", key);
	}
	int total = 0;
	for (int i = 0; i < m; i++) {
		cin >> key;
		int increment;
		for (increment = 0; increment < tsize; increment++) {
			int pos = key % tsize + increment * increment;
			if (pos >= tsize) pos %= tsize;
			if (hashtable[pos] == key) 
				break;
			if (hashtable[pos] == -1)
				break;
		}
		total += increment + 1;
	}
	printf("%.1f\n",((float)total)/m);
    return 0;
}
```