#include"import.h"

extern double winwidth, winheight;
extern adddata;
extern menu;

void Drawinput(){
	static char data[80]="";
	static char date[80] = "";
	static char results[200] = "";
	double fH = GetFontHeight();
	double h = fH*2; // �ؼ��߶�
	double w = winwidth/4; // �ؼ����
	double x = winwidth/3;
	double y = winheight*3/4-1.2*h;
	static double value = 0; 
	static int count = 1;

//	textbox(GenUIID(0), x, y, w, h, memo, sizeof(memo));

	SetPenColor("Brown"); 
	drawLabel(x-fH/2-TextStringWidth("����������"), (y-=h*1.8)+fH*0.7, "����������");
	if(textbox(GenUIID(0), x, y, w, h, data, sizeof(data)) )
	{
		sscanf(data,"%lf",&value);
		sprintf(results,"���޸ĵ�%d���dataΪ%.5lf", count,value);
//		printf("%.5lf %s %d\n",value,date,count);
	}
	
	SetPenColor("Brown"); 
	drawLabel(x-fH/2-TextStringWidth("����������"), (y-=h*1.8)+fH*0.7, "����������");
	if( textbox(GenUIID(0), x, y, w, h, date, sizeof(date)) )
		sprintf(results,"���޸ĵ�%d���dateΪ%s",count,date);
	SetPenColor("Gray"); 
	drawLabel(x, y+=fH*6, results);

	char name1[128]; sprintf(name1, "��һ��");
	if(button(GenUIID(0), x , y - 5*h, w, h, name1)){
		tmp = ReadnewData(tmp,value,date);
		count++;
//		InitConsole();
//		printf("%.5lf %s %d\n",value,tmp->date,count);
		data[0] = '\0';
		date[0] = '\0';
	}
	char name2[128]; sprintf(name2, "�ύ");
	if(button(GenUIID(0), x , y - 6.5*h, w, h, name2)){
		tmp = ReadnewData(tmp,value,date);
		data[0] = '\0';
		date[0] = '\0';
		count = 0;
		adddata = 0;
		menu = 1;
	} 
	//y = winheight/2;
//	if( textbox(GenUIID(0),x,y-=h*1.8,w,h,numstr,sizeof(numstr)) )
//	{
//		double value; sscanf(numstr,"%lf",&value);
//		sprintf(newnum,"Represented value is: %.20f", value);
//	}
//	SetPenColor("Gray"); 
//	drawLabel(x,y-=fH*1.2, newnum);
}

