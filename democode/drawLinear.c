#include "import.h"

extern double dx;
extern double dy;

//根据链表绘画折线 
void DrawLinear(Pnode head,int count,double* max,double* min){
	printf("draw line	");

	double x0,y0;
	double x1,x2,y1,y2;
	int prey;
	x0 = 1.0*(coorwidth)/(count+2);						//单位x长度  
	y0 = 1.0*(coorheight)/(2*(*max-0));					//单位y长度 
	Pnode p = head;
	x1 = dx;
	y1 = dy+y0*(p->data-0);
	p->x = x1;
	p->y = y1;
//	printf("%lf\n",p->data);
//	printf("%s\n",p->date);
	DrawData(p,x1,y1);
	DrawDot(x1,y1); 
	prey = p->data;
	p = p->next;
	while(p){
		x2 = x1+x0;
		y2 = y1+y0*(p->data - prey);
		MovePen(x1,y1);
		DrawLine(x2-x1,y2-y1);
		p->x = x2;
		p->y = y2;
		DrawDot(x2,y2);
		DrawData(p,x2,y2);
		prey = p->data;
		x1 = x2;
		y1 = y2;
		p = p->next;
	}
	
}


Pnode PickDot(Pnode head,double mx,double my){
	if(head == NULL)return NULL;
	Pnode p = head;

	while(p){
//		printf("%lf %lf %lf %lf\n",p->x,p->y,mx,my);
		if(abs(p->x-mx)<0.05&&abs(p->y==my)<0.05){
			if(!p->next) p->next = NULL;
			return p;
		}
		p = p->next;
	}
	return NULL;
}

void Lighten(Pnode p){
	double x,y;
	x = p->x;
	y = p->y;
	SetEraseMode(TRUE);
	DrawDot(x,y);
	SetEraseMode(FALSE);
	SetPenColor(SYSCOLOR);
	DrawDot(x,y);
	SetPenColor(ORICOLOR); 
}
void Recover(Pnode p){
	double x,y;
	x = p->x;
	y = p->y;
	SetEraseMode(TRUE);
	DrawDot(x,y);
	SetEraseMode(FALSE);
	DrawDot(x,y);
}
