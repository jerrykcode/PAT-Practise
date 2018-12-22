# L2-004 这是二叉搜索树吗 (25 分）
[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805070971912192)


> 作者: 陈越  
> 单位: 浙江大学  
> 时间限制: 400 ms  
> 内存限制: 64 MB  
> 代码长度限制: 16 KB  


一棵二叉搜索树可被递归地定义为具有下列性质的二叉树：对于任一结点，
* 其左子树中所有结点的键值小于该结点的键值；
* 其右子树中所有结点的键值大于等于该结点的键值；
* 其左右子树都是二叉搜索树。

所谓二叉搜索树的“镜像”，即将所有结点的左右子树对换位置后所得到的树。

给定一个整数键值序列，现请你编写程序，判断这是否是对一棵二叉搜索树或其镜像进行前序遍历的结果。

## 输入格式：

输入的第一行给出正整数 N（≤1000）。随后一行给出 N 个整数键值，其间以空格分隔。

## 输出格式：

如果输入序列是对一棵二叉搜索树或其镜像进行前序遍历的结果，则首先在一行中输出 YES ，然后在下一行输出该树后序遍历的结果。数字间有 1 个空格，一行的首尾不得有多余空格。若答案是否，则输出 NO。

## 输入样例 1：  

> 7  
> 8 6 5 7 10 8 11  


## 输出样例 1：

> YES  
> 5 7 6 8 11 10 8  


## 输入样例 2：

> 7  
> 8 10 11 8 6 7 5  


## 输出样例 2：

> YES  
> 11 8 10 7 5 6 8  


## 输入样例 3：
> 7  
> 8 6 8 5 10 9 11  


## 输出样例 3：
> NO  

## 思路

首先判断是否可能为正常BST，若不可能再判断是否可能为BST的镜像。判断过程中得到后序遍历结果。
以判断正常BST为例，preorder的第一个元素为postorder的最后一个，preorder中第一个大于等于preorder
的第一个元素的，即为右子树的根，划分左右子树递归求解。对于右子树，其每一个元素需要>=preorder的
第一个元素，否则就不是BST,这个判断条件需传到递归右子树的函数中。具体判断方法见代码注释。

## 代码

[L2-004 这是二叉搜索树吗 ? (25分).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L2-004%20%E8%BF%99%E6%98%AF%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E5%90%97%EF%BC%9F%20%EF%BC%8825%20%E5%88%86%EF%BC%89/L2-004%20%E8%BF%99%E6%98%AF%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E5%90%97%EF%BC%9F%20%EF%BC%8825%20%E5%88%86%EF%BC%89.cpp)

```cpp
#include <iostream>
using namespace std;
typedef enum {
	NORMAL, //正常BST，左小右大
	MIRROR_IMAGE, //镜像BST，左大右小
} BSTType; //BST种类

struct Flag { //preToPost函数中的一个flag
	BSTType type; //BST种类
	bool hasFlag; //是否有flag
	int val; //在hasFlag为true时，需要所有元素大于等于或小于等于val
	Flag(BSTType type, bool hasFlag, int val) : type(type), hasFlag(hasFlag), val(val) {}
};

int *preorder;
int *postorder;

bool preToPost(int preStart, int preEnd, int postStart, int postEnd, Flag flag) {
	if (preStart > preEnd) return true;
	postorder[postEnd] = preorder[preStart];	
	if (preStart == preEnd) return true;
	int i;
	for (i = preStart + 1; i <= preEnd; i++) {
		if (flag.hasFlag && flag.type == NORMAL && preorder[i] < flag.val) return false; //正常BST，在hadFlag为true时，不能小于val
		if (flag.hasFlag && flag.type == MIRROR_IMAGE && preorder[i] > flag.val) return false; //镜像BST，在hadFlag为true时，不能大于val
		if (flag.type == NORMAL && preorder[i] >= preorder[preStart]) break;
		if (flag.type == MIRROR_IMAGE && preorder[i] < preorder[preStart]) break;
	}
	//划分左右子树
	int leftSize = i - preStart - 1;
	if (!preToPost(preStart + 1, i - 1, postStart, postStart + leftSize - 1, Flag(flag.type, false, 0))) return false; //左子树的flag不需要判断
	if (!preToPost(i, preEnd, postStart + leftSize, postEnd - 1, Flag(flag.type, true, preorder[preStart]))) return false;
	return true;
}

int main() {
	int n;
	cin >> n;
	preorder = new int[n];
	postorder = new int[n];
	for (int i = 0; i < n; i++)
		cin >> preorder[i];
	if (preToPost(0, n - 1, 0, n - 1, Flag(NORMAL, false, 0))) { //正常BST
		cout << "YES" << endl;
		for (int i = 0; i < n; i++) {
			if (i != 0) putchar(' ');
			cout << postorder[i];
		}
	}
	else if (preToPost(0, n - 1, 0, n - 1, Flag(MIRROR_IMAGE, false, 0))) { //镜像BST
		cout << "YES" << endl;
		for (int i = 0; i < n; i++) {
			if (i != 0) putchar(' ');
			cout << postorder[i];
		}
	}
	else cout << "NO";
	free(preorder);
	free(postorder);
	return 0;
}
```
