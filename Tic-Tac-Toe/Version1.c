#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h> //随机数用

/*
project name: 井字棋（Tic-Tac-Toe）
author name: dragonet
date: 2020/7/15——2020/7/21
*/

/*全局变量区*/
int board[3][3] = {0}; //0代表空，1代表◆，-1代表★
int player; //1代表玩家、-1代表电脑
int weight[3][3] = { 5,5,5,5,5,5,5,5,5 }; //权重数组
int play_mode = 0; //0代表自娱自乐，1代表人机对战
int step = 0; //走的步数
int offence_defence; //电脑的下棋模式选择为进攻还是防守，0为防守，1为进攻

/*函数声明区*/
void gotoxy(int x, int y); //将界面放的位置改变一下
void menu(); //讲解规则，开始界面
void draw(); //打印棋盘面板
int choose(); //在weight数组中选出最大数或最小数
void update(); //更新棋盘
int leagality_check(int t, int minnum, int maxnum); //输入合法性检查，主要判断数字是否在范围内
void play_own(); //自娱自乐玩法
void play_computer(); //人机对战玩法
int weight_calculating(); //权重计算
int win_check(); //输赢判断，0为无法判断，1为◆赢，2为★赢，3为平局


int main()
{
	system("mode con cols=90 lines=30");
	int n = 0;
	Mode_choice:
	printf_s("请输入想要玩的模式(1代表自娱自乐，2代表人机对战)：");
	scanf_s("%d", &n);
	if (leagality_check(n, 1, 2) == 0) goto Mode_choice;
	if (n == 2)
	{
		gotoxy(0, 0);
		for (n = 0; n < 200; ++n)   printf_s("                                                                                             \n"); //清空所有
		play_computer();
	}
	else
	{
		gotoxy(0, 0);
		for (n = 0; n < 200; ++n)   printf_s("                                                                                             \n"); //清空所有
		play_own();
	}

	gotoxy(23, 22);
	system("pause");
	return 0;
}

void menu()
{
	gotoxy(23, 2);
	printf_s("欢迎来玩井字游戏(Tic-Tac-Toe)!");
	gotoxy(30, 3);
	printf_s("下面开始介绍规则");
	gotoxy(10, 4);
	printf_s("1. 赢局：任意行、列、对角线先占满三个同种棋，则该种棋的玩家赢");
	gotoxy(10, 5);
	printf_s("2. 输局：只存在于人机对战，任意行、列、对角线被电脑先占满三个棋");
	gotoxy(10, 6);
	printf_s("3. 平局：全部格子都已被占满且未分出胜负");
	gotoxy(10, 7);
	printf_s("4. 默认都是玩家先出手，且棋类型为◆");
}



void draw()
{
	gotoxy(26, 8);
	printf_s("┏━━━━━━━┳━━━━━━━┳━━━━━━━┓");
	gotoxy(26, 9);
	printf_s("┃       ┃       ┃       ┃");
	gotoxy(26, 10);
	printf_s("┃       ┃       ┃       ┃");
	gotoxy(26, 11);
	printf_s("┃       ┃       ┃       ┃");
	gotoxy(26, 12);
	printf_s("┣━━━━━━━╋━━━━━━━╋━━━━━━━┫");
	gotoxy(26, 13);
	printf_s("┃       ┃       ┃       ┃");
	gotoxy(26, 14);
	printf_s("┃       ┃       ┃       ┃");
	gotoxy(26, 15);
	printf_s("┃       ┃       ┃       ┃");
	gotoxy(26, 16);
	printf_s("┣━━━━━━━╋━━━━━━━╋━━━━━━━┫");
	gotoxy(26, 17);
	printf_s("┃       ┃       ┃       ┃");
	gotoxy(26, 18);
	printf_s("┃       ┃       ┃       ┃");
	gotoxy(26, 19);
	printf_s("┃       ┃       ┃       ┃");
	gotoxy(26, 20);
	printf_s("┗━━━━━━━┻━━━━━━━┻━━━━━━━┛");
	gotoxy(26, 21);
	printf_s("注：输错的话要重输的喔");
}


void gotoxy(int x, int y) {
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}



int choose()
{
	int max = 0, n = 0, min = 0;
	int num[9] = {0,0,0,0,0,0,0,0,0};
	Suiji:
	if (step < 3)
	{
		time_t t;
		srand((unsigned)time(&t));
		n = rand() % 10 + 1; //1-9随机数
		switch (n)
		{
		case 1:if (board[0][0] == 0) return n; else goto Suiji; break;
		case 2:if (board[0][1] == 0) return n; else goto Suiji; break;
		case 3:if (board[0][2] == 0) return n; else goto Suiji; break;
		case 4:if (board[1][0] == 0) return n; else goto Suiji; break;
		case 5:if (board[1][1] == 0) return n; else goto Suiji; break;
		case 6:if (board[1][2] == 0) return n; else goto Suiji; break;
		case 7:if (board[2][0] == 0) return n; else goto Suiji; break;
		case 8:if (board[2][1] == 0) return n; else goto Suiji; break;
		case 9:if (board[2][2] == 0) return n; else goto Suiji; break;
		}
	}
	else
	{
		if (offence_defence = 0)
		{
			for (int i = 0; i < 3; ++i)
				for (int j = 0; j < 3; ++j)
				{
					num[n] = weight[i][j];
					++n;
				}
			for (n = 0; n < 9; ++n)
				if (min >= num[n])
					min = num[n];
			for (n = 0; n < 9; ++n)  if (min == num[n])  break;
		}
		if (offence_defence = 1)
		{
			for (int i = 0; i < 3; ++i)
				for (int j = 0; j < 3; ++j)
				{
					num[n] = weight[i][j];
					++n;
				}
			for (n = 0; n < 9; ++n)
				if (max <= num[n])
					max = num[n];
			for (n = 0; n < 9; ++n)  if (max == num[n])  break;
		}
		return n;
	}
}

void update()
{
	int xp, yp;
	for (int i = 0; i < 3; ++i)
	{
		yp = 10 + (i * 4);
		for (int j = 0; j < 3; ++j)
		{
			xp = 30 + (j * 8);
			gotoxy(xp, yp);
			if (board[i][j] == 0)   printf_s(" ");
			if (board[i][j] == 1)   printf_s("◆");
			if (board[i][j] == -1)   printf_s("★");
			printf_s("\t");
		}
		printf_s("\n");
	}
}

int leagality_check(int t, int minnum, int maxnum)
{
	for (int i = minnum; i <= maxnum; ++i)    if (t == i)    return 1;
	return 0;
}

void play_own()
{
	player = 1; //从头到尾都是玩家
	play_mode = 0; //自娱自乐模式
	int temp = 1; //1为◆状态，-1为★状态
	int x, y; //行、列坐标
	menu(); //介绍面板
	draw(); //初始化棋盘面板
	while (win_check() == 0)
	{
		++step; //步数增加
/*-----------------打印当前棋子信息-----------------------*/
		gotoxy(54, 9);
		printf_s("╔      ═      ╗");
		gotoxy(54, 11);
		printf_s("╚      ═      ╝");
		if (temp == 1)
		{
			gotoxy(55, 10);
			printf_s("当前棋子：◆");
		}
		if (temp == -1)
		{
			gotoxy(55, 10);
			printf_s("当前棋子：★");
		}
/*----------------------------------------------------------*/
	own_play:
		/*先清空原先输入的坐标*/
		gotoxy(54, 17);
		printf_s("请输入行坐标（1-3）:                ");
		gotoxy(54, 18);
		printf_s("请输入列坐标（1-3）：               ");
		gotoxy(26, 22);
		printf_s("                                            ");
/*----------------------------------------------------------*/
		gotoxy(54, 17);
		printf_s("请输入行坐标（1-3）:");
		scanf_s("%d", &x);
		if (leagality_check(x, 1, 3) == 0)  goto own_play;
		gotoxy(54, 18);
		printf_s("请输入列坐标（1-3）:");
		scanf_s("%d", &y);
		if (leagality_check(y, 1, 3) == 0)  goto own_play;
		if (board[x - 1][y - 1] == 0)
		{
			board[x - 1][y - 1] = temp;
			update();
			temp *= -1;
		}
		else
		{
			gotoxy(26,22);
			printf_s("该坐标已有棋，请重下！");
			getchar();
			getchar(); //让玩家看得到信息
			goto own_play;
		}
	}
	switch (win_check())
	{
	case 1: MessageBox(NULL, TEXT("恭喜◆方胜利"), TEXT("输赢判断"), MB_OK); break;
	case 2: MessageBox(NULL, TEXT("恭喜★方胜利"), TEXT("输赢判断"), MB_OK); break;
	case 3: MessageBox(NULL, TEXT("平局！！！"), TEXT("输赢判断"), MB_OK); break;
	}
}


void play_computer()
{
	play_mode = 1; //人机对战模式
	player = 1; //玩家先出手 （1为玩家，-1为电脑）
	int temp = 1; //1为◆状态，-1为★状态
	int x, y; //行、列坐标
	menu(); //介绍面板
	draw(); //初始化棋盘面板
COM_play_mode:
	gotoxy(26, 22);
	printf_s("你想设置电脑的下棋模式为防守/进攻为主？(0-1)：                   "); //清空
	gotoxy(26, 22);
	printf_s("你想设置电脑的下棋模式为防守/进攻为主？(0-1)：");
	scanf_s("%d", &offence_defence);
	if (leagality_check(offence_defence, 0, 1) == 0)   goto COM_play_mode;
	if (offence_defence == 0)
	{
		gotoxy(55, 12);
		printf_s("当前电脑下棋模式：防守");
	}
	else
	{
		gotoxy(55, 12);
		printf_s("当前电脑下棋模式：进攻");
	}
	while (win_check() == 0)
	{
		++step; //步数增加
		gotoxy(20, 22);
		printf_s("                                                                    ");
		/*-------------------打印当前棋子信息-----------------------*/
		gotoxy(54, 9);
		printf_s("╔      ═      ╗");
		gotoxy(54, 11);
		printf_s("╚      ═      ╝");
		if (temp == 1)
		{
			gotoxy(55, 10);
			printf_s("当前棋子：◆");
		}
		if (temp == -1)
		{
			gotoxy(55, 10);
			printf_s("当前棋子：★");
		}
		/*----------------------------------------------------------*/
	com_play:
		/*先清空原先输入的坐标*/
		gotoxy(54, 17);
		printf_s("请输入行坐标（1-3）:                ");
		gotoxy(54, 18);
		printf_s("请输入列坐标（1-3）：               ");
		gotoxy(26, 22);
		printf_s("                                            ");
		/*----------------------------------------------------------*/
		if (player = 1)
		{
			gotoxy(54, 17);
			printf_s("请输入行坐标（1-3）:");
			scanf_s("%d", &x);
			if (leagality_check(x, 1, 3) == 0)  goto com_play;
			gotoxy(54, 18);
			printf_s("请输入列坐标（1-3）:");
			scanf_s("%d", &y);
			if (leagality_check(y, 1, 3) == 0)  goto com_play;
			if (board[x - 1][y - 1] == 0)
			{
				board[x - 1][y - 1] = temp;
				update();
				temp *= -1;
			}
			else
			{
				gotoxy(26, 22);
				printf_s("该坐标已有棋，请重下！");
				getchar();
				getchar(); //让玩家看得到信息
				goto com_play;
			}
			player *= -1; //玩家先出手 （1为玩家，-1为电脑）
		}
		
		if (player = -1)
		{
		/*------------单纯为了好玩，让玩家不会觉得自己孤独-------------*/
			gotoxy(23, 22);
			printf_s("电脑正在思考，请输入任意键以继续");
			getchar();
			getchar();

			weight_calculating();
			switch (choose())
			{
			case 1: if (board[0][0] == 0) board[0][0] = -1; else; break;
			case 2: if (board[0][1] == 0) board[0][1] = -1;  break;
			case 3: if (board[0][2] == 0) board[0][2] = -1;  break;
			case 4: if (board[1][0] == 0) board[1][0] = -1;  break;
			case 5: if (board[1][1] == 0) board[1][1] = -1;  break;
			case 6: if (board[1][2] == 0) board[1][2] = -1;  break;
			case 7: if (board[2][0] == 0) board[2][0] = -1;  break;
			case 8: if (board[2][1] == 0) board[2][1] = -1;  break;
			case 9: if (board[2][2] == 0) board[2][2] = -1;  break;
			}
			update();
			temp *= -1;
			player *= -1;
		}
		
	}
	switch (win_check())
	{
	case 1: MessageBox(NULL, TEXT("你真棒，你获得胜利！"), TEXT("输赢判断"), MB_OK); break;
	case 2: MessageBox(NULL, TEXT("电脑真棒，电脑获得胜利！"), TEXT("输赢判断"), MB_OK); break;
	case 3: MessageBox(NULL, TEXT("平局！！！"), TEXT("输赢判断"), MB_OK); break;
	}


}

int weight_calculating()
{
	int n;
	int fang = -2, xing = 2;
	if (step > 3)
	{
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
			{
				/*-------行的判断--------*/
				if (board[i][0] == 1 || board[i][1] == 1 || board[i][2] == 1)
					for (n = 0; n < 3; ++n)
						if (board[i][n] == 1)
							weight[i][j] += fang;
				if (board[i][0] == -1 || board[i][1] == -1 || board[i][2] == -1)
					for (n = 0; n < 3; ++n)
						if (board[i][n] == -1)
							weight[i][j] += xing;
				/*-------列的判断--------*/
				if (board[0][i] == 1 || board[1][i] == 1 || board[2][i] == 1)
					for (n = 0; n < 3; ++n)
						if (board[n][i] == 1)
							weight[i][j] += fang;
				if (board[0][i] == -1 || board[1][i] == -1 || board[2][i] == -1)
					for (n = 0; n < 3; ++n)
						if (board[n][i] == -1)
							weight[i][j] += xing;
				/*-------对角线的判断--------*/
				if (i == 0 && j == 0 || i == 0 && j == 2 || i == 1 && j == 1 || i == 2 && j == 0 || i == 2 && j == 2) //只有四个角的位置和中间的位置才有对角线的判断资格
				{
					/*-----正对角线------*/
					if (board[0][0] == 1 || board[1][1] == 1 || board[2][2] == 1)
						for (n = 0; n < 3; ++n)
							if (board[n][n] == 1)
								weight[i][j] += fang;
					if (board[0][0] == -1 || board[1][1] == -1 || board[2][2] == -1)
						for (n = 0; n < 3; ++n)
							if (board[n][n] == -1)
								weight[i][j] += xing;
					/*-----副对角线------*/
					if (board[0][2] == 1 || board[1][1] == 1 || board[2][0] == 1)
						for (n = 0; n < 3; ++n)
							if (board[0 + n][2 - n] == 1)
								weight[i][j] += fang;
					if (board[0][2] == -1 || board[1][1] == -1 || board[2][0] == -1)
						for (n = 0; n < 3; ++n)
							if (board[0 + n][2 - n] == -1)
								weight[i][j] += xing;
				}
			}
	}
}

int win_check()
{
	if (play_mode == 0) //自娱自乐模式下的判断
	{
		int i;
		/*赢局的情况（◆与★）*/
		for (i = 0; i < 3; ++i) //行
			if (board[i][0] == 1 && board[i][1] == 1 && board[i][2] == 1 || board[i][0] == -1 && board[i][1] == -1 && board[i][2] == -1)   break; //穷举行
		if(board[i][0] == 1 && board[i][1] == 1 && board[i][2] == 1)    return 1;
		if(board[i][0] == -1 && board[i][1] == -1 && board[i][2] == -1)    return 2;
	/*-----------------------------*/
		for (i = 0; i < 3; ++i) //列
			if (board[0][i] == 1 && board[1][i] == 1 && board[2][i] == 1 || board[0][i] == -1 && board[1][i] == -1 && board[2][i] == -1)   break; //穷举列
		if (board[0][i] == 1 && board[1][i] == 1 && board[2][i] == 1)    return 1;
		if (board[0][i] == -1 && board[1][i] == -1 && board[2][i] == -1)    return 2;
	/*-----------------------------*/ 
		//if (board[0][0]==board[1][1]==board[2][2] && board[0][0]!=0 && board[1][1]!=0 && board[2][2]!=0 || board[0][2]==board[1][1]==board[2][0] && board[0][2] != 0 && board[1][1] != 0 && board[2][0] != 0) //对角线
		if (board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1 || board[0][2] == 1 && board[1][1] == 1 && board[2][0] == 1 || board[0][0] == -1 && board[1][1] == -1 && board[2][2] == -1 || board[0][2] == -1 && board[1][1] == -1 && board[2][0] == -1 ) //穷举的对角线
		{
			if (board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1 || board[0][2] == 1 && board[1][1] == 1 && board[2][0] == 1)    return 1;
			if (board[0][0] == -1 && board[1][1] == -1 && board[2][2] == -1 || board[0][2] == -1 && board[1][1] == -1 && board[2][0] == -1)    return 2;
		}
		
		/*平局的情况*/
		if (step == 9)  return 3;
	}
	if (play_mode == 1) //人机对战模式下的判断
	{
		int i;
		/*赢局、输局的情况（◆与★）*/
		for (i = 0; i < 3; ++i) //行
			if (board[i][0] == 1 && board[i][1] == 1 && board[i][2] == 1 || board[i][0] == -1 && board[i][1] == -1 && board[i][2] == -1)   break; //穷举行
		if (i == 3) --i;
		if (board[i][0] == 1 && board[i][1] == 1 && board[i][2] == 1)    return 1;
		if (board[i][0] == -1 && board[i][1] == -1 && board[i][2] == -1)    return 2;
		/*-----------------------------*/
		for (i = 0; i < 3; ++i) //列
			if (board[0][i] == 1 && board[1][i] == 1 && board[2][i] == 1 || board[0][i] == -1 && board[1][i] == -1 && board[2][i] == -1)   break; //穷举列
		if (i == 3) --i;
		if (board[0][i] == 1 && board[1][i] == 1 && board[2][i] == 1)    return 1;
		if (board[0][i] == -1 && board[1][i] == -1 && board[2][i] == -1)    return 2;
		/*-----------------------------*/
		//if (board[0][0]==board[1][1]==board[2][2] && board[0][0]!=0 && board[1][1]!=0 && board[2][2]!=0 || board[0][2]==board[1][1]==board[2][0] && board[0][2] != 0 && board[1][1] != 0 && board[2][0] != 0) //对角线
		if (board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1 || board[0][2] == 1 && board[1][1] == 1 && board[2][0] == 1 || board[0][0] == -1 && board[1][1] == -1 && board[2][2] == -1 || board[0][2] == -1 && board[1][1] == -1 && board[2][0] == -1) //穷举的对角线
		{
			if (board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1 || board[0][2] == 1 && board[1][1] == 1 && board[2][0] == 1)    return 1;
			if (board[0][0] == -1 && board[1][1] == -1 && board[2][2] == -1 || board[0][2] == -1 && board[1][1] == -1 && board[2][0] == -1)    return 2;
		}

		/*平局的情况*/
		if (step == 9)  return 3;
	}
	return 0;
}