#include <stdio.h>

int main()
{
	int f, c;
	scanf("%d", &f);
	c = 5 * (f - 32) / 9;
	printf("Celsius = %d", c);
	return 0;
}