#include <stdio.h>

int main()
{
	int a = 2, b = 3, num =7;
	float c;

	c = num*1.0/(a+b);
	printf("%d\n", num);
	printf("%f\n", c);
	printf("num == %d\n", num);

	return 0;
}
