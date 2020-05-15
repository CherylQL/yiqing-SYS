#include "import.h"
double width,height;

extern double dx;
extern double dy;
extern double max;
extern double min;

void DrawSquare(Pnode head,int count,double* max,double* min){
	printf("draw square\n");
	double x0,y0;
	double x1,x2,y1,y2;
	
//	double prey;

	x0 = 1.0*(coorwidth)/(count+2);						//单位x长度  
	y0 = 1.0*(coorheight)/(2*(*max-0));					//单位y长度 
	Pnode p = head;
	x1 = dx*4/3;
	y1 = dy+y0*(p->data-0);
	p->x = x1;
	p->y = y1;
	width = x0/2;
	height = y1-dy;
//	prey = p->data;
//	printf("%lf\n",prey);
	while(p){
		printf("%lf\n",p->data);
		DrawData(p,x1,y1);
		DrawBasicSquare(x1,dy,width,height);
		if(p->next){
//			printf("%d\n",p->next->data);
			p = p->next;
			x2 = x1+x0;
			y2 =  dy+y0*(p->data-0);
			height = y2-dy;
			DrawData(p,x2,y2);
			x1 = x2;
			y1 = y2;
			p->x = x1;
			p->y = y1;	
		}else{
			p->next = NULL;
			break;
		}
	}

//	DrawData(p,x1,y1);
//	DrawBasicSquare(x1,dy,width,height);
}

void DrawBasicSquare(double x1,double y1,double width,double height){
	MovePen(x1,y1);
	DrawLine(width,0);
	DrawLine(0,height);
	DrawLine(-width,0);
	DrawLine(0,-height);
}

void LightenSquare(Pnode L){
	double x,y;
	x = L->x;
	y = L->y;
	SetEraseMode(TRUE);
	DrawBasicSquare(x,dy,width,y-dy);
	SetEraseMode(FALSE);
	SetPenColor(SYSCOLOR);
	DrawBasicSquare(x,dy,width,y-dy);
	SetPenColor(ORICOLOR); 
}

void RecoverSquare(Pnode L){
	double x,y;
	x = L->x;
	y = L->y;
	SetEraseMode(TRUE);
	DrawBasicSquare(x,dy,width,y-dy);
	SetEraseMode(FALSE);
	DrawBasicSquare(x,dy,width,y-dy);
}
