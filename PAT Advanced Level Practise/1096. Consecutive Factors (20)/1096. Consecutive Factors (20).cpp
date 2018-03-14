#include <iostream>
using namespace std;
#include <vector>
#include <math.h>

int main()
{
	int n;
	cin >> n;
	vector<int> best, tmp;
	for (int i = 2; i < sqrt(n); i++) {
		int m = n, factor = i;
		tmp.clear();
		while (1) {
			if (m % factor != 0) 
				break;
			tmp.push_back(factor);
			m /= factor;
			factor++;
		}
		if (tmp.size() > best.size())
			best = tmp;
	}
	if (best.size() == 0) {
		cout << "1" << endl << n;
		return 0;
	}
	cout << best.size() << endl;
	for (auto it = best.begin(); it != best.end(); it++) {
		if (it != best.begin()) cout << "*";
		cout << *it;
	}
	return 0;
}