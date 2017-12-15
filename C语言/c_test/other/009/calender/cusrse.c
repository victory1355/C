#include <curses.h>
#include <stdio.h>
#define StartX 1
#define StartY 1
void initial();
int main()
{
		   int x = StartX;
		   int y = StartY;
		   int ch;
		   
		   initial();
		   
		   box(stdscr,'|','--');  //自动画方框   
		   
		   attron(A_BLINK);//打开属性
		   
		   mvaddstr(0,25,"curses program");    //在指定指标打印字符串
		   
		   attroff(A_BLINK);//关闭属性
		   
		   move(x,y);//将光标移动至x,y的位置
		   
		   do{
			  ch = getch();//从键盘读取一个字符
			  switch(ch)
			  {
				case KEY_UP:
				             --y;
				            break;
				case KEY_DOWN: 
					         ++y; 
					        break;
				case KEY_RIGHT: 
							++x; 
							break;
				case KEY_LEFT: 
							--x; 
							break;
				case ' ': 
							++y;
							x=0;
							break;
				case '/t': 
							x+=7;
							break;
				case KEY_BACKSPACE: 
							mvaddch(y,--x,' ');//指定位置打印一个字符
							break;
				case 27: 
							endwin(); 
							exit(1); 
				default: 
							addch(ch); //显示某个字符
							x++;
						    break;
			  }
			  move(y,x);//将光标移动至x,y
		   }while(1);
}
void initial()
{
			 initscr();
			 cbreak();
			 nonl();
			 noecho();
			 intrflush(stdscr,false);
			 keypad(stdscr,true);
			 refresh();
}























