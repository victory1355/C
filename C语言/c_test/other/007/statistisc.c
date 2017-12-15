#include <stdio.h>

int main()
{
	int i=0, j, count=0;
	
	char str1[20], str2[] = {'a', 'e', 'i', 'o', 'u'};
	printf("%d  %d \n", str2[5], str2[6]);

	while((str1[i++]=getchar())!='#');
	str1[i-1] = '\0';
	
	
	printf("the str2 content is %s", str2);
	printf("the str1 content is %s\n", str1);

	printf("%d,,%d\n", strlen(str2),sizeof(str2));
	
	i = 0;
	while(str1[i])
	{
		for(j=0;j<5;j++)
			if(str1[i]==str2[j])
				count++;
		i++;
	}
	
	printf("the number of the same word  == %d\n", count);

	return 0;
}
