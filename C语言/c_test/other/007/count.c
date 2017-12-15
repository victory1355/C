#include <stdio.h>

int main()
{
	char str[10];
	int i = 0, j ,k;

	while((str[i++]=getchar()) != '\n');
	str[i-1] = '\0';
	printf("%s\n", str);

	for(j=0;j<i;j++)
	{
		if(str[j]>='0' && str[j]<='9')
		{
			for(k=j;k<i;k++)
				str[k] = str[k+1];
		}
	}

	printf("%s\n", str);

	for(j=0;j<i;j++)
	{
		if(str[j]>='a' && str[j]<='z')
			str[j] -= 32;
		printf("%c",str[j]);
	}
	printf("\n");
//	printf("%s\n", str);
	return 0;
}

