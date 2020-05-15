#include "import.h"

extern double dx;
extern double dy;

//画坐标轴 
void DrawCoor(double x,double y){
	double newx,newy;
	newx = x;
	newy = y-1.0;
	MovePen(newx,newy);
	DrawLine(0,coorheight);
	newy=newy+coorheight;
	MovePen(newx-0.5,newy-0.2);
	DrawTextString("data");
	MovePen(newx,newy);
	DrawLine(-tarlenth*sin(Pi/6.0),-tarlenth*cos(Pi/6.0));
	MovePen(newx,newy);
	DrawLine(tarlenth*sin(Pi/6.0),-tarlenth*cos(Pi/6.0));
	newx = x - 1.0;
	newy = y;
	MovePen(newx,newy);
	DrawLine(coorwidth,0);
	newx = newx + coorwidth;
	MovePen(newx-0.3,newy-0.3);
	DrawTextString("date");
	MovePen(newx,newy);
	DrawLine(-tarlenth*cos(Pi/6.0),tarlenth*sin(Pi/6.0));
	MovePen(newx,newy);
	DrawLine(-tarlenth*cos(Pi/6.0),-tarlenth*sin(Pi/6.0));
}

//画（x,y）上的标记 
void DrawDot(double x,double y){
//	SetPenColor(SYSCOLOR);
	
	double line = 0.1;
	MovePen(x,y);
	DrawLine(line*sin(Pi/4.0),line*cos(Pi)/4.0);
	MovePen(x,y);
	DrawLine(line*sin(Pi/4.0),-line*cos(Pi)/4.0);
	MovePen(x,y);
	DrawLine(-line*sin(Pi/4.0),-line*cos(Pi)/4.0);
	MovePen(x,y);
	DrawLine(-line*sin(Pi/4.0),line*cos(Pi)/4.0);

}

//写坐标数 
void DrawData(Pnode L,double x,double y){
	string s[20];
	sprintf(s,"%.2lf",L->data);
//	printf("%s\n",s);
	MovePen(dx-0.5,y);
	DrawTextString(s);
	
	MovePen(x,dy-0.3);
//	printf("%lf\n",L->data);
//	printf("%s\n",L->date);
	DrawTextString(L->date);
}
