# 1022. Digital Library (30)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1022)
* 时间限制 1000 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



A Digital Library contains millions of books, stored according to their titles, authors, key words 
of their abstracts, publishers, and published years. Each book is assigned an unique 7-digit number 
as its ID. Given any query from a reader, you are supposed to output the resulting books, sorted in 
increasing order of their ID's.



## Input Specification: 

Each input file contains one test case. For each case, the first line contains a positive integer N 
(<=10000) which is the total number of books. Then N blocks follow, each contains the information of 
a book in 6 lines:

* Line #1: the 7-digit ID number;   
* Line #2: the book title -- a string of no more than 80 characters;  
* Line #3: the author -- a string of no more than 80 characters;  
* Line #4: the key words -- each word is a string of no more than 10 characters without any white space, and the keywords are separated by exactly one space;  
* Line #5: the publisher -- a string of no more than 80 characters;  
* Line #6: the published year -- a 4-digit number which is in the range [1000, 3000].  

It is assumed that each book belongs to one author only, and contains no more than 5 key words; there 
are no more than 1000 distinct key words in total; and there are no more than 1000 distinct publishers.

After the book information, there is a line containing a positive integer M (<=1000) which is the number 
of user's search queries. Then M lines follow, each in one of the formats shown below:

* 1: a book title  
* 2: name of an author  
* 3: a key word  
* 4: name of a publisher  
* 5: a 4-digit number representing the year  



## Output Specification: 

For each query, first print the original query in a line, then output the resulting book ID's in 
increasing order, each occupying a line. If no book is found, print "Not Found" instead.



## Sample Input:

3  
1111111  
The Testing Book  
Yue Chen  
test code debug sort keywords  
ZUCS Print  
2011  
3333333  
Another Testing Book  
Yue Chen  
test code sort keywords  
ZUCS Print2  
2012
2222222  
The Testing Book  
CYLL  
keywords debug book  
ZUCS Print2  
2011  
6  
1: The Testing Book  
2: Yue Chen  
3: keywords  
4: ZUCS Print  
5: 2011  
3: blablabla  



## Sample Output:

1: The Testing Book  
1111111  
2222222  
2: Yue Chen  
1111111  
3333333  
3: keywords  
1111111  
2222222  
3333333  
4: ZUCS Print  
1111111  
5: 2011  
1111111  
2222222  
3: blablabla  
Not Found  



## 题意：

N本书，每本给出id、书名、作者、关键词（一个或多个）、出版社与出版日期。给出M条搜索，每条搜索是

1：书名  
2：作者  
3：一个关键词  
4：出版社  
5：出版日期  

中的一个，求符合搜索的所有书的id  


## 思路：

用map<string, vector<int>>存储除id外各种属性与书的id的对应关系。输入M条搜索后按序号确定在哪个map中
找到其对应的vector，输出vector中的id（若vector空输出"Not Found"）


## 代码：
[1022. Digital Library (30)_2.cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1022.%20Digital%20Library%20(30)/1022.%20Digital%20Library%20(30)_2.cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <map>
#include <vector>
#include <algorithm>

int main()
{
	int n;
	cin >> n;
	int id;
	string title, author, key, publisher, year; //属性与id的对应
	map<string, vector<int>> title_to_id;
	map<string, vector<int>> author_to_id;
	map<string, vector<int>> key_to_id;
	map<string, vector<int>> publisher_to_id;
	map<string, vector<int>> year_to_id;
	for (int i = 0; i < n; i++) {
		cin >> id;
		cin.ignore();
		getline(cin, title);
		getline(cin, author);
		getline(cin, key);
		getline(cin, publisher);
		cin >> year;
		title_to_id[title].push_back(id);
		author_to_id[author].push_back(id);
		string word = ""; //关键词
		for (int i = 0; i < key.length(); i++) {
			if (key[i] != ' ')
				word += key[i];
			else {
				if (word != "") key_to_id[word].push_back(id);
				word = "";
			}
		}
		if (word != "") key_to_id[word].push_back(id);
		publisher_to_id[publisher].push_back(id);
		year_to_id[year].push_back(id);
	}
	int m, index;
	string query;
	vector<int> book_id;
	cin >> m;
	for (int i = 0; i < m; i++) {
		scanf("%d: ", &index);
		getline(cin, query);
		switch (index) {
		case 1: {book_id = title_to_id[query]; break; }
		case 2: {book_id = author_to_id[query]; break; }
		case 3: {book_id = key_to_id[query]; break; }
		case 4: {book_id = publisher_to_id[query]; break; }
		case 5: {book_id = year_to_id[query]; break; }
		}
		printf("%d: ", index);
		cout << query << endl;
		if (book_id.empty()) { printf("Not Found\n"); continue; }
		sort(book_id.begin(), book_id.end());
		for (auto it = book_id.begin(); it != book_id.end(); it++)
			printf("%07d\n", *it);
	}
    return 0;
}


```