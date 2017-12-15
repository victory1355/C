#include "digital.h"

//挂载U盘
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
	
	

	system("fdisk -l | awk '{print $1, $9}' > ./usb.txt");
	FILE * fp = fopen("./usb.txt", "r+");
	if(fp == NULL)
	{
		//printf("fopen fail\n");
		return ;
	}
	//else
		//printf("open file successful\n");
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
	
	if(strpbrk(buf_type, "A"))
	{
		sprintf(com,"umount %s", buf_device);
		//printf("%s\n", com);
		system(com);
		bzero(com, sizeof(com));
		
		sprintf(com,"mount -t vfat %s /mnt/wine", buf_device);
		
		//printf("%s\n", com);
		system(com);
		mvaddstr(20, 20, "                                            ");
		mvaddstr(20,20, com);
		refresh();
	}
	
	if(strpbrk(buf_type, "N"))
	{
		sprintf(com,"umount %s", buf_device);
		//printf("%s\n", com);
		system(com);
		bzero(com, sizeof(com));
		sprintf(com,"mount -t ntfs %s /mnt/wine", buf_device);
		//printf("%s\n", com);
		system(com);
		mvaddstr(20, 20, "                                            ");
		mvaddstr(20,20, com);
		refresh();
	}
	
}

//卸载U盘
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
	
	mvaddstr(20, 20, "hello\n");  //
	refresh();
	
	int i =0;
	system("fdisk -l | awk '{print $1, $9}' > ./usb.txt");
	FILE * fp = fopen("./usb.txt", "r+");
	if(fp == NULL)
	{
		//printf("fopen fail\n");
		return ;
	}
	//else
		//printf("open file successful\n");
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
	mvaddstr(22, 30, "                                            ");
	mvaddstr(22,30, com);
	refresh();
	//printf("umount ok\n");
	
}
//U盘检测
void found_usb(int sig)
{
	//printf("welcome\n");
	int fd;
	DIR *dirp;
	dirp = opendir("/proc/scsi/usb-storage");
	if(dirp == NULL)
	{
		mvprintw(LINES/2, COLS/2-5, "                                                  ");
		mvprintw(LINES/2, COLS/2-5, "not found usb device\n");
		//sleep(2);
		//mvprintw(LINES/2, COLS/2-5, "                                                  ");
		refresh();
		return;
	}
	//printf("45345e45545\n");
	struct dirent *entry = NULL;
	char name[100];
	bzero(name, sizeof(name));
	
	while(entry = readdir(dirp))
	{
		if(!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
			continue;
		sprintf(name,"/proc/scsi/usb-storage/%s", entry->d_name);
		//printf("%s\n", name);
		//printf("hello\n");
		fd = open(name, O_RDONLY);
		//printf("dfsdfsdf\n");
		if(fd>0)
		{
			//printf("found usb device\n");
			mvprintw(LINES/2, COLS/2-5, "                                                  ");
			mvprintw(LINES/2, COLS/2-5, "found usb device\n");
			refresh();
			mount_usb();
			flag_usb = 11;
			return;
		}
		
	}
	//printf("not found usb device\n");
	mvprintw(LINES/2, COLS/2-5, "                                                  ");
	mvprintw(LINES/2, COLS/2-5, "not found usb device\n");
	//sleep(2);
	//mvprintw(LINES/2, COLS/2-5, "                                                  ");
	refresh();
	return ;
	//printf("bye\n");
	
}
















