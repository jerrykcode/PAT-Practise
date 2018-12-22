#include <stdio.h>

int main()
{
	int a, b;
	scanf("%d %d", &a, &b);
	int sum = 0;
	int count = 0;
	for (int val = a; val <= b; val++) {
		int nspace = 0;
		if (val < 0) {
			if (val == -100) nspace = 1; //-100
			else if (val <= -10) nspace = 2; //[-99, -10]
			else nspace = 3;//[-9, -1]
		}
		else {
			if (val < 10) nspace = 4;//[0, 9]
			else if (val < 100) nspace = 3; //[10, 99]
			else nspace = 2; //100
		}
		for (int i = 0; i < nspace; i++)
			putchar(' ');
		printf("%d", val);
		count++;
		if (count == 5 || val == b) {
			printf("\n");
			count = 0;
		}
		sum += val;
	}
	printf("Sum = %d\n", sum);
	return 0;
}