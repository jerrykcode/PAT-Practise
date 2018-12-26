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
