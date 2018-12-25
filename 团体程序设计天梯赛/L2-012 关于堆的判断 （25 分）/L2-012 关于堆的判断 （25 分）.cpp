#include <iostream>
#include <map>
#include <string>
using namespace std;

#define PARENT(i) ((i + 1)/2 - 1)
#define OUTPUT(boolean) cout << ((boolean) ? "T" : "F") << endl

class Heap {
public:
	Heap(int capacity) : capacity(capacity), size(0) {
		list = new int[capacity];
	}
	~Heap() { free(list); }
	void insert(int item);
	bool isRoot(int item);
	bool areSiblings(int x, int y);
	bool isParentOf(int x, int y);
	bool isChildOf(int x, int y);
private:
	int getIndexOf(int item);
	map<int, int> itemToIndex;
	int *list;
	int capacity;
	int size;
};

void Heap::insert(int item) {
	if (size == capacity) return;
	int i;
	for (i = size; i != 0 && list[PARENT(i)] > item; i = PARENT(i)) {
		list[i] = list[PARENT(i)];
		itemToIndex[list[i]] = i;
	}
	list[i] = item;
	itemToIndex[item] = i;
	size++;
}

bool Heap::isRoot(int item) {
	return getIndexOf(item) == 0;
}

bool Heap::areSiblings(int x, int y) {
	int x_idx = getIndexOf(x);
	int y_idx = getIndexOf(y);
	return PARENT(x_idx) == PARENT(y_idx);
}

bool Heap::isParentOf(int x, int y) {
	int x_idx = getIndexOf(x);
	int y_idx = getIndexOf(y);
	return x_idx == PARENT(y_idx);
}

bool Heap::isChildOf(int x, int y) {
	return isParentOf(y, x);
}

int Heap::getIndexOf(int item) {
	return itemToIndex[item];
}

int main() 
{
	int n, m;
	cin >> n >> m;
	Heap heap(n);
	int item;
	for (int i = 0; i < n; i++) {
		cin >> item;
		heap.insert(item);
	}
	int x, y;
	string cmd;
	for (int i = 0; i < m; i++) {
		cin >> x;
		cin >> cmd;
		if (cmd == "and") {
			cin >> y;
			cin >> cmd; //"are"
			cin >> cmd; //"siblings"
			OUTPUT(heap.areSiblings(x, y));
		}
		else { //cmd == "is"
			cin >> cmd;
			if (cmd == "a") {
				cin >> cmd; //"child"
				cin >> cmd; //"of"
				cin >> y;
				OUTPUT(heap.isChildOf(x, y));				
			}
			else { //cmd == "the"
				cin >> cmd;
				if (cmd == "root") {
					OUTPUT(heap.isRoot(x));	
				}
				else { //cmd == "parent"
					cin >> cmd; //"of"
					cin >> y;
					OUTPUT(heap.isParentOf(x, y));
				}
			}
		}
	}
	return 0;
}

