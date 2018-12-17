# L3-016 二叉搜索树的结构 （30 分）
[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805047903240192)

>题目作者: 陈越
单位: 浙江大学
时间限制: 400 ms
内存限制: 64 MB
代码长度限制: 16 KB



二叉搜索树或者是一棵空树，或者是具有下列性质的二叉树： 若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；它的左、右子树也分别为二叉搜索树。（摘自百度百科）

给定一系列互不相等的整数，将它们顺次插入一棵初始为空的二叉搜索树，然后对结果树的结构进行描述。你需要能判断给定的描述是否正确。例如将{ 2 4 1 3 0 }插入后，得到一棵二叉搜索树，则陈述句如“2是树的根”、“1和4是兄弟结点”、“3和0在同一层上”（指自顶向下的深度相同）、“2是4的双亲结点”、“3是4的左孩子”都是正确的；而“4是2的左孩子”、“1和3是兄弟结点”都是不正确的。

## 输入格式：

输入在第一行给出一个正整数N（≤100），随后一行给出N个互不相同的整数，数字间以空格分隔，要求将之顺次插入一棵初始为空的二叉搜索树。之后给出一个正整数M（≤100），随后M行，每行给出一句待判断的陈述句。陈述句有以下6种：

* A is the root，即"A是树的根"；
* A and B are siblings，即"A和B是兄弟结点"；
* A is the parent of B，即"A是B的双亲结点"；
* A is the left child of B，即"A是B的左孩子"；
* A is the right child of B，即"A是B的右孩子"；
* A and B are on the same level，即"A和B在同一层上"。

题目保证所有给定的整数都在整型范围内。

## 输出格式：

对每句陈述，如果正确则输出Yes，否则输出No，每句占一行。

## 输入样例：

5  
2 4 1 3 0  
8  
2 is the root  
1 and 4 are siblings  
3 and 0 are on the same level  
2 is the parent of 4  
3 is the left child of 4  
1 is the right child of 2  
4 and 0 are on the same level  
100 is the right child of 3  


## 输出样例：

Yes  
Yes  
Yes  
Yes  
Yes  
No  
No  
No  

## 思路

首先插入元素，构建BST。分单词输入，判断出是何种陈述句。对于A、B，在BST中找到它们对应的树结点指针，或者所在层数，进行判断。这里判断的函数封装在一个class中。

也可以用map存储元素与相应的树结点指针及层数的对应。map是红黑树，比直接在BST中索搜快一些。但由于树的总结点数较少(<= 100)，这里没有使用map。

## 代码

[L3-016 二叉搜索树的结构 （30 分）.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L3-016%20%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E7%9A%84%E7%BB%93%E6%9E%84%20(30%E5%88%86)/L3-016%20%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E7%9A%84%E7%BB%93%E6%9E%84%20%EF%BC%8830%20%E5%88%86%EF%BC%89.cpp)

```cpp
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


```