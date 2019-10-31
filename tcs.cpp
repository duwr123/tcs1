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

//游戏功能列表
//1.贪吃蛇上下左右移动
//2.吃食物长大
//3.撞墙或吃到自己，死掉
//4.游戏结束，打印得分


#define MAP_WIDTH 60
#define MAP_HEIGHT 20

void _DrawChar(int x, int y,char ch);

typedef struct Position
{
	int x;
	int y;
}Position;


//绘制贪吃蛇结构体
typedef struct Snack
{
	//贪吃蛇长度
	int size;
	Position pos[MAP_WIDTH * MAP_HEIGHT];
}Snack;

Snack g_snack;

//食物
Position g_food;

void InitFood()
{
	srand((unsigned)time(NULL));

	g_food.x = rand() % MAP_WIDTH;
	g_food.y = rand() % MAP_HEIGHT;

	_DrawChar(g_food.x, g_food.y,'#');
}


//开始时贪吃蛇大小

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

//绘制贪吃蛇
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


//在X,Y绘制字符ch
//_DrawChar(30.10.'0');

void _DrawChar(int x, int y,char ch)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;


	//设置光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);

	putchar(ch);
}



void InitMap()
{
	//一行一行
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
	//绘制地图
	InitMap();

	//初始化贪吃蛇

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


if(key=='w'||key=='W')//w 上
{
	delta_x=0;
	delta_y=-1;

}
else if(key=='s'||key=='S')//s下
{ 

	delta_x=0;
	delta_y=1;
}
 else if(key=='a'||key=='A')//a左
{
 
	 delta_x=-1;
	 delta_y=0;
 }
else if(key=='d'||key=='D')//d右
{
	delta_x=1;
	delta_y=0;

}
else
{
//无效按键
	return;
}
//删掉尾节点
_DrawChar(g_snack.pos[g_snack.size-1].x,g_snack.pos[g_snack.size-1].y,' ');

//后一个节点等于前个节点的坐标
	//i>0表示不包括头结点

	for(int i=g_snack.size-1;i>0;i--)
	{
	g_snack.pos[i].x=g_snack.pos[i-1].x;
	g_snack.pos[i].y=g_snack.pos[i-1].y;
	}

	g_snack.pos[0].x+=delta_x;
	g_snack.pos[0].y+=delta_y;
}
//头节点跟食物坐标相同
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
		//处理键盘输入

		//检测是否有按键输入
		if(_kbhit())
		{
			key = _getch();
		}

		//按Q退出游戏

		if(key == 'q' || key =='Q')
		{
			return;
		}

		SnackMove(key);
	
		//处理撞墙等事件
		//更新页面
		UpsdateScreen();
		EatFood();

		//延时
		Sleep(100);
	}
}

void Score()
{
}

int main(int argc, char* argv[])
{
	//初始化，画地图
	Init();

	GameLoop();

    //游戏的主循环，按键处理，游戏画面刷新，处理撞墙等事件
   Score();



	//打印得分


	return 0;
}

