#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "conio.h"
#include "cmd.h"

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27
#define ENTER 13

void main_select(int cur);
void kor_select(int cur);
void korlong_menu(void); //��ۿ���.
void kor_menu(void);
void Func_table(void);
int Func_line (char *file);
int short_kor(char *file, int line);
int long_kor(char *file,int line);
int kor_jawonmenu(void);		//�ѱ� �ڿ�ĳ�� �޴�
int eng_jawonmenu(void);		//���� �ڿ�ĳ�� �޴�
int jawon(int stage);			//�ѱ� �ڿ�ĳ��
int eng_jawon(int stage);		//���� �ڿ�ĳ��				 
void eng_select(int cur);		//����Ÿ�� �޴� ���ý�...
void eng_menu(void);			//����Ÿ�� �޴�.
void englong_menu(void);		//���� ��� �޴� 
void eng_rankformat(void);		//���� �ڿ�ĳ�� ��ŷ �ʱ�ȭ
void rankformat(void);			//�ѱ� �ڿ�ĳ�� ��ŷ �ʱ�ȭ
void eng_rankview(void);		//���� �ڿ�ĳ�� ��ŷ ����
void rankview(void);			//�ѱ� �ڿ�ĳ�� ��ŷ ����
void noCursor(void);			//Ŀ���� ���ش�.
void tetris_menu(void);
void Menu_print(char** menu,int x1, int n);
void Func_JDT(int color);
int sansongbi(int stage);		//�ѱ� �꼺��
int kor_sansongbimenu(void);	//�ѱ� �꼺�� �޴� 
int engsansongbi(int stage);	//���� �꼺��
int eng_sansongbimenu(void);	//���� �꼺�� �޴� 
void korsanrankformat(void);	//�ѱ� �꼺�� ��ŷ �ʱ�ȭ
void engsanrankformat(void);	//���� �꼺�� ��ŷ �ʱ�ȭ 
void korsanrankview(void);		//�ѱ� �꼺�� ��ŷ ����
void engsanrankview(void);		//���� �꼺�� ��ŷ ����
void cls(void);

int main(void)
{
    int x1=0;
    char *menu[]={"1.�ѱ� Ÿ�ڿ���","2.���� Ÿ�ڿ���", "3.��Ʈ����", "4.������"}; 
    char ch;
	int color[]={9,10,11,12,13,14};
	int ccur=0;
    int time1;
	int time2;

	noCursor();
	Func_table();
	Func_JDT(color[ccur]);
	Menu_print(menu,x1, 4);

	time1=GetTickCount();

    while(1)
    {
		time2=GetTickCount();

		if(time2-time1>1000){
			if(ccur==5) ccur=0;
			ccur++;
			Func_JDT(color[ccur]);
			time1=GetTickCount();
		}
		if(kbhit())
		{
			ch=getch();
			if(ch==-32 || ch==ENTER || ch==ESC)
			{
				if(ch!=ENTER && ch!=ESC)
					ch=getch();
				switch(ch)
				{
	    			case UP:
	    				if(x1>0)
	    					x1--;
						break;
					case DOWN:
	        			if(x1<3)
	        				x1++;
						break;
					case ENTER:
	        			main_select(x1);
	        			Func_table();
						Func_JDT(color[ccur]);
	        			break;
					case ESC:
						cls();
						return 0;
				}
				Menu_print(menu,x1, 4);

			}
		}
    }                   
}
//�ѱ�Ÿ�� �޴�
void kor_menu(void)
{
	int x1=0;
	char ch;
	char *menu[]={"1.ª���� ����","2.��� ����","3.�ڿ�ĳ��","4.�꼺��","5.���� �޴���"};
	int color[]={9,10,11,12,13,14};
	int ccur=0;
    int time1;
	int time2;

	Func_table();
	Func_JDT(color[ccur]);
	Menu_print(menu,x1, 5);
	time1=GetTickCount();

	while(1)
    {
		time2=GetTickCount();

		if(time2-time1>1000){
			if(ccur==5) ccur=0;
			ccur++;
			Func_JDT(color[ccur]);
			time1=GetTickCount();
		}
		
		if(kbhit())
		{
			ch=getch();
			if(ch==-32 || ch==ENTER || ch==ESC)
			{
				if(ch!=ENTER && ch!=ESC)
					ch=getch();
				switch(ch)
				{
	    			case UP:
	    				if(x1>0)
	    					x1--;
						break;
					case DOWN:
	        			if(x1<4)
	        				x1++;
						break;
					case ENTER:
						if(x1==4) 
							return;
	        			kor_select(x1);
	        			Func_table();
						Func_JDT(color[ccur]);
	        			break;
					case ESC:
						return;
				}
				Menu_print(menu,x1, 5);
			}
		}
    
	}
}
//���θ޴� ���ý�
void main_select(int cur)
{
	switch(cur)
	{
	case 0:
		kor_menu();
		break;
	case 1:
		eng_menu();
		break;
	case 2:
		tetris_menu();
		break;
	case 3:
		cls();
		exit(0);
	}
}

//�ѱ�Ÿ�� �޴� ���ý�
void kor_select(int cur)
{
	switch(cur)
	{
		case 0:
			short_kor("short_kor.txt",Func_line("short_kor.txt"));
			break;
		case 1:
			korlong_menu();
			break;
		case 2:
			kor_jawonmenu();
		case 3:
			kor_sansongbimenu();
			break;
	}
}

//�ѱ� ��ۿ��� �޴�
void korlong_menu(void)
{
    int x1=0;
	char ch;
    char* menu[]={"1.�����", "2.�޹в� �� ����", "3.�ҳ���", "4.��","5.���� �޴���"};
	int color[]={9,10,11,12,13,14};
	int ccur=0;
    int time1;
	int time2;

	Func_table();
	Func_JDT(color[ccur]);
	Menu_print(menu,x1, 5);

	time1=GetTickCount();

	while(1)
    {	
		time2=GetTickCount();

		if(time2-time1>1000){
			if(ccur==5) ccur=0;
			ccur++;
			Func_JDT(color[ccur]);
			time1=GetTickCount();
		}
		
		if(kbhit())
		{
			ch=getch();
			if(ch==-32 || ch==ENTER || ch==ESC)
			{
				if(ch!=ENTER && ch!=ESC)
					ch=getch();
				switch(ch)
				{
	    			case UP:
	    				if(x1>0)
	    					x1--;
						break;
					case DOWN:
	        			if(x1<4)
	        				x1++;
						break;
					case ENTER:
	        			if(x1==0)
						{
							long_kor("dongbec.dat",Func_line("dongbec.dat"));
							Func_table();
						}
						else if(x1==1)
						{
							long_kor("memil.dat",Func_line("memil.dat"));
							Func_table();
						}
						else if(x1==2)
						{
							long_kor("sonagi.dat",Func_line("sonagi.dat"));
							Func_table();
						}
						else if(x1==3)
						{
							long_kor("star.dat",Func_line("star.dat"));
							Func_table();
						}
						else if(x1==4)
							return;
	        			break;
					case ESC:
						return;
				}
				Menu_print(menu,x1, 5);
			}
		}
    }                  

}

//�ѱ� �ڿ�ĳ�� �޴�
int kor_jawonmenu(void)
{
	int i;
	int x1=0;
    int x=28,y=5;
	char ch;
    
    char *table[]={
         "����������������������","����������������������","����������������������"
	};

	char* menu[]={"Stage  1", "Stage  2", "Stage  3", "Stage  4", "Stage  5", "Stage  6", "Stage  7", "Stage  8", "Stage  9", "Stage 10", " ������ ", " �ʱ�ȭ "};
   
	cls();
  	

	while(1)
	{
		x=28, y=5;											//�׵θ� ǥ��
		gotoxy(x, y), printf("%s", table[0]);
		for(i=1; i<=14; i++)
			gotoxy(x, y+i), printf("%s", table[1]);
		gotoxy(x, y+i), printf("%s", table[2]);

		for(i=0, x=35, y=7; i<12; i++)						//�޴�ǥ��
			gotoxy(x, y+i), printf("%s", menu[i]);
		
		while(1)
		{
			for(i=0,x=35,y=7; i<12; i++)
			{
	    		if(x1==i)
				{
	    			gotoxy(x,y+i);
					textcolor(CC_FONT_WHITE,CC_BACK_DBLUE);
					printf("%s",menu[i]);
					textcolor(CC_FONT_WHITE,0);
					continue;
				}

				if(i<12)
					gotoxy(x, y+i), printf("%s",menu[i]);
			}


			
			
			while(1)
			{
				ch=getch();
				if(ch==-32 || ch==ENTER || ch==ESC)
				{
					if(ch!=ENTER && ch!=ESC)
						ch=getch();
					switch(ch)
					{
	    				case UP:
	    					if(x1>0)
	    						x1--;
							break;
						case DOWN:
	        				if(x1<11)
	        					x1++;
							break;
						case ENTER:
							if(x1==10)
							{
								rankview();
								cls();
								break;
							}
							if(x1==11)
							{
								rankformat();
								cls();
								break;
							}
	//							return;
	        				jawon(x1+1);
							cls();
	//	        			Func_table();
	        				break;
						case ESC:
							return 0;
					}
					break;
				}
				else
					continue;
			}
			break;
		}	
	}
}

//�����ڿ�ĳ�� �޴�
int eng_jawonmenu(void)
{
	int i;
	int x1=0;
    int x=28,y=5;
	char ch;
    
    char *table[]={
         "����������������������","����������������������","����������������������"
	};

	char* menu[]={"Stage  1", "Stage  2", "Stage  3", "Stage  4", "Stage  5", "Stage  6", "Stage  7", "Stage  8", "Stage  9", "Stage 10", " ������ ", " �ʱ�ȭ "};
   
	cls();
  	

	while(1)
	{
		x=28, y=5;											//�׵θ� ǥ��
		gotoxy(x, y), printf("%s", table[0]);
		for(i=1; i<=14; i++)
			gotoxy(x, y+i), printf("%s", table[1]);
		gotoxy(x, y+i), printf("%s", table[2]);

		for(i=0, x=35, y=7; i<12; i++)						//�޴�ǥ��
			gotoxy(x, y+i), printf("%s", menu[i]);
		
		while(1)
		{
			for(i=0,x=35,y=7; i<12; i++)
			{
	    		if(x1==i)
				{
	    			gotoxy(x,y+i);
					textcolor(CC_FONT_WHITE,CC_BACK_DBLUE);
					printf("%s",menu[i]);
					textcolor(CC_FONT_WHITE,0);
					continue;
				}

				if(i<12)
					gotoxy(x, y+i), printf("%s",menu[i]);
			}


			
			
			while(1)
			{
				ch=getch();
				if(ch==-32 || ch==ENTER || ch==ESC)
				{
					if(ch!=ENTER && ch!=ESC)
						ch=getch();
					switch(ch)
					{
	    				case UP:
	    					if(x1>0)
	    						x1--;
							break;
						case DOWN:
	        				if(x1<11)
	        					x1++;
							break;
						case ENTER:
							if(x1==10)
							{
								eng_rankview();
								cls();
								break;
							}
							if(x1==11)
							{
								eng_rankformat();
								cls();
								break;
							}
	//							return;
	        				eng_jawon(x1+1);
							cls();
	//	        			Func_table();
	        				break;
						case ESC:
							return 0;
					}
					break;
				}
				else
					continue;
			}
			break;
		}	
	}
}


//����Ÿ�� �޴�
void eng_menu(void)
{
	int x1=0;
	char ch;
	char *menu[]={"1.ª���� ����","2.��� ����","3.�ڿ�ĳ��","4.�꼺��","5.���� �޴���"};
	int color[]={9,10,11,12,13,14};
	int ccur=0;
    int time1;
	int time2;

	Func_table();
	Func_JDT(color[ccur]);
	Menu_print(menu,x1, 5);

	time1=GetTickCount();

	while(1)
    {
		time2=GetTickCount();

		if(time2-time1>1000){
			if(ccur==5) ccur=0;
			ccur++;
			Func_JDT(color[ccur]);
			time1=GetTickCount();
		}
		
		if(kbhit())
		{
			ch=getch();
			if(ch==-32 || ch==ENTER || ch==ESC)
			{
				if(ch!=ENTER && ch!=ESC)
					ch=getch();
				switch(ch)
				{
	    			case UP:
	    				if(x1>0)
	    					x1--;
						break;
					case DOWN:
	        			if(x1<4)
	        				x1++;
						break;
					case ENTER:
						if(x1==4) 
							return;
	        			eng_select(x1);
	        			Func_table();
	        			break;
					case ESC:
						return;
				}
				Menu_print(menu,x1, 5);
			}
		}
    
	}
}

//����Ÿ�� �޴� ���ý�
void eng_select(int cur)
{
	switch(cur)
	{
		case 0:
			short_kor("short_eng.dat",Func_line("short_eng.dat"));
			break;
		case 1:
			englong_menu();
			break;
		case 2:
			eng_jawonmenu();
			break;
		case 3:
			eng_sansongbimenu();	//���� �꼺�� �޴� 
			break;
	}
}

//���� ��ۿ��� �޴�
void englong_menu(void)
{
    int x1=0;
	char ch;
    char* menu[]={"1.The Selfish Giant", "2.The Elves and the Shoemaker", "3.Rapunzel", "4.Narcissus","5.���� �޴���"};
	int color[]={9,10,11,12,13,14};
	int ccur=0;
    int time1;
	int time2;

	Func_table();
	Func_JDT(color[ccur]);
	Menu_print(menu,x1, 5);

	time1=GetTickCount();

	noCursor();
	while(1)
    {
		time2=GetTickCount();

		if(time2-time1>1000){
			if(ccur==5) ccur=0;
			ccur++;
			Func_JDT(color[ccur]);
			time1=GetTickCount();
		}
		
		while(1)
		{
			ch=getch();
			if(ch==-32 || ch==ENTER || ch==ESC)
			{
				if(ch!=ENTER && ch!=ESC)
					ch=getch();
				switch(ch)
				{
	    			case UP:
	    				if(x1>0)
	    					x1--;
						break;
					case DOWN:
	        			if(x1<4)
	        				x1++;
						break;
					case ENTER:
	        			if(x1==0)
						{
							long_kor("The Selfish Giant.dat",Func_line("The Selfish Giant.dat"));
							Func_table();
						}
						else if(x1==1)
						{
							long_kor("The Elves and the Shoemaker.dat",Func_line("The Elves and the Shoemaker.dat"));
							Func_table();
						}
						else if(x1==2)
						{
							long_kor("Rapunzel.dat",Func_line("Rapunzel.dat"));
							Func_table();
						}
						else if(x1==3)
						{
							long_kor("Narcissus.dat",Func_line("Narcissus.dat"));
							Func_table();
						}
						else if(x1==4)
							return;
	        			break;
					case ESC:
						return;
				}
				Menu_print(menu,x1, 5);
			}
		}
    }                  
}

//�ѱ� �꼺�� �޴�
int kor_sansongbimenu(void)
{
	int i;
	int x1=0;
    int x=28,y=5;
	char ch;
    
    char *table[]={
         "����������������������","����������������������","����������������������"
	};

	char* menu[]={"Stage  1", "Stage  2", "Stage  3", "Stage  4", "Stage  5", "Stage  6", "Stage  7", "Stage  8", "Stage  9", "Stage 10", " ������ ", " �ʱ�ȭ "};
   
	cls();
  	

	while(1)
	{
		x=28, y=5;											//�׵θ� ǥ��
		gotoxy(x, y), printf("%s", table[0]);
		for(i=1; i<=14; i++)
			gotoxy(x, y+i), printf("%s", table[1]);
		gotoxy(x, y+i), printf("%s", table[2]);

		for(i=0, x=35, y=7; i<12; i++)						//�޴�ǥ��
			gotoxy(x, y+i), printf("%s", menu[i]);
		
		while(1)
		{
			for(i=0,x=35,y=7; i<12; i++)
			{
	    		if(x1==i)
				{
	    			gotoxy(x,y+i);
					textcolor(CC_FONT_WHITE,CC_BACK_DBLUE);
					printf("%s",menu[i]);
					textcolor(CC_FONT_WHITE,0);
					continue;
				}

				if(i<12)
					gotoxy(x, y+i), printf("%s",menu[i]);
			}


			
			
			while(1)
			{
				ch=getch();
				if(ch==-32 || ch==ENTER || ch==ESC)
				{
					if(ch!=ENTER && ch!=ESC)
						ch=getch();
					switch(ch)
					{
	    				case UP:
	    					if(x1>0)
	    						x1--;
							break;
						case DOWN:
	        				if(x1<11)
	        					x1++;
							break;
						case ENTER:
							if(x1==10)
							{
								korsanrankview();
								cls();
								break;
							}
							if(x1==11)
							{
								korsanrankformat();
								cls();
								break;
							}
	//							return;
	        				sansongbi(x1+1);
							cls();
	//	        			Func_table();
	        				break;
						case ESC:
							return 0;
					}
					break;
				}
				else
					continue;
			}
			break;
		}	
	}
}

int eng_sansongbimenu(void)
{
	int i;
	int x1=0;
    int x=28,y=5;
	char ch;
    
    char *table[]={
         "����������������������","����������������������","����������������������"
	};

	char* menu[]={"Stage  1", "Stage  2", "Stage  3", "Stage  4", "Stage  5", "Stage  6", "Stage  7", "Stage  8", "Stage  9", "Stage 10", " ������ ", " �ʱ�ȭ "};
   
	cls();
  	

	while(1)
	{
		x=28, y=5;											//�׵θ� ǥ��
		gotoxy(x, y), printf("%s", table[0]);
		for(i=1; i<=14; i++)
			gotoxy(x, y+i), printf("%s", table[1]);
		gotoxy(x, y+i), printf("%s", table[2]);

		for(i=0, x=35, y=7; i<12; i++)						//�޴�ǥ��
			gotoxy(x, y+i), printf("%s", menu[i]);
		
		while(1)
		{
			for(i=0,x=35,y=7; i<12; i++)
			{
	    		if(x1==i)
				{
	    			gotoxy(x,y+i);
					textcolor(CC_FONT_WHITE,CC_BACK_DBLUE);
					printf("%s",menu[i]);
					textcolor(CC_FONT_WHITE,0);
					continue;
				}

				if(i<12)
					gotoxy(x, y+i), printf("%s",menu[i]);
			}

			while(1)
			{
				ch=getch();
				if(ch==-32 || ch==ENTER || ch==ESC)
				{
					if(ch!=ENTER && ch!=ESC)
						ch=getch();
					switch(ch)
					{
	    				case UP:
	    					if(x1>0)
	    						x1--;
							break;
						case DOWN:
	        				if(x1<11)
	        					x1++;
							break;
						case ENTER:
							if(x1==10)
							{
								engsanrankview();
								cls();
								break;
							}
							if(x1==11)
							{
								engsanrankformat();
								cls();
								break;
							}
	//							return;
	        				engsansongbi(x1+1);
							cls();
	//	        			Func_table();
	        				break;
						case ESC:
							return 0;
					}
					break;
				}
				else
					continue;
			}
			break;
		}	
	}
}