// 1093. Count PAT's (25).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>

int main()
{
	string pats;
	cin >> pats;
	long long countT = 0, countAT = 0, countPAT = 0;
	for (int i = pats.length() - 1; i >= 0; i--) {
		if (pats[i] == 'T')
			countT++;
		if (pats[i] == 'A')
			countAT += countT;
		if (pats[i] == 'P')
			countPAT += countAT;
	}
	countPAT %= 1000000007;
	cout << countPAT << endl;
    return 0;
}

