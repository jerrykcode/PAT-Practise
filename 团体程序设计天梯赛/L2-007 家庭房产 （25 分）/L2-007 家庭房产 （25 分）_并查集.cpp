#include <iostream>
#include <algorithm>
using namespace std;

#define MIN(a, b) (a < b ? a : b)
#define ID_INF 10000
typedef short ID;
typedef struct Family {
	ID min_id;
	short size;
	double nHouse;
	double area;
	Family() {}
	Family(ID min_id, double nHouse, double area) : min_id(min_id), nHouse(nHouse), area(area) {}
} *PFamily;

struct SetData {
	ID parent;
	PFamily pFamily;
};
bool compare(SetData a, SetData b) {
	if (a.pFamily != NULL && b.pFamily != NULL) {
		return (a.pFamily->area != b.pFamily->area ? (a.pFamily->area > b.pFamily->area) : (a.pFamily->min_id < b.pFamily->min_id));
	}
	else if (a.pFamily != NULL || b.pFamily != NULL) { //非NULL的排在前
		return a.pFamily != NULL;
	}
	else return a.parent < b.parent; //均为NULL时并列即可，a.parent < b.parent可以改为任意判断句
}

class USet {
public:
	USet() {
		_set = new SetData[ID_INF];
		for (int i = 0; i < ID_INF; i++) {
			_set[i].parent = -1;
			_set[i].pFamily = NULL;
		}
	}
	~USet() {
		for (int i = 0; i < ID_INF; i++)
			if (_set[i].pFamily != NULL) {
				delete _set[i].pFamily;
				_set[i].pFamily = NULL;
			}
		free(_set);
	}

	void unionSet(ID a, ID b); //合并a，b
	void add(ID a, double nHouse, double area); //对a所属的集合增加nHouse, area
	int size(); //集合数量
	void printSetData(); //输出
private:
	ID findRoot(ID a);
	SetData *_set;
};

ID USet::findRoot(ID a) {
	if (_set[a].parent < 0) return a;
	return _set[a].parent = findRoot(_set[a].parent);
}

void USet::unionSet(ID a, ID b) {
	if (a == -1 || b == -1) return;
	ID root_a = findRoot(a);
	ID root_b = findRoot(b);
	if (root_a == root_b) return;
	ID root_x, root_y;
	//小集合并到大集合上
	if (_set[root_a].parent < _set[root_b].parent) {
		root_x = root_a;
		root_y = root_b;
	}
	else {
		root_x = root_b;
		root_y = root_a;
	}
	_set[root_x].parent += _set[root_y].parent;
	_set[root_y].parent = root_x;
	if (_set[root_x].pFamily == NULL)
		_set[root_x].pFamily = new Family(root_x, 0.0, 0.0);
	if (_set[root_y].pFamily == NULL)
		_set[root_y].pFamily = new Family(root_y, 0.0, 0.0);
	if (_set[root_x].pFamily->min_id > _set[root_y].pFamily->min_id)
		_set[root_x].pFamily->min_id = _set[root_y].pFamily->min_id;
	_set[root_x].pFamily->nHouse += _set[root_y].pFamily->nHouse;
	_set[root_x].pFamily->area += _set[root_y].pFamily->area;
	delete _set[root_y].pFamily;
	_set[root_y].pFamily = NULL;
}

void USet::add(ID a, double nHouse, double area) {
	ID root = findRoot(a);
	if (_set[root].pFamily == NULL)
		_set[root].pFamily = new Family(root, 0.0, 0.0);
	_set[root].pFamily->nHouse += nHouse;
	_set[root].pFamily->area += area;
}

int USet::size() {
	int _size = 0;
	for (int i = 0; i < ID_INF; i++)
		if (_set[i].pFamily != NULL)
			_size++;
	return _size;
}

void USet::printSetData() {
	for (ID id = 0; id < ID_INF; id++) {
		if (_set[id].pFamily == NULL) continue;
		int size = _set[id].parent * (-1);
		_set[id].pFamily->nHouse /= size; //平均值
		_set[id].pFamily->area /= size;
	}
	sort(_set, _set + ID_INF, compare);
	for (ID id = 0; id < ID_INF; id++) {
		if (_set[(int)id].pFamily == NULL)continue;
		int size = _set[id].parent * (-1);
		printf("%04hd %d %.3f %.3f\n", _set[id].pFamily->min_id, size, _set[id].pFamily->nHouse, _set[id].pFamily->area);
	}
}


int main()
{
	USet uset;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		ID id, father_id, mother_id, child_id;
		scanf("%hd %hd %hd", &id, &father_id, &mother_id);
		uset.unionSet(id, father_id);
		uset.unionSet(id, mother_id);
		int k;
		scanf("%d", &k);
		for (int i = 0; i < k; i++) {
			scanf("%hd", &child_id);
			uset.unionSet(id, child_id);
		}
		double nHouse, area;
		scanf("%lf %lf", &nHouse, &area);
		uset.add(id, nHouse, area);
	}
	printf("%d\n", uset.size());
	uset.printSetData();
	return 0;
}
