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
//读数时暂存链表
Pnode tmp; 

//折线链表 
Pnode line;

//柱形图 
Pnode square;

//饼状图
Pnode circle; 

//创建链表 
Pnode Createlist();
Pnode Insert(Pnode head,Pnode num);
//读取链表长 
int countnum(Pnode head,double* max,double* min);
//获取data总和
double getsum(Pnode head);
//外部读入数据         j为城市编号 
Pnode Readlist(int j); 
//删除某个结点的数据
Pnode del(Pnode head,string date); 
//增加数据 
Pnode add(Pnode head); 
 //未来预测           有两个参数  医学水平和流动性 
    Pnode predict(Pnode head ,  int yixue , int liudongxing);   
    
    
 
//画图工具 
void DrawCoor(double x,double y);									//画坐标 
void DrawDot(double x,double y); 
void DrawData(Pnode head,double x,double y);
void MouseEventProcess1(int x, int y, int button, int event);/*鼠标消息回调函数*/

//选择将要移动的点
Pnode currentdot;
Pnode PickDot(Pnode head,double mx,double my); 
void Lighten(Pnode p);
void Recover(Pnode p);


//主页面渲染
void PureMenu(); 

// 清屏函数，provided in libgraphics
void DisplayClear(void); 

// 用户的显示函数
void display(void); 

// 用户的字符事件响应函数
void CharEventProcess(char ch); 
 
// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event);

// GUI自带用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event);

//本地鼠标点击事件监听函数 
void MouseEventProcess1(int x, int y, int button, int event);

Pnode PickDot(Pnode head,double mx,double my);

//画logo 
void readmatrix(); 
//画坐标轴 
void DrawCoor(double x,double y);
void DrawDot(double x,double y);										//画（x,y）上的标记 
void DrawData(Pnode L,double x,double y);								//写坐标数 				 

//根据链表绘画折线
void DrawLinear(Pnode head,int count,double* max,double* min);		//根据链表画折线图
void Lighten(Pnode p);
void Recover(Pnode p);

//画柱状图
void DrawSquare(Pnode head,int count,double* max,double* min);
void DrawBasicSquare(double x1,double y1,double width,double height);
void LightenSquare(Pnode L);
void RecoverSquare(Pnode L); 

//画饼状图
void DrawCircle(Pnode head,int count,double sum); 
void DrawSplitLine(Pnode head,int count,double sum);

//画背景
void Animation();
void display();
void TimerEventProcess(int timerID);
void fillRound(double x, double y, double l);
void DrawSolidCube(double x, double y, double l);
void DrawEagle(int a[][79], double x, double y, double size);
void FillBackgound();
void DrawLogo(int b[][167], double x, double y, double size); 

#endif
