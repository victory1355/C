#include <stdio.h>

void swap(int *x,int *y);


int main()
{
	int a = 20;
	int b = 30;
	
	printf("a=%d     %p,b=%d     %p.\n", a, &a , b, &b);

	swap(&a, &b);
	printf("a=%d     %p, b=%d     %p.\n", a, &a, b, &b);

	return 0;
}

void swap(int* x,int* y)
{
	int *p;
	p = x;
	x = y;
	y = p;
	printf("%d     %p %d    %p \n", *x, x, *y, y);
}
