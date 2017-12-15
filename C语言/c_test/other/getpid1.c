//需求：输入可执行文件名和另外一个进程，打印其PID

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("请输入一个可执行文件名\n");
		return -1;
	}
	struct dirent *pd;
	char buf[100];
	char buf_read[100];
	
	DIR * dir = opendir("/proc/");
	
	if(dir == NULL)
	{
		printf("open dir fail\n");
		return -1;
	}
	printf("argv[1] = %s\n",argv[1]);
	
		
	while((pd = readdir(dir)) != NULL)
	{
		if(!strcmp(pd->d_name, ".") || !strcmp(pd->d_name, ".."))
			continue;
		
		if(pd->d_type == DT_DIR)
		{
			
			bzero(buf, sizeof(buf));
			bzero(buf_read, sizeof(buf_read));
			sprintf(buf, "%s%s/%s", "/proc/", pd->d_name, "comm");
			int fd = open(buf, O_RDONLY);
			if(fd == -1)
			{
				//perror("open fail\n");
				continue;
			}
			else
			read(fd, buf_read, strlen(argv[1]));
			if(!strcmp(buf_read, argv[1]))
			{
				printf("%s pid = %s\n", argv[1], pd->d_name);
				//return 0;
			}
		}
	}
	printf("getpid = %d\n", getpid());
	return -1;
}




















