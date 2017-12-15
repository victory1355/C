#include <stdio.h>

int main()
{
	int a[4]= {1,2,3,4};
	int *p1=(int *)(&a+1);
	int *p2=(int )((int )a+1);
	printf("%x,%u,%u\n", p1[-1], *p2, p2[1]);	
	return 0;
}
