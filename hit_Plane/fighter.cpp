# include "fighter.h"
# include<iostream>
# include <conio.h>
# include<iomanip>
# include<windows.h>
using namespace std;

// 全局变量
int height, width;          // 游戏画面尺寸
int fighter_x, fighter_y;   // 飞机位置
int bullet_x, bullet_y;     // 飞机子弹位置
int enemy_x, enemy_y;       // 敌机位置
int score;                  // 得分
int fighter;                // 血量
string difficulty;          // 难度

void init()
{
	score = 0;
	height = 33;
	width = 50;
	fighter_x = height / 2;     // 初始化飞机在屏幕正中间
	fighter_y = width / 2;
	bullet_x = -2;
	bullet_y = fighter_y;       // 初始化子弹位置
	enemy_x = 1;
	difficulty = "简单";        // 初始为简单模式
	fighter = 3;                // 初始生命值为 3
	enemy_y = rand() % long(width - 5) + 2;  // 生成2——(width - 5)之内的随机数
	HideCursor();
}

void drawPicture()
{
	zeroXy(0, 0);
	cout << " " << setfill('#') << setw(width + 2) << "#" << endl;   // 画出上边界
	for (int x = 0; x <= height; x++)
	{
		for (int y = 0; y <= width + 1; y++)
		{
			if ((x == enemy_x) && (y == enemy_y))           // 画出敌机
			{
				cout << "@";
			}
			else if ((x == fighter_x) && (y == fighter_y))
			{
				cout << setfill(' ') << setw(4) << "***";    // 画出飞机
			}
			// 防止边界出界，不输出空格
			else if ((x == fighter_x) && ((y == fighter_y + 1) ||   
				(y == fighter_y + 2) || (y == fighter_y + 3)));

			// 防止边界出界，不输出空格
			else if ((x == fighter_x + 1) && ((y == fighter_y + 1) ||
				(y == fighter_y + 2) || (y == fighter_y + 3) ||
				(y == fighter_y + 4) || (y == fighter_y + 5)));

			else if ((x == fighter_x + 1) && (y == fighter_y))
			{
				cout << setfill('*') << setw(6) << " ";
			}
			else if ((x == fighter_x + 2) && (y == fighter_y))
			{
				cout << " * *";
			}
			// 防止边界出界，不输出空格
			else if ((x == fighter_x + 2) && ((y == fighter_y + 1) ||
				(y == fighter_y + 2) || (y == fighter_y + 3)));

			else if ((x == bullet_x) && (y == bullet_y))    // 画出子弹
			{
				cout << "|";
			}
			else
			{
				cout << " ";                                // 输出空格
			}
			if (y == width || y == 0)
			{
				cout << "。";                               // 输出边界	
			}
		}
		cout << endl;
	}
	cout << " " << setfill('#') << setw(width + 2) << "#" << endl;
	cout << "  " << "难度: " << difficulty << endl;
	cout << "  " << "生命: " << fighter << endl;
	cout << "  " << "得分: " << score << endl;
}

void operateFighger()
{
	char input;
	if (_kbhit())
	{
		input = _getch();             // 根据用户的不同输入来移动
		if (input == 'a')
		{
			fighter_y--;
		}
		if (input == 'd')
		{
			fighter_y++;
		}
		if (input == 'w')
		{
			fighter_x--;
		}
		if (input == 's')
		{
			fighter_x++;
		}
		if (input == ' ')             // 空格为发射子弹
		{
			bullet_x = fighter_x - 1;
			bullet_y = fighter_y + 2;
		}
		if (input == 27)
		{
			exit(0);                  // 退出程序
		}
	}
}

void pcOperate()
{
	enemyFighter();
	floatBullet();
}

void floatBullet()
{
	if (bullet_x > -1)               // 如果屏幕上有子弹，则子弹沿直线向上走
	{
		bullet_x--;
	}
}

void zeroXy(int x, int y)            // 使光标返回(0, 0)位置处
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };        // 第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void enemyFighter()
{
	// 防止子弹打到敌机时敌机恰好在移动，子弹穿过敌机，为子弹增加垂直方向3格伤害
	if (((bullet_x == enemy_x) && (bullet_y == enemy_y) || (bullet_x == enemy_x + 1))
		&& (bullet_y == enemy_y) || (bullet_x == enemy_x - 1) && (bullet_y == enemy_y))    //子弹击中敌机
	{
		score++;                                           // 分数加 1
		enemy_x = -1;                                      // 产生新飞机
		enemy_y = rand() % (width - 5) + 2;
		bullet_x = -2;                                     // 子弹无效
	}

	static int speed = 0;            // 得分越高，难度越大，敌机速度越快
	if (score > 5)
	{
		speed++;
		difficulty = "普通";         // 普通模式，敌机速度加快
	}
	if (score > 15)
	{
		speed += 2;
		difficulty = "困难";         // 困难模式，敌机速度最快
	}
	if (speed < 10)
	{
		speed++;
	}
	else
	{
		enemy_x++;
		speed = 0;
	}
	// 判断飞机是否出界，出界即为死亡
	if ((fighter_x == 0) || (fighter_x == height - 1) || 
		(fighter_y == width - 4) || (fighter_y == 0))
	{
		WinLose();
	}
	// 判断敌机击中飞机机身的位置
	if ((enemy_x == fighter_x) && ((enemy_y == fighter_y) ||
		(enemy_y == fighter_y + 1) || (enemy_y == fighter_y + 3) ||
		(enemy_y == fighter_y + 4)) || ((enemy_x == fighter_x) &&
			(enemy_y == fighter_y + 2)))

	{
		WinLose();
	}
	if (enemy_x > height)
	{
		score--;                       // 若敌机飞到底线，分数减 1
		enemy_x = -1;                  // 产生新飞机
		enemy_y = rand() % width + 2;  // 在2——width位置处随即产生敌机 
		bullet_x = -2;
	}
}

void WinLose() 
{
	fighter--;
	if (fighter > 0)
	{
		// 重新产生飞机
		fighter_x = -3;
		fighter_x = height / 2;
		fighter_y = width / 2;
	}
	else    
	{
		fighter = 0;
		cout << "  ***********************你输了！**********************\n";
		fighter_x = -3;
		system("pause");
		cout << "  *******************按任意键退出游戏*******************\n";
		exit(0);
	}
}
