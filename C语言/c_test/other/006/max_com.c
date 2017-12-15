#include <stdio.h>


int max_common;

void max_com1(int ,int);
void max_com(int ,int);

int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	printf("%d   %d\n" , a, b);
	max_com1(a ,b);
	printf("the max_common is %d\n",max_common);

	return 0;
	
}

void max_com1(int a, int b)
{
	int temp;
	do
	{
		if(a>b)
			temp = a-b;
		else
 			temp = b-a;
		if(temp)
		{
			a = b;	
			b = temp;
		}
	}while(temp != 0);

	max_common = b;
}
void max_com(int a, int b)
{
//	int a_, b_;
	int p;
	do
	{
		p = a%b;
		a = b;
		b = p;	

	}while(p!=0);
	max_common = a;
}
