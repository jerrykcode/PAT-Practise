# 1001. A+B Format (20)

* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue


Calculate a + b and output the sum in standard format -- that is, the digits must be separated into 
groups of three by commas (unless there are less than four digits).



## Input

Each input file contains one test case. Each case contains a pair of integers a and b where -1000000 <= a, 
b <= 1000000. The numbers are separated by a space.



## Output

For each test case, you should output the sum of a and b in one line. 
The sum must be written in the standard format. 



## Sample Input
-1000000 9


## Sample Output
-999,991



## 题意：

输入两个整数a、b，将a + b的值按标准格式输出(如a = 1003，b = -2，输出1,001)

## 思路：

用字符串存储a + b的结果，从末尾每隔3个数插入逗号(具体实现方法见代码)

## 代码

[1001. A+B Format (20).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1001.%20A%2BB%20Format%20(20)/1001.%20A%2BB%20Format%20(20).cpp)
```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>

int main()
{
	int a, b;
	cin >> a >> b;
	int sum = a + b;
	int flag = 0;
	if (sum < 0) {
		sum *= -1;
		flag = 1;
	}
	string result = std::to_string(sum);
	int len = result.length();
	for (int i = 1; i <= (len - 1)/3; i++) {
		result = result.substr(0, result.length() - 4 * i + 1) + "," + result.substr(result.length() - 4*i + 1);
	}
	if (flag)
		cout << "-";
	cout << result;
    return 0;
}
```

[AplusBFormat1001.java](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1001.%20A%2BB%20Format%20(20)/AplusBFormat1001.java)

```Java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

public class AplusBFormat1001 {
	
	public static void main(String[] args) throws IOException {
		StreamTokenizer st = new StreamTokenizer(
				new BufferedReader(new InputStreamReader(System.in)));
		st.nextToken();
		int a = (int) st.nval;
		st.nextToken();
		int b = (int) st.nval;
		int sum = a + b;
		String sumStr = "" + sum;
		sumStr = format(sumStr);
		System.out.println(sumStr);
	}
	
	/* 
	 * Changes a String with all the characters as integers into the format
	 * integer String.Example: changes "1999" to "1,999".
	 */
	private static String format(String str) {
		boolean neg = false; //Not negative
		if (str.charAt(0) == '-') {
			neg = true;
			str = str.substring(1);
		}
		str = adverse(str);//Adverse
		int nCommas = (str.length() - 1)/3;//The number of commas
		for (int i = 0; i < nCommas; i ++) {
			str = str.substring(0, 4*i + 3) + "," + str.substring(4*i + 3);
		}
		if (neg)
			str += '-';
		return adverse(str);
	}

	private static String adverse(String str) {
		String result = "";
		for (int i = 0; i < str.length(); i ++) {
			result += str.charAt(str.length() - i - 1);
		}
		return result;
	}
}
```
