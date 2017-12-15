#include <stdio.h>

int main()
{
	int (*p)(const char *format, ...);
	p = printf;
	p("helloworld\n");
}

