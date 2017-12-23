package pat1001TO1010;

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
