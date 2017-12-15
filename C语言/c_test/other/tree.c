#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <pthread.h>
#include <unistd.h>

int i;

void *count_time(void *arg)
{
	//int i = 0;
	while(1)
	{
		printf("second:%d\n", ++i);
		sleep(1);
	}
}

int main(int argc ,char *argv[])
{
	i = 0;
	if(argc != 2)
	{
		printf("Usage:xxx.elf dest_path\n");
		return -1;
	}
	char com[300];
	bzero(com, sizeof(com));
	
	sprintf(com ,"tree %s", argv[1]);
	
	
	pthread_t time;
	int ret = pthread_create(&time, NULL, count_time, NULL);
	if(ret != 0)
	{
		printf("create fail\n");
		return -1;
	}
	
	system(com);
	printf("second : %d\n", i);
	pthread_cancel(time);
	//printf("hello\n");
	int retj = pthread_join(time, NULL);
	
	if(retj != 0)
	{
		printf("jion fail\n");
	}
	else
		printf("join ok\n");
	
	//sleep(2);
	pthread_exit(NULL);
	
	return 0;
}

























