#include <iostream>
#include <map>
#include <string>
using namespace std;

struct PAT {
	PAT() {}
	PAT(string id, int test, int exam) : id(id), test(test), exam(exam) {}
	string id;
	int test, exam;
};

int main()
{
	map<int, PAT> testToPAT;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string id;
		int test, exam;
		cin >> id >> test >> exam;
		PAT pat(id, test, exam);
		testToPAT[test] = pat;
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int test;
		cin >> test;
		PAT pat = testToPAT[test];
		cout << pat.id << " " << pat.exam << endl;
	}
	return 0;
}