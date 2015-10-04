#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "conio.h"
#include "cmd.h"
#include <mmsystem.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27
#define ENTER 13
#define KORNUM 2780			//�ѱ� �ܾ� ����

typedef struct korwords {	//���Ͽ� �ִ� �ܾ ������ String�� ����ü
	char korword[20];
}korwords;

typedef struct viewwords {	//ȭ�鿡 ������ �ܾ�
	char words[20];
	int x;					//x��ǥ
	int y;					//y��ǥ
}viewwords;

struct rank{				//��ŷ ����ü(�̸�, ��������, ����)
	char name[15];
	int stage;
	int score;
};

void noCursor(void);
void gotoxy(int x, int y);
void textcolor(unsigned int text, unsigned int back);
void noCursor(void);
void ready(int level);
void korsanrank(int totalscore, int stage);			//�ѱ� �꼺�� ��ŷ
void engsanrank(int totalscore, int stage);			//���� �꼺�� ��ŷ
void korsanrankupdate(char name[], int stage, int score);	//�ѱ� �꼺�� ��ŷ ������Ʈ 
void engsanrankupdate(char name[], int stage, int score);	//���� �꼺�� ��ŷ ������Ʈ 
void korsanrankview(void);							//�ѱ� �꼺�� ��ŷ ���� 
void engsanrankview(void);							//���� �꼺�� ��ŷ ���� 
void korsanrankformat(void);						//�ѱ� �꼺�� ��ŷ �ʱ�ȭ	
void engsanrankformat(void);						//���� �꼺�� ��ŷ �ʱ�ȭ	
void jawon_GameOver(void);
void cls(void);
	

int sansongbi(int stage)
{
	korwords kor[KORNUM];
	viewwords view[40];		//ȭ�鿡 �ѷ��� 40���� �ܾ�
	FILE* fp;
	int index[40];			//���� �ε��� �� 40��
	int temp;
	int check;				//�ߺ�üũ�� ���� ����.
	int i, j;				//���� ����
	int time1, time2;		//�ð� ����.
	int score=0;
	int count=0;
	char cmpstring[20];			
	int ch_pointer;
	char ch;
	int templife=20, countlife=20;				//HP
	char* menu[3]={
		"������������������������������������������������������������������",
		"������������������������������������������������������������������",
		"������������������������������������������������������������������"};

	noCursor();

	fp=fopen("wordkor.dat", "rb");
	if(fp==NULL)
		printf("File Open Error!\n");

	for(i=0; i<KORNUM; i++)
		fscanf(fp, "%s", kor[i].korword);

	srand((int)time(NULL));

	while(1)
	{
		ready(stage);
		count=0;
		templife=20;
		cls();
		textcolor(10, 0);								//�׵θ�..
		gotoxy(0,0), printf("%s", menu[0]);
		for(i=1; i<21; i++)
			gotoxy(0, i), printf("%s", menu[1]);
		gotoxy(0, i), printf("%s", menu[2]);
		
		textcolor(11, 0);
		gotoxy(15, 22), printf("��������������������������");
		gotoxy(15, 23), printf("��������������������������");
		gotoxy(15, 24), printf("��������������������������");  
		textcolor(15, 0);

		textcolor(11, 0);
		gotoxy(66, 0), printf("��������������");
		gotoxy(66, 1), printf("��������������");	//�꼺��
		gotoxy(66, 2), printf("��������������");
		gotoxy(66, 3), printf("��������������");	//�ѱ�
		gotoxy(66, 4), printf("��������������");
		gotoxy(66, 5), printf("��������������");	//Stage
		gotoxy(66, 6), printf("��������������");
		gotoxy(66, 7), printf("��������������");	//����
		gotoxy(66, 8), printf("��������������");	//
		for(i=1; i<=10; i++)
			gotoxy(66, 8+i), printf("��������������");
		gotoxy(66, 8+i), printf("��������������");
		gotoxy(66, 9+i), printf("��������������");
		gotoxy(66, 10+i), printf("��������������");
		textcolor(11, 0);

		//HP���� ��
		textcolor(12, 0);
		for(i=1; i<=10; i++)
			gotoxy(70, 8+i), printf("��");

		for(i=1 ; i<=10; i++)
			gotoxy(74, 8+i), printf("��");
		textcolor(15, 0);

		textcolor(12, 0);
		if(countlife>=10)
		{
			for(i=1; i<=(20-countlife); i++)
			{
				gotoxy(70, 8+i), printf("��");
				gotoxy(19+ch_pointer, 23);
			}
		}
		else
		{	
			for(i=1; i<=10; i++)
				gotoxy(70, 8+i), printf("  ");

			for(i=1 ; i<=(10-countlife); i++)
			{
				gotoxy(74, 8+i), printf("��");
				gotoxy(19+ch_pointer, 23);
			}
		}
		textcolor(15, 0);

		textcolor(14, 0);
		gotoxy(69, 1), printf("�� �� ��");
		textcolor(15, 0);

		textcolor(9, 0);
		gotoxy(70, 3), printf("��  ��");
		textcolor(15, 0);

		textcolor(13, 0);
		gotoxy(69, 5), printf("Stage %2d", stage);	
		textcolor(15, 0);

		textcolor(10, 0);
		gotoxy(69, 7), printf("%5d ��", 0);
		textcolor(15, 0);

		textcolor(10, 0);
		gotoxy(69, 7), printf("%5d", score*50);
		textcolor(15, 0);

		textcolor(12, 0);
		gotoxy(70, 20), printf("H    P");
		textcolor(15, 0);

		textcolor(8, 0);
		gotoxy(60, 23), printf("Press ESC to quit");
		textcolor(15, 0);

		for(i=0; i<40; i++, check=0)			//�ߺ� ����.
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
		
		for(i=0; i<40; i++)
		{
			for(j=0; j<=strlen(kor[index[i]].korword); j++)
				view[i].words[j]=kor[index[i]].korword[j];
			view[i].x=(rand()%4)*15+5;
			view[i].y = -2*i;
		}
		
		time1=GetTickCount();
		ch_pointer=0;

		gotoxy(19+ch_pointer, 23);
		cmpstring[ch_pointer]='\0';
		for(j=0; j<40; j++)
		{
			if(strcmp(cmpstring,view[j].words)==0)
			{
	//			sndPlaySound("MsgBell.wav", SND_ASYNC|SND_NODEFAULT);
				strcpy(view[j].words, "             ");

			}
			gotoxy(19+ch_pointer, 23);
		}
		gotoxy(19,23), printf("               ");
		gotoxy(19,23);
		ch_pointer=0;



		while(1)
		{
			ch='\0';
			if(kbhit())
			{
				ch=getch();
				if(ch==-32)
					ch=getch();

				if(ch_pointer==0)
					gotoxy(19, 23);
			}

			time2=GetTickCount();
			if( (time2-time1)>(900-(stage*50)) )
			{
				for(i=0; i<40; i++)
				{
					gotoxy(19+ch_pointer, 23);
					if(view[i].y>0 && view[i].y<=19)
					{
						if(view[i].y>1)
						{
							gotoxy(view[i].x, view[i].y-1), printf("             ");
							gotoxy(19+ch_pointer, 23);
							gotoxy(view[i].x, view[i].y-1), printf("             ");
							gotoxy(19+ch_pointer, 23);
							if(view[i].y!=19)
								gotoxy(view[i].x, view[i].y+1), printf("             ");
							gotoxy(19+ch_pointer, 23);
						}
						if(view[i].y!=19)
						{
							gotoxy(view[j].x, view[j].y), printf("             ");
							gotoxy(19+ch_pointer, 23);
							gotoxy(view[i].x, view[i].y), printf("%s", view[i].words);
							gotoxy(19+ch_pointer, 23);
						}
					}
					view[i].y++;
				}
				time1=GetTickCount();

				for(i=0; i<40; i++)
				{
					if(view[i].words[0]!=' ' && view[i].y==20)
					{
						strcpy(view[i].words, "             ");
						templife--;
						countlife--;
					}
				}
	//			gotoxy(60, 23), printf("%2d", life);
				gotoxy(19+ch_pointer, 23);

				textcolor(12, 0);

				if(countlife>=10)
				{
					for(i=1; i<=(20-countlife); i++)
					{
						gotoxy(70, 8+i), printf("��");
						gotoxy(19+ch_pointer, 23);
					}
				}

				else
				{	
					for(i=1 ; i<=(10-countlife); i++)
					{
						gotoxy(74, 8+i), printf("��");
						gotoxy(19+ch_pointer, 23);
					}
				}

				textcolor(15, 0);
			}

			if(ch!='\0')
			{
				if(ch_pointer==15 || ch==13) 
				{//���͸� �Է� ����.
					gotoxy(19+ch_pointer, 23);
					cmpstring[ch_pointer]='\0';
					for(j=0; j<40; j++)
					{
						if(strcmp(cmpstring,view[j].words)==0)
						{
							sndPlaySound("MsgBell.wav", SND_ASYNC|SND_NODEFAULT);
							strcpy(view[j].words, "             ");
							gotoxy(view[j].x, view[j].y), printf("             ");
							gotoxy(19+ch_pointer, 23);
							gotoxy(view[j].x, view[j].y), printf("             ");
							gotoxy(19+ch_pointer, 23);
							count++;
							score++;
							textcolor(10, 0);
							gotoxy(69, 7), printf("%5d", score*50);
							textcolor(15, 0);
							gotoxy(19+ch_pointer, 23);
							
						}
						gotoxy(19+ch_pointer, 23);
					}
					gotoxy(19,23), printf("               ");
					gotoxy(19,23);
					ch_pointer=0;
				}

				else if ( ch == 8 )
				{ // �齺���̽� ������
					if ( ch_pointer > 0 )
					{
			    		if(cmpstring[ch_pointer-1]>0)							//�ѱ��� �ƴҰ��
			    			gotoxy(19+ch_pointer, 23), printf("\b \b");			// ȭ�鿡 ��ĭ �����
			    		if(cmpstring[ch_pointer-1]<0)							//�ѱ��ϰ��..
						{
							gotoxy(19+ch_pointer, 23), printf("\b \b\b");		//ȭ�鿡 2ĭ�� ����
							ch_pointer--;
						}
			    		ch_pointer--;
					}
				}
				else if ( ch == 27 ) 
				{
					korsanrank(score*50, stage);
					cls();
					return 0;
				}
				else
				{
					printf("%c", ch);											//ȭ�鿡 �ѱ��ھ� ���
					cmpstring[ch_pointer]=ch;									//�迭�� �ѱ��ھ� ���� 
					ch_pointer++;
				}
			}		
			if(countlife==0)						//HP�� 0�̸� ���� ����
			{
				korsanrank(score*50, stage);
				jawon_GameOver();
				return 0;
			}
			if(count+(20-templife)==40)
				break;
		}
		stage++;
		continue;
	}
	
	return 0;
}

//��ŷ
void korsanrank(int totalscore, int stage)
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

	fp=fopen("korsanranking.DAT", "rb");
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
		gotoxy(26, 10), printf("����� �Դϴ�!");
		textcolor(CC_FONT_WHITE, 0);
		gotoxy(26, 13), printf("�̸� : ");
		textcolor(CC_FONT_BLUE, 0);
		scanf("%s", name);
		textcolor(CC_FONT_WHITE, 0);
	}
	else
		return ;

	korsanrankupdate(name, stage, totalscore);
	korsanrankview();

}

//�ѱ� �꼺�� ��ŷ ������Ʈ
void korsanrankupdate(char name[], int stage, int score)
{
	struct rank ranking[10];								//��ŷ Top 10;
	int i, j;											//������ ���� ����
	FILE* fp;	
	
	noCursor();

	fp=fopen("korsanranking.dat", "rb");
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

	fp=fopen("korsanranking.dat", "wt");
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

//�ѱ� �꼺�� ��ŷ���� 
void korsanrankview(void)
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

	fp=fopen("korsanranking.dat", "rb");
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
	gotoxy(30, 2), printf("�� �� �� �� ��  ");
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
//�ѱ� �꼺�� ��ŷ ���� 
void korsanrankformat(void)
{
	FILE* fp;
	int i;
	char* menu[3]={
		"����������������������������������������",
		"����������������������������������������",
		"����������������������������������������"};

	noCursor();

	fp=fopen("korsanranking.dat", "wt");
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

//���� �꼺�� 
int engsansongbi(int stage)
{
	korwords kor[1000];
	viewwords view[40];		//ȭ�鿡 �ѷ��� 40���� �ܾ�
	FILE* fp;
	int index[40];			//���� �ε��� �� 40��
	int temp;
	int check;				//�ߺ�üũ�� ���� ����.
	int i, j;				//���� ����
	int time1, time2;		//�ð� ����.
	int score=0;
	int count=0;
	char cmpstring[20];			
	int ch_pointer;
	char ch;
	int templife=20, countlife=20;				//HP
	char* menu[3]={
		"������������������������������������������������������������������",
		"������������������������������������������������������������������",
		"������������������������������������������������������������������"};

	noCursor();

	fp=fopen("wordeng.dat", "rb");
	if(fp==NULL)
		printf("File Open Error!\n");

	for(i=0; i<1000; i++)
		fscanf(fp, "%s", kor[i].korword);

	srand((int)time(NULL));

	while(1)
	{
		ready(stage);
		count=0;
		templife=20;
		cls();
		textcolor(10, 0);								//�׵θ�..
		gotoxy(0,0), printf("%s", menu[0]);
		for(i=1; i<21; i++)
			gotoxy(0, i), printf("%s", menu[1]);
		gotoxy(0, i), printf("%s", menu[2]);
		
		textcolor(11, 0);
		gotoxy(15, 22), printf("����������������������������");
		gotoxy(15, 23), printf("����������������������������");
		gotoxy(15, 24), printf("����������������������������");  
		textcolor(15, 0);

		textcolor(11, 0);
		gotoxy(66, 0), printf("��������������");
		gotoxy(66, 1), printf("��������������");	//�꼺��
		gotoxy(66, 2), printf("��������������");
		gotoxy(66, 3), printf("��������������");	//�ѱ�
		gotoxy(66, 4), printf("��������������");
		gotoxy(66, 5), printf("��������������");	//Stage
		gotoxy(66, 6), printf("��������������");
		gotoxy(66, 7), printf("��������������");	//����
		gotoxy(66, 8), printf("��������������");	//
		for(i=1; i<=10; i++)
			gotoxy(66, 8+i), printf("��������������");
		gotoxy(66, 8+i), printf("��������������");
		gotoxy(66, 9+i), printf("��������������");
		gotoxy(66, 10+i), printf("��������������");
		textcolor(11, 0);

		//HP���� ��
		textcolor(12, 0);
		for(i=1; i<=10; i++)
			gotoxy(70, 8+i), printf("��");

		for(i=1 ; i<=10; i++)
			gotoxy(74, 8+i), printf("��");
		textcolor(15, 0);

		textcolor(12, 0);
		if(countlife>=10)
		{
			for(i=1; i<=(20-countlife); i++)
			{
				gotoxy(70, 8+i), printf("��");
				gotoxy(19+ch_pointer, 23);
			}
		}
		else
		{	
			for(i=1; i<=10; i++)
				gotoxy(70, 8+i), printf("  ");

			for(i=1 ; i<=(10-countlife); i++)
			{
				gotoxy(74, 8+i), printf("��");
				gotoxy(19+ch_pointer, 23);
			}
		}
		textcolor(15, 0);

		textcolor(14, 0);
		gotoxy(69, 1), printf("�� �� ��");
		textcolor(15, 0);

		textcolor(9, 0);
		gotoxy(70, 3), printf("��    ��");
		textcolor(15, 0);

		textcolor(13, 0);
		gotoxy(69, 5), printf("Stage %2d", stage);	
		textcolor(15, 0);

		textcolor(10, 0);
		gotoxy(69, 7), printf("%5d ��", 0);
		textcolor(15, 0);

		textcolor(10, 0);
		gotoxy(69, 7), printf("%5d", score*50);
		textcolor(15, 0);

		textcolor(12, 0);
		gotoxy(70, 20), printf("H    P");
		textcolor(15, 0);

		textcolor(8, 0);
		gotoxy(60, 23), printf("Press ESC to quit");
		textcolor(15, 0);

		for(i=0; i<40; i++, check=0)			//�ߺ� ����.
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
		
		for(i=0; i<40; i++)
		{
			for(j=0; j<=strlen(kor[index[i]].korword); j++)
				view[i].words[j]=kor[index[i]].korword[j];
			view[i].x=(rand()%4)*15+5;
			view[i].y = -2*i;
		}
		
		time1=GetTickCount();
		ch_pointer=0;

		gotoxy(19+ch_pointer, 23);
		cmpstring[ch_pointer]='\0';
		for(j=0; j<40; j++)
		{
			if(strcmp(cmpstring,view[j].words)==0)
			{
	//			sndPlaySound("MsgBell.wav", SND_ASYNC|SND_NODEFAULT);
				strcpy(view[j].words, "             ");

			}
			gotoxy(19+ch_pointer, 23);
		}
		gotoxy(19,23), printf("               ");
		gotoxy(19,23);
		ch_pointer=0;



		while(1)
		{
			ch='\0';
			if(kbhit())
			{
				ch=getch();
				if(ch==-32)
					ch=getch();

				if(ch_pointer==0)
					gotoxy(19, 23);
			}

			time2=GetTickCount();
			if( (time2-time1)>(900-(stage*50)) )
			{
				for(i=0; i<40; i++)
				{
					gotoxy(19+ch_pointer, 23);
					if(view[i].y>0 && view[i].y<=19)
					{
						if(view[i].y>1)
						{
							gotoxy(view[i].x, view[i].y-1), printf("             ");
							gotoxy(19+ch_pointer, 23);
							gotoxy(view[i].x, view[i].y-1), printf("             ");
							gotoxy(19+ch_pointer, 23);
							if(view[i].y!=19)
								gotoxy(view[i].x, view[i].y+1), printf("             ");
							gotoxy(19+ch_pointer, 23);
						}
						if(view[i].y!=19)
						{
							gotoxy(view[j].x, view[j].y), printf("             ");
							gotoxy(19+ch_pointer, 23);
							gotoxy(view[i].x, view[i].y), printf("%s", view[i].words);
							gotoxy(19+ch_pointer, 23);
						}
					}
					view[i].y++;
				}
				time1=GetTickCount();

				for(i=0; i<40; i++)
				{
					if(view[i].words[0]!=' ' && view[i].y==20)
					{
						strcpy(view[i].words, "             ");
						templife--;
						countlife--;
					}
				}
	//			gotoxy(60, 23), printf("%2d", life);
				gotoxy(19+ch_pointer, 23);

				textcolor(12, 0);

				if(countlife>=10)
				{
					for(i=1; i<=(20-countlife); i++)
					{
						gotoxy(70, 8+i), printf("��");
						gotoxy(19+ch_pointer, 23);
					}
				}

				else
				{	
					for(i=1 ; i<=(10-countlife); i++)
					{
						gotoxy(74, 8+i), printf("��");
						gotoxy(19+ch_pointer, 23);
					}
				}

				textcolor(15, 0);
			}

			if(ch!='\0')
			{
				if(ch_pointer==15 || ch==13) 
				{//���͸� �Է� ����.
					gotoxy(19+ch_pointer, 23);
					cmpstring[ch_pointer]='\0';
					for(j=0; j<40; j++)
					{
						if(strcmp(cmpstring,view[j].words)==0)
						{
							sndPlaySound("MsgBell.wav", SND_ASYNC|SND_NODEFAULT);
							strcpy(view[j].words, "             ");
							gotoxy(view[j].x, view[j].y), printf("             ");
							gotoxy(19+ch_pointer, 23);
							gotoxy(view[j].x, view[j].y), printf("             ");
							gotoxy(19+ch_pointer, 23);
							count++;
							score++;
							textcolor(10, 0);
							gotoxy(69, 7), printf("%5d", score*50);
							textcolor(15, 0);
							gotoxy(19+ch_pointer, 23);
							
						}
						gotoxy(19+ch_pointer, 23);
					}
					gotoxy(19,23), printf("               ");
					gotoxy(19,23);
					ch_pointer=0;
				}

				else if ( ch == 8 )
				{ // �齺���̽� ������
					if ( ch_pointer > 0 )
					{
			    		if(cmpstring[ch_pointer-1]>0)							//�ѱ��� �ƴҰ��
			    			gotoxy(19+ch_pointer, 23), printf("\b \b");			// ȭ�鿡 ��ĭ �����
			    		if(cmpstring[ch_pointer-1]<0)							//�ѱ��ϰ��..
						{
							gotoxy(19+ch_pointer, 23), printf("\b \b\b");		//ȭ�鿡 2ĭ�� ����
							ch_pointer--;
						}
			    		ch_pointer--;
					}
				}
				else if ( ch == 27 ) 
				{
					engsanrank(score*50, stage);
					cls();
					return 0;
				}
				else
				{
					printf("%c", ch);											//ȭ�鿡 �ѱ��ھ� ���
					cmpstring[ch_pointer]=ch;									//�迭�� �ѱ��ھ� ���� 
					ch_pointer++;
				}
			}		
			if(countlife==0)						//HP�� 0�̸� ���� ����
			{
				engsanrank(score*50, stage);
				jawon_GameOver();
				return 0;
			}
			if(count+(20-templife)==40)
				break;
		}
		stage++;
		continue;
	}
	
	return 0;
}

//���� �꼺�� ��ŷ
void engsanrank(int totalscore, int stage)
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

	fp=fopen("engsanranking.DAT", "rb");
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
		gotoxy(26, 10), printf("����� �Դϴ�!");
		textcolor(CC_FONT_WHITE, 0);
		gotoxy(26, 13), printf("�̸� : ");
		textcolor(CC_FONT_BLUE, 0);
		scanf("%s", name);
		textcolor(CC_FONT_WHITE, 0);
	}
	else
		return ;

	engsanrankupdate(name, stage, totalscore);
	engsanrankview();

}

//���� �꼺�� ��ŷ ������Ʈ
void engsanrankupdate(char name[], int stage, int score)
{
	struct rank ranking[10];								//��ŷ Top 10;
	int i, j;											//������ ���� ����
	FILE* fp;	
	
	noCursor();

	fp=fopen("engsanranking.dat", "rb");
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

	fp=fopen("engsanranking.dat", "wt");
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

//���� �꼺�� ��ŷ���� 
void engsanrankview(void)
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

	fp=fopen("engsanranking.dat", "rb");
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
	gotoxy(30, 2), printf("�� �� �� �� ��  ");
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
//���� �꼺�� ��ŷ ���� 
void engsanrankformat(void)
{
	FILE* fp;
	int i;
	char* menu[3]={
		"����������������������������������������",
		"����������������������������������������",
		"����������������������������������������"};

	noCursor();

	fp=fopen("engsanranking.dat", "wt");
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