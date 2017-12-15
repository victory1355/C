#include <stdio.h>

int main()
{
	char str1[] = {'a', 'e','i','o', 'u'};
	char str2[] = "aeiou";
	printf("  %d   %#x    %d    %#x\n",
			 sizeof( str1), str1[5], sizeof(str2), str2[5]);

	return 0;
}

