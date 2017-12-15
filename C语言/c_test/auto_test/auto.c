#include "auto.h"

//信号处理函数
void stop_music_photo(int sig)
{
	printf("get the signal %d to stop\n", sig);
	flag_stop = 100;
	//其他都不满足
	flag_continue = 102;
	flag_exit = 103;
	flag_work = 100;
}
void continue_music_photo(int sig)
{
	printf("get the %d signal to continue\n", sig);
	flag_continue = 100;
	//其他条件都不满足
	flag_stop = 102;
	flag_exit = 103;
	flag_work = 100;
}
void exit_auto(int sig)
{
	//printf("exit\n");
	printf("get the signal %d to exit\n", sig);
	flag_exit = 104;
}
//进入自动模式
int auto_model(File_info *head_music1, File_info *head_photo1)
{
	if(head_music1 == NULL)
		return -1;
	if(head_photo1 == NULL)
		return -1;
	
	flag_stop = 101;
	flag_continue = 102;
	flag_exit = 103;
	flag_work = 104;
	
	char com_stop[50];
	
	while(1)
	{
		if(flag_exit == 104)
		{
			printf("thank you for using again! goodbye\n");
			sleep(1);
			break;
		}
		//循环播放，收到停止信号就暂停音乐和图片
		if(flag_work == 104)
		{
			//随机播放音乐
			printf("welcome to auto model\n");
			//rand_music(head_music1);
			sleep(3);
			//打开图
			brower_photo(head_photo1);
		}
		if(flag_stop == 100)
		{
			//停止播放音乐和图片
			printf("stoping music and photo..............!\n");
			//sleep(10);
			
			bzero(com_stop, sizeof(com_stop));
			sprintf(com_stop,"killall shotwell");
			printf("%s\n", com_stop);
			
			system(com_stop);
			
			sleep(1);
			/*
			bzero(com_stop, sizeof(com_stop));
			sprintf(com_stop, "")
			system(com_stop);
			sleep(1);*/
			
		}
		if(flag_continue == 100)
		{
			//随机播放音乐
			//rand_music(head_music1);
			printf("continuing open photo................\n");
			sleep(3);
			//打开图
			brower_photo(head_photo1);
		}
		//用户输入信号值
		send_signal();
		sleep(3);
	}
	return 0;
}
//发送信号
int send_signal()
{
	char key;
	int flag =1;
	//注册信号
	signal(30, stop_music_photo);
	signal(40, continue_music_photo);
	signal(50, exit_auto);
	
	printf("1,press 'c' to continue 2,presss 's' to stop 3,press 'e' to exit\n");
	printf("input:");
	do
	{
		key = getchar();  //阻塞模式
		switch(key)
		{
			case 'c':raise(40);flag = 0;break;
			case 's':raise(30);flag = 0;break;
			case 'e':raise(50);flag = 0;break;
			default:break;
		}
		if(flag == 0)
			return 0;
	}while(1);
	
	printf("leave the send signal\n");
	
	
	return 0;
}
//浏览图片
int  brower_photo(File_info *photo_head2) 
{
	if(photo_head2 == NULL)
	{
		return -1;
	}
	char com_photo[50];
	bzero(com_photo, sizeof(com_photo));
	
	struct list_head *pos = NULL;
	
	//图片浏览器名字
	char photo_brower[50];
	bzero(photo_brower, sizeof(photo_brower));
	strcpy(photo_brower, "shotwell");
	
	list_for_each(pos, &photo_head2->list)
	{
		File_info *file = list_entry(pos, File_info, list);
		sprintf(com_photo, "%s %s &", photo_brower, file->file_group.path);
		
		printf("%s\n", com_photo);
		system(com_photo);
		bzero(com_photo, sizeof(com_photo));
		
		sleep(5);
		
		sprintf(com_photo, "killall %s", photo_brower);
		printf("%s\n", com_photo);
		
		system(com_photo);
		sleep(1);
		
	}
	return -1;
}

/*//随机播放音乐
int  rand_music(File_info *music_head2) 
{
	if(music_head2 == NULL)
	{
		return -1;
	}
	srand(time(0));
	char com_music[50];
	bzero(com_music, sizeof(com_music));
	
	struct list_head *pos = NULL;
	
	//播放器名字
	char player[50];
	bzero(player, sizeof(player));
	strcpy(player, "madplay");
	
	list_for_each(pos, &music_head2->list)
	{
		File_info *file = list_entry(pos, File_info, list);
		if(rand()%5 == 0)
		{
			sprintf(com_music, "%s %s", player, file->file_group.path);
			system(com_music);
			break;
		}
		else{
			sprintf(com_music, "%s %s", player, file->file_group.path);
			system(com_music);
			break;
		}
	}
	return 0;
}*/
































