#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef short ID;
bool compare(ID a, ID b) {
	return a > b;
}
class USet {
public:
	USet(int n) : n(n) {
		_set = new ID[n];
		fill(_set, _set + n, -1);
	}
	~USet() { free(_set); }
	
	void unionSets(ID a, ID b);
	void getSets(vector<ID>& sets);

private:
	ID findRoot(ID a);

	int n;
	ID *_set;
};

ID USet::findRoot(ID a) {
	if (_set[(int)a] < 0) return a;
	return _set[(int)a] = findRoot(_set[(int)a]);
}

void USet::unionSets(ID a, ID b) {
	ID root_a = findRoot(a);
	ID root_b = findRoot(b);
	if (root_a == root_b) return;
	if (_set[root_a] < _set[root_b]) {
		_set[root_a] += _set[root_b];
		_set[root_b] = root_a;
	}
	else {
		_set[root_b] += _set[root_a];
		_set[root_a] = root_b;
	}
}

void USet::getSets(vector<ID>& sets) {
	for (int i = 0; i < n; i++)
		if (_set[i] < 0) {
			sets.push_back(_set[i] * (-1));		
		}	
	sort(sets.begin(), sets.end(), compare);
}

int main() {
	int n;
	scanf("%d", &n);
	USet uset(n);
	ID hobbies[1000];
	for (int i = 0; i < 1000; i++) hobbies[i] = -1;
	int k, hobby;
	for (int i = 0; i < n; i++) {
		scanf("%d:", &k);	
		for (int j = 0; j < k; j++) {
			scanf("%d", &hobby);
			hobby--;
			if (hobbies[hobby] == -1)
				hobbies[hobby] = (ID)i;
			else {
				uset.unionSets(hobbies[hobby], (ID)i);
			}
		}
	}
	vector<ID> sets;
	uset.getSets(sets);
	printf("%d\n", sets.size());
	for (auto it = sets.begin(); it != sets.end(); it++) {
		if (it != sets.begin()) putchar(' ');
		printf("%hd", *it);
	}
	return 0;
}
