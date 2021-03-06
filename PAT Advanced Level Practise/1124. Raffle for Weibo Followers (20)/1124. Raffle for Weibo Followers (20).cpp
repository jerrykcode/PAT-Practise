// 1124. Raffle for Weibo Followers (20).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <map>

int main()
{
	int m, n, s;
	cin >> m >> n >> s;
	map<string, int>flag;
	int tag = 0;
	for (int i = 1; i <= m; i++) {
		string name;
		cin >> name;
		if (i >= s && (i - s) % n == 0) {
			if (flag[name] == 0) {
				cout << name << endl;
				tag = 1;
				flag[name] = 1;
			}
			else {
				i--;
				m--;
			}
		}
	}
	if (tag == 0) cout << "Keep going..." << endl;
    return 0;
}

