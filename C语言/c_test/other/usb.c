#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <stdlib.h>

int flag_stop;
int flag_continue;
int flag_exit;

//挂载USB设备
void mount_usb()
{
	char buf_device[100];
	bzero(buf_device, sizeof(buf_device));
	char buf_type[100];
	bzero(buf_type, sizeof(buf_type));
	char com[50];
	bzero(com, sizeof(com));

	char ch1 = '&';
	char ch2 = '&';
	
	int i =0;
	system("fdisk -l | awk '{print $1, $8}' > ./usb.txt");
	FILE * fp = fopen("./usb.txt", "r+");
	if(fp == NULL)
	{
		printf("fopen fail\n");
		return ;
	}
	else
		printf("open file successful\n");
	fseek(fp,0, SEEK_END);
	while(ch1 != ' ')
	{
		 fseek(fp,-(++i), SEEK_END);
		 ch1 =fgetc(fp);
		
	}
	fscanf(fp,"%s", buf_type);
	//printf("type: %s\n", buf_type);
	
	while(ch2 != '\n' && ch2 != ' ')
	{
		fseek(fp,-(++i), SEEK_END);
		ch2 =fgetc(fp);
	}
	fscanf(fp,"%s", buf_device);
	
	sprintf(com,"mount -t ntfs %s /mnt/wine", buf_device);
	system(com);
	printf("mount ok\n");
	//printf("device: %s\n", buf_device);
}
//卸载USB设备
void umount_usb()
{
	char buf_device[100];
	bzero(buf_device, sizeof(buf_device));
	char buf_type[100];
	bzero(buf_type, sizeof(buf_type));
	char com[50];
	bzero(com, sizeof(com));

	char ch1 = '&';
	char ch2 = '&';
	
	int i =0;
	system("fdisk -l | awk '{print $1, $8}' > ./usb.txt");
	FILE * fp = fopen("./usb.txt", "r+");
	if(fp == NULL)
	{
		printf("fopen fail\n");
		return ;
	}
	else
		printf("open file successful\n");
	fseek(fp,0, SEEK_END);
	while(ch1 != ' ')
	{
		 fseek(fp,-(++i), SEEK_END);
		 ch1 =fgetc(fp);
		
	}
	fscanf(fp,"%s", buf_type);
	
	while(ch2 != '\n' && ch2 != ' ')
	{
		fseek(fp,-(++i), SEEK_END);
		ch2 =fgetc(fp);
	}
	fscanf(fp,"%s", buf_device);
	
	sprintf(com,"umount %s", buf_device);
	system(com);
	printf("umount ok\n");
	
	
	
}
//检测USB设备
void found_usb(int sig)
{
	//printf("welcome\n");
	int fd;
	DIR *dirp;
	dirp = opendir("/proc/scsi/usb-storage");
	if(dirp == NULL)
	{
		printf("not found usb device\n");
		return;
	}
	struct dirent *entry = NULL;
	char name[100];
	bzero(name, sizeof(name));
	
	while(entry = readdir(dirp))
	{
		if(!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
			continue;
		sprintf(name,"/proc/scsi/usb-storage/%s", entry->d_name);
		printf("hello\n");
		fd = open(name, O_RDONLY);
		if(fd>0)
		{
			printf("found usb device\n");
			mount_usb();
			flag = 11;
			return ;
		}
		
	}
	printf("not found usb device\n");
	return;
	//printf("bye\n");
	
}
//信号处理函数
void stop_music_photo(sig)
{
	flag_stop = 100;
}
void continue_music_photo(int sig)
{
	flag_continue = 100;
}
void exit_auto(int sig)
{
	flag_exit = 104;
}

//进入自动模式
void auto_model(File_info *head_music1, File_info *head_photo1)
{
	//全局变量
	flag_stop = 101;
	flag_continue = 102;
	flag_exit = 103;
	
	signal(30, stop_music_photo);
	signal(40, continue_music_photo);
	signal(50, exit_auto);
	
	while(1)
	{
		//循环播放，收到停止信号就暂停音乐和图片
		if(flag_stop == 101)
		{
			//随机播放音乐
			sleep(3);
			//打开图片
		}
		if(flag_stop == 100)
		{
			//停止播放音乐和图片
		}
		if(flag_continue == 100)
		{
			//继续播放音乐和图片
		}
		if(flag_exit == 104)
		{
			//退出自动模式
			break;
		}
	}
	//提示用户退出自动模式
	
	
}

//用户输入信号
send_signal()
{	
	int key;
	mvaddstr(20,20,"press 'c','s','e' ");
	do{
		key = getch();    //阻塞状态
		switch(key)
		{
			case 's';
					//停止播放音乐和图片，产生停止信号
					raise(30);
			case 'c';
					//继续播放音乐和图片，产生继续信号
					raise(40);
			case 'e';
					//退出自动模式，产生退出信号
					raise(50);
			default:break;
		}
			
	}while(1)
	
}

/*int main(int argc ,char *argv[])
{
	//alarm(2);
	signal(SIGALRM, found_usb);
	while(1)
	{
		if(flag == 10)
			raise(SIGALRM);
		sleep(10);
		printf("doing other thing\n");
		umount_usb();
	}
		
	return 0;
}*/
















