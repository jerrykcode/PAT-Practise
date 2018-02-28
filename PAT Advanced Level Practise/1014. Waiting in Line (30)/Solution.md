# 1014. Waiting in Line (30)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1014)
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



Suppose a bank has N windows open for service. There is a yellow line in front of the windows which 
devides the waiting area into two parts. The rules for the customers to wait in line are: 

* The space inside the yellow line in front of each window is enough to contain a line with M customers. 
Hence when all the N lines are full, all the customers after (and including) the (NM+1)st one will have 
to wait in a line behind the yellow line. 
* Each customer will choose the shortest line to wait in when crossing the yellow line. If there are two 
or more lines with the same length, the customer will always choose the window with the smallest number. 
* Customer[i] will take T[i] minutes to have his/her transaction processed. 
* The first N customers are assumed to be served at 8:00am. 

Now given the processing time of each customer, you are supposed to tell the exact time at which a customer 
has his/her business done.

For example, suppose that a bank has 2 windows and each window may have 2 custmers waiting inside the yellow 
line. There are 5 customers waiting with transactions taking 1, 2, 6, 4 and 3 minutes, respectively. At 08:00 
in the morning, customer1 is served at window1 while customer2 is served at window2. Customer3 will wait in 
front of window1 and customer4 will wait in front of window2. Customer5 will wait behind the yellow line.

At 08:01, customer1 is done and customer5 enters the line in front of window1 since that line seems shorter now. 
Customer2 will leave at 08:02, customer4 at 08:06, customer3 at 08:07, and finally customer5 at 08:10.
----



## Input

Each input file contains one test case. Each case starts with a line containing 4 positive integers: 
N (<=20, number of windows), M (<=10, the maximum capacity of each line inside the yellow line), K 
(<=1000, number of customers), and Q (<=1000, number of customer queries).

The next line contains K positive integers, which are the processing time of the K customers.

The last line contains Q positive integers, which represent the customers who are asking about the time 
they can have their transactions done. The customers are numbered from 1 to K.



## Output

For each of the Q customers, print in one line the time at which his/her transaction is finished, in the format 
HH:MM where HH is in [08, 17] and MM is in [00, 59]. Note that since the bank is closed everyday after 17:00, 
for those customers who cannot be served before 17:00, you must output "Sorry" instead.




## Sample Input
2 2 7 5  
1 2 6 4 3 534 2  
3 4 5 6 7  

## Sample Output
08:07  
08:06  
08:10  
17:00  
Sorry  




## 题意：

银行有N个窗口，每个窗口可排队M人，排不下的客户就排在黄线外，当一个窗口有一个客户离开，黄线外的一个客户便进到此窗口
排队，已知总共有K个客户，及每个客户需要的时间，输入Q个客户，求他们离开的时间，用hh:mm格式输出（客户的编号从1~K，客
户在08:00到达，对于开始时间大于17:00的客户，输出“Sorry”） 

## 思路：

用数组windows存储N个队列，队列存储客户的编号 - 1(题目中编号1~K，程序中0~K - 1)，表示在窗口排队的客户，用长度为N的数
组first和last分别表示每个窗口的第一个和最后一个客户离开的时间，用长度为K的数组start和departure分别表示这K个客户开始
办事和离开的时间，时间用从00:00到当前时刻的分钟数表示。

边输入客户需要的时间，边计算该客户的开始时间与离开时间：

first和departure初始化为480(08:00)，输入每个客户的时间minutes，对于N个窗口能排下的客户(编号0~N*M-1，设其编号为i)，通
过编号i找到相应的窗口w(w = (i < N) ? i : i%N)，i进队列windows[w]，若i < N，则i是当天第一个到达该窗口的人，first[w] += minutes，
否则first[w]不变化，i进入窗口前last[w]是窗口w的最后一个客户离开的时间(还没有人排队则为480(08:00))，也就是客户i开始的时间，
故start[i]　= last[w]，i进入窗口后窗口w的最后一个客户为i，故last[w]更新为last[w] +　minutes，即加上i的时间，更新后的last[w]
也是i的离开时间，故departure[i] = last[w]
 
对于N个窗口不能排下，在黄线外的客户，设每个客户编号为i，则在first中找到最小值的下标w，w就是最先有客户离开的窗口，即i应
该进入排队的窗口，windows[w]队列的第一个元素出队列，i进队列，此时first[w]更新为窗口当前第一个客户的离开时间，即first[w] 
= departure[widows[w].front()]，i进入窗口前last[w]是窗口w的最后一个客户离开的时间，也就是客户i开始的时间，故start[i]　= 
last[w]，i进入窗口后窗口w的最后一个客户为i，故last[w]更新为last[w] +　minutes，即加上i的时间，更新后的last[w]也是i的离开
时间，故departure[i] = last[w]

对于Q个客户，若其start值>=17*60 (17:00)，输出"Sorry"，否则输出departure值 (更改为hh:mm)

## 代码：

[1014. Waiting in Line (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1014.%20Waiting%20in%20Line%20(30)/1014.%20Waiting%20in%20Line%20(30).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <queue>

int main()
{
	int n, m, k, q;
	cin >> n >> m >> k >> q;
	queue<int> * windows = new queue<int>[n]; //n个窗口
	//时间用00:00到当前时间hh:mm的分钟数表示
	int *first = new int[n]; //每个窗口第一个客户的离开时间
	int *last = new int[n]; //每个窗口最后一个客户的离开时间
	int *start = new int[k]; //k个客户的开始时间
	int *departure = new int[k]; //k个客户的离开时间
	for (int i = 0; i < n; i++)
		first[i] = last[i] = 480; //08:00
	int minutes;
	for (int i = 0; i < n * m && i < k; i++) { //n个窗口能够排下的人
		cin >> minutes; //第i个客户办事的时间
		int w = i < n ? i : i % n; //窗口
		windows[w].push(i);
		if (i < n) first[w] += minutes;
		start[i] = last[w]; //第i个客户开始的时间
		last[w] += minutes;
		departure[i] = last[w]; //第i个客户离开的时间
	}
	for (int i = n * m; i < k; i++) { //n个窗口不能够排下，在黄线外等待的人
		cin >> minutes;
		int w = 0;
		for (int j = 0; j < n; j++) //最先离开一个客户的窗口
			if (first[j] < first[w])
				w = j;
		windows[w].pop(); //该窗口第一个客户离开
		windows[w].push(i); //第i个客户进入该窗口
		first[w] = departure[windows[w].front()]; //更新first
		start[i] = last[w];
		last[w] += minutes; //更新last
		departure[i] = last[w]; //第i个客户离开的时间
	}
	int customer;
	for (int i = 0; i < q; i++) {
		cin >> customer;
		customer--;
		if (start[customer] >= 17 * 60) {
			cout << "Sorry\n";
			continue;
		}
		int hour = departure[customer] / 60;
		int min = departure[customer] % 60;
		printf("%02d:%02d\n", hour, min);
	}
    return 0;
}
```

