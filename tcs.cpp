// tcs.cpp : Defines the entry point for the console application.
//

// snack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

//��Ϸ�����б�
//1.̰�������������ƶ�
//2.��ʳ�ﳤ��
//3.ײǽ��Ե��Լ�������
//4.��Ϸ��������ӡ�÷�


#define MAP_WIDTH 60
#define MAP_HEIGHT 20

void _DrawChar(int x, int y,char ch);

typedef struct Position
{
	int x;
	int y;
}Position;


//����̰���߽ṹ��
typedef struct Snack
{
	//̰���߳���
	int size;
	Position pos[MAP_WIDTH * MAP_HEIGHT];
}Snack;

Snack g_snack;

//ʳ��
Position g_food;

void InitFood()
{
	srand((unsigned)time(NULL));

	g_food.x = rand() % MAP_WIDTH;
	g_food.y = rand() % MAP_HEIGHT;

	_DrawChar(g_food.x, g_food.y,'#');
}


//��ʼʱ̰���ߴ�С

void InitSnack()
{
 g_snack.size = 3;

 g_snack.pos[0].x = MAP_WIDTH / 2;
 g_snack.pos[0].y = MAP_HEIGHT / 2;

 g_snack.pos[1].x = MAP_WIDTH / 2 - 1;
 g_snack.pos[1].y = MAP_HEIGHT / 2;

 g_snack.pos[2].x = MAP_WIDTH / 2 - 2;
 g_snack.pos[2].y = MAP_HEIGHT / 2;
}

//����̰����
void DrawSnack()
{
	for(int i = 0;i < g_snack.size;i++)
	{
		if(i == 0)
		{
			_DrawChar(g_snack.pos[i].x, g_snack.pos[i].y,'*');
		}
		else
		{
			_DrawChar(g_snack.pos[i].x, g_snack.pos[i].y,'#');
		}
	}
}


//��X,Y�����ַ�ch
//_DrawChar(30.10.'0');

void _DrawChar(int x, int y,char ch)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;


	//���ù��λ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);

	putchar(ch);
}



void InitMap()
{
	//һ��һ��
	for(int i = 0;i<=MAP_HEIGHT;i++)
	{
			for(int j = 0;j<=MAP_WIDTH;j++)
			{
				if(j==MAP_WIDTH)
				{
					printf("|\n");
			}
			else if(i==MAP_HEIGHT)
			{
				printf("-");
			}
			else
			{
				printf(" ");
			}
	}
}
}

void Init()
{
	//���Ƶ�ͼ
	InitMap();

	//��ʼ��̰����

	InitSnack();

	InitFood();
}
 
void UpsdateScreen()
{
	DrawSnack();
}




void SnackMove(int key)
{
	int delta_x=0;
	int delta_y=0;


if(key=='w'||key=='W')//w ��
{
	delta_x=0;
	delta_y=-1;

}
else if(key=='s'||key=='S')//s��
{ 

	delta_x=0;
	delta_y=1;
}
 else if(key=='a'||key=='A')//a��
{
 
	 delta_x=-1;
	 delta_y=0;
 }
else if(key=='d'||key=='D')//d��
{
	delta_x=1;
	delta_y=0;

}
else
{
//��Ч����
	return;
}
//ɾ��β�ڵ�
_DrawChar(g_snack.pos[g_snack.size-1].x,g_snack.pos[g_snack.size-1].y,' ');

//��һ���ڵ����ǰ���ڵ������
	//i>0��ʾ������ͷ���

	for(int i=g_snack.size-1;i>0;i--)
	{
	g_snack.pos[i].x=g_snack.pos[i-1].x;
	g_snack.pos[i].y=g_snack.pos[i-1].y;
	}

	g_snack.pos[0].x+=delta_x;
	g_snack.pos[0].y+=delta_y;
}
//ͷ�ڵ��ʳ��������ͬ
void EatFood()
{
	if (g_snack.pos[0].x == g_food.x &&
		g_snack.pos[0].y == g_food.y)
	{
		g_snack.size++;
		g_snack.pos [g_snack.size - 1].x =g_food.x;
		g_snack.pos [g_snack.size - 1].y =g_food.y;
	}
}


void GameLoop()
{

	int key = 0 ;

	while(1)
	{
		//������������

		//����Ƿ��а�������
		if(_kbhit())
		{
			key = _getch();
		}

		//��Q�˳���Ϸ

		if(key == 'q' || key =='Q')
		{
			return;
		}

		SnackMove(key);
	
		//����ײǽ���¼�
		//����ҳ��
		UpsdateScreen();
		EatFood();

		//��ʱ
		Sleep(100);
	}
}

void Score()
{
}

int main(int argc, char* argv[])
{
	//��ʼ��������ͼ
	Init();

	GameLoop();

    //��Ϸ����ѭ����������������Ϸ����ˢ�£�����ײǽ���¼�
   Score();



	//��ӡ�÷�


	return 0;
}
