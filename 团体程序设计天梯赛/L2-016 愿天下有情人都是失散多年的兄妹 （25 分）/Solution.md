# L2-016 愿天下有情人都是失散多年的兄妹 （25 分）
[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805061769609216)

> 作者: 陈越  
> 单位: 浙江大学  
> 时间限制: 200 ms  
> 内存限制: 64 MB  
> 代码长度限制: 16 KB  


呵呵。大家都知道五服以内不得通婚，即两个人最近的共同祖先如果在五代以内（即本人、父母、祖父母、曾祖父母、高祖父母）则不可通婚。本题就请你帮助一对有情人判断一下，他们究竟是否可以成婚？

## 输入格式：

输入第一行给出一个正整数N（2 ≤ N ≤10^4），随后N行，每行按以下格式给出一个人的信息：

> 本人ID 性别 父亲ID 母亲ID


其中ID是5位数字，每人不同；性别M代表男性、F代表女性。如果某人的父亲或母亲已经不可考，则相应的ID位置上标记为-1。

接下来给出一个正整数K，随后K行，每行给出一对有情人的ID，其间以空格分隔。

`注意：题目保证两个人是同辈，每人只有一个性别，并且血缘关系网中没有乱伦或隔辈成婚的情况。`

## 输出格式：

对每一对有情人，判断他们的关系是否可以通婚：如果两人是同性，输出Never Mind；如果是异性并且关系出了五服，输出Yes；如果异性关系未出五服，输出No。

## 输入样例：

> 24  
> 00001 M 01111 -1  
> 00002 F 02222 03333  
> 00003 M 02222 03333  
> 00004 F 04444 03333  
> 00005 M 04444 05555  
> 00006 F 04444 05555  
> 00007 F 06666 07777  
> 00008 M 06666 07777  
> 00009 M 00001 00002  
> 00010 M 00003 00006  
> 00011 F 00005 00007  
> 00012 F 00008 08888  
> 00013 F 00009 00011  
> 00014 M 00010 09999  
> 00015 M 00010 09999  
> 00016 M 10000 00012  
> 00017 F -1 00012  
> 00018 F 11000 00013  
> 00019 F 11100 00018  
> 00020 F 00015 11110  
> 00021 M 11100 00020  
> 00022 M 00016 -1  
> 00023 M 10012 00017  
> 00024 M 00022 10013  
> 9  
> 00021 00024  
> 00019 00024  
> 00011 00012  
> 00022 00018  
> 00001 00004  
> 00013 00016  
> 00017 00015  
> 00019 00021  
> 00010 00011  


## 输出样例：

Never Mind  
Yes  
Never Mind  
No  
Yes  
No  
Yes  
No  
No  

## 思路

用二叉树结构存储一个人的信息，包括id，性别，父亲id和母亲id。用长度为100000的数组存储树结构体的指针（id对应数组下标）。
对每一对id，若他们的性别不同，判断从它们开始层序遍历5层之内的结点有无相同。对一个id层序遍历时，将5层内的结点id用map
记录，对另一个id层序遍历时，判断5层内的结点id有无在map中出现过。

注意输入时，若一个id的父母id未输入过，则也应将父母作为新的结构体存储。参考 //http://www.cnblogs.com/taozi1115402474/p/8486484.html


## 代码

```cpp
#include <iostream>
#include <queue>
#include <map>
using namespace std;

typedef struct Node {
	int id;
	char gender;
	int father_id, mother_id;
	Node(int id, char gender, int father_id, int mother_id) : id(id),
		gender(gender),
		father_id(father_id),
		mother_id(mother_id)
	{

	}
	~Node() {}
} *Tree;
Tree list[100000];
map<int, bool> id_exist;

bool bfs(int id, bool flag) {
	queue<Tree> q;
	q.push(list[id]);	
	Tree last = list[id], tail = list[id];
	int level = 1;
	while (!q.empty()) {
		Tree t = q.front();
		q.pop();
		if (t == NULL) continue;
		if (t->father_id != -1) {
			q.push(list[t->father_id]);
			last = list[t->father_id];
			if (flag) id_exist[t->father_id] = true;
			else if (id_exist[t->father_id]) return false;
		}
		if (t->mother_id != -1) {
			q.push(list[t->mother_id]);
			last = list[t->mother_id];
			if (flag) id_exist[t->mother_id] = true;
			else if (id_exist[t->mother_id]) return false;
		}
		if (t == tail) {
			if (++level == 5) break;
			tail = last;
		}
	}
	queue<Tree>().swap(q);
	return true;
}

int main()
{
	int n;
	scanf("%d", &n);
	int id, father_id, mother_id;
	char gender;
	for (int i = 0; i < n; i++) {
		scanf("%d %c %d %d", &id, &gender, &father_id, &mother_id);
		list[id] = new Node(id, gender, father_id, mother_id);
		if (list[father_id] == NULL) list[father_id] = new Node(father_id, 'M', -1, -1); //http://www.cnblogs.com/taozi1115402474/p/8486484.html
		if (list[mother_id] == NULL) list[mother_id] = new Node(mother_id, 'F', -1, -1);
	}
	int k, id1, id2;
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &id1, &id2);
		if (list[id1]->gender == list[id2]->gender)
			printf("Never Mind\n");
		else {
			id_exist.clear();
			bfs(id1, true);
			if (bfs(id2, false)) {
				printf("Yes\n");
			}
			else printf("No\n");
		}
	}
	for (int i = 0; i < 100000; i++)
		if (list[i] != NULL)
			delete list[i];
	id_exist.clear();
	map<int, bool>().swap(id_exist);
	return 0;
}
```
