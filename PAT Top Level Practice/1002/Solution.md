# 1002 Business (35)
---
[原题地址](https://pintia.cn/problem-sets/994805148990160896/problems/994805156145643520)

* Author: CHEN, Yue
* Organization: PAT联盟
* Time Limit: 800ms
* Memory Limit: 64MB
* Code Size Limit: 16KB

As the manager of your company, you have to carefully consider, for each project, the time taken to finish it, the deadline, and the profit you can gain, in order to decide if your group should take this project. For example, given 3 projects as the following:

* Project[1] takes 3 days, it must be finished in 3 days in order to gain 6 units of profit.

* Project[2] takes 2 days, it must be finished in 2 days in order to gain 3 units of profit.

* Project[3] takes 1 day only, it must be finished in 3 days in order to gain 4 units of profit.

You may take Project[1] to gain 6 units of profit. But if you take Project[2] first, then you will have 1 day left to complete Project[3] just in time, and hence gain 7 units of profit in total. Notice that once you decide to work on a project, you have to do it from beginning to the end without any interruption.

## Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N(<=50), and then followed by N lines of projects, each contains three numbers P, L, and D where P is the profit, L the lasting days of the project, and D the deadline. It is guaranteed that L is never more than D, and all the numbers are non-negative integers.

## Output Specification:

For each test case, output in a line the maximum profit you can gain.

## Sample Input:

4   
7 1 3  
10 2 3  
6 1 2  
5 1 1  
## Sample Output:

18  

## 题意

已知N个项目的利润，完成所需时间，最晚完成截至时间，如何选择项目，使利润最大？

## 思路
定义项目结构体：
```cpp
typedef struct pnode {
    int profit;
    int lasting_days;
    int deadline;
} * Project;
```
动态规划。
先对项目按截至时间非递减排序，用二维数组 dp, dp[i][j] 表示对前i个项目，在时间j前能获得的最大利润，有：
* dp[0][j] = 0
* dp[i][0] = 0
* 若 j < 项目 i 所需的时间，则dp[i][j] = dp[i - 1][j]，即不能选择项目 i，i 从1开始计数
* 若 j >= 项目 i 所需的时间 && j <= 项目 i 的截至时间， 则 dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - p[i].lasting_days] + p[i].profit) ，即选择项目 i 与不选 i 中利润大的，数组p为项目数组
* 若 j > 项目 i 的截至时间，则dp[i][j] = max(dp[i - 1][j], dp[i][p[i].deadline])，此时不选 i 为 dp[i - 1][j]，选择 i 为 dp[i][p[i].deadline]

## 代码

[1002 Business (35) .cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Top%20Level%20Practice/1002/1002%20Business%20(35)%20.cpp)

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

typedef struct pnode {
    int profit;
    int lasting_days;
    int deadline;
} * Project;

bool compare(pnode a, pnode b) {
    return a.deadline < b.deadline;
}

int main()
{
    int n;
    cin >> n;
    Project p = new pnode[n + 1];
    for (int i = 1; i < n + 1; i ++) {
        cin >> p[i].profit >> p[i].lasting_days >> p[i].deadline;
    }
    sort(p + 1, p + n + 1, compare);
    int last_deadline = p[n].deadline;
    int **dp = new int * [n + 1];
    //dp[i][j]表示对前i个项目，在时间j前能获得的最大利润
    for (int i = 0; i < n + 1; i ++) {
        dp[i] = new int[last_deadline + 1];
        dp[i][0] = 0;
    }
    fill(dp[0], dp[0] + last_deadline + 1, 0);    
    for (int i = 1; i < n + 1; i ++)
        for (int j = 1; j <= last_deadline; j ++) {
            if (j < p[i].lasting_days)
                dp[i][j] = dp[i - 1][j];
            else if (j <= p[i].deadline) 
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - p[i].lasting_days] + p[i].profit);
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][p[i].deadline]);
        }
    cout << dp[n][last_deadline] << endl;
    return 0;
}
```

