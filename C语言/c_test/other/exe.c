#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int Get_proc_Pid(const char *path,char pid[])
{
	DIR *dir;
	int fd;
	struct dirent *tmp;
	
	char dir_buffer[40];
	char r_buffer[20];
	
	//打开系统管理进程目录
	dir = opendir("/proc/");
	if(dir == NULL)
	{
		printf("opend dir failure!\n");
		return -1;
	}
	//检索目录下的文件
	while((tmp = readdir(dir)) != NULL)
	{
		if(!strcmp(tmp->d_name,".") || !strcmp(tmp->d_name,".."))
			continue;
		//判断是否为目录
		if(tmp->d_type == DT_DIR)
		{
			memset(dir_buffer,0,sizeof(dir_buffer));
			//拼接存放进程名文件的路径
			sprintf(dir_buffer,"%s%s/%s","/proc/",tmp->d_name,"comm");
			fd = open(dir_buffer,O_RDONLY);
			if(fd  == -1)
			{
				//printf("open file failure!\n");
				continue;
			}
			bzero(r_buffer,sizeof(r_buffer));
			//读文件中进程名
			read(fd,r_buffer,strlen(path));
			if(!strcmp(r_buffer,path))
			{
				strcpy(pid,tmp->d_name);
				return 0;
			}
		
		}
		
	}
	return -1;
}

int main(int argc, char *argv[])
{
	char pid[8];
	int i;
	
	memset(pid ,0 ,8);
	if(argc != 2 )
	{
		printf("请输入可执行文件及另一个进程名\n");
		return -1;
	}
	
	i = Get_proc_Pid(argv[1],pid);

	if(i == -1)
	{
		printf("查找进程PID失败！\n");
	}
	else
		printf("%s 进程PID: %d\n",argv[1],atoi(pid));
		
	return 0;
}