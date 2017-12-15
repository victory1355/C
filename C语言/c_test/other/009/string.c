#include <stdio.h>

int main()
{
	
	int i = 0;
	char *p;
	char str3[20];
	p = str3;
	char str1[10] = "hello", str2[10] = "world";
//	str1++;//&str[0] = &str[0]+1;
	while(str1[i] != '\0')
	{
		*p = str1[i];
		p++;
		i++;
	}	
	i = 0;
	while(str2[i] != '\0')
	{
		*p = str2[i];
		p++;
		i++;
	}
	*p++ = '\0';
	printf("%s\n", str3);
}
