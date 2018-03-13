# 1071. Speech Patterns (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1071)
* 时间限制 300 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 HOU, Qiming


People often have a preference among synonyms of the same word. For example, some may prefer "the police", 
while others may prefer "the cops". Analyzing such patterns can help to narrow down a speaker's identity, 
which is useful when validating, for example, whether it's still the same person behind an online avatar.

Now given a paragraph of text sampled from someone's speech, can you find the person's most commonly used word?



## Input Specification: 

Each input file contains one test case. For each case, there is one line of text no more than 1048576 characters 
in length, terminated by a carriage return '\n'. The input contains at least one alphanumerical character, i.e., 
one character from the set [0-9 A-Z a-z].


## Output Specification: 

For each test case, print in one line the most commonly occurring word in the input text, followed by a space and 
the number of times it has occurred in the input. If there are more than one such words, print the lexicographically 
smallest one. The word should be printed in all lower case. Here a "word" is defined as a continuous sequence of 
alphanumerical characters separated by non-alphanumerical characters or the line beginning/end.

Note that words are case insensitive. 



## Sample Input:

Can1: "Can a can can a can?  It can!"

## Sample Output:

can 5



## 题意：

输入一行字符（含空格），由 非字母数字字符 或 字符串起始 或 结尾'\n' 分隔开的 连续字母数字字符串 为一个单词。
字母不区分大小写，求出现次数最多的单词及出现次数。若有多个出现次数最多的单词则输出最小的单词（string比较大小）


## 思路：

用getline输入字符串，用map存储单词与出现次数的对应。

注意分隔单词时，当读到输入字符串的最后一个字符时，不管此字符是否为alnum（字母数字），这里一定是一个单词的结尾
关于这一点参考了 [1071. Speech Patterns (25) (柳婼 の blog)](https://www.liuchuo.net/archives/2257)


## 参考：

[1071. Speech Patterns (25) (柳婼 の blog)](https://www.liuchuo.net/archives/2257)

## 代码：

[1071. Speech Patterns (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1071.%20Speech%20Patterns%20(25)/1071.%20Speech%20Patterns%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <map>

int main()
{
	string line;
	getline(cin, line);
	map<string, int> wordsFrequency;
	string word = "";
	for (int i = 0; i < line.length(); i++) {
		if (isalnum(line[i])) word += line[i];
		if (!isalnum(line[i]) || i == line.length() - 1) { //此单词结束
			if (word == "") continue;
			for (int j = 0; j < word.length(); j++) //转小写
				if (isupper(word[j])) word[j] = tolower(word[j]);
			wordsFrequency[word]++;
			word = "";
		}
	}
	int max = 0;
	string mostFrequency;
	for (auto it = wordsFrequency.begin(); it != wordsFrequency.end(); it++) {
		if (it->second > max) {
			max = it->second;
			mostFrequency = it->first;
		}
		else if (it->second == max && it->first < mostFrequency) 
			mostFrequency = it->first;
	}
	cout << mostFrequency << " " << max;
    return 0;
}
```
