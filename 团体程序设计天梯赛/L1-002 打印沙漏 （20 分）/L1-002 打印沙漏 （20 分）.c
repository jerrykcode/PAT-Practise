#include <stdio.h>

int main()
{
	int n;
	char c;
	scanf("%d %c", &n, &c);
	int len = 1, sum = 1;
	while (sum <= n) {
		len += 2;
		sum += 2 * len;
	}
	sum -= 2 * len;
	len -= 2;
	int space = 0;
	int flag = 0;
	while (space >= 0) {
		for (int i = 0; i < space; i++)
			putchar(' ');
		for (int i = 0; i < len - 2 * space; i++)
			putchar(c);
		/*for (int i = 0; i < space; i++)
			putchar(' ');*/
		if (len - 2 * space == 1) flag = 1;
		if (flag == 0) space++;
		else space--;
		printf("\n");
	}
	printf("%d", (n - sum));
	return 0;
}