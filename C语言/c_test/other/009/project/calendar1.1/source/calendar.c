/**************************************************************************************************************
*	Date:			2017/07/12
*	FileName:		calendar.c
*	Author: 		Leytou
*	Version:		1.1	(Show Weather)
*	Description: 	A calendar program.
*
*	本程序在ubuntu-12.04 gcc 4.6.3,curses 5.7环境下测试通过。
*	图形界面终端显示不佳，需在黑窗口终端执行。在图形桌面按Ctrl+Alt+1 输入用户密码可进入。（按Ctrl+Alt+7可返会图像桌面)
*	编译命令: （1）直接在calendar1.1/路径下执行makefile一键编译，输入：
*				  	make
*			  （2）当然也可以在calendar1.1/source/路径下输入以下命令进行编译：	
*			  		gcc calendar.c http.c cJSON.c -o app -lcurses -lpthread -lm
*
*	程序功能:
*	1.用户在终端执行程序后，在当前的终端窗口中显示当前的年、月、日
*	2.显示日历时是以表格形式显示：
*		表格的标题是年月
*		表头是星期，并且是从星期日开始
*		显示日期时，如果当前月份的1日不是星期日，则用上个有的末尾几日补齐表格。
*		同样，如果当前月的结尾日期不是周六，则用下个月的开始几日补齐。
*		
*	3.普通的日期用白色显示，当前日期用绿色显示，星期六和星期日用红色显示，用来补齐表格的日期用灰色显示。
*	4.用户使用左、右键控制月份的增减，上、下键控制年份的增减。
*	5.用户想直接查看某日期的日历时，可以按下“f”键，提示用户输入年、月，在用户输入结束以后，显示用户
*	  输入的日期日历。按“p”键盘，可回到当月日历。
*	6.天气温湿度的显示
*	7.按下“ESC”键，退出整个程序。
*
*	星期计算公式： W = [C/4] - 2C + y + [y/4] + [13 * (M+1) / 5] + d - 1
*				  W%7即为星期，若星期小于0，则+7。
*
*	FeiQ:192.168.10.145 欢迎同学提出指正。
**************************************************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> 
#include <curses.h>			//curses图形库
#include <time.h> 			//获取系统时间
#include <pthread.h>		//创建多线程
#include "cJSON.h"			//JSON库
#include "http.h"			//http

#define MAX_YEAR	2100										//支持最大年份
#define MIN_YEAR	1900										//支持最小年份

#define WIDTH		5											//日历单元宽度

#define P_ROW		(LINES/2-6)									//日历显示行位置		
#define P_COL		(LINES/2+12)								//日历显示列位置

#define HEAD_ROW	(P_ROW+2)									//日历标题(年月)行位置
#define HEAD_COL	((int)(P_COL+WIDTH*7/2-3))					//日历标题(年月)列位置

#define LOCAL_KEY_EXIT	27										//ESC键键值

#define IsLeapYear(year) ((year%4==0) && (year%100!=0) || year%400==0)	//判断是否闰年

int PrintInit();												//打印初始化
int PrintCalendar(const int year, const int month);				//打印某年某月日历
int Week(const int year, const int month, const int day);		//计算星期
int InputDate(int *year, int *month);							//输入日期跳转并打印日历
int DateLimit(int *year, int *month);							//日期限幅
void* TimeShow();												//系统时间显示线程服务
void* KeyRes();													//按键事件响应线程服务
void* WeaShow();												//天气显示线程服务

const char * const Week_head[7] = {"Sun.", "Mon.", "Tues.", "Wed." , "Thur.", "Fri.", "Sat."};
const int Days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
enum Colour{WHITE=1, MAGENTA, RED ,GREEN, YELLOW, BLUE, CYAN};	//颜色对标记号

struct Date{													//当前年月日，调用TimeShow线程中实时更新
	int year;
	int month;
	int day;
}date_pre;

int main()
{
	pthread_t time_pid, cmd_pid, wea_pid;			//线程ID
	
	pthread_create(&time_pid, NULL, TimeShow, NULL);	//创建时间显示线程
	pthread_create(&wea_pid, NULL, WeaShow, NULL);//创建天气显示线程
	usleep(50*1000);								//延迟50ms，确保时间显示线程创建完毕而保证获取了系统时间
	
	PrintInit();									//打印初始化
	
	PrintCalendar(date_pre.year, date_pre.month);	//打印本月日历
	
	pthread_create(&cmd_pid,NULL,KeyRes,NULL); 	//创建按键事件处理线程
	
	pthread_join(cmd_pid,NULL);					//挂起，等待键盘事件处理线程结束
	
	endwin();										//结束curses
	exit(EXIT_SUCCESS);								//退出程序
	
	return 0;
}

int PrintInit()
{
	initscr();										//curses初始化
	curs_set(0);									//隐藏光标
	clear();										//清屏
	refresh();										//屏幕刷新
	
	start_color();									//启用颜色功能	
	
	//设置颜色对
	init_pair(WHITE,COLOR_WHITE,COLOR_BLACK);		//用WHITE(1)代表 （字体白色，背景黑色）组合
	init_pair(MAGENTA,COLOR_MAGENTA,COLOR_BLACK);	//用MAGENTA(2)代表 （字体白色，背景黑色）组合
	init_pair(RED,COLOR_RED,COLOR_BLACK);			//……
	init_pair(GREEN,COLOR_GREEN,COLOR_BLACK);
	init_pair(YELLOW,COLOR_YELLOW,COLOR_BLACK);
	init_pair(BLUE,COLOR_BLUE,COLOR_BLACK);
	init_pair(CYAN,COLOR_CYAN,COLOR_BLACK);
	
	return 0;
}

//键盘事件响应
void* KeyRes()												
{
	int year_go=0, month_go=0;				//日期跳转的变量
	int key=0;								//键值
	
	year_go = date_pre.year;						//初始化为系统日期
	month_go = date_pre.month;
	
	crmode();								//立即读取模式
	keypad(stdscr, TRUE);					//可以使用键盘上的一些特殊字元
    noecho();								//关闭回显
	
	while(key != ERR && key != LOCAL_KEY_EXIT )						//循环检测键盘输入与对应处理
	{
		switch(key)
		{
				case KEY_UP: 	++year_go;	break;		
				case KEY_DOWN: 	--year_go;	break;
				case KEY_LEFT:	--month_go;	break;
				case KEY_RIGHT: ++month_go;	break;
				case 'f':		InputDate(&year_go, &month_go);			//日期跳转
								break;	
				case 'p':												//回到系统当前日期
								year_go=date_pre.year;
								month_go = date_pre.month;
								break;
				default: break;
		}
		
		DateLimit(&year_go, &month_go);		//日期限幅
		PrintCalendar(year_go, month_go);	//日历打印
		key = getch();						//等待或读取键盘输入
	}                              
}

//打印日历
int PrintCalendar(const int year, const int month)
{
	int row=0, col = 0;			//字符坐标
	int col_j=0;				//列下标，共7列（0~6）				
	int day_i = 1;				//天下标
	
	int week=0;					//某月1日星期几
	int days_of_month = 0; 		//某月总天数
	
	//clear();					//清屏
	move(HEAD_ROW,0);
	clrtobot();					//清除当前光标所在行下面的所有行，包括当前光标所在行的光标位置右边直到行尾的内容

	//表头，年月
	attron(COLOR_PAIR(CYAN));		//以下内容青色字体输出
	mvprintw( HEAD_ROW, HEAD_COL, "%d.%d", year, month);
	
	//星期栏目
	attron(COLOR_PAIR(BLUE));		//以下内容蓝色字体输出
	row = HEAD_ROW + 1;
	
	for(col_j=0; col_j<7; col_j++)
	{	
		col = P_COL + col_j*WIDTH;	//计算打印列位置，col = 起始位置 + 列下标 * 列宽
		mvprintw( row,col,"%s", Week_head[col_j] );
	}
	
	days_of_month = (2 == month && IsLeapYear(year)) ? 29 : Days[month-1];		//得到该月总天数
	week = Week(year, month, 1);												//得到该月1日星期几
	
	//补全上月份
	if(week != 0)
	{	
		int year_t = year;
		int month_t = month - 1;
		int days_of_last_month = 0;
		if(0 == month_t)						//如果该月是1月，则上一个月是去年的12月
		{
			month_t = 12;
			year_t = year - 1; 
		}
		
		//获取上月天数。若该月为2月，且闰年，29天，否则是平年对应的月天数
		days_of_last_month = (2 == month_t && IsLeapYear(year_t)) ? 29 : Days[month_t-1];	
		
		//第一格的日期 = 上月天数 - 该月1日星期几 + 1 
		day_i =  days_of_last_month - week + 1;												
		
		attron(COLOR_PAIR(MAGENTA));			//紫色打印
		row = HEAD_ROW + 2;						//行位置
		for(col_j = 0; col_j<week ; ++col_j)
		{
			col = P_COL + col_j*WIDTH;			//列位置
			mvprintw( row,col,"%d", day_i);
			++day_i;
		}
	}
	
	//打印当前月日期以及下月的补全日期
	col_j = week;																//设置当前列的值为星期值，即1日的位置
	for(row=HEAD_ROW+2, day_i=1; row < (HEAD_ROW+8); row++)
	{
		for(; col_j<7; col_j++ )
		{
			
			col = P_COL + col_j*WIDTH;
		
			if( day_i<=days_of_month)
			{
				if(day_i==date_pre.day && month==date_pre.month && year==date_pre.year)		//今日绿色
					attron(COLOR_PAIR(GREEN));		
				else if( 0==col_j || 6==col_j)									//周末灰色
					attron(COLOR_PAIR(RED));									
				else															//普通日期白色
					attron(COLOR_PAIR(WHITE));									
				mvprintw( row,col,"%d", day_i);
			}
			else																//补全下个月的日期
			{
				attron(COLOR_PAIR(MAGENTA));									//紫色
				mvprintw( row,col,"%d", day_i-days_of_month);
			}
			++day_i;
		}
		col_j = 0;
	}
	
	refresh();							//刷新屏幕
	
  return 0;
}		

//计算某年某天星期几
int Week(const int year, const int month, const int day)
{
	int Zeller_value = 0;				//Zeller结果值
	int century_z = 0;					
	int year_z,month_z,day_z;
	int week=0;
	
	century_z = (int)(year/100);		//世纪 减1
	year_z = year % 100;				//年份，后两位
	month_z = month;
	day_z = day;
	
	if(1 == month || 2 == month )
	{
		month_z += 12;
		year_z -= 1;
	}
	//蔡勒公式
	Zeller_value = year_z + year_z/4 + century_z/4 - 2*century_z + 13*(month_z+1)/5 + day_z -1;
	
	while(Zeller_value<0)				//注意处理负数情况
		Zeller_value += 7;
		
	week = Zeller_value % 7;
	
	return week;
}

//判断是否闰年
/*int IsLeapYear(const int year)
{
	return ((year%4==0) && (year%100!=0) || year%400==0); 
}*/


//输入日期打印日历
int InputDate(int *year, int *month)
{
	echo();							//开启屏幕回显
	curs_set(1);					//显示光标
	mvprintw( HEAD_ROW+8, P_COL, "Please input year(1900-2100), month(1-12)(e.g. 2017,7)\n");
	do
	{
		move(HEAD_ROW+9,P_COL);
		clrtoeol();					//清除光标所在行内容
		scanw("%d,%d",year,month);
		
	}while( (*year)<MIN_YEAR || (*year)>MAX_YEAR || (*month)<1 || (*month)>12 );
	
	noecho();						//关闭屏幕回显
	curs_set(0);					//隐藏光标
	return 0;
}

void* TimeShow()
{
	time_t timep;  
	struct tm *pt; 
	char time_str[30]; 
	
	while(1)
	{
		time(&timep);  
		pt =localtime(&timep); 		//此函数获得的tm结构体的时间，是已经进行过时区转化为本地时间   

		date_pre.year = 1900 + pt->tm_year;
		date_pre.month = 1 + pt->tm_mon;
		date_pre.day = pt->tm_mday;
		
		strcpy(time_str,ctime(&timep)); 
		
		//打印更新时间会改变光标，造成在按f输入跳转日期时无法正常显示输入内容的bug。
		//解决方法：先记录当前光标，打印完，再返会原处
		int y=0,x=0;			
		getyx(stdscr,y,x);			//记录光标
		
		move(P_ROW, P_COL+4);
		clrtoeol();
		attron(COLOR_PAIR(YELLOW));
		mvprintw(P_ROW, P_COL+(WIDTH*7-strlen(time_str))/2, "%s", time_str);		//列坐标的计算是为了居中显示
		
		move(y,x);					//回到打印前光标位置
	
		refresh();
		
		usleep(20*1000);			//20ms更新一次时间
		
	}
}

//日期限幅，限制年份和月份
int DateLimit(int *year, int *month)
{
	//月份限幅
	if( *month < 1)
	{
		if(*year <= MIN_YEAR)			//年份以达支持下限，保持不变
			*month = 1;
		else						//否则，翻到上一年
		{
			*month += 12;		
			*year -= 1;
		}
	}
	else if(*month > 12)
	{
		if(*year>=MAX_YEAR)			//年份以达支持上限，保持不变
			*month = 12;
		else						//否则，翻到下一年
		{
			*month -= 12;
			*year += 1;
		}
	}
	
	//年份限幅
	*year = (*year <= MIN_YEAR) ? MIN_YEAR : *year;
	*year = (*year >= MAX_YEAR) ? MAX_YEAR : *year;
	
	return 0;
}

//天气显示线程服务
void *WeaShow()
{
	const char *url= "http://www.weather.com.cn/data/sk/101280101.html";		//中国气象网-广州天气url
	while(1)
	{	
		char *wea_str = http_get(url);											//获取气象信息
		if(NULL == wea_str)	continue;
		
		wea_str += 2;
		
		cJSON *jsonroot = cJSON_Parse(wea_str);									//气象信息字符串格式化为JSON结构
		
		cJSON *jdata = cJSON_GetObjectItem(jsonroot,"weatherinfo");				//到"weatherinfo"标签
		
		char *temp_str = cJSON_GetObjectItem(jdata, "temp")->valuestring;		//取温度
		char *humi_str = cJSON_GetObjectItem(jdata, "SD")->valuestring;		//取湿度
		
		if(NULL == temp_str || NULL == humi_str)	continue;
		
		int y=0,x=0;			
		getyx(stdscr,y,x);			//记录光标
		
		move(P_ROW, P_COL);
		clrtoeol();
		attron(COLOR_PAIR(YELLOW));

		mvprintw(P_ROW+1, P_COL+(WIDTH*7-(strlen(temp_str)+strlen(humi_str)+8)),"T:%s W:%s", temp_str, humi_str);	//温湿度靠右显示
		refresh();
		
		move(y,x);					//回到打印前光标位置
		
		cJSON_Delete(jsonroot);
		
		sleep(3);
	}
}

