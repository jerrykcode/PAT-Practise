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
