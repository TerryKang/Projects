#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "cmd.h"
#include <windows.h>
#include "conio.h"

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27
#define ENTER 13
#define BX 5
#define BY 1
#define BW 12
#define BH 22
#define SPACE 32
#define F3 61
#define F2 60


void gotoxy(int x, int y);
void start(void);
void screen(int n);
int side(int nx1);
int down(void);
void clean(void);
void print(void);
void noCursor(void);
int bottom(void);
void random(void);
int Func_score(void);
void Func_next(int n);
void reset(void);
void noCursor(void);
void tetris_menu(void);
void GameOver(int a);
void Func_ready(int level);
void PAUSE(void);
void cls(void);
void tetrisrank(int totalscore);
void tetrisrankupdate(char name[], int score);
void tetrisrankview(void);
void tetrisrankformat(void);

struct rank{				//랭킹 구조체(이름, 스테이지, 점수)
	char name[15];
	int stage;
	int score;
};

char color[]={12,8,9,13,14,10,11};
char *board[]={"　","■","┃","□"};
char block[7][4][4][4]=
{
	//막대모양
	0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,	0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,
	
	//네모모양
	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
	
	//'ㅓ'모양
	0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,	0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,

	//'ㄱ'모양
	0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,	1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,	0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,	
	
	//'ㄴ'모양	
	1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,	0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,	0,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,

	//'Z' 모양
	0,0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,

	//'S' 모양
	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0
};

int bg[BW+1][BH+1];
int shape;
int nshape;
int num;
int nx,ny;
int next[7][7];
int stage;

int tetris(void)
{
    char ch;
	int time1;
	int time2;
	int time3;
	int over=0;
	int score=0;

	Func_ready(stage);

	srand(time(NULL));
	noCursor();
	while(1)
	{
		int temp;
		temp=getch();
		if(temp==13)
			break;
	}
	start();
	textcolor(14,0);
	gotoxy(31,12),printf("SCORE :%5d",score);
	textcolor(15,0);

	time1=GetTickCount();
	time3=stage*100;

	while(1)
	{
		if(score>=stage*1000 && stage<11){
			stage++;
			sndPlaySound("next.wav", SND_ASYNC|SND_NODEFAULT);
			Func_ready(stage);
			while(1)
			{
				int temp;
				temp=getch();
				if(temp==13)
					break;
			}
			cls();
			screen(0);
			Func_next(0);
			textcolor(14,0);
			gotoxy(31,12),printf("SCORE :%5d",score);
			textcolor(15,0);
			if(stage<11) time3=stage*100;
			else time3=1050;
		}
		if(over==9){
			GameOver(0);
			tetrisrank(score);
			return 0;
		}
		time2=GetTickCount();
		
		if(time2-time1>1070-time3){
			if(down()){
				clean();
				ny++;
				print();
				time1 =GetTickCount();
			}
			else{
				over=bottom();
				score+=Func_score();
				textcolor(14,0);
				gotoxy(31,12),printf("SCORE :%5d",score);
				textcolor(15,0);
				if(over==9) continue;
				random();
			}
		}
	


		if(kbhit()){
			ch=getch();
			if(ch==-32)
				ch=getch();
			switch(ch)
			{
				case LEFT:
					if(side(nx-1)){
						clean();
						nx--;
						print();
						sndPlaySound("side.wav", SND_ASYNC|SND_NODEFAULT);
					}
					break;
				case RIGHT:
					 if(side(nx+1)){
						clean();
						nx++;
						print();
						sndPlaySound("side.wav", SND_ASYNC|SND_NODEFAULT);
					}
					break;
				case DOWN:
					if(down()){
						clean();
						ny++;
						print();
						sndPlaySound("side.wav", SND_ASYNC|SND_NODEFAULT);
					}
					else{
						over=bottom();
						score+=Func_score();
						textcolor(14,0);
						gotoxy(31,12),printf("SCORE :%5d",score);
						textcolor(15,0);
						if(over==9) break;
						random();
					}
					break;
				case UP:
					if(num==3) num=0;
					else num++;
					if(down()!=1 || side(nx)!=1 || side(nx)!=1 || shape==1){
						if(num==0) num=3;
						else num--;
						break;
					}
					sndPlaySound("turn.wav", SND_ASYNC|SND_NODEFAULT);
					clean();
					print();
					break;
				case SPACE:
					while(1){
						if(down()){
							clean();
							ny++;
							print();
							continue;
						}
						else{
							over=bottom();
							score+=Func_score();
							textcolor(14,0);
							gotoxy(31,12),printf("SCORE :%5d",score);
							textcolor(15,0);
							if(over==9) break;
							random();
							break;
						}
					}
					break;
				case F2:
						start();
						score=0;
						textcolor(14,0);
						gotoxy(31,12),printf("SCORE :%5d",score);
						textcolor(15,0);
						time1=GetTickCount();
						break;
				case F3:
					textcolor(7,0);
					gotoxy(31,12),printf("SCORE :%5d",score);
					PAUSE();
					textcolor(15,0);
					while(1)
					{
						int ch;
						ch=getch();

						if(ch==F3) break;
					}
					cls();
					screen(0);
					Func_next(0);
					textcolor(14,0);
					gotoxy(31,12),printf("SCORE :%5d",score);
					textcolor(15,0);
					break;
				case ESC:
					return 0;
			}
		}
	}
	return 0;
}

void random()
{
	shape=nshape;
	nshape=rand()%7;

	nx=5,ny=1;
	num=0;

	Func_next(1);

    print();

}

void screen(int n)
{
	int x,y;
	int i;
	if(n==0){
		textcolor(13, 0);
		gotoxy(35, 20), printf("┌───────┐");
		gotoxy(35, 21), printf("│   ");

		textcolor(10, 0);
		printf("STAGE %2d ", stage);
		textcolor(13, 0);
		printf("　│");
		gotoxy(35, 22), printf("└───────┘"); 
		textcolor(15, 0);
		gotoxy(45,1),puts("┏━━━━━━━━━━━━┓");
		gotoxy(45,2),puts("┃　　　  　　  　　　　　┃");
		gotoxy(45,3),puts("┣━━━━━━━━━━━━┫");

		for(i=0;i<10;i++){
			gotoxy(45,4+i),puts("┃　　　　　　　　　　　　┃");
		}

		gotoxy(45,4+i),puts("┗━━━━━━━━━━━━┛");
		textcolor(14,0);
		gotoxy(57,2),puts("K E Y");
		gotoxy(48,5),puts("↑ - Rotate");
		gotoxy(48,6),puts("→ - Right Move");
		gotoxy(48,7),puts("← - Left Move");
		gotoxy(48,8),puts("↓ - Down One Box");
		gotoxy(48,9),puts("Space - Put Down Block");
		gotoxy(48,10),puts("F2 - Restart");
		gotoxy(48,11),puts("F3 - Pause");
		gotoxy(48,12),puts("ESC - Game Exit");
		textcolor(15,0);

	}
	for(x=0+n;x<BW-n;x++){
		for(y=0+n;y<BH-n;y++){
			gotoxy(BX+x*2,BY+y);
			if(bg[y][x]==1 ){
				textcolor(color[shape],0);
				puts(board[1]);
				textcolor(15,0);
			}
			else if(bg[y][x]>2){
				textcolor(color[bg[y][x]-3],0);
				puts(board[1]);
				textcolor(15,0);
			}
			else if(y==0 && x==0) puts("┏");
			else if(y==0 && x==11) puts("┓");
			else if(y==21 && x==0) puts("┗");
			else if(y==21 && x==11) puts("┛");
			else if((x!=0 || x!=11) && (y==0 || y==21)) puts("━");
            else puts(board[bg[y][x]]);
		}
	}
}

void clean()
{
	int x,y;
	for(y=1;y<BH-1;y++){
		for(x=1;x<BW-1;x++){
			if(bg[y][x]==1){
				gotoxy(BX+x*2,BY+y);
				bg[y][x]=0;
				puts(board[bg[y][x]]);
			}
		}
	}
}

void print(void)
{
     int i,j;
     
     for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(block[shape][num][i][j]==1){
				textcolor(color[shape],0);
				bg[ny+i][nx+j]=block[shape][num][i][j];
				gotoxy(BX+nx*2+j*2,BY+ny+i);
				puts(board[block[shape][num][i][j]]);
				textcolor(15,0);
			}
		}
	}
}

int side(int nx1)
{
	int i,j;

	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(block[shape][num][i][j]==1){
				if(bg[ny+i][nx+j]+bg[ny+i][nx1+j]>2 || nx1+j==0 || nx1+j==11)
					return 0;
			}
		}
	}

	return 1;
}

int down(void)
{
	int i,j;
	int ny1=ny+1;

	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(block[shape][num][i][j]==1){
				if(bg[ny+i][nx+j]+bg[ny1+i][nx+j]>2){
					return 0;
				}
			}
		}
	}
	return 1;
}

int bottom(void)
{
	int x,y;
	int over=0;

	for(y=1;y<21;y++){
		for(x=1;x<11;x++){
			if(bg[y][x]==1){
				textcolor(color[shape],0);
				gotoxy(BX+x*2,BY+y);
				bg[y][x]=shape+3;
				puts(board[1]);
				textcolor(15,0);
				if(y-1<1) over=9;
			}
		}
	}
	sndPlaySound("bottom.wav", SND_ASYNC|SND_NODEFAULT);
	return over;
}

int Func_score(void)
{
	int i,j,k;
	int xcount=0;
	int ycount=0;
	int temp=0;

	for(i=20;i>0;xcount=0){
		for(j=1;j<11;j++){
			if(bg[i][j]>2) xcount++;
		}
		if(xcount==10){
			sndPlaySound("score.wav", SND_ASYNC|SND_NODEFAULT);
			for(j=1;j<11;j++){
				textcolor(7,0);
				gotoxy(BX+j*2,BY+i),puts(board[1]);
				Sleep(30);
			}
			textcolor(15,0);
			ycount++;
			temp++;
			for(k=i;k>1;k--){
				for(j=1;j<11;j++){
					bg[k][j]=bg[k-1][j];
                }
			}
			screen(1);
		}
		else i--;
	}
	if(ycount==4) return temp*50+100;
	else if(ycount==3) return temp*50+50;
	else return temp*50;
}

void Func_next(int n)
{
	int x,y;
	int i,j;
	
	for(y=1;y<6;y++){
		for(x=1;x<6;x++){
			gotoxy(30+x*2,3+y);
			next[y][x]=0;
			puts(board[next[y][x]]);
		}
	}

	x=2,y=2;
	if(nshape==0) x--;
	if(n==0){
		gotoxy(30,1),puts("┏━━━━━┓");
		gotoxy(30,2),puts("┃　　　　　┃");
	}
	textcolor(14,0);
	gotoxy(34,2),puts("N E X T");
	textcolor(15,0);

	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(block[nshape][num][i][j]==1)
				next[y+i][x+j]=block[nshape][num][i][j];
		}
	}
		
	for(y=0+n;y<7-n;y++){
		for(x=0+n;x<7-n;x++){
			if(next[y][x]==1) textcolor(color[nshape],0);
			gotoxy(30+x*2,3+y);
			if(y==0 && x==0) puts("┣");
			else if(y==0 && x==6) puts("┫");
			else if(y==6 && x==0) puts("┗");
			else if(y==6 && x==6) puts("┛");
			else if((x!=0 || x!=6) && (y==0 || y==6)) puts("━");
            else puts(board[next[y][x]]);
			textcolor(15,0);
		}
		
	}
}

void reset(void)
{
	int x,y;
	cls();
	for(x=0;x<BW;x++){
		for(y=0;y<BH;y++){
			bg[y][x] = (y==0 || y==BH-1 || x==0 || x==BW-1) ? 2:0;
        }
    }

	for(x=0;x<7;x++){
		for(y=0;y<7;y++){
			next[y][x]= (y==0 || y==6 || x==6 || x==0) ? 2:0;
		}
	}

	nshape=rand()%7;
}

void start(void)
{
	reset();	
	screen(0);
	random();
	Func_next(0);
}

void tetris_menu(void)
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
							else if(x1==0) x1=9;
							break;
						case DOWN:
	        				if(x1<11)
	        					x1++;
							else if(x1==9) x1=0;
							break;
						case ENTER:
							if (x1==10){
								tetrisrankview();
								break;
							}
							else if(x1==11){
								tetrisrankformat();
								break;
							}
							stage=x1+1;
	        				tetris();
							x1=0;
							cls();
	        				break;
						case ESC:
							return;
					}
					break;
				}
				else
					continue;
			}
			if(ch==ENTER) break;
		}	
	}
}

void GameOver(int a)
{
	int i,x,y;

	char *table[]={
         "┌───────────────────┐","│　　　　　　　　　　　　　　　　　　　│","└───────────────────┘"
	};
	if(a==0){
		textcolor(7,0);
		for(y=20;y>0;y--){
			for(x=1;x<BW-1;x++){
				if(bg[y][x]>0){
					gotoxy(BX+x*2,BY+y);
					puts(board[1]);
				}
			}
			Sleep(20);
		}
	}
	textcolor(15,0);
	if(a==1){
		textcolor(12,0);
		gotoxy(22,10),puts(table[0]);
		for(i=0;i<5;i++)
			gotoxy(22,11+i),puts(table[1]);
		gotoxy(22,11+i),puts(table[2]);
		textcolor(10,0);
		gotoxy(38,12),puts("GameOver");
		Sleep(100);

		textcolor(9,0);
		for(i=0;i<15;i++){
			gotoxy(28+i*2,14),puts("■");
			Sleep(70);
		}
		textcolor(15,0);
		Sleep(100);
	}
}

void PAUSE(void)
{
	int x,y,i;
	char *table[]=
	{
		"┌───────────────────┐",
		"│　　　　　　　　　　　　　　　　　　　│",
		"└───────────────────┘",
	};

	gotoxy(35, 20), printf("┌───────┐");
	gotoxy(35, 21), printf("│   ");
	printf("STAGE %2d ", stage);
	printf("　│");
	gotoxy(35, 22), printf("└───────┘");
	gotoxy(45,1),puts("┏━━━━━━━━━━━━┓");
	gotoxy(45,2),puts("┃　　　  　　  　　　　　┃");
	gotoxy(45,3),puts("┣━━━━━━━━━━━━┫");

	for(i=0;i<10;i++){
		gotoxy(45,4+i),puts("┃　　　　　　　　　　　　┃");
	}
	gotoxy(45,4+i),puts("┗━━━━━━━━━━━━┛");
	gotoxy(57,2),puts("K E Y");
	gotoxy(48,5),puts("↑ - Rotate");
	gotoxy(48,6),puts("→ - Right Move");
	gotoxy(48,7),puts("← - Left Move");
	gotoxy(48,8),puts("↓ - Down One Box");
	gotoxy(48,9),puts("Space - Put Down Block");
	gotoxy(48,10),puts("F2 - Restart");
	gotoxy(48,11),puts("F3 - Pause");
	gotoxy(48,12),puts("ESC - Game Exit");

	for(x=0;x<BW;x++){
		for(y=0;y<BH;y++){
			gotoxy(BX+x*2,BY+y);
			if(bg[y][x]>2) puts(board[1]);
			else if(y==0 && x==0) puts("┏");
			else if(y==0 && x==11) puts("┓");
			else if(y==21 && x==0) puts("┗");
			else if(y==21 && x==11) puts("┛");
			else if((x!=0 || x!=11) && (y==0 || y==21)) puts("━");
            else puts(board[bg[y][x]]);
		}
	}

	gotoxy(30,1),puts("┏━━━━━┓");
	gotoxy(30,2),puts("┃　　　　　┃");
	gotoxy(34,2),puts("N E X T");

	for(y=0;y<7;y++){
		for(x=0;x<7;x++){
			gotoxy(30+x*2,3+y);
			if(y==0 && x==0) puts("┣");
			else if(y==0 && x==6) puts("┫");
			else if(y==6 && x==0) puts("┗");
			else if(y==6 && x==6) puts("┛");
			else if((x!=0 || x!=6) && (y==0 || y==6)) puts("━");
            else puts(board[next[y][x]]);
		}		
	}
	textcolor(14,0);
	gotoxy(15,10),puts("PAUSE");
	textcolor(15,0);
}

void Func_ready(int level)
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
}

//테트리스 랭킹
void tetrisrank(int totalscore)
{
	char* menu[3]={
		"┌───────────────────┐",
		"│　　　　　　　　　　　　　　　　　　　│",
		"└───────────────────┘"};
	int i;
	char name[10];
	char temp[10];
	int scorecheck;
	FILE* fp;
	
	noCursor();

	fp=fopen("tetrisranking.DAT", "rb");
	if(fp==NULL)
		fputs("File Open Error!\n", stderr);

	for(i=0; i<30; i++)
		fgets(temp, sizeof(temp), fp);

	fclose(fp);

	scorecheck=atoi(temp);

	if(totalscore>scorecheck)
	{
		textcolor(CC_FONT_YELLOW, 0);
		gotoxy(12,8), printf("%s", menu[0]);
		for(i=1; i<7; i++)
			gotoxy(12, 8+i), printf("%s", menu[1]);
		gotoxy(12, 8+i), printf("%s", menu[2]);
		textcolor(CC_FONT_GREEN, 0);
		gotoxy(26, 10), printf("고득점 입니다!");
		textcolor(CC_FONT_WHITE, 0);
		gotoxy(26, 13), printf("이름 : ");
		textcolor(CC_FONT_BLUE, 0);
		scanf("%s", name);
		textcolor(CC_FONT_WHITE, 0);
	}
	else{
		GameOver(1);
		return ;
	}

	tetrisrankupdate(name, totalscore);
	tetrisrankview();

}

//테트리스 랭킹 업데이트
void tetrisrankupdate(char name[], int score)
{
	struct rank ranking[10];								//랭킹 Top 10;
	int i, j;											//루프를 위한 변수
	FILE* fp;	
	
	noCursor();

	fp=fopen("tetrisranking.dat", "rb");
	if(fp==NULL)
		fputs("File Open error!\n", stderr);
	for(i=0; i<10; i++)
	{
		fscanf(fp,"%s", ranking[i].name);
		fseek(fp, 2, SEEK_CUR);
		fscanf(fp,"%d", &ranking[i].stage);
		fseek(fp, 2, SEEK_CUR);
		fscanf(fp,"%d", &ranking[i].score);
		fseek(fp, 2, SEEK_CUR);
	}
	fclose(fp);

	for(i=0; i<10; i++)
	{
		if(ranking[i].score<score)
		{
			for(j=9; j-1>=i; j--)
			{
				memset(ranking[j].name, '\0', sizeof(ranking[j].name));
				strcpy(ranking[j].name, ranking[j-1].name);	
				ranking[j].stage=ranking[j-1].stage;
				ranking[j].score=ranking[j-1].score;
			}
			memset(ranking[i].name, '\0', sizeof(ranking[i].name));
			strcpy(ranking[i].name, name);
			ranking[i].stage=stage;
			ranking[i].score=score;
			break;
		}
	}

	fp=fopen("tetrisranking.dat", "wt");
	if(fp==NULL)
		fputs("File Open error!\n", stderr);
	
	for(i=0; i<10; i++)
	{
		fprintf(fp, "%s\n", ranking[i].name);
		fprintf(fp, "%d\n", ranking[i].stage);
		fprintf(fp, "%d\n", ranking[i].score);
	}

	fclose(fp);
}

//테트리스 랭킹보기 
void tetrisrankview(void)
{
	struct rank ranking[10];
	char* tbl[3]={
		"┌─────────────────────────────★",
		"│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│",
		"□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□"};
	int x=10, y=5;
	int i;
	FILE* fp;	
	
	noCursor();

	fp=fopen("tetrisranking.dat", "rb");
	if(fp==NULL)
		fputs("File Open error!\n", stderr);
	for(i=0; i<10; i++)
	{
		fscanf(fp,"%s", ranking[i].name);
		fseek(fp, 2, SEEK_CUR);
		fscanf(fp,"%d", &ranking[i].stage);
		fseek(fp, 2, SEEK_CUR);
		fscanf(fp,"%d", &ranking[i].score);
		fseek(fp, 2, SEEK_CUR);
	}
	fclose(fp);
	cls();

	textcolor(CC_FONT_GREEN, 0);
	gotoxy(23, 1), printf("┌────────────────┐");
	gotoxy(23, 2), printf("│　　　　　　　　　　　　　　　　│");
	gotoxy(23, 3), printf("└────────────────┘");
	textcolor(CC_FONT_WHITE, 0);

	textcolor(CC_FONT_YELLOW, 0);
	gotoxy(30, 2), printf("테 트 리 스 순 위  ");

	textcolor(32, 0);
	gotoxy(x, y), printf("%s", tbl[0]);
	for(i=1; i<14; i++)
		gotoxy(x, y+i), printf("%s", tbl[1]);
	textcolor(CC_FONT_WHITE, 0);
	textcolor(68, 0);
	gotoxy(x, y+i), printf("%s", tbl[2]);
	textcolor(CC_FONT_WHITE, 0);
	textcolor(47, 0);
	gotoxy(16,6),printf("떠든사람                                     ＃＃\n");
	textcolor(CC_FONT_WHITE, 0);

	for(i=0; i<10; i++)
	{
		textcolor(47, 0);
		gotoxy(16, 8+i); 
		printf("%2d등\t", i+1); 
		printf("이름 : %6s\t", ranking[i].name);
		printf("스테이지 : %2d\t", ranking[i].stage);
		printf("점수 : %5d", ranking[i].score);
		textcolor(CC_FONT_WHITE, 0);
	}
	gotoxy(26,22);
	getch();
	cls();
}
//테트리스 랭킹 포맷 
void tetrisrankformat(void)
{
	FILE* fp;
	int i;
	char* menu[3]={
		"┌──────────────────┐",
		"│　　　　　　　　　　　　　　　　　　│",
		"└──────────────────┘"};

	noCursor();

	fp=fopen("tetrisranking.dat", "wt");
	if(fp==NULL)
		fputs("File Open Error!\n", stderr);

	for(i=0; i<30; i++)
	{
		fprintf(fp, "익명\n" );
		fprintf(fp, "0\n");
		fprintf(fp, "0\n");
	}

	fclose(fp);

	textcolor(CC_FONT_RED, 0);
	gotoxy(19, 9), printf("%s", menu[0]);
	for(i=1; i<7; i++)
		gotoxy(19, 9+i), printf("%s", menu[1]);
	gotoxy(19, 9+i), printf("%s", menu[2]);
	textcolor(CC_FONT_WHITE, 0);

	textcolor(CC_FONT_GREEN, 0);
	gotoxy(27, 11), printf("점수가 초기화 되었습니다.");
	textcolor(CC_FONT_WHITE, CC_BACK_BLUE);
	gotoxy(37, 14), printf("확인");
	textcolor(CC_FONT_WHITE, 0);
	
	getch();
	cls();
}