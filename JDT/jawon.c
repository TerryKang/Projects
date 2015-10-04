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
	int x;					//x��ǥ
	int y;					//y��ǥ
}viewwords;

void gotoxy(int x, int y);
void textcolor(unsigned int text, unsigned int back);
void noCursor(void);
void ready(int level);
void rank(int totalscore, int stage);					//���� ������ 10���� �ȿ� ����� Ȯ�����ִ� �Լ�
void eng_rank(int totalscore, int stage);				//���� `` `` `` ``
void rankupdate(char name[], int stage, int score);			//������ 10�� �ȿ� �������� ���� ���ִ� �Լ�
void eng_rankupdate(char name[], int stage, int score);	//���� �ڿ�ĳ�� ��ŷ ����.
void rankview(void);							//�ѱ� �ڿ�ĳ�� ��ŷ ����
void rankformat(void);							//���� �ڿ�ĳ�� ��ŷ �ʱ�ȭ
void eng_rankformat(void);						//���� �ڿ�ĳ�� ��ŷ �ʱ�ȭ
void eng_rankview(void);						//���� �ڿ�ĳ�� ��ŷ ����
void eng_rank(int totalscore, int stage);
int Func_line (char *file);
void jawon_GameOver(void);
void cls(void);

struct rank{							//��ŷ ����ü(�̸�, ��������, ����)
	char name[15];
	int stage;
	int score;
};

//�ѱ� �ڿ�ĳ��
int jawon(int stage)
{
	korwords kor[KORNUM];
	viewwords view[54];		//ȭ�鿡 �ѷ��� 54���� �ܾ�

	int temp, check=0;				
	int index[54];			//
	unsigned int i, j, k;				//������ ���� ����.
	int time1, time2;
	int x, y;				//��ǥ
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
	for(i=0; i<KORNUM; i++)					//���Ϸκ��� �ܾ� �о����
		fscanf(fp, "%s", kor[i].korword);

	srand((int)time(NULL));

	while(1)
	{
		ready(stage);
		cls();
		checkcount=0;
		userscore=0, comscore=0;
		comgage=20, usergage=20, comcount=0, usercount=0;
		memset(index, -1, sizeof(index));		//index �ʱ�ȭ

		for(i=0; i<54; i++, check=0)			//�ߺ� ����.
		{
			temp=rand()%KORNUM;
			if(i>0)								//i�� 1 �̻��� ������ �ߺ� �˻�.
			{
				for(j=0; j<i; j++ )			
				{
					if(temp==index[j])			//������ ������ temp ���� index �߿� �ִ��� �˻�..
						check++;
				}
				if(check!=0)					//���� �ߺ��� �Ǿ��ٸ� ���ο� ���� ����..
				{
					i--;
					continue;
				}
				else
					index[i]=temp;				//�ߺ����� �ʾҴٸ� index�� ����
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
			view[i].x=x;										//����� ��ġ�� ��ǥ�� ����.
			view[i].y=y;
			y=y+2;
			if(y>18)
			{
				y=2;
				x+=10;
			}
		}

		gotoxy(25, 21), printf("��������������������������");
		gotoxy(25, 22), printf("��������������������������");
		gotoxy(25, 23), printf("��������������������������");  

		textcolor(13, 0);
		gotoxy(2, 21), printf("������������������");
		gotoxy(2, 22), printf("��   ");

		textcolor(10, 0);
		printf("STAGE %2d ", stage);
		textcolor(13, 0);
		printf("����");
		gotoxy(2, 23), printf("������������������"); 
		textcolor(11, 0);
		for(j=1; j<23; j++)
			gotoxy(65, j), printf("��    ��    ��");
		gotoxy(65, j),     printf("��������������");
		gotoxy(65, 0),     printf("��������������");
		gotoxy(65, 21),    printf("��������������");
		gotoxy(65, 2),     printf("��������������");
		textcolor(CC_FONT_WHITE, 0);
		gotoxy(67, 1),     printf("����");
		gotoxy(73, 1),	   printf("����");
		gotoxy(29, 22);

		memset(index, -1, sizeof(index));
		
		for(j=0; j<54; j++, check=0)			//�ߺ� ����.
		{
			temp=rand()%54;
			if(j>0)								//i�� 1 �̻��� ������ �ߺ� �˻�.
			{
				for(k=0; k<j; k++ )			
				{
					if(temp==index[k])			//������ ������ temp ���� index �߿� �ִ��� �˻�..
						check++;
				}
				if(check!=0)					//���� �ߺ��� �Ǿ��ٸ� ���ο� ���� ����..
				{
					j--;
					continue;
				}
				else
					index[j]=temp;				//�ߺ����� �ʾҴٸ� index�� ����
			}
			index[j]=temp;
		}

		time1=GetTickCount(); //���۽ð� �Է�
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

			if((time2-time1)>5000-(stage*400))//��ǻ�ʹ� 5�ʸ��� �ϳ��� ����.
			{
				if(view[index[i]].words[0]!='-')
				{
					memset(view[index[i]].words, '-', sizeof(view[index[i]].words));		//��ǻ�Ͱ� ���� �ܾ�� - �� �ʱ�ȭ
					gotoxy(view[index[i]].x, view[index[i]].y), printf("         ");
					gotoxy(29+ch_pointer, 22);
					checkcount++;
					comscore++;
					gotoxy(68, 22), printf("%2d", comscore);						//���� ����
					
					//���� ���� ������
					textcolor(12, 0);
					gotoxy(68, comgage), printf("��");
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
				{//���͸� �Է� ����.
					cmpstring[ch_pointer]='\0';
					for(j=0; j<54; j++)
					{
						if(strcmp(cmpstring,view[j].words)==0)
						{
							sndPlaySound("MsgBell.wav", SND_ASYNC|SND_NODEFAULT);
							memset(view[j].words, '-', sizeof(view[j].words));		//����ڰ� ���� �ܾ - �� �ʱ�ȭ.
							gotoxy(view[j].x, view[j].y), printf("         ");

							totalscore++;	//������ �� �ܾ ĥ������ ���� 1���� ����.

							checkcount++;
							userscore++;
							gotoxy(74, 22), printf("%2d", userscore);			//����� ����.
							//���� ���� ������
							textcolor(9, 0);
							gotoxy(74, usergage), printf("��");
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
				{  //ESC ������ ����
					textcolor(CC_FONT_WHITE,0);
					rank(totalscore*50, stage);
					cls();
					return 0;
				}
				else if ( ch == 8 )
				{ // �齺���̽� ������
					if ( ch_pointer > 0 )
					{
			    		if(cmpstring[ch_pointer-1]>0)							//�ѱ��� �ƴҰ��
			    			gotoxy(29+ch_pointer, 22), printf("\b \b");			// ȭ�鿡 ��ĭ �����
			    		if(cmpstring[ch_pointer-1]<0)							//�ѱ��ϰ��..
						{
							gotoxy(29+ch_pointer, 22), printf("\b \b\b");		//ȭ�鿡 2ĭ�� ����
							ch_pointer--;
						}
			    		ch_pointer--;
					}
				}
				else
				{
					printf("%c", ch);											//ȭ�鿡 �ѱ��ھ� ���
					cmpstring[ch_pointer]=ch;									//�迭�� �ѱ��ھ� ���� 
					ch_pointer++;
				}
			}
			if(checkcount>53)													//�ܾ� 54���� �������� �����ش�.
				break;	
		}
		if(userscore>comscore)										//����ڰ� �̰��� ��� ���� ����������.
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
		"������������������������������������������",
		"������������������������������������������",
		"������������������������������������������"};
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
		gotoxy(26, 10), printf("������ �Դϴ�!");
		textcolor(CC_FONT_WHITE, 0);
		gotoxy(26, 13), printf("�̸� : ");
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
	struct rank ranking[10];								//��ŷ Top 10;
	int i, j;											//������ ���� ����
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
		"��������������������������������������������������������������",
		"��������������������������������������������������������������",
		"��������������������������������"};
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
	gotoxy(23, 1), printf("������������������������������������");
	gotoxy(23, 2), printf("������������������������������������");
	gotoxy(23, 3), printf("������������������������������������");
	textcolor(CC_FONT_WHITE, 0);

	textcolor(CC_FONT_YELLOW, 0);
	gotoxy(29, 2), printf("�� �� ĳ �� �� ��  ");
	textcolor(13, 0);
	printf("(�ѱ�)");
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
	gotoxy(16,6),printf("������                                     ����\n");
	textcolor(CC_FONT_WHITE, 0);

	for(i=0; i<10; i++)
	{
		textcolor(47, 0);
		gotoxy(16, 8+i); 
		printf("%2d��\t", i+1); 
		printf("�̸� : %6s\t", ranking[i].name);
		printf("�������� : %2d\t", ranking[i].stage);
		printf("���� : %5d", ranking[i].score);
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
		"����������������������������������������",
		"����������������������������������������",
		"����������������������������������������"};

	noCursor();

	fp=fopen("ranking.dat", "wt");
	if(fp==NULL)
		fputs("File Open Error!\n", stderr);

	for(i=0; i<30; i++)
	{
		fprintf(fp, "�͸�\n" );
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
	gotoxy(27, 11), printf("������ �ʱ�ȭ �Ǿ����ϴ�.");
	textcolor(CC_FONT_WHITE, CC_BACK_BLUE);
	gotoxy(37, 14), printf("Ȯ��");
	textcolor(CC_FONT_WHITE, 0);
	
	getch();
}

//���� �ڿ�ĳ��
int eng_jawon(int stage)
{
	korwords kor[1000];
	viewwords view[36];		//ȭ�鿡 �ѷ��� 36���� �ܾ�

	int temp, check=0;				
	int index[36];			//
	unsigned int i, j, k;				//������ ���� ����.
	int time1, time2;
	int x, y;				//��ǥ
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
	for(i=0; i<1000; i++)					//���Ϸκ��� �ܾ� �о����
		fscanf(fp, "%s", kor[i].korword);

	srand((int)time(NULL));

	while(1)
	{
		ready(stage);
		cls();
		checkcount=0;
		userscore=0, comscore=0;
		comgage=20, usergage=20, comcount=0, usercount=0;
		memset(index, -1, sizeof(index));		//index �ʱ�ȭ

		for(i=0; i<36; i++, check=0)			//�ߺ� ����.
		{
			temp=rand()%1000;
			if(i>0)								//i�� 1 �̻��� ������ �ߺ� �˻�.
			{
				for(j=0; j<i; j++ )			
				{
					if(temp==index[j])			//������ ������ temp ���� index �߿� �ִ��� �˻�..
						check++;
				}
				if(check!=0)					//���� �ߺ��� �Ǿ��ٸ� ���ο� ���� ����..
				{
					i--;
					continue;
				}
				else
					index[i]=temp;				//�ߺ����� �ʾҴٸ� index�� ����
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
			view[i].x=x;										//����� ��ġ�� ��ǥ�� ����.
			view[i].y=y;
			y=y+2;
			if(y>18)
			{
				y=2;
				x+=15;
			}
		}

		gotoxy(25, 21), printf("��������������������������");
		gotoxy(25, 22), printf("��������������������������");
		gotoxy(25, 23), printf("��������������������������");  

		textcolor(13, 0);
		gotoxy(2, 21), printf("������������������");
		gotoxy(2, 22), printf("��   ");

		textcolor(10, 0);
		printf("STAGE %2d ", stage);
		textcolor(13, 0);
		printf("����");
		gotoxy(2, 23), printf("������������������"); 
		textcolor(11, 0);
		for(j=1; j<23; j++)
			gotoxy(65, j), printf("��    ��    ��");
		gotoxy(65, j),     printf("��������������");
		gotoxy(65, 0),     printf("��������������");
		gotoxy(65, 21),    printf("��������������");
		gotoxy(65, 2),     printf("��������������");
		textcolor(CC_FONT_WHITE, 0);
		gotoxy(67, 1),     printf("����");
		gotoxy(73, 1),	   printf("����");
		gotoxy(29, 22);

		memset(index, -1, sizeof(index));
		
		for(j=0; j<36; j++, check=0)			//�ߺ� ����.
		{
			temp=rand()%36;
			if(j>0)								//i�� 1 �̻��� ������ �ߺ� �˻�.
			{
				for(k=0; k<j; k++ )			
				{
					if(temp==index[k])			//������ ������ temp ���� index �߿� �ִ��� �˻�..
						check++;
				}
				if(check!=0)					//���� �ߺ��� �Ǿ��ٸ� ���ο� ���� ����..
				{
					j--;
					continue;
				}
				else
					index[j]=temp;				//�ߺ����� �ʾҴٸ� index�� ����
			}
			index[j]=temp;
		}

		time1=GetTickCount(); //���۽ð� �Է�
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

			if((time2-time1)>5000-(stage*400))//��ǻ�ʹ� 5�ʸ��� �ϳ��� ����.
			{
				if(view[index[i]].words[0]!='-')
				{
					memset(view[index[i]].words, '-', sizeof(view[index[i]].words));		//��ǻ�Ͱ� ���� �ܾ�� - �� �ʱ�ȭ
					gotoxy(view[index[i]].x, view[index[i]].y), printf("             ");
					gotoxy(29+ch_pointer, 22);
					checkcount++;
					comscore++;
					gotoxy(68, 22), printf("%2d", comscore);						//���� ����
					
					//���� ���� ������
					textcolor(12, 0);
					gotoxy(68, comgage), printf("��");
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
				{//���͸� �Է� ����.
					cmpstring[ch_pointer]='\0';
					for(j=0; j<36; j++)
					{
						if(strcmp(cmpstring,view[j].words)==0)
						{
							sndPlaySound("MsgBell.wav", SND_ASYNC|SND_NODEFAULT);
							memset(view[j].words, '-', sizeof(view[j].words));		//����ڰ� ���� �ܾ - �� �ʱ�ȭ.
							gotoxy(view[j].x, view[j].y), printf("              ");

							totalscore++;	//������ �� �ܾ ĥ������ ���� 1���� ����.

							checkcount++;
							userscore++;
							gotoxy(74, 22), printf("%2d", userscore);			//����� ����.
							//���� ���� ������
							textcolor(9, 0);
							gotoxy(74, usergage), printf("��");
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
				{  //ESC ������ ����
					textcolor(CC_FONT_WHITE,0);
					eng_rank(totalscore*50, stage);
					cls();
					return 0;
				}
				else if ( ch == 8 )
				{ // �齺���̽� ������
					if ( ch_pointer > 0 )
					{
			    		if(cmpstring[ch_pointer-1]>0)							//�ѱ��� �ƴҰ��
			    			gotoxy(29+ch_pointer, 22), printf("\b \b");			// ȭ�鿡 ��ĭ �����
			    		if(cmpstring[ch_pointer-1]<0)							//�ѱ��ϰ��..
						{
							gotoxy(29+ch_pointer, 22), printf("\b \b\b");		//ȭ�鿡 2ĭ�� ����
							ch_pointer--;
						}
			    		ch_pointer--;
					}
				}
				else
				{
					printf("%c", ch);											//ȭ�鿡 �ѱ��ھ� ���
					cmpstring[ch_pointer]=ch;									//�迭�� �ѱ��ھ� ���� 
					ch_pointer++;
				}
			}
			if(checkcount>35)													//�ܾ� 36���� �������� �����ش�.
				break;	
		}
		if(userscore>comscore)										//����ڰ� �̰��� ��� ���� ����������.
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
		"������������������������������������������",
		"������������������������������������������",
		"������������������������������������������"};
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
		gotoxy(26, 10), printf("������ �Դϴ�!");
		textcolor(CC_FONT_WHITE, 0);
		gotoxy(26, 13), printf("�̸� : ");
		textcolor(CC_FONT_BLUE, 0);
		scanf("%s", name);
		textcolor(CC_FONT_WHITE, 0);
	}
	else
		return ;

	eng_rankupdate(name, stage, totalscore);
	eng_rankview();

}


//���� ��ŷ �ʱ�ȭ
void eng_rankformat(void)
{
	FILE* fp;
	int i;
	char* menu[3]={
		"����������������������������������������",
		"����������������������������������������",
		"����������������������������������������"};

	noCursor();

	fp=fopen("engranking.dat", "wt");
	if(fp==NULL)
		fputs("File Open Error!\n", stderr);

	for(i=0; i<30; i++)
	{
		fprintf(fp, "�͸�\n" );
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
	gotoxy(27, 11), printf("������ �ʱ�ȭ �Ǿ����ϴ�.");
	textcolor(CC_FONT_WHITE, CC_BACK_BLUE);
	gotoxy(37, 14), printf("Ȯ��");
	textcolor(CC_FONT_WHITE, 0);
	
	getch();
}

//���� ��ŷ ������Ʈ
void eng_rankupdate(char name[], int stage, int score)
{
	struct rank ranking[10];								//��ŷ Top 10;
	int i, j;											//������ ���� ����
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
		"��������������������������������������������������������������",
		"��������������������������������������������������������������",
		"��������������������������������������������������������������"};
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
	gotoxy(23, 1), printf("������������������������������������");
	gotoxy(23, 2), printf("������������������������������������");
	gotoxy(23, 3), printf("������������������������������������");
	textcolor(CC_FONT_WHITE, 0);

	textcolor(CC_FONT_YELLOW, 0);
	gotoxy(29, 2), printf("�� �� ĳ �� �� ��  ");
	textcolor(13, 0);
	printf("(����)");
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
	gotoxy(16,6),printf("������                                    ����\n");
	textcolor(CC_FONT_WHITE, 0);
	for(i=0; i<10; i++)
	{
		textcolor(47, 0);
		gotoxy(16, 8+i); 
		printf("%2d��\t", i+1); 
		printf("�̸� : %6s\t", ranking[i].name);
		printf("�������� : %2d\t", ranking[i].stage);
		printf("���� : %5d", ranking[i].score);
		textcolor(CC_FONT_WHITE, 0);
	}
	gotoxy(26,22);
	getch();
}

void jawon_GameOver(void)
{
	int i;

	char *table[]={
         "������������������������������������������","������������������������������������������","������������������������������������������"
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
		gotoxy(18+i*2,12),puts("��");
		Sleep(70);
	}
	textcolor(15,0);
	Sleep(100);
}