# 1010 Lehmer Code（35 point(s)）

[原题地址](https://pintia.cn/problem-sets/994805148990160896/problems/994805152735674368)

## 题目信息
* Author: LIU, Yaoting
* Organization: 浙江大学
* Time Limit: 400 ms
* Memory Limit: 64 MB
* Code Size Limit: 16 KB

## Description

According to Wikipedia: 
>"In mathematics and in particular in combinatorics, the Lehmer code is a particular way to encode each possible permutation of a sequence of n numbers." 

To be more specific, for a given permutation of items {A1, A2, ⋯, An }, Lehmer code is a sequence of numbers {L1 , L2 , ⋯, Ln } such that Li is the total number of items from Ai to An which are less than Ai . For example, given { 24, 35, 12, 1, 56, 23 }, the second Lehmer code L2 is 3 since from 35 to 23 there are three items, { 12, 1, 23 }, less than the second item, 35.

## Input Specification:
Each input file contains one test case. For each case, the first line gives a positive integer N (≤10^5 ). Then N distinct numbers are given in the next line.

## Output Specification:
For each test case, output in a line the corresponding Lehmer code. The numbers must be separated by exactly one space, and there must be no extra space at the beginning or the end of the line.

## Sample Input:
6  
24 35 12 1 56 23  
## Sample Output:
3 3 1 0 1 0  

## 题意

输入数组A，输出数组L，L[i]为A[i]到A[n - 1]中小于A[i]的元素个数

## 思路

本题更简单解法为使用数状数组。这里的思路是用一颗二叉搜索树BST。将数组A的元素从后往前插入BST，插入A[i]时记录当前BST中小于A[i]的结点个数，此数即为L[i]。插入A[i]时A[i]与根结点T比较，若A[i]比T小则递归插入左子树; 比T大则递归插入右子树，此时T的左子树的结点均比A[i]小，T本身也比A[i]小，故比A[i]小的元素数量增长T的左子树结点个数+1。由于需要记录结点的子节点个数，且为防止BST退化为链表，故使用以结点数量作为平衡依据的SBT平衡树代替普通BST。SBT树由[陈启峰](https://cqf.io/)提出，SBT树参考CSDN:[Size Balanced Tree(SBT树)整理](https://blog.csdn.net/murmured/article/details/17029131)。

## 参考

[Size Balanced Tree(SBT树)整理](https://blog.csdn.net/murmured/article/details/17029131)

## 代码

[Lehmer Code.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Top%20Level%20Practice/1010/Lehmer%20Code.cpp)


```cpp
#include <iostream>
using namespace std;

//SBT树解法

//数组存储树结点
#define KEY(x)    tree[x].key
#define LEFT(x)   tree[x].left
#define RIGHT(x)  tree[x].right
#define SIZE(x)   tree[x].size

#define GET_SIZE(x) (LEFT(x) != -1 ? SIZE(LEFT(x)) : 0) + \
                    (RIGHT(x) != -1 ? SIZE(RIGHT(x)) : 0) + 1

typedef int Index; //数组下标类型
typedef struct SBTNode {
    SBTNode() : key(-1), left(-1), right(-1), size(0) {}
    int key;      //值
    Index left;   //左子树结点在数组中的下标
    Index right;  //右子树结点在数组中的下标
    int size;     //树的总结点个数（包括自己）
} *SBTree;

enum {
    Maintain_Left,  //维护平衡--左子树
    Maintain_Right, //维护平衡--右子树
};

//SBT，类中封装插入结点函数，提供public lehmerCode函数
class SBT {
public:
    SBT(int n);
    ~SBT();
    int lehmerCode(int key); //插入结点key，并返回当前树中比key小的结点总数
private:
    SBTree tree; //存储结点的数组
    int n;       //树的结点个数
    Index root;  //根结点下标，初始化为-1（开始没有结点）
    Index lastNodeIndex;  //数组中最后一个使用的下标，初始为0
    //tree[x] is the SBTree to deal with
    Index left_rotate(Index x);     //对tree[x]进行左旋，返回左旋后的根结点下标
    Index right_rotate(Index x);    //对tree[x]进行右旋，返回右旋后的根结点下标
    Index insert(Index x, int key); //插入结点
    Index maintain(Index x, int maintain_flag); //插入结点后维护平衡树
    bool heighter(Index x, int h);  //判断tree[x]是否有h层高
    int lehmer;  //每次调用lehmerCode函数时更新为0，在insert过程中记录比要插入的key小的结点数量
};

SBT::SBT(int n) {
    this->n = n;
    tree = new SBTNode[n];
    lastNodeIndex = -1;
    root = -1;
}

SBT::~SBT() {
    free(tree);
}

int SBT::lehmerCode(int key) {
    lehmer = 0;
    root = insert(root, key);
    return lehmer;
}

Index SBT::left_rotate(Index x) { //左旋
    Index y = RIGHT(x);
    RIGHT(x) = LEFT(y);
    LEFT(y) = x;
    SIZE(y) = SIZE(x);
    SIZE(x) = GET_SIZE(x);
    return y; //y为左旋后的根结点
}

Index SBT::right_rotate(Index x) { //右旋
    Index y = LEFT(x);
    LEFT(x) = RIGHT(y);
    RIGHT(y) = x;
    SIZE(y) = SIZE(x);
    SIZE(x) = GET_SIZE(x);
    return y; //y为右旋后的根结点
}

Index SBT::insert(Index x, int key) {
   if (x == -1) { //tree[x]不存在
       x = ++lastNodeIndex; //下一个结点
       KEY(x) = key;
       SIZE(x) = 1;
   } else {
       SIZE(x)++;
       if (key < KEY(x)) { //Left
           LEFT(x) = insert(LEFT(x), key); //插入左子树
           x = maintain(x, Maintain_Left); //维护平衡--左子树
       } else {
           lehmer += LEFT(x) != -1 ? SIZE(LEFT(x)) + 1 : 1; //tree[x]的左子树的结点及tree[x]本身均小于key, lehmer增加
           RIGHT(x) = insert(RIGHT(x), key); //插入右子树
           x = maintain(x, Maintain_Right);  //维护平衡--右子树
       }
   }
   return x;
}

Index SBT::maintain(Index x, int maintain_flag) {
    if (x == -1) return x; //tree[x]不存在，本来就平衡
    switch (maintain_flag)
    {
    case Maintain_Left : //维护平衡--左子树
        if (!heighter(LEFT(x), 2)) return x; //左子树不足2层，本来就平衡
        if (SIZE(LEFT(LEFT(x))) > (RIGHT(x) != -1 ? SIZE(RIGHT(x)) : 0)) { //左子树的左子树的size大于右子树的size，不平衡
            x = right_rotate(x);
        } else if (SIZE(RIGHT(LEFT(x))) >(RIGHT(x) != -1 ? SIZE(RIGHT(x)) : 0)) { //左子树的右子树的size大于右子树的size，不平衡
            LEFT(x) = left_rotate(LEFT(x));
            x = right_rotate(x);
        } else return x;
        break;
    case Maintain_Right : //维护平衡--右子树
        if (!heighter(RIGHT(x), 2)) return x; //右子树不足2层，本来就平衡
        if (SIZE(RIGHT(RIGHT(x))) > (LEFT(x) != -1 ? SIZE(LEFT(x)) : 0)) { //右子树的右子树的size大于左子树的size，不平衡
            x = left_rotate(x);
        } else if (SIZE(LEFT(RIGHT(x))) > (LEFT(x) != -1 ? SIZE(LEFT(x)) : 0)) { //右子树的左子树的size大于左子树的size，不平衡
            RIGHT(x) = right_rotate(RIGHT(x));
            x = left_rotate(x);
        } else return x;
        break;
    default:
        break;
    }
    LEFT(x) = maintain(LEFT(x), Maintain_Left);
    RIGHT(x) = maintain(RIGHT(x), Maintain_Right);
    x = maintain(x, Maintain_Left);
    x = maintain(x, Maintain_Right);
    return x; //返回维护后平衡树的根结点
}

bool SBT::heighter(Index x, int h) {
    if (h == 0) return true;
    if (x == -1) return false;
    return heighter(LEFT(x), h - 1) || heighter(RIGHT(x), h - 1);
}

int main()
{
    int n;
    cin >> n;
    int *A = new int[n];
    int *L = new int[n];
    for (int i = 0; i < n; i++) cin >> A[i];
    SBT sbt(n);
    for (int i = n - 1; i >= 0; i--) {
        L[i] = sbt.lehmerCode(A[i]); //SBT插入A[i]，SBT中比A[i]小的结点数量即为L[i]
    }
    for (int i = 0; i < n; i++) {
        if (i != 0) putchar(' ');
        cout << L[i];
    }
    cout << endl;
    free(A);
    free(L);
    return 0;
}
```
