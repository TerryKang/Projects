//ª����(kor)
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
    int time1, time2;//�ð������� ���� ����.
	int count=0;
    char cmpstring[100]; //����ڰ� �Է��� ���ڿ�...  strings[line]�� ��..
  // ���ڿ� �����ͺ��̽�..
	char temp[100];					// �ӽ÷� ���ڿ��� ������ �迭.
    char ch;
    int i, j, ch_pointer;
	float maxspeed=0, curspeed;		//maxspeed�� �ְ� Ÿ��...  curspeed... ���� Ÿ�� 
	float check;	//��Ȯ��
	int chcount=0;		//��Ȯ�� �����ϱ� ���� ����.
	int k,e,length;
	FILE* fp;

    
    cls();
    srand((int)time(NULL)); //�õ尪 �Է�
	fp=fopen(file, "rb"); 
	if(fp==NULL)
		printf("file open error!\n");
	
	for(i=0; i<line; i++)
	{
		fgets(temp, sizeof(temp), fp); //���� ���Ϸκ��� ���ڿ��� temp�� �޾Ƶ���..
		
		for(j=0; j < strlen(temp)-2; j++) // /r/n�� �����ֱ����� �۾�.
			strings[i].string[j]=temp[j];  //temp�� ���� longstring�� ����.
		strings[i].string[j]='\0'; //���ڿ��� ���� NULL�� ����.
		
		strings[i].keynum=strlen(strings[i].string); //Ű���̸� ����.
	}

	fclose(fp);

//38���ޡߢ�
		/*textcolor(CC_FONT_BLUE,CC_BACK);
		gotoxy(2,1), printf("�ʢʢ� �ʢ�   �ʢʢ�");
		gotoxy(2,2), printf("  ��   ��  ��   ��  ");
		gotoxy(2,3), printf("  ��   ��  ��   ��  ");
		gotoxy(2,4), printf("�ʢ�   �ʢ�     ��  ");
		textcolor(CC_FONT_WHITE,0);*/
		gotoxy(2,1), printf("��������������������������������������ᡡ��������");
		gotoxy(2,2), printf("��������������������������������������ᡡ������");
		gotoxy(2,3), printf("��������������������������������������ᡡ����");
		gotoxy(2,4), printf("��������������������������������������ᡡ��");
		gotoxy(2,5), printf("��������������������������������������ᡡ");
		gotoxy(2,6), printf("��ᡡ�������������������������������������������������������������������");
		gotoxy(2,7), printf("�ᡡ�����������ᡡ���������������������������������ᡡ����������������");
		gotoxy(2,8), printf("�ᡡ�������ᡡ�����ᡡ���������������������������ᡡ�����ᡡ���������������");
		gotoxy(2,9), printf("�ᡡ������������������������������������������������������������������������");
		gotoxy(2,10), printf("�ᡡ������������������������������������������������������������������������");
		gotoxy(2,11), printf("�ᡡ������������������������������������������������������������������������");
		gotoxy(2,12), printf("�ᡡ������������������������������������������������������������������������");
		gotoxy(2,13), printf("�ᡡ������������������������������������������������������������������������");
		gotoxy(2,14), printf("�ᡡ������������������������������������������������������������������������");
		gotoxy(2,15), printf("�ᡡ������������������������������������������������������������������������");
		gotoxy(2,16), printf("�ᡡ������������������������������������������������������������������������");
		gotoxy(2,17), printf("�ᡡ������������������������������������������������������������������������");
		gotoxy(2,18), printf("�ᡡ������������������������������������������������������������������������");
		gotoxy(2,19), printf("�ᡡ������������������������������������������������������������������������");
		gotoxy(2,20), printf("�ᡡ������������������������������������������������������������������������");
		gotoxy(2,21), printf("�ᡡ������������������������������������������������������������������������");
		gotoxy(2,22), printf("���ᡡ�������������������������������������� �� ��������������������������");
		gotoxy(2,23), printf("�������ᡡ��������������������������������  �����������������������ᡡ��");
		gotoxy(2,24), printf("��������������������������������������ᡡ������");
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

		time1=GetTickCount(); //���۽ð� �Է�

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
			}//Enter ������ �����Է� ����
			else if ( ch == 27 ) {  //ESC ������ ����
				textcolor(CC_FONT_WHITE,0);
				return 0;
			}
			else if ( ch == 8 ){ // �齺���̽� ������
			    if ( ch_pointer != 0 ){
			    	if(cmpstring[ch_pointer-1]>0)
			    		printf("\b \b"); // ȭ�鿡 �ѱ��� �����
			    	if(cmpstring[ch_pointer-1]<0){
				        printf("\b \b\b");
				        ch_pointer--;
				    }
			    	ch_pointer--;
			    }
			}
			else if ( ch != 13){ // �齺���̽��� �ƴϰ� Enter�� �ƴϸ�
				if ( ch_pointer == 0 ) time1 = GetTickCount(); //ó���̸� �ð� ����
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
		


		time2=GetTickCount(); //��ħ �ð� ����.
		
		if(atoi(cmpstring)==999)
		{
			printf("���� ����\n");
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

		check=(float)chcount/length*100;					//��Ȯ�� �Է�.	
		curspeed=(float)strings[i].keynum/(time2-time1)*70000*check/100;				//Ÿ�� ����.

		if(curspeed>maxspeed)
			maxspeed=curspeed;

		gotoxy(22, 14), printf("���� Ÿ�� :         ");
		gotoxy(22, 14), printf("���� Ÿ�� : %0.0f", curspeed);

//���� Ÿ�� ������
		gotoxy(22, 15), printf("                                                 ");
		gotoxy(22, 15);
		for(j=0; j<((int)curspeed/50); j++)
			printf("��");
		gotoxy(22+2*j, 15);
		for(j=0; j<20-((int)curspeed/50); j++)
			printf("��");
	
		gotoxy(25, 18), printf("�ְ� Ÿ�� :       ");
		gotoxy(25, 18), printf("�ְ� Ÿ�� : %0.0f", maxspeed);
//�ְ�Ÿ�� ������
	/*		gotoxy(25, 17), printf("                                             ");
		gotoxy(25, 17);
		for(j=0; j<((int)maxspeed/50); j++)
			printf("��");
		gotoxy(25+2*j, 17);
		for(j=0; j<20-((int)maxspeed/50); j++)
			printf("��");*/

		gotoxy(25, 20), printf("��Ȯ�� :         ");
		gotoxy(25, 20), printf("��Ȯ�� : %0.1f", check);
		
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


//��Ȯ�� ������
	/*	gotoxy(25, 20), printf("                                                ");
		gotoxy(25, 20);
		for(j=0; j<((int)check/5); j++)
			printf("��");
		gotoxy(25+2*j, 20);
		for(j=0; j<20-((int)check/5); j++)
			printf("��");*/
	}
	free(strings);
}


void tedu(void)
{
	int i;
	int x=12,y=7;
	char *table1[]={
		"�����ᡡ�������������������������������ᡡ������",
		"��������������������������������������������������������"};		

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
		"����������",
		"�ᡡ�ᡡ�ᡡ�ᡡ��",
		"�ᡡ�ᡡ�ᡡ�ᡡ����",
		"�ᡡ�������������ᡡ��",
		"�ᡡ�������������ᡡ��",
		"���ᡡ����������",
		"�����ᡡ������",
		"�����ᡡ������"};		

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
		"�����ᡡ�������������������������������ᡡ������",
		"���ᡡ�ᡡ�������������������������������ᡡ�ᡡ��������",
		"���ᡡ�ᡡ�������������������������������ᡡ��"};

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
		"�����ᡡ���������������������������������ᡡ��������",
		"�ᡡ�����ᡡ���������������������������ᡡ�����ᡡ������",
		"��������������������������������������������������������"};

	for(i=0;i<3;i++)
	{
		gotoxy(x,y+i);
		printf("%s",table1[i]);
	}
}