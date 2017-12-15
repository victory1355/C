#include <stdio.h>

int b = 99;
int c;

int main()
{
	int a = 88;	
	static int d;
	static int e = 11;
	
	printf("&a = %p, &b = %p, &c = %p, &d = %p, &e = %p\n", 
		&a, &b, &c, &d, &e);
	printf("main = %p\n", main);

	char *ptr = "helloworld";
	printf("ptr = %p\n", ptr);
	
	int *pmal = malloc(20);
	printf("pmal = %p\n", pmal);

	return 0;
}
