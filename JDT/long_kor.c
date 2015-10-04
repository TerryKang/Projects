//���(kor)
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

	typedef struct longstring {
		char string[150];
		int keynum;
		float percent; //��Ȯ��.
		float speed; //Ÿ��
	}longstring;

int continueconfirm(void);
void printresult(longstring strings[], int i);
void printresult2(void);
void printresult3(void);
void printresult4(void);
void printresult5(void);
void cls(void);

int long_kor(char *file,int line)
{
	
	longstring *strings=(longstring*)malloc(line*sizeof(longstring));

	int i, j, k,l; //������ ���� ����..
	char temp[150];
	char inputstring[150]={0}; //����ڰ� �Է��ϴ� ���ڿ�.
	int time1, time2;
	int chcount;
	char ch;
	int ch_pointer;
	int ko,en;
	int length;
	FILE* fp=fopen(file,"rb");

	for(i=0; i<line; i++)
	{
		fgets(temp,sizeof(temp),fp); //���� ���Ϸκ��� ���ڿ��� temp�� �޾Ƶ���..

		for(j=0; j<strlen(temp)-2; j++) // /r/n�� �����ֱ����� �۾�.
			strings[i].string[j]=temp[j];  //temp�� ���� string�� ����.
		strings[i].string[j]='\0'; //���ڿ��� ���� NULL�� ����.
		
		strings[i].keynum=strlen(strings[i].string); //Ű���̸� ����.
	}
	fclose(fp);
	for(i=0, chcount=0; i<line;)
	{
		cls();
		for(k=0, l=0; k<6; k++)
		{
			if(i==line)
				break;
			textcolor(CC_FONT_GREEN,0); //���ù��� �Ķ��۲÷� �ٲ�.
			gotoxy(3,3+l), fputs(strings[i].string, stdout);
			l=l+3;
			i++;
		}
		for(i-=6, k=0, l=0; k<6; k++)
		{
			if(i==line)
				break;
			textcolor(CC_FONT_WHITE, 0); //�۲� ������ ����Ʈ�� ����
			gotoxy(3,4+l);
			ch_pointer=0;
			while(1)
			{
				ch=getch();
				sndPlaySound("MsgType.wav", SND_ASYNC|SND_NODEFAULT);
				if ( ch == 13 && ch_pointer == strings[i].keynum ) break; //Enter ������ �����Է� ����
				else if ( ch == 27 ) {  //ESC ������ ����
					textcolor(CC_FONT_WHITE,0);
					return 0;
				}
				else if ( ch == 8 ){ // �齺���̽� ������
					if ( ch_pointer != 0 ){
						sndPlaySound("MsgBack.wav", SND_ASYNC|SND_NODEFAULT);
			    		if(inputstring[ch_pointer-1]>0)
			    			printf("\b \b"); // ȭ�鿡 �ѱ��� �����
			    		if(inputstring[ch_pointer-1]<0){
							printf("\b \b\b");
							ch_pointer--;
						}
			    		ch_pointer--;
					}
				}
				else if ( ch != 13){ // �齺���̽��� �ƴϰ� Enter�� �ƴϸ�
					if(ch_pointer==0) time1 = GetTickCount();
					if(strings[i].string[ch_pointer]!=ch){
						textcolor(CC_FONT_RED,0);
						sndPlaySound("MsgBeep.wav", SND_ASYNC|SND_NODEFAULT);
						printf("%c",ch);
						textcolor(CC_FONT_WHITE,0);
					}
					else{
						printf("%c",ch);
					}
					inputstring[ch_pointer++] = ch;
					if(ch_pointer==strings[i].keynum+1) break;    
				}
			}
			time2=GetTickCount()-time1; //������ �ð�.

			for(j=0, ko=0, en=0; j < strings[i].keynum; j++)
			{
				if(strings[i].string[j]<0)
					ko++;
				else if(strings[i].string[j]>=0)
					en++;
			}
			length=en+(ko/2);

			for(j=0, ko=0, en=0; j < strings[i].keynum; j++)
			{
				
				if(inputstring[j]==strings[i].string[j])
					if(strings[i].string[j]<0)
						ko++;
					else if(strings[i].string[j]>=0)
						en++;
			}
			chcount=en+(ko/2);

			memset(inputstring, (char)0, sizeof(inputstring));

			strings[i].percent=(float)chcount/length*100;  //��Ȯ���� ���Ѵ�.
			strings[i].speed=(float)strings[i].keynum/time2*70000*(strings[i].percent/100); //Ÿ���� ���
		//	printf("%4.0f",strings[i].speed);
			l+=3;
			i++;
		}
		if(continueconfirm()==0)
			continue;
		if(continueconfirm()==1)
		{
			printresult(strings, i);
			break;
		}

	}
	free(strings);
	
	return 0;
}

int continueconfirm(void)
{
	int i;
	char select=1, ch;
    int x=18,y=5;
	char ask[]="����Ͻðڽ��ϱ�?";
	char* yesorno[2]={"��","�ƴϿ�"};
	char *table[]={
     "������������������������������������������������","������������������������������������������������","������������������������������������������������",
     "������������������������������������������������","������������������������������������������������","������������������������������������������������",
     "������������������������������������������������","������������������������������������������������","������������������������������������������������"};

	for(i=0;i<9;i++)
	{
    	gotoxy(x,y+i);
    	printf("%s",table[i]);
    }
	gotoxy(22, 7), fputs(ask, stdout);

	while(1)
	{
		if(select==0)
		{
			textcolor(CC_FONT_WHITE,CC_BACK_DBLUE);
			gotoxy(50, 11), fputs(yesorno[0], stdout);
			textcolor(CC_FONT_WHITE,0);
			gotoxy(55, 11), fputs(yesorno[1], stdout);
		}
		if(select==1)
		{
			textcolor(CC_FONT_WHITE,CC_BACK_DBLUE);
			gotoxy(55, 11), fputs(yesorno[1], stdout);
			textcolor(CC_FONT_WHITE,0);
			gotoxy(50, 11), fputs(yesorno[0], stdout);
		}
		while(1)
		{
			ch=getch();
			if(ch==-32 || ch==ENTER )
			{
				if(ch!=ENTER)
					ch=getch();
				switch(ch)
				{
	    			case LEFT:
	    				if(select>0)
	    					select--;
						break;
					case RIGHT:
	        			if(select<1)
	        				select++;
						break;
					case ENTER:
	        			if(select==0)
	        				return 0;
	        			if(select==1)
							return 1;
				}
				break;
			}
			else
				continue;
		}
	}	

	return 0;
}

void printresult(longstring strings[], int i)
{
	int j;//�ݺ����� ���� ����.
	int x=18,y=5;
	float temp=0; 	int speed=0;	//Ÿ�� 
	float check;	//��Ȯ�� 
	char *table[]={
    "��������������������������������������������������",
	"��������������������������������������������������",
	"��������������������������������������������������",
    "��������������������������������������������������",
	"��������������������������������������������������",
	"��������������������������������������������������",
    "��������������������������������������������������",
	"��������������������������������������������������",
	"��������������������������������������������������"};


	for(j=0; j<i; j++)
		temp+=strings[j].speed;
	speed=(int)temp/i;

	for(j=0, temp=0; j<i; j++)
		temp+=strings[j].percent;
	check=temp/i;


	for(i=0;i<9;i++)
	{
    	gotoxy(x,y+i);
    	printf("%s",table[i]);
    }
	gotoxy(22, 7), printf("���Ÿ�� : %d\n", speed);
	gotoxy(22, 10), printf("��� ��Ȯ�� : %0.1f \n", check);
		if(check==100 && speed>=500)
			printresult2();
		if(check>95 && check<100 || speed>400 && speed<500)
			printresult3();
		if(check>90 && check<95 || speed>300 && speed<400)
			printresult4();
		if(check<90 && speed<300)
			printresult5();
	gotoxy(22, 23), printf("Press Any Key to Continue...");
	getch();
}

void printresult2(void)
{
	int i;//�ݺ����� ���� ����.
	int x=50,y=7;
	char *table[]={
    "   ��",
	" ��  ��",
    " ����",
	"��    ��",
	"��    ��"};

	for(i=0;i<5;i++)
	{
    	gotoxy(x,y+i);
		textcolor(14,0);
    	printf("%s",table[i]);
		textcolor(CC_FONT_WHITE, 0);
    }
	gotoxy(50,12), printf("So cool!\n");
}

void printresult3(void)
{
	int i;//�ݺ����� ���� ����.
	int x=50,y=7;
	char *table[]={
    "����",
	"��   ��",
    "����",
	"��   ��",
	"����"};

	for(i=0;i<5;i++)
	{
    	gotoxy(x,y+i);
		textcolor(9,0);
    	printf("%s",table[i]);
		textcolor(CC_FONT_WHITE, 0);
    }
	gotoxy(50,12), printf("Good!\n");
}

void printresult4(void)
{
	int i;//�ݺ����� ���� ����.
	int x=50,y=7;
	char *table[]={
    " ����",
	"��    ��",
    "��",
	"��    ��",
	" ����"};

	for(i=0;i<5;i++)
	{
    	gotoxy(x,y+i);
		textcolor(12,0);
    	printf("%s",table[i]);
		textcolor(CC_FONT_WHITE, 0);
    }
	gotoxy(50,12), printf("���� ����..\n");
}

void printresult5(void)
{
	int i;//�ݺ����� ���� ����.
	int x=50,y=7;
	char *table[]={
    "����",
	"��    ��",
    "��    ��",
	"��    ��",
	"����"};

	for(i=0;i<5;i++)
	{
    	gotoxy(x,y+i);
		textcolor(13,0);
    	printf("%s",table[i]);
		textcolor(CC_FONT_WHITE, 0);
    }
	gotoxy(50,12), printf("������ �ϳ�..\n");
}