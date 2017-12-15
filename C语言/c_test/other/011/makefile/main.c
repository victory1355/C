#include <stdio.h>
#include "sub_func.h"
#include "add_func.h"

int main()
{
	int  i, j, number;
	
	printf("input two interger:\n");
	scanf("%d%d", &i, &j);
	
	number = add_func(i, j);
	printf("i+j = %d\n", number);
		
	number = sub_func(i, j);
	printf("i-j = %d\n", number);


	return 0;
	
}
