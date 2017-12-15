#include <stdio.h>

	
struct a
{
	char name[20];
	double b;
	char sex;

};
int main()
{
	char *p1;
	
	struct a x = {.name="hello",.b = 3.14, .sex = 'n' };
	struct a *p = &x;
	
	p1 = (&p->sex);
	printf("%c      %p\n",*p1, p1);
	p1 = p1+1;
	printf("%c :     %p\n", *p1, p1);
	
	printf("the p   address is %p\n", p);
	p += 1;
	printf("the p+1 address is %p\n", p);

	
	return 0;
	
}
