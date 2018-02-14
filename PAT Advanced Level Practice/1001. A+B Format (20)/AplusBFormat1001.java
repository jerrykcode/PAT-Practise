/*
1001. A+B Format (20)

时间限制 400 ms

内存限制 65536 kB

代码长度限制 16000 B

判题程序 Standard 

作者 CHEN, Yue
------------------------------------------------------------


Calculate a + b and output the sum in standard format -- that is, the digits must be separated into 
groups of three by commas (unless there are less than four digits).
-------------------------------------------------------------


Input

Each input file contains one test case. Each case contains a pair of integers a and b where -1000000 <= a, 
b <= 1000000. The numbers are separated by a space.
------------------------------------------------------------


Output

For each test case, you should output the sum of a and b in one line. 
The sum must be written in the standard format. 
----------------------------------------------------------


Sample Input
-1000000 9


Sample Output
-999,991
-----------------------------------------------------------
*/

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
