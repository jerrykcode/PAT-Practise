#include <iostream>
using namespace std;

struct node {
	int ad, data, next;
};

int main()
{
	int head, n, k;
	cin >> head >> n >> k;
	node  list[100000];
	for (int i = 0; i < n; i++) {
		int ad;
		cin >> ad;
		cin >> list[ad].data >> list[ad].next;
	}
	int p0 = -1, tmp0, p1 = -1, tmp1, p2 = -1, tmp2;
	int ad = head;
	while (ad != -1) {
		if (list[ad].data < 0) {
			if (p0 == -1) {
				p0 = ad;
				tmp0 = p0;
			}
			else {
				list[tmp0].next = ad;
				tmp0 = ad;
			}
		}
		else if (list[ad].data <= k) {
			if (p1 == -1) {
				p1 = ad;
				tmp1 = p1;
			}
			else {
				list[tmp1].next = ad;
				tmp1 = ad;
			}
		}
		else {
			if (p2 == -1) {
				p2 = ad;
				tmp2 = p2;
			}
			else {
				list[tmp2].next = ad;
				tmp2 = ad;
			}
		}
		ad = list[ad].next;
	}
	if (p0 != -1) {
		ad = p0;
		while (ad != tmp0) {
			printf("%05d %d ", ad, list[ad].data);
			if (list[ad].next != -1) printf("%05d\n", list[ad].next);
			else cout << "-1" << endl;
			ad = list[ad].next;
		}
		printf("%05d %d ", tmp0, list[tmp0].data);
		if (p1 != -1) printf("%05d\n", p1);
		else if (p2 != -1) printf("%05d\n", p2);
		else cout << "-1" << endl;
	}
	if (p1 != -1) {
		ad = p1;
		while (ad != tmp1) {
			printf("%05d %d ", ad, list[ad].data);
			if (list[ad].next != -1) printf("%05d\n", list[ad].next);
			else cout << "-1" << endl;
			ad = list[ad].next;
		}
		printf("%05d %d ", tmp1, list[tmp1].data);
		if (p2 != -1) printf("%05d\n", p2);
		else cout << "-1" << endl;
	}
	if (p2 != -1) {
		ad = p2;
		while (ad != tmp2) {
			printf("%05d %d ", ad, list[ad].data);
			if (list[ad].next != -1) printf("%05d\n", list[ad].next);
			else cout << "-1" << endl;
			ad = list[ad].next;
		}
		printf("%05d %d ", tmp2, list[tmp2].data);
		cout << "-1" << endl;
	}
	return 0;
}