# ifndef _fighter_h
# define _fighter_h

void init();                // ���ݳ�ʼ��
void drawPicture();         // ��ʾ��ҷɻ����л����ӵ���
void operateFighger();      // �û��ٿطɻ�
void pcOperate();           // PC���ɵл��������ӵ�����Ư�Ƶ�


void floatBullet();         // �����ӵ��ƶ�
void enemyFighter();        // �������Ƶл������ƶ����ٶȡ�ÿ��10��һ��ѭ�����ƶ�һ�εл�

void zeroXy(int x, int y);  // ����ƶ���(x, y)λ��
void HideCursor();          // �������ع��
void WinLose();             // �ж���Ӯ


# endif