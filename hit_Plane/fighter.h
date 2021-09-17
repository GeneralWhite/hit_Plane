# ifndef _fighter_h
# define _fighter_h

void init();                // 数据初始化
void drawPicture();         // 显示玩家飞机、敌机、子弹等
void operateFighger();      // 用户操控飞机
void pcOperate();           // PC生成敌机、处理子弹向上漂移等


void floatBullet();         // 处理子弹移动
void enemyFighter();        // 用来控制敌机向下移动的速度。每隔10次一个循环，移动一次敌机

void zeroXy(int x, int y);  // 光标移动到(x, y)位置
void HideCursor();          // 用与隐藏光标
void WinLose();             // 判断输赢


# endif