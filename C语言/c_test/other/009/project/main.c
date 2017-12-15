#include <stdio.h>
#include "Interface.h"
#include "List.h"

int main()
{
	Initial();
	pList list = Creat_List();
	Sort_List(list,NULL,3,0);
	int PAGE = 0;                //记录翻到了第几面
	pList Head = list;           //记录头节点
	pList temp = NULL;
	pList del  = list;           //用于删除节点
	Draw(list,3,0);

	int i,j;
	char str[16];               //保存从键盘输入的字符串（名字）
	int Chi,Math,Eng,num;       //保存从键盘输入的数字 
	int ch;                     //保存从键盘输入的字符
	int X = 0,Y = 3;            //x，y轴坐标
	int line = 0;              //用于记录本页画了多少行
	int Dir = 0;              //排序方向
	while(1)
	{
		line = Draw(list,Y,X);
		ch = getch();
		switch(ch)
		{
			case 61:                      //升序 =号（加号需要用组合键输入）
				Dir = 0;
				Sort_List(Head,NULL,X-2,Dir);
				break;
			case 45:                   //降序   -号
				Dir = 1;
				Sort_List(Head,NULL,X-2,Dir);			
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
			case ' ' :			       //查询 空格
				clear();
				Search_Stu(Head,X);
				break;
			case KEY_BACKSPACE:
				clear();
				mvaddstr(0,0,"Delete this line or change this unit? ");
				mvaddstr(1,0,"1.Delete the whole line 2.Change the unit");
				move(2,0);
				scanw("%d",&i);
				del = Head;
				if(i == 1)                       //删除整行
				{
					temp = (pList)malloc(sizeof(List));
					for(i = 0;i<PAGE;i++)        //翻页
					{
						for(j = 0;j<21;j++)
						{
							del = del -> next;
						}
					}					
					for(j = 1;j < Y-2;j++)       //移动到指定行
					{
						del = del -> next;
					}						
					
					temp -> Data = del -> Data;
					temp -> next = NULL;
					Head = Del_List(Head,temp);
					
					list = Head;                  //回到当前页
					for(i = 0;i<PAGE;i++)
					{
						for(j = 0;j<21;j++)
						{
							list = list -> next;
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
				break;
			case 'i':                //插入一行数据
				clear();
				memset(str,0,16);
				mvaddstr(0,0,"Please enter the student number");
				move(1,0);
				
				temp = Head;
				scanw("%d",&num);
				while(temp != NULL)                //检查学号有无重复输入
				{
					while(num == temp -> Data -> Number)
					{
						clear();
						mvaddstr(0,0,"The number has been used,please enter again");
						move(1,0);
						scanw("%d",&num);
					}
					temp = temp -> next;
				}
				temp = NULL;
				
				mvaddstr(2,0,"Please enter the student name");
				move(3,0);
				scanw("%s",str);
				mvaddstr(4,0,"Please enter the Chinese Math and English score");
				move(5,0);
				
				scanw("%d%d%d",&Chi,&Math,&Eng);				
				while(Chi>100 || Chi<0)              //检查数据合法性
				{
					clear();
					mvaddstr(0,0,"The Chinese score is wrong,please enter again");
					move(1,0);
					scanw("%d",&Chi);
				}
				while(Math>100 || Math<0)
				{
					clear();
					mvaddstr(0,0,"The Math score is wrong,please enter again");
					move(1,0);
					scanw("%d",&Math);
				}
				while(Eng>100 || Eng<0)
				{
					clear();
					mvaddstr(0,0,"The English score is wrong,please enter again");
					move(1,0);
					scanw("%d",&Eng);
				}
				
				Head = Insert_List(Head,Chi,Math,Eng,num,str);
				list = Head;
				break;
			case KEY_NPAGE:             //下一页
				if(line > 22)
				{
					PAGE++;
					for(i = 0;i<21;i++)
					{
						list = list -> next;
					}
				}
				break;
			case KEY_PPAGE:              //上一页
				if(PAGE != 0)
				{
					PAGE --;
					list = Head;
					for(j=0;j<PAGE;j++)
					{
						for(i = 0;i<21;i++)
						{
							list = list -> next;
						}
					}
				}
				break;
			case 27:                  //ESC 结束程序
				endwin();
				return 0;
		}
	}
	return 0;

	
}