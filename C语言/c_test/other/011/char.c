#include <stdio.h>

int main()
{
	int a[10] = {1, 32, 45};
	
	int *p = a;	
	p[0] = 100;
	
	printf("p[0] = %d, &a[0] = %d\n", p[0], &a[0]);
	
	return 0;
}
