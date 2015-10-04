#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "cmd.h"
#include <windows.h>
#include "conio.h"
#define KORNUM 2780
#include<mmsystem.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27
#define ENTER 13

typedef struct korwords {
	char korword[20];
}korwords;

typedef struct viewwords {
	char words[20];
	int x;					//x좌표
	int y;					//y좌표
}viewwords;

void gotoxy(int x, int y);
void textcolor(unsigned int text, unsigned int back);
void noCursor(void);
void ready(int level);
void rank(int totalscore, int stage);					//현재 점수가 10위권 안에 드는지 확인해주는 함수
void eng_rank(int totalscore, int stage);				//영문 `` `` `` ``
void rankupdate(char name[], int stage, int score);			//점수가 10위 안에 들었을경우 업뎃 해주는 함수
void eng_rankupdate(char name[], int stage, int score);	//영문 자원캐기 랭킹 업뎃.
void rankview(void);							//한글 자원캐기 랭킹 보기
void rankformat(void);							//영문 자원캐기 랭킹 초기화
void eng_rankformat(void);						//영문 자원캐기 랭킹 초기화
void eng_rankview(void);						//영문 자원캐기 랭킹 보기
void eng_rank(int totalscore, int stage);
int Func_line (char *file);
void jawon_GameOver(void);
void cls(void);

struct rank{							//랭킹 구조체(이름, 스테이지, 점수)
	char name[15];
	int stage;
	int score;
};

//한글 자원캐기
int jawon(int stage)
{
	korwords kor[KORNUM];
	viewwords view[54];		//화면에 뿌려질 54개의 단어

	int temp, check=0;				
	int index[54];			//
	unsigned int i, j, k;				//루프를 위한 변수.
	int time1, time2;
	int x, y;				//좌표
	char ch;
	char cmpstring[20];
	int ch_pointer;
	int checkcount;
	int userscore=0, comscore=0;
	int totalscore=0;
	int comgage=20, usergage=20, comcount=0, usercount=0;
	FILE* fp;

	noCursor();
	cls();

	fp=fopen("wordkor.dat", "rb");
	if(fp==NULL)
	{
		printf("file Open error!\n");
		fflush(stdout);
	}
	for(i=0; i<KORNUM; i++)					//파일로부터 단어 읽어들임
		fscanf(fp, "%s", kor[i].korword);

	srand((int)time(NULL));

	while(1)
	{
		ready(stage);
		cls();
		checkcount=0;
		userscore=0, comscore=0;
		comgage=20, usergage=20, comcount=0, usercount=0;
		memset(index, -1, sizeof(index));		//index 초기화

		for(i=0; i<54; i++, check=0)			//중복 방지.
		{
			temp=rand()%KORNUM;
			if(i>0)								//i가 1 이상일 경우부터 중복 검사.
			{
				for(j=0; j<i; j++ )			
				{
					if(temp==index[j])			//난수로 생성된 temp 값이 index 중에 있는지 검사..
						check++;
				}
				if(check!=0)					//만약 중복이 되었다면 새로운 난수 생성..
				{
					i--;
					continue;
				}
				else
					index[i]=temp;				//중복되지 않았다면 index에 대입
			}
			index[i]=temp;
		}
		
		for(i=0; i<54; i++)
		{
			for(j=0; j<=strlen(kor[index[i]].korword); j++)
				view[i].words[j]=kor[index[i]].korword[j];
		}

		for(i=0, x=5, y=2; i<54; i++)
		{
			gotoxy(x, y), printf("%s\n", view[i].words);
			view[i].x=x;										//출력한 위치의 좌표를 저장.
			view[i].y=y;
			y=y+2;
			if(y>18)
			{
				y=2;
				x+=10;
			}
		}

		gotoxy(25, 21), printf("┌───────────┐");
		gotoxy(25, 22), printf("│　　　　　　　　　　　│");
		gotoxy(25, 23), printf("└───────────┘");  

		textcolor(13, 0);
		gotoxy(2, 21), printf("┌───────┐");
		gotoxy(2, 22), printf("│   ");

		textcolor(10, 0);
		printf("STAGE %2d ", stage);
		textcolor(13, 0);
		printf("　│");
		gotoxy(2, 23), printf("└───────┘"); 
		textcolor(11, 0);
		for(j=1; j<23; j++)
			gotoxy(65, j), printf("│    │    │");
		gotoxy(65, j),     printf("└──┴──┘");
		gotoxy(65, 0),     printf("┌──┬──┐");
		gotoxy(65, 21),    printf("├──┼──┤");
		gotoxy(65, 2),     printf("├──┼──┤");
		textcolor(CC_FONT_WHITE, 0);
		gotoxy(67, 1),     printf("컴터");
		gotoxy(73, 1),	   printf("유저");
		gotoxy(29, 22);

		memset(index, -1, sizeof(index));
		
		for(j=0; j<54; j++, check=0)			//중복 방지.
		{
			temp=rand()%54;
			if(j>0)								//i가 1 이상일 경우부터 중복 검사.
			{
				for(k=0; k<j; k++ )			
				{
					if(temp==index[k])			//난수로 생성된 temp 값이 index 중에 있는지 검사..
						check++;
				}
				if(check!=0)					//만약 중복이 되었다면 새로운 난수 생성..
				{
					j--;
					continue;
				}
				else
					index[j]=temp;				//중복되지 않았다면 index에 대입
			}
			index[j]=temp;
		}

		time1=GetTickCount(); //시작시간 입력
		ch_pointer=0;
		ch='\0';	

		memset(cmpstring,'\0', sizeof(cmpstring));
		for(i=0; i<54; )
		{
			ch='\0';
			
			if(kbhit())
			{
				ch=getch();
				if(ch==-32)
					ch=getch();

				if(ch_pointer==0)
					gotoxy(29, 22);
			}
			time2=GetTickCount();

			if((time2-time1)>5000-(stage*400))//컴퓨터는 5초마다 하나식 지움.
			{
				if(view[index[i]].words[0]!='-')
				{
					memset(view[index[i]].words, '-', sizeof(view[index[i]].words));		//컴퓨터가 지운 단어는 - 로 초기화
					gotoxy(view[index[i]].x, view[index[i]].y), printf("         ");
					gotoxy(29+ch_pointer, 22);
					checkcount++;
					comscore++;
					gotoxy(68, 22), printf("%2d", comscore);						//컴터 점수
					
					//컴터 점수 게이지
					textcolor(12, 0);
					gotoxy(68, comgage), printf("■");
					textcolor(CC_FONT_WHITE, 0);
					comcount++;
					if(comcount%2==0)
					{
						if(comgage>3)
							comgage--;
					}
					
					gotoxy(29+ch_pointer, 22);
					time1=GetTickCount();
					gotoxy(view[index[i]].x, view[index[i]].y), printf("         ");
					gotoxy(29+ch_pointer, 22);
					i++;
				}
				else
					i++;
			}
			if(ch!='\0')
			{
				if(ch_pointer==8 || ch==13) 
				{//엔터면 입력 종료.
					cmpstring[ch_pointer]='\0';
					for(j=0; j<54; j++)
					{
						if(strcmp(cmpstring,view[j].words)==0)
						{
							sndPlaySound("MsgBell.wav", SND_ASYNC|SND_NODEFAULT);
							memset(view[j].words, '-', sizeof(view[j].words));		//사용자가 지운 단어도 - 로 초기화.
							gotoxy(view[j].x, view[j].y), printf("         ");

							totalscore++;	//유저가 한 단어를 칠때마다 점수 1점씩 증가.

							checkcount++;
							userscore++;
							gotoxy(74, 22), printf("%2d", userscore);			//사용자 점수.
							//유저 점수 게이지
							textcolor(9, 0);
							gotoxy(74, usergage), printf("■");
							textcolor(CC_FONT_WHITE, 0);
							usercount++;
							if(usercount%2==0)
							{
								if(usergage>3)
									usergage--;
							}
							gotoxy(view[j].x, view[j].y), printf("         ");
							break;
						}
						
					}
					memset(cmpstring, '\0', sizeof(cmpstring));
			
					gotoxy(29,22), printf("           ");
					gotoxy(29,22);
					ch_pointer=0;
				}
				else if ( ch == 27 ) 
				{  //ESC 누르면 종료
					textcolor(CC_FONT_WHITE,0);
					rank(totalscore*50, stage);
					cls();
					return 0;
				}
				else if ( ch == 8 )
				{ // 백스페이스 누르면
					if ( ch_pointer > 0 )
					{
			    		if(cmpstring[ch_pointer-1]>0)							//한글이 아닐경우
			    			gotoxy(29+ch_pointer, 22), printf("\b \b");			// 화면에 한칸 지우기
			    		if(cmpstring[ch_pointer-1]<0)							//한글일경우..
						{
							gotoxy(29+ch_pointer, 22), printf("\b \b\b");		//화면에 2칸씩 지움
							ch_pointer--;
						}
			    		ch_pointer--;
					}
				}
				else
				{
					printf("%c", ch);											//화면에 한글자씩 출력
					cmpstring[ch_pointer]=ch;									//배열에 한글자씩 저장 
					ch_pointer++;
				}
			}
			if(checkcount>53)													//단어 54개가 없어지면 끝내준다.
				break;	
		}
		if(userscore>comscore)										//사용자가 이겼을 경우 다음 스테이지로.
		{
			stage++;
		}
		else
		{
			rank(totalscore*50, stage);
			jawon_GameOver();
			break;
		}
	}
	return 0;
}

void rank(int totalscore, int stage)
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

	fp=fopen("ranking.DAT", "rb");
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
	else
		return ;

	rankupdate(name, stage, totalscore);
	rankview();

}

void rankupdate(char name[], int stage, int score)
{
	struct rank ranking[10];								//랭킹 Top 10;
	int i, j;											//루프를 위한 변수
	FILE* fp;	
	
	noCursor();

	fp=fopen("ranking.dat", "rb");
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

	fp=fopen("ranking.dat", "wt");
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

void rankview(void)
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

	fp=fopen("ranking.dat", "rb");
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
	gotoxy(29, 2), printf("자 원 캐 기 순 위  ");
	textcolor(13, 0);
	printf("(한글)");
	textcolor(15, 0);

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
}

void rankformat(void)
{
	FILE* fp;
	int i;
	char* menu[3]={
		"┌──────────────────┐",
		"│　　　　　　　　　　　　　　　　　　│",
		"└──────────────────┘"};

	noCursor();

	fp=fopen("ranking.dat", "wt");
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
}

//영문 자원캐기
int eng_jawon(int stage)
{
	korwords kor[1000];
	viewwords view[36];		//화면에 뿌려질 36개의 단어

	int temp, check=0;				
	int index[36];			//
	unsigned int i, j, k;				//루프를 위한 변수.
	int time1, time2;
	int x, y;				//좌표
	char ch;
	char cmpstring[20];
	int ch_pointer;
	int checkcount;
	int userscore=0, comscore=0;
	int totalscore=0;
	int comgage=20, usergage=20, comcount=0, usercount=0;
	int line;
	FILE* fp;

	noCursor();
	cls();

	fp=fopen("wordeng.dat", "rb");
	if(fp==NULL)
	{
		printf("file Open error!\n");
		fflush(stdout);
	}

	line=Func_line("wordeng.dat");
	for(i=0; i<1000; i++)					//파일로부터 단어 읽어들임
		fscanf(fp, "%s", kor[i].korword);

	srand((int)time(NULL));

	while(1)
	{
		ready(stage);
		cls();
		checkcount=0;
		userscore=0, comscore=0;
		comgage=20, usergage=20, comcount=0, usercount=0;
		memset(index, -1, sizeof(index));		//index 초기화

		for(i=0; i<36; i++, check=0)			//중복 방지.
		{
			temp=rand()%1000;
			if(i>0)								//i가 1 이상일 경우부터 중복 검사.
			{
				for(j=0; j<i; j++ )			
				{
					if(temp==index[j])			//난수로 생성된 temp 값이 index 중에 있는지 검사..
						check++;
				}
				if(check!=0)					//만약 중복이 되었다면 새로운 난수 생성..
				{
					i--;
					continue;
				}
				else
					index[i]=temp;				//중복되지 않았다면 index에 대입
			}
			index[i]=temp;
		}
		
		for(i=0; i<36; i++)
		{
			for(j=0; j<=strlen(kor[index[i]].korword); j++)
				view[i].words[j]=kor[index[i]].korword[j];
		}

		for(i=0, x=5, y=2; i<36; i++)
		{
			gotoxy(x, y), printf("%s\n", view[i].words);
			view[i].x=x;										//출력한 위치의 좌표를 저장.
			view[i].y=y;
			y=y+2;
			if(y>18)
			{
				y=2;
				x+=15;
			}
		}

		gotoxy(25, 21), printf("┌───────────┐");
		gotoxy(25, 22), printf("│　　　　　　　　　　　│");
		gotoxy(25, 23), printf("└───────────┘");  

		textcolor(13, 0);
		gotoxy(2, 21), printf("┌───────┐");
		gotoxy(2, 22), printf("│   ");

		textcolor(10, 0);
		printf("STAGE %2d ", stage);
		textcolor(13, 0);
		printf("　│");
		gotoxy(2, 23), printf("└───────┘"); 
		textcolor(11, 0);
		for(j=1; j<23; j++)
			gotoxy(65, j), printf("│    │    │");
		gotoxy(65, j),     printf("└──┴──┘");
		gotoxy(65, 0),     printf("┌──┬──┐");
		gotoxy(65, 21),    printf("├──┼──┤");
		gotoxy(65, 2),     printf("├──┼──┤");
		textcolor(CC_FONT_WHITE, 0);
		gotoxy(67, 1),     printf("컴터");
		gotoxy(73, 1),	   printf("유저");
		gotoxy(29, 22);

		memset(index, -1, sizeof(index));
		
		for(j=0; j<36; j++, check=0)			//중복 방지.
		{
			temp=rand()%36;
			if(j>0)								//i가 1 이상일 경우부터 중복 검사.
			{
				for(k=0; k<j; k++ )			
				{
					if(temp==index[k])			//난수로 생성된 temp 값이 index 중에 있는지 검사..
						check++;
				}
				if(check!=0)					//만약 중복이 되었다면 새로운 난수 생성..
				{
					j--;
					continue;
				}
				else
					index[j]=temp;				//중복되지 않았다면 index에 대입
			}
			index[j]=temp;
		}

		time1=GetTickCount(); //시작시간 입력
		ch_pointer=0;
		ch='\0';	

		memset(cmpstring,'\0', sizeof(cmpstring));
		for(i=0; i<36; )
		{
			ch='\0';
			
			if(kbhit())
			{
				ch=getch();
				if(ch==-32)
					ch=getch();


				if(ch_pointer==0)
					gotoxy(29, 22);
			}
			time2=GetTickCount();

			if((time2-time1)>5000-(stage*400))//컴퓨터는 5초마다 하나식 지움.
			{
				if(view[index[i]].words[0]!='-')
				{
					memset(view[index[i]].words, '-', sizeof(view[index[i]].words));		//컴퓨터가 지운 단어는 - 로 초기화
					gotoxy(view[index[i]].x, view[index[i]].y), printf("             ");
					gotoxy(29+ch_pointer, 22);
					checkcount++;
					comscore++;
					gotoxy(68, 22), printf("%2d", comscore);						//컴터 점수
					
					//컴터 점수 게이지
					textcolor(12, 0);
					gotoxy(68, comgage), printf("■");
					textcolor(CC_FONT_WHITE, 0);
					comcount++;
					if(comcount%2==0)
					{
						if(comgage>3)
							comgage--;
					}
					
					gotoxy(29+ch_pointer, 22);
					time1=GetTickCount();
					gotoxy(view[index[i]].x, view[index[i]].y), printf("             ");
					gotoxy(29+ch_pointer, 22);
					i++;
				}
				else
					i++;
			}
			if(ch!='\0')
			{
				if(ch_pointer==15 || ch==13) 
				{//엔터면 입력 종료.
					cmpstring[ch_pointer]='\0';
					for(j=0; j<36; j++)
					{
						if(strcmp(cmpstring,view[j].words)==0)
						{
							sndPlaySound("MsgBell.wav", SND_ASYNC|SND_NODEFAULT);
							memset(view[j].words, '-', sizeof(view[j].words));		//사용자가 지운 단어도 - 로 초기화.
							gotoxy(view[j].x, view[j].y), printf("              ");

							totalscore++;	//유저가 한 단어를 칠때마다 점수 1점씩 증가.

							checkcount++;
							userscore++;
							gotoxy(74, 22), printf("%2d", userscore);			//사용자 점수.
							//유저 점수 게이지
							textcolor(9, 0);
							gotoxy(74, usergage), printf("■");
							textcolor(CC_FONT_WHITE, 0);
							usercount++;
							if(usercount%2==0)
							{
								if(usergage>3)
									usergage--;
							}
							gotoxy(view[j].x, view[j].y), printf("             ");
							break;
						}
						
					}
					memset(cmpstring, '\0', sizeof(cmpstring));
			
					gotoxy(29,22), printf("               ");
					gotoxy(29,22);
					ch_pointer=0;
				}
				else if ( ch == 27 ) 
				{  //ESC 누르면 종료
					textcolor(CC_FONT_WHITE,0);
					eng_rank(totalscore*50, stage);
					cls();
					return 0;
				}
				else if ( ch == 8 )
				{ // 백스페이스 누르면
					if ( ch_pointer > 0 )
					{
			    		if(cmpstring[ch_pointer-1]>0)							//한글이 아닐경우
			    			gotoxy(29+ch_pointer, 22), printf("\b \b");			// 화면에 한칸 지우기
			    		if(cmpstring[ch_pointer-1]<0)							//한글일경우..
						{
							gotoxy(29+ch_pointer, 22), printf("\b \b\b");		//화면에 2칸씩 지움
							ch_pointer--;
						}
			    		ch_pointer--;
					}
				}
				else
				{
					printf("%c", ch);											//화면에 한글자씩 출력
					cmpstring[ch_pointer]=ch;									//배열에 한글자씩 저장 
					ch_pointer++;
				}
			}
			if(checkcount>35)													//단어 36개가 없어지면 끝내준다.
				break;	
		}
		if(userscore>comscore)										//사용자가 이겼을 경우 다음 스테이지로.
		{
			stage++;
		}
		else
		{
			eng_rank(totalscore*50, stage);
			jawon_GameOver();
			break;
		}
	}
	return 0;
}

void eng_rank(int totalscore, int stage)
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

	fp=fopen("engranking.dat", "rb");
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
	else
		return ;

	eng_rankupdate(name, stage, totalscore);
	eng_rankview();

}


//영문 랭킹 초기화
void eng_rankformat(void)
{
	FILE* fp;
	int i;
	char* menu[3]={
		"┌──────────────────┐",
		"│　　　　　　　　　　　　　　　　　　│",
		"└──────────────────┘"};

	noCursor();

	fp=fopen("engranking.dat", "wt");
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
}

//영문 랭킹 업데이트
void eng_rankupdate(char name[], int stage, int score)
{
	struct rank ranking[10];								//랭킹 Top 10;
	int i, j;											//루프를 위한 변수
	FILE* fp;	
	
	noCursor();

	fp=fopen("engranking.dat", "rb");
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

	fp=fopen("engranking.dat", "wt");
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

void eng_rankview(void)
{
	struct rank ranking[10];
	char* tbl[3]={
		"┌─────────────────────────────★",
		"│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│",
		"└─────────────────────────────┘"};
	int x=10, y=5;
	int i;
	FILE* fp;	
	
	noCursor();

	fp=fopen("engranking.dat", "rb");
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
	gotoxy(29, 2), printf("자 원 캐 기 순 위  ");
	textcolor(13, 0);
	printf("(영문)");
	textcolor(15, 0);

	textcolor(32, 0);
	gotoxy(x, y), printf("%s", tbl[0]);
	for(i=1; i<14; i++)
		gotoxy(x, y+i), printf("%s", tbl[1]);
	textcolor(CC_FONT_WHITE, 0);
	textcolor(68, 0);
	gotoxy(x, y+i), printf("%s", tbl[2]);
	textcolor(CC_FONT_WHITE, 0);
	textcolor(47, 0);
	gotoxy(16,6),printf("떠든사람                                    ＃＃\n");
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
}

void jawon_GameOver(void)
{
	int i;

	char *table[]={
         "┌───────────────────┐","│　　　　　　　　　　　　　　　　　　　│","└───────────────────┘"
	};
	textcolor(12,0);
	gotoxy(12,8),puts(table[0]);
	for(i=1;i<6;i++)
		gotoxy(12,8+i),puts(table[1]);
	gotoxy(12,8+i),puts(table[2]);
	textcolor(10,0);
	gotoxy(28,10),puts("GameOver");
	Sleep(100);

	textcolor(9,0);
	for(i=0;i<15;i++){
		gotoxy(18+i*2,12),puts("■");
		Sleep(70);
	}
	textcolor(15,0);
	Sleep(100);
}
