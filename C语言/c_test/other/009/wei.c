#include <stdio.h>

int main()
{
	int a[3][3] = {12,15,58,56,69,36,96,45,20};
	printf("a address is %p\n", a);
	printf("main = %p\n", main);
	printf("a[0] address is %p   a[1] address is %p\n",a[0], a[1]);


	return 0;
}
