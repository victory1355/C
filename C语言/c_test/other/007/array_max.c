#include <stdio.h>

int main()
{
	int student[10], i, max, pass = 0, fail = 0;
	for(i=0;i<10;i++)
		scanf("%d", &student[i]);
	for(i=0;i<10;i++)
		printf("%-6d", student[i]);
	printf("\n");

//	max = num[i];
	for(i=0;i<10;i++)
	{
		if(student[i]>=60)
			pass++;
		if(student[i]<60)
			fail++;
	//	if(max<num[i])
	//		max = num[i];
	}
	printf("the pass number is %d\n", pass);
	printf("the fail number is %d\n", fail);
//	printf("the max number is %d\n", max);
	
	return 0;
}
