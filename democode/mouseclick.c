#include "import.h"

extern double max;
extern double min;
extern double dx;
extern double dy;
extern double winwidth, winheight; 

extern bool isSelected;
extern bool isMove;

extern int zhexian;
extern int yidong;
extern int backtomenu;
extern int zhuzhuang;

void MouseEventProcess1(int x, int y, int button, int event){
	double fH = GetFontHeight();
	double h = fH*2;  // 控件高度
	double bx = winwidth/2.5+winwidth/6;  
	double by = winheight/6*5-h; 
	double w = winwidth/6; // 控件宽度
	static bool isMove = FALSE;
	static double omx = 0.0, omy =0.0 ;/*前一鼠标坐标*/ 
	double mx,my;
	Pnode selectdot;
	
	int count;
	
	double cx,cy;
	
	mx = ScaleXInches(x);/*pixels --> inches*/
	my = ScaleYInches(y);/*pixels --> inches*/ 
	switch(event){
		case BUTTON_DOWN:
			if(isSelected){
				omx = mx;
				omy = my;
				if(button = LEFT_BUTTON)
					isMove = TRUE;
			}
			if(zhexian)
				selectdot = PickDot(line,mx,my);
			else if(zhuzhuang)
				selectdot = PickDot(square,mx,my);
			currentdot = selectdot;
			if(zhexian){
				Lighten(currentdot);	
			}else if(zhuzhuang){
				LightenSquare(currentdot);
			}
			isSelected = TRUE;
			break;
		case MOUSEMOVE:
			if(isSelected&&isMove){
//				DisplayClear();
//				DrawCoor(dx,dy);
//				my = ScaleYInches(y);
				cy = (my - omy);
				omx = mx;
				omy = my;
				if(isMove){
					currentdot->y += cy;
					currentdot->data = (currentdot->y-dy)*2*max/coorheight;
					if(currentdot->data>max) max = currentdot->data;
					if(currentdot->data<min) min = currentdot->data;
//					if(zhexian){
//						count = countnum(line,&max,&min);
//						DrawLinear(line,count,&max,&min);
//					}
//					else if(zhuzhuang){
//						count = countnum(square,&max,&min);
//						DrawSquare(square,count,&max,&min);
//					}
				}
			}
			break;
		case BUTTON_UP:
			isMove = FALSE;
//			isSelected = FALSE;
//			if(currentdot)	Recover(currentdot);
//			currentdot = NULL;
			break;
	}
} 
