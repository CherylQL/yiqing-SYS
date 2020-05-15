#include "import.h"

#define R  2.0
#define Pi 3.1415926535
#define Ox winwidth*3/4
#define Oy winwidth/3 

extern double winwidth, winheight;

//画圆圈 
void DrawCircle(Pnode head,int count,double sum){
	MovePen(Ox, Oy);
    DrawEllipticalArc(R, R, 0.0, 360.0);
    DrawSplitLine(head,count,sum);
}

//画分割线，count=1时不画，否则画count条 
void DrawSplitLine(Pnode head,int count,double sum){
	double angle,current=0;
	if(count==0)return;
	if(count==1)return;
	Pnode p = head;
	while(p){
		angle = 2*Pi*(p->data)/sum;
		current = current + angle;
		MovePen(Ox-R,Oy);
		DrawLine(R*cos(current),R*sin(current));
		DrawCircleData(p,Ox-R+1.2*R*cos(current-angle/2),Oy+1.2*R*sin(current-angle/2));
		p = p->next;
	} 
} 

void DrawCircleData(Pnode L,double x,double y){
	MovePen(x,y);
//	printf("%lf\n",L->data);
//	printf("%s\n",L->date);
	DrawTextString("date:");
	DrawTextString(L->date);
	
	string s[20];
	sprintf(s,"%.2lf",L->data);
	DrawTextString("data:");
	DrawTextString(s);
	
}
