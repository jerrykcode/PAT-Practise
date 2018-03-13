# 1037. Magic Coupon (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1037)
* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



The magic shop in Mars is offering some magic coupons. Each coupon has an integer N printed on it, 
meaning that when you use this coupon with a product, you may get N times the value of that product 
back! What is more, the shop also offers some bonus product for free. However, if you apply a coupon 
with a positive N to this bonus product, you will have to pay the shop N times the value of the bonus 
product... but hey, magically, they have some coupons with negative N's! 

For example, given a set of coupons {1 2 4 -1}, and a set of product values {7 6 -2 -3} (in Mars dollars 
M$) where a negative value corresponds to a bonus product. You can apply coupon 3 (with N being 4) to 
product 1 (with value M$7) to get M$28 back; coupon 2 to product 2 to get M$12 back; and coupon 4 to 
product 4 to get M$3 back. On the other hand, if you apply coupon 3 to product 4, you will have to pay 
M$12 to the shop.

Each coupon and each product may be selected at most once. Your task is to get as much money back as 
possible.


## Input Specification: 

Each input file contains one test case. For each case, the first line contains the number of coupons NC, 
followed by a line with NC coupon integers. Then the next line contains the number of products NP, followed 
by a line with NP product values. Here 1<= NC, NP <= 10^5, and it is guaranteed that all the numbers will not 
exceed 2^30. 



## Output Specification: 

For each test case, simply print in a line the maximum amount of money you can get back.



## Sample Input:  

4  
1 2 4 -1  
4  
7 6 -2 -3  

## Sample Output:  

43  


## 题意：

求两组整数中各选取数量相同的元素，每一对相乘的结果相加的最大和

## 思路：

两组整数存储在两个数组中并对它们进行非递减排序，对小于0的对相乘，再对大于0的对相乘，这些相乘结果相加
即可。

## 代码：

[1037. Magic Coupon (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1037.%20Magic%20Coupon%20(25)/1037.%20Magic%20Coupon%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <algorithm>

int main()
{
	int nc, np;
	cin >> nc;
	int *coupon = new int[nc];
	for (int i = 0; i < nc; i++)
		cin >> coupon[i];
	cin >> np;
	int *product = new int[np];
	for (int i = 0; i < np; i++)
		cin >> product[i];
	sort(coupon, coupon + nc);
	sort(product, product + np);
	int i = 0, j = 0;
	int total = 0;
	while (i < nc && j < np && coupon[i] < 0 && product[i] < 0)
		total += coupon[i++] * product[j++];
	i = nc - 1;
	j = np - 1;
	while (i >= 0 && j >= 0 && coupon[i] > 0 && product[j] > 0)
		total += coupon[i--] * product[j--];
	cout << total;
    return 0;
}
```
