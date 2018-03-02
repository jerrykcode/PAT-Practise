

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;

public class Readme {

	static ArrayList<String> url404 = new ArrayList<String>();

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			String pathName = "E:\\gitcode\\tmp\\readme.txt";
			BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream(new File(pathName))));
			String line = in.readLine();
			while (line != null) {
				System.out.println(handle(line));
				line = in.readLine();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		for (int i = 0; i < url404.size(); i++) {
			System.out.println(url404.get(i));
		}
	}

	private static String handle(String line) { // line的形式："x...x 1xxx x...x
												// (xx) x...x"
		String result = "";
		String index = ""; // 题号，如1001
		String question = ""; // 题目字符串，如1001. A+B Format (20)
		int flag = 0;
		for (int i = 0; i < line.length(); i++) {
			char c = line.charAt(i);
			if (c == ')' && i - 1 >= 0 && Character.isDigit(line.charAt(i - 1))) { // eg:
																					// ...(25)
				question += ")";
				break;
			}
			if (c == '1') // 开始题号
				flag = 1;
			if (flag == 1 || flag == 2) {
				if (flag == 1 && Character.isDigit(c))
					index += c; // 题号是"1003"，分数"25"不在题号中
				else { // 题号结束
					if (flag == 1)
						question += ".";
					flag = 2;
				}
				question += c;
			}
		}
		if (line.charAt(0) != 'Y'){
			return "|[" + question + "](https://www.patest.cn/contests/pat-a-practise/" + index  + ")|-|-|";
		}
		result = "|[" + question + "](https://www.patest.cn/contests/pat-a-practise/" + index + ")|[C++](";
		String codeURL = getURLofCppCode(question);
		String solutionURL = getURLofSolution(question);
		/*if (!testURL(codeURL) || !testURL(solutionURL)) { //判断此URL
			System.out.println("404");
			url404.add(index);
		}*/
		result += codeURL + ")|[Solution](";
		result += solutionURL + ")|";
		return result;
	}

	/* 文件夹URL，即题目字符串中所有空格由"%20"代替 */
	public static String getURLofFolder(String question) {
		for (int i = 0; i < question.length(); i++) {
			if (question.charAt(i) == ' ') {
				question = question.substring(0, i) + "%20" + question.substring(i + 1);
				i += 2; // ' ' -> "%20"
			}
		}
		return question;
	}

	public static String getURLofCppCode(String question) {
		String url = "https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/";
		question = getURLofFolder(question);
		url += question + "/" + question + ".cpp";
		return url;
	}

	public static String getURLofSolution(String question) {
		String url = "https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/";
		url += getURLofFolder(question) + "/Solution.md";
		return url;
	}

	public static boolean testURL(String urlText) {
		try {
			URL url = new URL(urlText);
			HttpURLConnection co = (HttpURLConnection) url.openConnection();
			int state = co.getResponseCode();
			if (state == 200) {
				System.out.println("URL可用！");
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			System.out.println("404");
			return false;
		}
		return true;
	}
}
