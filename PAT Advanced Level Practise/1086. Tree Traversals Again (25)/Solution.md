## 1086. Tree Traversals Again (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1086)

* 时间限制 200 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



An inorder binary tree traversal can be implemented in a non-recursive way with a stack. For example, 
suppose that when a 6-node binary tree (with the keys numbered from 1 to 6) is traversed, the stack 
operations are: push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); push(5); push(6); pop(); 
pop(). Then a unique binary tree (shown in Figure 1) can be generated from this sequence of operations. 
Your task is to give the postorder traversal sequence of this tree. 

![](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1086.jpg)


## Input Specification: 

Each input file contains one test case. For each case, the first line contains a positive integer N (<=30) 
which is the total number of nodes in a tree (and hence the nodes are numbered from 1 to N). Then 2N lines 
follow, each describes a stack operation in the format: "Push X" where X is the index of the node being pushed 
onto the stack; or "Pop" meaning to pop one node from the stack.


## Output Specification: 

For each test case, print the postorder traversal sequence of the corresponding tree in one line. A solution is 
guaranteed to exist. All the numbers must be separated by exactly one space, and there must be no extra space at 
the end of the line. 



## Sample Input:

6  
Push 1  
Push 2  
Push 3  
Pop  
Pop  
Push 4  
Pop  
Pop  
Push 5  
Push 6  
Pop  
Pop  

## Sample Output:

3 4 2 6 5 1  


## 题意：

通过进栈出栈表示一颗树，求树的后序遍历结果

## 思路：

建立树结点，初始化结点current、root为NULL，

#### 对于 "Push X"操作：

* 若current == NULL，则current->data = X，然后current赋给根，即root = current
	
* 若current != NULL，则建立结点tmp，其data为X，若current的left不存在则tmp赋给current的left，(right同)，
* 若current的left、right都存在则current更新为current的父结点，再次判断其left、right是否存在，最后tmp的left、right均为NULL，tmp的父指针parent为current，最后更新current为tmp，current进栈
	
#### 对于 "Pop"操作：
	
* 栈顶元素赋给current，栈顶元素出栈

从root开始递归，后序遍历树


## 代码：

### C++

[1086. Tree Traversals Again (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1086.%20Tree%20Traversals%20Again%20(25)/1086.%20Tree%20Traversals%20Again%20(25).cpp)


```cpp
#include <iostream>
using namespace std;
#include <string>
#include <stack>

typedef struct node {
	int data;
	struct node * left, * right, *parent;
} tnode;
typedef tnode *tree;

void post(tree root)
{
	if (!root->left && !root->right)
		cout << root->data << " ";
	else {
		if (root->left) post(root->left);
		if (root->right) post(root->right);
		cout << root->data << " ";
	}
}

int main()
{
	int n;
	cin >> n;
	tree root = NULL;
	tree current = NULL;
	stack<tree> s;
	for (int i = 0; i < 2 * n; i++) {
		string cmd;
		cin >> cmd;
		if (cmd == "Push") {
			int data;
			cin >> data;
			if (current == NULL) {
				current = new tnode;
				current->data = data;
				current->left = current->right = NULL;
				root = current;
			}
			else {
				tree tmp = new tnode;
				tmp->data = data;
			PUSH: {
				if (!current->left)
					current->left = tmp;
				else if (!current->right)
					current->right = tmp;
				else {
					current = current->parent;
					goto PUSH;
				}
				}
				  tmp->left = tmp->right = NULL;
				  tmp->parent = current;
				  current = tmp;
			}
			s.push(current);
		}
		else {
			current = s.top();
			s.pop();
		}
	}
	if (root->left) post(root->left);
	if (root->right) post(root->right);
	cout << root->data;
    return 0;
}
```


### Java

[TreeTraversalsAgain.java](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1086.%20Tree%20Traversals%20Again%20(25)/TreeTraversalsAgain.java)


```Java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.util.Stack;

public class Main{

	private static TNode[] tree;//Array to store the tree
	
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		StreamTokenizer st = new StreamTokenizer(
				new BufferedReader(new InputStreamReader(System.in)));
		st.nextToken();
		int nNodes = (int) st.nval;//Number of nodes
		tree = new TNode[nNodes];
		Stack<TNode> stack = new Stack<TNode>();//Stack 
		int current = 0;//The index of the node on which the new nodes attach to
		int index = 0;
		for (int i = 0; i < 2*nNodes; i ++) {
			st.nextToken();
			String s = st.sval;
			if (s.equals("Push")) {
				st.nextToken();
				int data = (int) st.nval;
				TNode node = new TNode(index, data);
				stack.push(node);
				tree[index] = node;
				if (i != 0)
					if (tree[current].getLeft() == -1)
						tree[current].setLeft(index);
					else
						tree[current].setRight(index);
				current = index ++;
			} else if (s.equals("Pop")) 
				current = stack.pop().getIndex();
		}
		String str = traversal(0);
		str = str.substring(0, str.length() - 1);
		System.out.println(str);
	}

	private static String traversal(int root) {
		// TODO Auto-generated method stub
		String result = "";
		if (root != -1) {
			result += traversal(tree[root].getLeft());
			result += traversal(tree[root].getRight());
			result += tree[root].getData();
			result += " ";
		}
		return result;
	}

}

class TNode {
	
	//Constructor
	public TNode (int index, int data) {
		this.index = index;
		this.data = data;
		this.left = -1;
		this.right = -1;
	}
	
	/** Returns the index of the node. */
	public int getIndex() {
		return index;
	}
	
	/** Returns the data. */
	public int getData() {
		return data;
	}
	
	/** Returns the index of the left. */
	public int getLeft() {
		return left;
	}
	
	/** Sets the index of the left. */
	public void setLeft(int left) {
		this.left = left;
	}
	
	/** Returns the index of the right. */
	public int getRight() {
		return right;
	}
	
	/** Sets the index of the right. */
	public void setRight(int right) {
		this.right = right;
	}
	
	/* Private instance variables. */
	private int index;
	private int data;
	private int left;
	private int right;
}
```