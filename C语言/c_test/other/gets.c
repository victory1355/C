#include <stdio.h>
#include <strings.h>

int main()
{
	char ch = '&';
	int i = 0;
	FILE * fp =fopen("./usb.txt", "r+");
	if(fp == NULL)
	{
		printf("fopen fail\n");
		return -1;
	}
	char buf[100];
	bzero(buf, sizeof(buf));
	fseek(fp,0, SEEK_END);
	while(ch != ' ')
	{
		 fseek(fp,-(++i), SEEK_END);
		 ch =fgetc(fp);
		
	}
	fscanf(fp,"%s", buf);
	printf("buf = %s\n", buf);
	
	char buf1[100];
	bzero(buf1, sizeof(buf1));

	char ch1 = '&';
	while(ch1 != '\n' && ch1 != ' ')
	{
		fseek(fp,-(++i), SEEK_END);
		ch1 =fgetc(fp);
	}
	fscanf(fp,"%s", buf1);
	printf("buf1 = %s\n", buf1);
	
	
	return 0;
}