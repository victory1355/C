#include <stdio.h>

int main()
{
	char a[2][3];
	
	printf(" a = %p    &a =  %p    a[0] = %p  &a[0] = %p\n"
			, a, &a, a[0] ,&a[0]);
	
	printf(" a+1 = %p  &a+1 =  %p  a[0]+1 = %p  &a[0]+1= %p\n"
			, a+1, &a+1, a[0]+1, &a[0]+1);
}
