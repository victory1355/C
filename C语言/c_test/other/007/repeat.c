#include <stdio.h>
#include <string.h>

int main()
{
	char ch[10]="hello";
	printf("%d\n", strlen(ch));

//	int ch_i = 0;
	gets(ch);
	printf("%d\n", strlen(ch));

	printf("the ch[0] is %c\n", ch[0]);
	printf("the last one is %c\n", ch[strlen(ch)]);


//	ch[ch_i-1] = '\0';
	printf("%s\n", ch);

	return 0;
}

