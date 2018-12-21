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

