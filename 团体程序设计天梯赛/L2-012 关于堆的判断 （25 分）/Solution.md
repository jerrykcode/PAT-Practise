# L2-012 关于堆的判断 （25 分）

[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805064676261888)

> 作者: 陈越  
> 单位: 浙江大学  
> 时间限制: 400 ms  
> 内存限制: 64 MB  
> 代码长度限制: 16 KB  

将一系列给定数字顺序插入一个初始为空的小顶堆H[]。随后判断一系列相关命题是否为真。命题分下列几种：
* `is the root`：x是根结点；
* `and y are siblings`：x和y是兄弟结点；
* `is the parent of y`：x是y的父结点；
* `is a child of y`：x是y的一个子结点。

## 输入格式：

每组测试第1行包含2个正整数N（≤ 1000）和M（≤ 20），分别是插入元素的个数、以及需要判断的命题数。下一行给出区间[-10000,10000]内的N个要被插入一个初始为空的小顶堆的整数。之后M行，每行给出一个命题。题目保证命题中的结点键值都是存在的。

## 输出格式：

对输入的每个命题，如果其为真，则在一行中输出T，否则输出F。

## 输入样例：

> 5 4  
> 46 23 26 24 10  
> 24 is the root  
> 26 and 23 are siblings  
> 46 is the parent of 23  
> 23 is a child of 10  


## 输出样例：

> F  
> T  
> F  
> T 

## 思路 

将元素插入最小堆，对每一条输入，调用相应的函数判断

## 代码

[L2-012 关于堆的判断 （25 分）.cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L2-012%20%E5%85%B3%E4%BA%8E%E5%A0%86%E7%9A%84%E5%88%A4%E6%96%AD%20%EF%BC%8825%20%E5%88%86%EF%BC%89/L2-012%20%E5%85%B3%E4%BA%8E%E5%A0%86%E7%9A%84%E5%88%A4%E6%96%AD%20%EF%BC%8825%20%E5%88%86%EF%BC%89.cpp)

```cpp
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

```
