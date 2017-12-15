#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sort(void *data, int n, int type_size, 
			int (*ptr)(const void *, const void *))
{
	int i,j;
	void *temp = malloc(type_size);
	void *addr_1, *addr_2;
	
	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j<n;j++)
		{
			addr_1 = data+i*type_size;
			addr_2 = data+j*type_size;
			

			if(ptr(addr_1,addr_2)>0)
			{
				memcpy(temp,addr_1,type_size);
				memcpy(addr_1,addr_2,type_size);
				memcpy(addr_2,addr_1,type_size);
			}
			
		}		
	}	
	free(temp);
}

int comp_int(const void *a, const void *b)
{
	if(*(int *)a-*(int *)b>0)
		return 1;
	else if(*(int*)a-*(int*)b<0)
		return 0;
	return -1;
}


int comp_double(const void *a, const void *b)
{
	if(*(double*)a-*(double*)b>0)
		return 1;
	else if(*(double*)a-*(double*)b<0.001)
		return 0;
	return -1;
	
}


int main()
{
	int i;
	int group_ints[10] = {4,5,3,2,3,4,6,8,9,10};
	double group_doubles[10] = {12.3,4,5,3.4,1,8.12,45,23,3.14,78};

	printf("ints test-----------------------\n");
	sort(group_ints, 10,sizeof(int), comp_int);

	for(i=0;i<10;i++)
		printf("%d", group_ints[i]);
	printf("\n");
	
	printf("dobs test-----------------------\n");
	
	sort(group_doubles,10, sizeof(double), comp_double);

	
	for(i=0;i<10;i++)
		printf("%.2f", group_doubles[i]);
	printf("\n");
	

	return 0;	
}
