#include <stdio.h>

void fun(char **(p))
{
	++p;
	printf("%s\n", *p);
}


int main(void)
{
	char *aa[] = {"Morning", "Afternoon", "Evening", "Night"};
	char *bb[4] = {"Morning", "Afternoon", "Evening", "Night"};
	
	aa[1][1]='w'; 
	fun(a);
	printf("%d\n",  sizeof bb);
	printf("%s\n", bb[1]);
	
	int a = 1,b = 2, c = 3;
	a = a+7 = c+b;


}
