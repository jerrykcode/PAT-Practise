#include <iostream>
#include <string>
using namespace std;

typedef struct TNode {
	int val;
	struct TNode *left;
	struct TNode *right;
	struct TNode *parent;
	TNode(int val) : val(val), left(NULL), right(NULL), parent(NULL) {}
} *Tree;

Tree insert(Tree t, int val) {
	if (t == NULL) {
		return new TNode(val);		
	}
	if (val < t->val) { 
		Tree left = insert(t->left, val);	
		t->left = left;
		left->parent = t;
	}
	else {
		Tree right = insert(t->right, val);
		t->right = right;
		right->parent = t;
	}
	return t;
}

class Statement {
public:
	Statement(Tree t) : t(t) {}
	~Statement() {}

	bool isRoot(int a);
	bool areSiblings(int a, int b);
	bool isParent(int a, int b);
	bool isLeftChild(int a, int b);
	bool isRightChild(int a, int b);
	bool areOnSameLevel(int a, int b);

private:
	Tree t;
	Tree findTreeByVal(Tree tree, int val);
	int getLevel(Tree tree, int val, int level);
};

bool Statement::isRoot(int a) {
	if (t == NULL) return false;
	return t->val == a;
}

bool Statement::areSiblings(int a, int b) {
	if (t == NULL) return false;
	Tree ta = findTreeByVal(t, a);
	if (ta == NULL) return false;
    Tree tb = findTreeByVal(t, b);
	if (tb == NULL) return false;
	return ta->parent == tb->parent;	
}

bool Statement::isParent(int a, int b) {
	if (t == NULL) return false;
	Tree ta = findTreeByVal(t, a);
	if (ta == NULL) return false;
	Tree tb = findTreeByVal(t, b);
	if (tb == NULL) return false;
	return tb->parent == ta;
}

bool Statement::isLeftChild(int a, int b) {
	if (t == NULL) return false;
	Tree ta = findTreeByVal(t, a);
	if (ta == NULL) return false;
	Tree tb = findTreeByVal(t, b);
	if (tb == NULL) return false;
	return tb->left == ta;
}

bool Statement::isRightChild(int a, int b) {
	if (t == NULL) return false;
	Tree ta = findTreeByVal(t, a);
	if (ta == NULL) return false;
	Tree tb = findTreeByVal(t, b);
	if (tb == NULL) return false;
	return tb->right == ta;
}

bool Statement::areOnSameLevel(int a, int b) {
	if (t == NULL) return false;
	int al = getLevel(t, a, 0);
	if (al == -1) return false;
	int bl = getLevel(t, b, 0);
	if (bl == -1) return false;
	return al == bl;
}

Tree Statement::findTreeByVal(Tree tree, int val) {
	if (tree == NULL) return NULL;
	if (val == tree->val)
		return tree;
	else if (val < tree->val)
		return findTreeByVal(tree->left, val);
	else if (val > tree->val)
		return findTreeByVal(tree->right, val);
}

int Statement::getLevel(Tree tree, int val, int level) {
	if (tree == NULL) return -1;
	if (val == tree->val) return level;
	else if (val < tree->val)
		return getLevel(tree->left, val, level + 1);
	else if (val > tree->val)
		return getLevel(tree->right, val, level + 1);
}

int main() {
	Tree t = NULL;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int val;
		cin >> val;
		t = insert(t, val);
	}
	Statement statement(t);
	int m;
	cin >> m;
	int a, b;
	string cmd;
	for (int i = 0; i < m; i++) {
		cin >> a;
		cin >> cmd;
		if (cmd == "is") {
			cin >> cmd; //"the"
			cin >> cmd;
			if (cmd == "root") 
				cout << (statement.isRoot(a) ? "Yes" : "No") << endl;
			else if (cmd == "parent") {
				cin >> cmd; //"of"
				cin >> b;
				cout << (statement.isParent(a, b) ? "Yes" : "No") << endl;
			}
			else if (cmd == "left") {
				cin >> cmd; //"child"
				cin >> cmd; //"of"
				cin >> b;
				cout << (statement.isLeftChild(a, b) ? "Yes" : "No") << endl;
			}
			else if (cmd == "right") {
				cin >> cmd; //"child"
				cin >> cmd; //"of"
				cin >> b;
				cout << (statement.isRightChild(a, b) ? "Yes" : "No") << endl;
			}
		}
		else { //"and"
			cin >> b;
			cin >> cmd; //"are"
			cin >> cmd;
			if (cmd == "siblings") {
				cout << (statement.areSiblings(a, b) ? "Yes" : "No") << endl;
			}
			else { //"on"
				cin >> cmd; //"the"
				cin >> cmd; //"same"
				cin >> cmd; //"level"
				cout << (statement.areOnSameLevel(a, b) ? "Yes" : "No") << endl;
			}
		}
	}
	return 0;
}

