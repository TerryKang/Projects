//짧은글(kor)
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "cmd.h"
#include <windows.h>
#include "conio.h"
#include<mmsystem.h>

void tedu(void);
void tedu2(void);
void tedu3(void);
void tedu1(void);
void cls(void);

	typedef struct shortstring {	
		char string[100];
		int keynum;
	}shortstring;

int short_kor(char *file, int line)
{
	shortstring* strings=(shortstring*)malloc(line*sizeof(shortstring)); 
    int time1, time2;//시간측정을 위한 변수.
	int count=0;
    char cmpstring[100]; //사용자가 입력한 문자열...  strings[line]과 비교..
  // 문자열 데이터베이스..
	char temp[100];					// 임시로 문자열을 저장할 배열.
    char ch;
    int i, j, ch_pointer;
	float maxspeed=0, curspeed;		//maxspeed는 최고 타수...  curspeed... 현재 타수 
	float check;	//정확도
	int chcount=0;		//정확도 측정하기 위한 변수.
	int k,e,length;
	FILE* fp;

    
    cls();
    srand((int)time(NULL)); //시드값 입력
	fp=fopen(file, "rb"); 
	if(fp==NULL)
		printf("file open error!\n");
	
	for(i=0; i<line; i++)
	{
		fgets(temp, sizeof(temp), fp); //먼저 파일로부터 문자열을 temp에 받아들임..
		
		for(j=0; j < strlen(temp)-2; j++) // /r/n을 지워주기위한 작업.
			strings[i].string[j]=temp[j];  //temp의 값을 longstring에 대입.
		strings[i].string[j]='\0'; //문자열의 끝에 NULL값 대입.
		
		strings[i].keynum=strlen(strings[i].string); //키길이를 구함.
	}

	fclose(fp);

//38□■◇◆▩
		/*textcolor(CC_FONT_BLUE,CC_BACK);
		gotoxy(2,1), printf("▧▧▧ ▧▧   ▧▧▧");
		gotoxy(2,2), printf("  ▧   ▧  ▧   ▧  ");
		gotoxy(2,3), printf("  ▧   ▧  ▧   ▧  ");
		gotoxy(2,4), printf("▧▧   ▧▧     ▧  ");
		textcolor(CC_FONT_WHITE,0);*/
		gotoxy(2,1), printf("　　　　　■■■■■■■■■■■■■■■■□□□■□□■■□□□■　　　　　");
		gotoxy(2,2), printf("　　　　■■■■■■■■■■■■■■■■■■□■■□■□■■□■■■　　　　");
		gotoxy(2,3), printf("　　　■■■■■■■■■■■■■■■■■■■□■■□■□■■□■■■■　　　");
		gotoxy(2,4), printf("　　■■■■■■■■■■■■■■■■■■■□□■■□□■■■□■■■■■　　");
		gotoxy(2,5), printf("　■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■　");
		gotoxy(2,6), printf("■■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■■■■");
		gotoxy(2,7), printf("■　　　　　■■■　　　　　　　　　　　　　　　　■■■　　　　　　　■■■");
		gotoxy(2,8), printf("■　　　　■　　　■　　　　　　　　　　　　　　■　　　■　　　　　　　■■");
		gotoxy(2,9), printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■");
		gotoxy(2,10), printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■");
		gotoxy(2,11), printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■");
		gotoxy(2,12), printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■");
		gotoxy(2,13), printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■");
		gotoxy(2,14), printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■");
		gotoxy(2,15), printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■");
		gotoxy(2,16), printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　■");
		gotoxy(2,17), printf("■　　　　　　　　　┏━━━━━━━━━━┓　　　　　　　　　　　　　　　■");
		gotoxy(2,18), printf("■　　　　　　　　　┃　　　　　　　　　　┃　　　　　　　　　　　　　　　■");
		gotoxy(2,19), printf("■　　　　　　　　　┃　　　　　　　　　　┃　　　　　　　　　　　　　　　■");
		gotoxy(2,20), printf("■　　　　　　　　　┃　　　　　　　　　　┃　　　　　　　　　　　　　　　■");
		gotoxy(2,21), printf("■　　　　　　　　　┗━━━━━━━━━━┛　　　　　　　　　　　　　　　■");
		gotoxy(2,22), printf("　■　　　　　　　　　　　　　　　　　　　　 　 　　　　　　　　　　　　■");
		gotoxy(2,23), printf("　　■■■　　　　　　　　　　　　　　　　　  　　　　　　　　　　■■■　　");
		gotoxy(2,24), printf("　　　　■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■　　　　");
		gotoxy(0,0);


    ch_pointer=0;
	while(1)
	{
		i=rand()%line;
		
		gotoxy(5,11), printf("                                                                      ");
		textcolor(CC_FONT_GREEN,0);
		gotoxy(5,11), fputs(strings[i].string, stdout);
		fflush(stdout);
		
		memset(cmpstring, 0, sizeof(cmpstring) );

		time1=GetTickCount(); //시작시간 입력

		textcolor(CC_FONT_WHITE,CC_BACK_DBLUE);
		gotoxy(5,12); 
		for(j=0; j<strings[i].keynum; j++)
			printf(" ");
		gotoxy(5,12);
		ch_pointer=0;
		while(1)
		{
			ch=getch();
			if ( ch == 13 && ch_pointer == strings[i].keynum ) 
			{
				sndPlaySound("c:\\sound\\Windows Error.wav", SND_ASYNC|SND_NODEFAULT);
				//printf("\a");
				break;
			}//Enter 누르면 문장입력 종료
			else if ( ch == 27 ) {  //ESC 누르면 종료
				textcolor(CC_FONT_WHITE,0);
				return 0;
			}
			else if ( ch == 8 ){ // 백스페이스 누르면
			    if ( ch_pointer != 0 ){
			    	if(cmpstring[ch_pointer-1]>0)
			    		printf("\b \b"); // 화면에 한글자 지우기
			    	if(cmpstring[ch_pointer-1]<0){
				        printf("\b \b\b");
				        ch_pointer--;
				    }
			    	ch_pointer--;
			    }
			}
			else if ( ch != 13){ // 백스페이스도 아니고 Enter도 아니면
				if ( ch_pointer == 0 ) time1 = GetTickCount(); //처음이면 시간 측정
				if(strings[i].string[ch_pointer]!=ch){
					textcolor(CC_FONT_RED,CC_BACK_DBLUE);
					printf("%c",ch);
					textcolor(CC_FONT_WHITE,CC_BACK_DBLUE);
				}
				else{
					printf("%c",ch);
				}
				if(ch_pointer==strings[i].keynum) 
					break;    
			    cmpstring[ch_pointer++] = ch;
			    
			}
		}
		textcolor(CC_FONT_WHITE,0);
		gotoxy(5,12), printf("                                                                       ");
		


		time2=GetTickCount(); //마침 시간 측정.
		
		if(atoi(cmpstring)==999)
		{
			printf("게임 종료\n");
			return 0;
		}
		for(j=0, k=0, e=0; j < strings[i].keynum; j++)
		{
			if(strings[i].string[j]<0)
				k++;
			else if(strings[i].string[j]>=0)
				e++;
		}
		length=e+(k/2);
	
		for(j=0, k=0, e=0; j < strings[i].keynum; j++)
		{
			
			if(cmpstring[j]==strings[i].string[j])
				if(strings[i].string[j]<0)
					k++;
				else if(strings[i].string[j]>=0)
					e++;
		}
		chcount=e+(k/2);

		check=(float)chcount/length*100;					//정확도 입력.	
		curspeed=(float)strings[i].keynum/(time2-time1)*70000*check/100;				//타수 측정.

		if(curspeed>maxspeed)
			maxspeed=curspeed;

		gotoxy(22, 14), printf("현재 타수 :         ");
		gotoxy(22, 14), printf("현재 타수 : %0.0f", curspeed);

//현재 타수 게이지
		gotoxy(22, 15), printf("                                                 ");
		gotoxy(22, 15);
		for(j=0; j<((int)curspeed/50); j++)
			printf("■");
		gotoxy(22+2*j, 15);
		for(j=0; j<20-((int)curspeed/50); j++)
			printf("□");
	
		gotoxy(25, 18), printf("최고 타수 :       ");
		gotoxy(25, 18), printf("최고 타수 : %0.0f", maxspeed);
//최고타수 게이지
	/*		gotoxy(25, 17), printf("                                             ");
		gotoxy(25, 17);
		for(j=0; j<((int)maxspeed/50); j++)
			printf("■");
		gotoxy(25+2*j, 17);
		for(j=0; j<20-((int)maxspeed/50); j++)
			printf("□");*/

		gotoxy(25, 20), printf("정확도 :         ");
		gotoxy(25, 20), printf("정확도 : %0.1f", check);
		
		if(check<100)
		{
			tedu();
			count++;
		}
		if(count>=2)
			tedu2();
		if(check==100){
			tedu3();
			count=0;}


//정확도 게이지
	/*	gotoxy(25, 20), printf("                                                ");
		gotoxy(25, 20);
		for(j=0; j<((int)check/5); j++)
			printf("■");
		gotoxy(25+2*j, 20);
		for(j=0; j<20-((int)check/5); j++)
			printf("□");*/
	}
	free(strings);
}


void tedu(void)
{
	int i;
	int x=12,y=7;
	char *table1[]={
		"■■■■■　　　　　　　　　　　　　　■■■■■　　┛┗",
		"　　　　　　　　　　　　　　　　　　　　　　　　　　┓┏"};		

	for(i=0;i<2;i++)
	{
		gotoxy(x,y+i);
		printf("%s",table1[i]);
	}
}

/*void tedu1(void)
{
	int i;
	int x=50,y=16;
	char *table4[]={
		"■■■■■■■■■",
		"■　■　■　■　■",
		"■　■　■　■　■■■",
		"■　　　　　　　■　■",
		"■　　　　　　　■　■",
		"■■■　　　■■■■■",
		"　　■　　　■",
		"　　■　　　■"};		

	for(i=0;i<8;i++)
	{
		gotoxy(x,y+i);
		printf("%s",table4[i]);
	}
}*/

void tedu2(void)
{
	int i;
	int x=12,y=7;
	char *table2[]={
		"■■■■■　　　　　　　　　　　　　　■■■■■　　　　",
		"　■　■　　　　　　　　　　　　　　　　■　■　　　　　",
		"　■　■　　　　　　　　　　　　　　　　■　■"};

	for(i=0;i<3;i++)
	{
	gotoxy(x,y+i);
	printf("%s",table2[i]);
	}
}

void tedu3(void)
{
	int i;
	int x=12,y=7;
	char *table1[]={
		"　■■■　　　　　　　　　　　　　　　　■■■　　　　　",
		"■　　　■　　　　　　　　　　　　　　■　　　■　　　　",
		"　　　　　　　　　　　　　　　　　　　　　　　　　　　　"};

	for(i=0;i<3;i++)
	{
		gotoxy(x,y+i);
		printf("%s",table1[i]);
	}
}