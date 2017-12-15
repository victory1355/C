#include <stdio.h>

char *get_memory(void)
{
	char p[] = "hello world";
	printf("p = %p\n", p);

	return p;
}
int main()
{
	char *str;
	str =  get_memory();
	//printf("%s\n", str);
	printf("str = %p\n", str);
}

