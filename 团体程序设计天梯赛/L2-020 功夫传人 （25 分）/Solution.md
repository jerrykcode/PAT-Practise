# L2-020 功夫传人 （25 分）
[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805059118809088)

> 作者: 陈越  
> 单位: 浙江大学  
> 时间限制: 400 ms  
> 内存限制: 64 MB  
> 代码长度限制: 16 KB  

一门武功能否传承久远并被发扬光大，是要看缘分的。一般来说，师傅传授给徒弟的武功总要打个折扣，于是越往后传，弟子们的功夫就越弱…… 直到某一支的某一代突然出现一个天分特别高的弟子（或者是吃到了灵丹、挖到了特别的秘笈），会将功夫的威力一下子放大N倍 —— 我们称这种弟子为“得道者”。

这里我们来考察某一位祖师爷门下的徒子徒孙家谱：假设家谱中的每个人只有1位师傅（除了祖师爷没有师傅）；每位师傅可以带很多徒弟；并且假设辈分严格有序，即祖师爷这门武功的每个第i代传人只能在第i-1代传人中拜1个师傅。我们假设已知祖师爷的功力值为Z，每向下传承一代，就会减弱r%，除非某一代弟子得道。现给出师门谱系关系，要求你算出所有得道者的功力总值。

## 输入格式：

输入在第一行给出3个正整数，分别是：N（≤10^5）——整个师门的总人数（于是每个人从0到N-1编号，祖师爷的编号为0）；Z——祖师爷的功力值（不一定是整数，但起码是正数）；r ——每传一代功夫所打的折扣百分比值（不超过100的正数）。接下来有N行，第i行（i=0,?,N?1）描述编号为i的人所传的徒弟，格式为：

`Ki ID[1] ID[2] ID[Ki]`

其中`Ki`是徒弟的个数，后面跟的是各位徒弟的编号，数字间以空格间隔。`Ki`为零表示这是一位得道者，这时后面跟的一个数字表示其武功被放大的倍数。

## 输出格式：

在一行中输出所有得道者的功力总值，只保留其整数部分。题目保证输入和正确的输出都不超过10^10。

## 输入样例：

> 10 18.0 1.00  
> 3 2 3 5  
> 1 9  
> 1 4  
> 1 7  
> 0 7  
> 2 6 1  
> 1 8  
> 0 9  
> 0 4  
> 0 3  


## 输出样例：

> 404 

## 思路

用结构体存储每个人的id，功力放大倍数（若不是得道者则为0，忽略此项），功力，及弟子（用vector存弟子id，得道者没有弟子，其vector为空）。
输入时即可确定每个人的id，功力放大倍数及弟子。若祖师爷是得道者，则输出z*祖师爷的功力放大倍数即可，否则bfs层序遍历，求出每个人的功力，
对于得道者，其功力需乘以功力放大倍数，并计入结果中。

## 代码

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct Node {
	int id;
	double multiple;
	double power;
	vector<int> disciple;
	Node(int id) : id(id), multiple(0.0), power(0.0) {}
	~Node() {};
} *Tree;

int bfs(Tree *list, int n, double z, double r) {	
	if (list[0]->multiple > 0)
		return (int)(z * list[0]->multiple);
	double result = 0;
	list[0]->power = z;
	queue<Tree> q;
	q.push(list[0]);	
	while (!q.empty()) {
		Tree t = q.front();
		q.pop();
		for (int id : t->disciple) {
			list[id]->power = t->power * (100 - r) / 100;
			if (list[id]->multiple > 0) {
				list[id]->power *= list[id]->multiple;
				result += list[id]->power;
			}
			else q.push(list[id]);
		}
	}
	queue<Tree>().swap(q);
	return (int)result;
}

int main()
{
	int n;
	double z, r;
	cin >> n >> z >> r;
	Tree *list = new Tree[n];
	int k;
	for (int i = 0; i < n; i++) {
		cin >> k;
		list[i] = new Node(i);
		if (k > 0) {
			int id;
			for (int j = 0; j < k; j++) {
				cin >> id;
				list[i]->disciple.push_back(id);
			}
		}
		else {//k == 0
			double p;
			cin >> p;
			list[i]->multiple = p;
		}
	}
	printf("%d", bfs(list, n, z, r));
	for (int i = 0; i < n; i++)
		if (list[i] != NULL)
			delete list[i];
	free(list);
	return 0;
}
```

