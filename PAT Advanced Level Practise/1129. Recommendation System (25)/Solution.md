# 1129. Recommendation System (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1129)

* 时间限制 400 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 作者 CHEN, Yue



Recommendation system predicts the preference that a user would give to an item. Now you are asked to program a very simple recommendation system that rates the user's preference by the number of times that an item has been accessed by this user.

## Input Specification: 

Each input file contains one test case. For each test case, the first line contains two positive integers: N (<= 50000), the total number of queries, and K (<= 10), the maximum number of recommendations the system must show to the user. Then given in the second line are the indices of items that the user is accessing -- for the sake of simplicity, all the items are indexed from 1 to N. All the numbers in a line are separated by a space.

## Output Specification: 

For each case, process the queries one by one. Output the recommendations for each query in a line in the format:

*query: rec[1] rec[2] ... rec[K]* 

where query is the item that the user is accessing, and rec[i] (i = 1, ... K) is the i-th item that the system recommends to the user. The first K items that have been accessed most frequently are supposed to be recommended in non-increasing order of their frequencies. If there is a tie, the items will be ordered by their indices in increasing order.

Note: there is no output for the first item since it is impossible to give any recommendation at the time. It is guaranteed to have the output for at least one query. 

## Sample Input:
12 3  
3 5 7 5 5 3 2 1 8 3 8 12  

##Sample Output:
5: 3  
7: 3 5  
5: 3 5 7  
5: 5 3 7  
3: 5 3 7  
2: 5 3 7  
1: 5 3 2  
8: 5 3 1  
3: 5 3 1  
8: 3 5 1  
12: 3 5 8  

## 题意：
用户进行N次查询，查询的项目为数字1~N中的某些数字。在每次查询前，系统需要向用户推荐K个供查询的数字。这K个数字是用户之前查询次数最多的前K个数字。第一次查询前用户没有查询过任何数字，故不需要推荐。输入N与K，以及N次查询的数字，在每次查询前（第一次除外）输出推荐的数字，若两个推荐的数字的查询次数相同则先输出小的

## 思路：

本题思路参考：[柳婼 の blog PAT 1129. Recommendation System (25) 甲级](https://www.liuchuo.net/archives/3848)

set会自动排序，故可建立结构体存储一个查询数字的数字与查询次数，结构体内重载小于号`<`。用set存储结构体。输入查询的数字时，先输出set中的前K个结构体的数字，然后将查询数字结构体插入set中（set中已存在该结构体则erase该结构体并插入出现次数增1后的结构体）。对第一个输入的查询不输出直接插入set中。set会自动排序结构体

## 参考：
[柳婼 の blog PAT 1129. Recommendation System (25) 甲级](https://www.liuchuo.net/archives/3848)

## 代码：

[1129. Recommendation System (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1129.%20Recommendation%20System%20(25)/1129.%20Recommendation%20System%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <set>

struct node {
  int value, num;
  bool operator < (const node a) const {
    return num != a.num ? num > a.num : value < a.value;
  }
};

int main()
{
  int n, k;
  cin >> n >> k;
  set<node> s;
  int *num = new int[n];
  fill(num, num + n, 0);
  for (int i = 0; i < n; i++) {
    int value;
    cin >> value;
    value--;
    int index = 0;
    if (i == 0) goto Insert;
    printf("%d:", value + 1);
    for (auto it = s.begin(); it != s.end() && index < k; it++, index++) 
      printf(" %d", it->value + 1);
    cout << endl;
  Insert: {
    auto it = s.find({ value, num[value] });
    if (it != s.end())
      s.erase(it);
    s.insert({ value, ++num[value] });
    }
  }
    return 0;
}

```
