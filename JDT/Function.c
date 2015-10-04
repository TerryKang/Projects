#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "conio.h"
#include "cmd.h"

void gotoxy(int x, int y)
{
	COORD co;
	co.X = x;
	co.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), co);
}

void textcolor(unsigned int text, unsigned int back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | back);
}

int Func_line (char *file)
{
	int line=0;
	char str[50];
	
	FILE* fp=fopen(file,"rb");

	while(fgets(str,sizeof(str),fp)!=NULL)
		line++;
	
	fclose(fp);

	return line;
}

void Func_table(void)
{
    int i;
    int x=16,y=6;
    
    char *table[]={
        "┌─────────────────☆★","│　　　　　　　　　　　　　　　　　　☆","│　　　　　　　　　　　　　　　　　　│",
        "│　　　　　　　　　　　　　　　　　　│","│　　　　　　　　　　　　　　　　　　│","│　　　　　　　　　　　　　　　　　　│",
        "│　　　　　　　　　　　　　　　　　　│","★　　　　　　　　　　　　　　　　　　│","☆★─────────────────┘ver.1"};
    cls();
    for(i=0;i<9;i++){
    	gotoxy(x,y+i);
		textcolor(8,0);
    	printf("%s",table[i]);
		textcolor(15,0);
    }
}

void Func_JDT(int color)
{
	int i;
	int x=18,y=2;

	char *table[]={
		"■■■　■■　　■■■",
		"　■　　■　■　　■　",
		"　■　　■　■　　■　",
		"■■　　■■　　　■　타자연습"};
	textcolor(color,0);
	for(i=0;i<4;i++){
		gotoxy(x,y+i);
		printf("%s",table[i]);
	}
	textcolor(15,0);
}
void Menu_print(char** menu,int x1, int n)
{
	int i,x,y;

	 for(i=0,x=24,y=8; i<n; i++)
		{
	    	if(x1==i)
			{
	    		gotoxy(x,y+i);
	            textcolor(CC_FONT_WHITE,CC_BACK_DBLUE);
	            printf("%s",menu[i]);
	            textcolor(CC_FONT_WHITE,0);
	            continue;
	        }
	        gotoxy(x,y+i);
	        printf("%s",menu[i]);
	    }
}

void noCursor(void) //커서를 없앤다.
{
 CONSOLE_CURSOR_INFO CurInfo;
 CurInfo.dwSize=1;
 CurInfo.bVisible=FALSE;
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}

void cls(void)
{
	int i;

	for(i=0;i<27;i++){
			gotoxy(0,i);
			printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
	}
	gotoxy(0,0);
}

void ready(int level)
{
	char* menu[3]={
		"┌───────────────────────┐", 
		"│　　　　　　　　　　　　　　　　　　　　　　　│",
		"└───────────────────────┘"};
	int x=9, y=5;
	int i;
	
	cls();

	noCursor();

	textcolor(CC_FONT_RED, 0);
	gotoxy(x, y), printf("%s", menu[0]);
	for(i=1; i<7; i++)
		gotoxy(x, y+i), printf("%s", menu[1]);
	gotoxy(x, y+i), printf("%s", menu[2]);
	textcolor(CC_FONT_WHITE, 0);

	textcolor(CC_FONT_GREEN, 0);
	gotoxy(23, 7), printf("Stage %2d 을 시작합니다.", level);
	textcolor(CC_FONT_WHITE, 0);

	textcolor(CC_FONT_WHITE, CC_BACK_DYELLOW);
	gotoxy(32, 10), printf("확인");
	textcolor(CC_FONT_WHITE, 0);

	while(1)
	{
		int temp;
		temp=getch();
		if(temp==13)
			break;
	}	
}