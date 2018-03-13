# 1130. Infix Expression (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1130)

* 时间限制 400 ms  



* 内存限制 65536 kB  



* 代码长度限制 16000 B  



* 判题程序 Standard  

* 作者 CHEN, Yue  



Given a syntax tree (binary), you are supposed to output the corresponding infix expression, with parentheses reflecting the precedences of the operators. 

##  Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N ( <= 20 ) which is the total number of nodes in the syntax tree. Then N lines follow, each gives the information of a node (the i-th line corresponds to the i-th node) in the format: 

*data left_child right_child*

where data is a string of no more than 10 characters, left_child and right_child are the indices of this node's left and right children, respectively. The nodes are indexed from 1 to N. The NULL link is represented by -1. The figures 1 and 2 correspond to the samples 1 and 2, respectively. 


 

 


![Figure 1 ](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1130_1.jpg)   ![Figure 2 ](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1130_2.jpg)



## Output Specification: 

For each case, print in a line the infix expression, with parentheses reflecting the precedences of the operators. Note that there must be no extra parentheses for the final expression, as is shown by the samples. There must be no space between any symbols. 
## Sample Input 1:

8
 \* 8 7  
a -1 -1  
\* 4 1  
\+ 2 5  
b -1 -1  
d -1 -1  
\-  -1 6  
c -1 -1  

## Sample Output 1:

(a+b)\*(c\*(-d))

## Sample Input 2:

8  
2.35 -1 -1  
\* 6 1  
\- -1 4  
% 7 8  
\+ 2 3  
a -1 -1  
str -1 -1  
871 -1 -1  

## Sample Output 2:

(a\*2.35)+(-(str%871))

## 题意：

表示运算表达式的二叉树有N个结点，编号1~N。输入每个结点的string表达式及左、右孩子的编号，求该二叉树表示的运算表达式


##  思路：

递归，中序遍历二叉树  

在输入时用flag数组将所有结点的孩子结点标记为1，之后遍历flag数组，标记唯一不为1的结点即为根结点(不是任何结点的孩子)。从根结点开始，若左孩子存在则递归 求左孩子的 表达式，加上根的string，然后若有右孩子则 递归求右孩子的表达式。若一个结点无左、右孩子，则返回该结点的string，不再继续深入递归。

 对于括号： 全局 int  flag 初始化为0，返回表达式时若表达式与结点的 string 不一样，则说明该表达式包含了其孩子的表达式，flag更新为1，递归回到上一层时若flag为1则需要加括号，然后flag赋回0
 
 
## 代码：

[1130. Infix Expression (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1130.%20Infix%20Expression%20(25)/1130.%20Infix%20Expression%20(25).cpp)


```cpp

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>

struct node {
	string data;
	int left, right;
};

int flag = 0;
string getExpression(node *tree, int root)
{
	string result = "", left, right;
	if (tree[root].left != -1) {
		left = getExpression(tree, tree[root].left); //Get the expression of the left child
		if (flag) { // If a pair of parentheses is needed
			left = "(" + left + ")";
			flag = 0; //Sets "flag" back to 0
		}
		result += left;
	}
	result += tree[root].data; 
	if (tree[root].right != -1) {
		right = getExpression(tree, tree[root].right); //Get the expression of the right child
		if (flag) { // If a pair of parentheses is needed
			right = "(" + right + ")";
			flag = 0; //Sets "flag" back to 0
		}
		result += right;
	}
	if (result != tree[root].data) flag = 1; //If the expression contains not only the data in the root but also the expression in its children
												// then a pair of parentheses is needed
	return result;
}

int main()
{
	int n;
	cin >> n;
	node *tree = new node[n];
	int *flag = new int[n];
	for (int i = 0; i < n; i++) {
		string data;
		int left, right;
		cin >> data >> left >> right;
		if (left != -1) left--; //Inputs indexed from 1 ~ N while in the array they indexed from 0 ~ N - 1
		if (right != -1) right--;
		tree[i] = { data, left, right };
		if (left != -1) flag[left] = 1; //The left child appeared as a child of another node
		if (right != -1) flag[right] = 1; //So do the right child
	}
	int root;
	for (int i = 0; i < n ; i++)
		if (flag[i] != 1) {
			root = i; //Root can never be a child
			break;
		}
	cout << getExpression(tree, root);
    return 0;
}

```

