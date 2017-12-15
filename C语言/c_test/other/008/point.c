#include <stdio.h>

int main()
{
	int number =123;
	int  *p = &number;
	printf("%p     %p\n", &number, p);
}
