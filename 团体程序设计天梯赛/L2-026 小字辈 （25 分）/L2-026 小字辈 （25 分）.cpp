#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct TNode{
	int id;
	vector<int> children;
	TNode(int id) : id(id) {}
} *Tree;

int main()
{
	int n;
	cin >> n;
	Tree *list = new Tree[n];
	for (int i = 0; i < n; i++)
		list[i] = new TNode(i);
	int parent_id, root_id;
	for (int i = 0; i < n; i++) {
		cin >> parent_id;
		if (parent_id == -1) {
			root_id = i;
			continue;
		}
		parent_id--;
		list[parent_id]->children.push_back(i);	
	}
	Tree root = list[root_id];
	queue<Tree> q;
	q.push(root);
	Tree last = root, tail = root;
	int level = 0;
	vector<int> lastLevel;		
	while (!q.empty()) {
		Tree t = q.front();
		q.pop();
		lastLevel.push_back(t->id);
		for (int child_id : t->children) {				
			Tree tree = list[child_id];
			q.push(tree);
			last = tree;
		}
		if (t == tail) {
			level++;
			tail = last;
			if (!q.empty()) lastLevel.clear();
		}
	}
	cout << level << endl;
	for (auto it = lastLevel.begin(); it != lastLevel.end(); it++) {
		if (it != lastLevel.begin()) putchar(' ');
		cout << (*it + 1);
	}
	for (int i = 0; i < n; i++)
		if (list[i] != NULL)
			delete list[i];
	free(list);	
	return 0;
}
