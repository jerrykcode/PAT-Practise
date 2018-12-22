#include <stdio.h>

#define MAX(a, b) (a > b ? a : b)
#define MAX_THREE(a, b, c) (MAX(MAX(a, b), c))
#define MIN(a, b) (a < b ? a : b)
#define MIN_THREE(a, b, c) (MIN(MIN(a, b), c))

int main() {
	int a, b, c;
	scanf("%d %d %d ", &a, &b, &c);
	int max = MAX_THREE(a, b, c);
	int min = MIN_THREE(a, b, c);
	printf("%d->", min);
	if (a != max && a != min) printf("%d", a);
	else if (b != max && b != min) printf("%d", b);
	else printf("%d", c);
	printf("->%d", max);
	return 0;
}