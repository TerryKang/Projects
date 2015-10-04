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
void korlong_menu(void); //긴글연습.
void kor_menu(void);
void Func_table(void);
int Func_line (char *file);
int short_kor(char *file, int line);
int long_kor(char *file,int line);
int kor_jawonmenu(void);		//한글 자원캐기 메뉴
int eng_jawonmenu(void);		//영문 자원캐기 메뉴
int jawon(int stage);			//한글 자원캐기
int eng_jawon(int stage);		//영문 자원캐기				 
void eng_select(int cur);		//영문타자 메뉴 선택시...
void eng_menu(void);			//영문타자 메뉴.
void englong_menu(void);		//영문 긴글 메뉴 
void eng_rankformat(void);		//영문 자원캐기 랭킹 초기화
void rankformat(void);			//한글 자원캐기 랭킹 초기화
void eng_rankview(void);		//영문 자원캐기 랭킹 보기
void rankview(void);			//한글 자원캐기 랭킹 보기
void noCursor(void);			//커서를 없앤다.
void tetris_menu(void);
void Menu_print(char** menu,int x1, int n);
void Func_JDT(int color);
int sansongbi(int stage);		//한글 산성비
int kor_sansongbimenu(void);	//한글 산성비 메뉴 
int engsansongbi(int stage);	//영문 산성비
int eng_sansongbimenu(void);	//영문 산성비 메뉴 
void korsanrankformat(void);	//한글 산성비 랭킹 초기화
void engsanrankformat(void);	//영문 산성비 랭킹 초기화 
void korsanrankview(void);		//한글 산성비 랭킹 보기
void engsanrankview(void);		//영문 산성비 랭킹 보기
void cls(void);

int main(void)
{
    int x1=0;
    char *menu[]={"1.한글 타자연습","2.영문 타자연습", "3.테트리스", "4.끝내기"}; 
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
//한글타자 메뉴
void kor_menu(void)
{
	int x1=0;
	char ch;
	char *menu[]={"1.짧은글 연습","2.긴글 연습","3.자원캐기","4.산성비","5.이전 메뉴로"};
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
//메인메뉴 선택시
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

//한글타자 메뉴 선택시
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

//한글 긴글연습 메뉴
void korlong_menu(void)
{
    int x1=0;
	char ch;
    char* menu[]={"1.동백꽃", "2.메밀꽃 필 무렵", "3.소나기", "4.별","5.이전 메뉴로"};
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

//한글 자원캐기 메뉴
int kor_jawonmenu(void)
{
	int i;
	int x1=0;
    int x=28,y=5;
	char ch;
    
    char *table[]={
         "┌─────────┐","│　　　　　　　　　│","└─────────┘"
	};

	char* menu[]={"Stage  1", "Stage  2", "Stage  3", "Stage  4", "Stage  5", "Stage  6", "Stage  7", "Stage  8", "Stage  9", "Stage 10", " 점수판 ", " 초기화 "};
   
	cls();
  	

	while(1)
	{
		x=28, y=5;											//테두리 표시
		gotoxy(x, y), printf("%s", table[0]);
		for(i=1; i<=14; i++)
			gotoxy(x, y+i), printf("%s", table[1]);
		gotoxy(x, y+i), printf("%s", table[2]);

		for(i=0, x=35, y=7; i<12; i++)						//메뉴표시
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

//영문자원캐기 메뉴
int eng_jawonmenu(void)
{
	int i;
	int x1=0;
    int x=28,y=5;
	char ch;
    
    char *table[]={
         "┌─────────┐","│　　　　　　　　　│","└─────────┘"
	};

	char* menu[]={"Stage  1", "Stage  2", "Stage  3", "Stage  4", "Stage  5", "Stage  6", "Stage  7", "Stage  8", "Stage  9", "Stage 10", " 점수판 ", " 초기화 "};
   
	cls();
  	

	while(1)
	{
		x=28, y=5;											//테두리 표시
		gotoxy(x, y), printf("%s", table[0]);
		for(i=1; i<=14; i++)
			gotoxy(x, y+i), printf("%s", table[1]);
		gotoxy(x, y+i), printf("%s", table[2]);

		for(i=0, x=35, y=7; i<12; i++)						//메뉴표시
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


//영문타자 메뉴
void eng_menu(void)
{
	int x1=0;
	char ch;
	char *menu[]={"1.짧은글 연습","2.긴글 연습","3.자원캐기","4.산성비","5.이전 메뉴로"};
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

//영문타자 메뉴 선택시
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
			eng_sansongbimenu();	//영문 산성비 메뉴 
			break;
	}
}

//영문 긴글연습 메뉴
void englong_menu(void)
{
    int x1=0;
	char ch;
    char* menu[]={"1.The Selfish Giant", "2.The Elves and the Shoemaker", "3.Rapunzel", "4.Narcissus","5.이전 메뉴로"};
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

//한글 산성비 메뉴
int kor_sansongbimenu(void)
{
	int i;
	int x1=0;
    int x=28,y=5;
	char ch;
    
    char *table[]={
         "┌─────────┐","│　　　　　　　　　│","└─────────┘"
	};

	char* menu[]={"Stage  1", "Stage  2", "Stage  3", "Stage  4", "Stage  5", "Stage  6", "Stage  7", "Stage  8", "Stage  9", "Stage 10", " 점수판 ", " 초기화 "};
   
	cls();
  	

	while(1)
	{
		x=28, y=5;											//테두리 표시
		gotoxy(x, y), printf("%s", table[0]);
		for(i=1; i<=14; i++)
			gotoxy(x, y+i), printf("%s", table[1]);
		gotoxy(x, y+i), printf("%s", table[2]);

		for(i=0, x=35, y=7; i<12; i++)						//메뉴표시
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
         "┌─────────┐","│　　　　　　　　　│","└─────────┘"
	};

	char* menu[]={"Stage  1", "Stage  2", "Stage  3", "Stage  4", "Stage  5", "Stage  6", "Stage  7", "Stage  8", "Stage  9", "Stage 10", " 점수판 ", " 초기화 "};
   
	cls();
  	

	while(1)
	{
		x=28, y=5;											//테두리 표시
		gotoxy(x, y), printf("%s", table[0]);
		for(i=1; i<=14; i++)
			gotoxy(x, y+i), printf("%s", table[1]);
		gotoxy(x, y+i), printf("%s", table[2]);

		for(i=0, x=35, y=7; i<12; i++)						//메뉴표시
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