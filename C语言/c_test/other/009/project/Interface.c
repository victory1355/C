#include "Interface.h"

int Deep = 0;            //记录递归深度

/* 初始化屏幕 */
void Initial()
{
	initscr();
	keypad(stdscr,TRUE);
	clear();
	echo();
	refresh();
}

/* 画框框 */
static void Draw_Box(int y,int x,int cols)                    
{
	int i = 0;
	char Blank[80];
	for(i;i<80;i++)                                    //利用下划线画横线
	{
		Blank[i] = ' ';
	}
	attron(A_UNDERLINE);
	mvprintw(y-1,0,"%s",Blank);
	mvprintw(y-1+cols,0,"%s",Blank);
	//attroff(A_UNDERLINE);
	
	move(y,0);                                          //画竖线
	vline(ACS_VLINE,cols);
	move(y,x+1);
	vline(ACS_VLINE,cols);
	move(y,x+14);
	vline(ACS_VLINE,cols);
	move(y,x+23);
	vline(ACS_VLINE,cols);
	move(y,x+30);
	vline(ACS_VLINE,cols);
	move(y,x+40);
	vline(ACS_VLINE,cols);
	move(y,x+47);
	vline(ACS_VLINE,cols);
	move(y,x+58);
	vline(ACS_VLINE,cols);
	move(y,x+69);
	vline(ACS_VLINE,cols);
}

/* 绘制表格 */
int Draw(pList list,int Y,int X)
{
	int i = 0;
	int x,y = 0;
	char Buf[7] = "Student";
	clear();
	x = COLS/2 - strlen(Buf)/2;
	mvaddstr(y,x,Buf);
	x = 13;
	y = 3;
	attron(A_UNDERLINE);
	mvaddstr(y-1,x-13,"   Number   ");
	mvaddstr(y-1,x-1,"   Name     ");                       //绘制表头
	mvaddstr(y-1,x+11," Chinese  ");
	mvaddstr(y-1,x+21," Math ");
	mvaddstr(y-1,x+27,"  English ");
	mvaddstr(y-1,x+37,"   Sum   ");
	mvaddstr(y-1,x+44,"   Average  ");
	mvaddstr(y-1,x+56,"    Rank   ");
	while(list != NULL && i < 21)                                 //将数据从链表中取出
	{
		Draw_Box(2,10,y-1);	
		//attron(A_UNDERLINE);
		
		mvprintw(y,1,"%d",list -> Data -> Number);
		mvaddstr(y,x,list -> Data -> Name);
		move(y,x+15);			
		printw("%d",list -> Data -> Score[0]);
		move(y,x+23);
		printw("%d",list -> Data -> Score[1]);
		move(y,x+32);
		printw("%d",list -> Data -> Score[2]);
		move(y,x+40);
		printw("%d",list -> Data -> Score[3]);
		move(y,x+48);
		printw("%0.1f",list -> Data -> avg);
		if(list -> Data -> rank != 0)
			mvprintw(y,x+60,"%d",list -> Data -> rank);
		if(y == Y)                                                 //判断是不是对应行
		{
			attron(A_BOLD);                                        //判断是不是对应列
			switch(X)
			{
				case 0:
				mvprintw(y,1,"%d",list -> Data -> Number);
				break;
				case 1:
				mvprintw(y,x,"%s",list -> Data -> Name);
				break;
				case 2:
				mvprintw(y,x+15,"%d",list -> Data -> Score[0]);
				break;
				case 3:
				mvprintw(y,x+23,"%d",list -> Data -> Score[1]);
				break;
				case 4:
				mvprintw(y,x+32,"%d",list -> Data -> Score[2]);
				break;
				case 5:
				mvprintw(y,x+40,"%d",list -> Data -> Score[3]);
				break;
				case 6:
				mvprintw(y,x+48,"%0.1f",list -> Data -> avg);
				break;
				case 7:
				if(list -> Data -> rank != 0)
					mvprintw(y,x+60,"%d",list -> Data -> rank);
				break;
			}
			attroff(A_BOLD);
		}
				
		refresh();
		list = list -> next;
		i++;
		y = y+1;

	}
	move(LINES -1,0);
	attroff(A_UNDERLINE);
	return y-1;
}

/* 将字符串转换成整形数据 */
static int StrtoInt(char *Num)                    
{
	int i = 0,j = 0,k = 0;
	int num = 0;
	int temp = 1;
	if(Num == NULL)
		return -1;
	while(*(Num+i) != '\0')
	{
		i++;
	}
	k = i;
	for(j;j<k;j++)
	{
		num = (*(Num+i-1) - '0')*temp +num;
		temp = temp*10;
		i--;
	}
	return num;
}

/* 搜索子界面*/
pList Search_Stu(pList list,int type)
{
	int i,j;
	int PAGE = 0;
	int Y = 3,X = 1;             //初始坐标
	int line = 0;            //总行数
	int Dir = 0;             //排序方向
	char str[16];
	int ch;
	char Buf[20];
	char *buffer = Buf;
	char *p,*p1;
	int Max,Min = 0;
	pList List_Result = NULL;        //搜索结果
	pList List_Del = NULL;           //要删除的子链表
	pList Head = NULL;
	pList temp = NULL;
	
	if(type <0 || type > 7)
		return NULL;
	
	if((type >= 2&&type < 8) || type == 0)            //搜索数字
	{
		mvaddstr(0,0,"Please enter the range you want to search");
		move(1,0);
		scanw("%s",Buf);
		p = strsep(&buffer,"-");
		p1 = strsep(&buffer,"-");
		Min = StrtoInt(p);
		Max = StrtoInt(p1);		
		
		List_Result = Search_StuList(list,type,Max,Min,buffer);				
	}
	else if(type == 1)                                //搜索字符串（名字）
	{
		mvaddstr(0,0,"Please enter the name you want to search");
		move(1,0);
		scanw("%s",Buf);
		
		List_Result = Search_StuList(list,type,Max,Min,Buf);
	}
	Head = List_Result;

	while(1)
	{
		line = Draw(List_Result,Y,X);
		ch = getch();
		switch(ch)
		{
			case 61:                      //升序 =号（加号需要用组合键输入）
				if(X != 5)               //不允许对子链表的总分进行排序，否则会影响主链表
				{
					Dir = 0;
				    Sort_List(List_Result,NULL,X-2,Dir);
				}
				break;
			case 45:                   //降序   -号
				if(X != 5)
				{
					Dir = 1;
					Sort_List(List_Result,NULL,X-2,Dir);
				}
				break;
			case KEY_UP:                    //光标上移
				Y--;
				if(Y<3)
					Y = line;
				break;					
			case KEY_DOWN:                  //光标下移
				Y++;
				if(Y>line)
					Y = 3;
				break;									
			case KEY_LEFT:                 //光标左移
			    X--;
				if(X < 0)
					X = 7;
				break;
			case KEY_RIGHT:                //光标右移
                X++;
				if(X > 7)
					X = 0;
				break;
			case KEY_NPAGE:               //下一页
				if(line > 22)
				{
					PAGE++;
					for(i = 0;i<21;i++)
					{
						List_Result = List_Result -> next;
					}
				}
				break;
			case KEY_PPAGE:               //上一页
				if(PAGE != 0)
				{
					PAGE --;
					List_Result = Head;
					for(j=0;j<PAGE;j++)
					{
						for(i = 0;i<21;i++)
						{
							List_Result = List_Result -> next;
						}
					}
				}
				break;
			case ' ' :			       //递归查询，可以实现多个条件的查询
				if(X != type)
				{
					clear();
					Deep++;
					Search_Stu(List_Result,X);
				}
				break;
/* 			case KEY_BACKSPACE:
				if(Deep == 0)    //只允许在最外层执行删除操作
				{
					clear();
					mvaddstr(0,0,"Delete this line or change this unit? ");
					mvaddstr(1,0,"1.Delete the whole line 2.Change the unit");
					move(2,0);
					scanw("%d",&i);
					List_Del = Head;
					if(i == 1)                       //删除整行
					{
						temp = (pList)malloc(sizeof(List));
						for(i = 0;i<PAGE;i++)        //翻页
						{
							for(j = 0;j<21;j++)
							{
								List_Del = List_Del -> next;
							}
						}					
						for(j = 1;j < Y-2;j++)       //移动到指定行
						{
							List_Del = List_Del -> next;
						}						
						
						temp -> Data = List_Del -> Data;
						temp -> next = NULL;
						Head = Del_List(Head,temp);
						
						List_Result = Head;                  //回到当前页
						for(i = 0;i<PAGE;i++)
						{
							for(j = 0;j<21;j++)
							{
								List_Result = List_Result -> next;
							}
						}
						
						free(temp);					
					}
					else if(i == 2)                 //修改单元格
					{
						clear();					
						mvaddstr(0,0,"Please enter the new item");
						move(1,0);
						if(X == 1)                  //修改字符串
						{
							memset(str,0,16);
							scanw("%s",str);
							Change_List(list,X,str,i,Y-2);
						}
						else                       //修改数字
						{
							scanw("%d",&i);
							if(Change_List(list,X,str,i,Y-2) == -1)
							{
								mvaddstr(3,0,"Wrong data was inserted");
								move(4,0);
								getch();
							}						
						}					
					}
				}
				
				break; */
			case 27:			//ESC 返回主程序
				return NULL;
		}
	}		
}

































