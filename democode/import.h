#ifndef _IMPORT_H
#define _IMPORT_H

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <math.h>
#include "imgui.h"


#define coorheight  4.0
#define coorwidth   7.0
#define tarlenth	0.2
#define Pi 			3.1415926535
#define SYSCOLOR    "Red"
#define ORICOLOR	"Black"

#define DEMO_MENU
#define DEMO_BUTTON

typedef struct node{
	double data;
	string date[20];
	double x;
	double y;
	bool isSelected;
	struct node *next;
}*Pnode; 
//����ʱ�ݴ�����
Pnode tmp; 

//�������� 
Pnode line;

//����ͼ 
Pnode square;

//��״ͼ
Pnode circle; 

//�������� 
Pnode Createlist();
Pnode Insert(Pnode head,Pnode num);
//��ȡ���� 
int countnum(Pnode head,double* max,double* min);
//��ȡdata�ܺ�
double getsum(Pnode head);
//�ⲿ��������         jΪ���б�� 
Pnode Readlist(int j); 
//ɾ��ĳ����������
Pnode del(Pnode head,string date); 
//�������� 
Pnode add(Pnode head); 
 //δ��Ԥ��           ����������  ҽѧˮƽ�������� 
    Pnode predict(Pnode head ,  int yixue , int liudongxing);   
    
    
 
//��ͼ���� 
void DrawCoor(double x,double y);									//������ 
void DrawDot(double x,double y); 
void DrawData(Pnode head,double x,double y);
void MouseEventProcess1(int x, int y, int button, int event);/*�����Ϣ�ص�����*/

//ѡ��Ҫ�ƶ��ĵ�
Pnode currentdot;
Pnode PickDot(Pnode head,double mx,double my); 
void Lighten(Pnode p);
void Recover(Pnode p);


//��ҳ����Ⱦ
void PureMenu(); 

// ����������provided in libgraphics
void DisplayClear(void); 

// �û�����ʾ����
void display(void); 

// �û����ַ��¼���Ӧ����
void CharEventProcess(char ch); 
 
// �û��ļ����¼���Ӧ����
void KeyboardEventProcess(int key, int event);

// GUI�Դ��û�������¼���Ӧ����
void MouseEventProcess(int x, int y, int button, int event);

//����������¼��������� 
void MouseEventProcess1(int x, int y, int button, int event);

Pnode PickDot(Pnode head,double mx,double my);

//��logo 
void readmatrix(); 
//�������� 
void DrawCoor(double x,double y);
void DrawDot(double x,double y);										//����x,y���ϵı�� 
void DrawData(Pnode L,double x,double y);								//д������ 				 

//��������滭����
void DrawLinear(Pnode head,int count,double* max,double* min);		//������������ͼ
void Lighten(Pnode p);
void Recover(Pnode p);

//����״ͼ
void DrawSquare(Pnode head,int count,double* max,double* min);
void DrawBasicSquare(double x1,double y1,double width,double height);
void LightenSquare(Pnode L);
void RecoverSquare(Pnode L); 

//����״ͼ
void DrawCircle(Pnode head,int count,double sum); 
void DrawSplitLine(Pnode head,int count,double sum);

//������
void Animation();
void display();
void TimerEventProcess(int timerID);
void fillRound(double x, double y, double l);
void DrawSolidCube(double x, double y, double l);
void DrawEagle(int a[][79], double x, double y, double size);
void FillBackgound();
void DrawLogo(int b[][167], double x, double y, double size); 

#endif
