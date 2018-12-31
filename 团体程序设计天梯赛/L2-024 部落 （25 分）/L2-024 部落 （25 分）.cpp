#include <iostream>
using namespace std;

typedef int Set;
class USet {
public:
	USet(int n) : n(n) {
		s = new Set[n];
		fill(s, s + n, -1);
	}
	~USet() { free(s); }
	bool isSameSet(Set a, Set b);
	void unionSets(Set a, Set b);
	int numSets();
private:
	Set findRoot(Set a);
	int n;
	Set *s;
};

Set USet::findRoot(Set a) {
	if (s[a] < 0) return a;
	return s[a] = findRoot(s[a]);
}

bool USet::isSameSet(Set a, Set b) {
	return findRoot(a) == findRoot(b);
}

void USet::unionSets(Set a, Set b) {
	Set a_root = findRoot(a);
	Set b_root = findRoot(b);
	if (a_root == b_root) return;
	if (s[a_root] < s[b_root]) {
		s[a_root] += s[b_root];
		s[b_root] = a_root;
	}
	else {
		s[b_root] += s[a_root];
		s[a_root] = b_root;
	}
}

int USet::numSets() {
	int size = 0;
	for (int i = 0; i < n; i++)
		if (s[i] < 0) size++;
	return size;
}

int main()
{
	int n;
	cin >> n;
	USet uset(n);	
	int *circle = new int[10001];
	fill(circle, circle + 10001, -1);
	int num = 0;
	int k, id;
	for (int i = 0; i < n; i++) {
		cin >> k;
		for (int j = 0; j < k; j++) {
			cin >> id;
			if (circle[id] == -1) {
				circle[id] = i;
				num++;
			}
			else
				uset.unionSets(i, circle[id]);
		}	
	}
	cout << num << " " << uset.numSets() << endl;
	int q, id1, id2;
	cin >> q;
	for (int i = 0; i < q; i++) {
		cin >> id1 >> id2;
		cout << ((circle[id1] == circle[id2] || uset.isSameSet(circle[id1], circle[id2])) ? "Y" : "N") << endl;
	}
	free(circle);
	return 0;
}

