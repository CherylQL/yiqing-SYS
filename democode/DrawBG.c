#ifndef _LIB_GRAPHICS

#include "import.h"

#include "imgui.h"

#define _LIB_GRAPHICS
#endif


extern double winwidth, winheight;   // ´°¿Ú³ß´ç 

char color[13][11]={"black","Dark Gray","Gray","Light Gray","Brown","Orange","Yellow","Violet","Magenta","Cyan","blue","red","green"};
double X,Y;
int eagle[63][79];
int zjulogo[44][167];
double Size;


void FillBackgound()
{
	MovePen(ScaleXInches(0),ScaleYInches(0));
	SetPenColor("BackGround");
	StartFilledRegion(1);
    DrawLine(winwidth,0);
    DrawLine(0,-winheight);
    DrawLine(-winwidth,0);
    DrawLine(0,winheight);
    EndFilledRegion();
	
}

void bgdisplay()
{
	// ÇåÆÁ
//	DisplayClear();
	FillBackgound();
	Animation();
}


void DrawSolidCube(double x, double y, double l)
{
	SetPenColor("Eagle");
    MovePen(x,y);
//    StartFilledRegion(1);
//    DrawLine(l,0);
//    DrawLine(0,-l);
//    DrawLine(-l,l);
    DrawLine(l,l);
//	DrawArc(l,0,360);
//    fillRound(x,y,l);
//    EndFilledRegion();
}

void DrawEagle(int a[][79], double x, double y, double size)
{
	double m=x,n=y;
	MovePen(m,n);
	int i,j;
	for(i=0;i<63;i++){
		for(j=0;j<79;j++){
//			printf("%d",a[i][j]); 
			if(a[i][j] == 1){
				DrawSolidCube(m,n,size);
				
			}
				
				m +=size;
		}
		
		m = x;
		n-=size;
	}
}

void DrawLogo(int b[][167], double x, double y, double size)
{
	double m=x,n=y;
	MovePen(m,n);
	int i,j;
	for(i=0;i<44;i++){
		for(j=0;j<167;j++){
			if(b[i][j] == 1)
				DrawSolidCube(m,n,size/3);
				m +=size/3;
		}
		m = x;
		n-=size/3;
	}
}

void Animation()
{
	DrawEagle(eagle, X, Y, Size);
	DrawLogo(zjulogo, X+ScaleXInches(55), Y-4, Size);
}

//int eagle[63][79];
//int zjulogo[44][167];

void readmatrix()
{
	FILE *fp=fopen("./eagle.txt","r+");
	int i,j;
	for(i=0;i<63;i++){
		for(j=0;j<79;j++){
			fscanf(fp,"%d",&eagle[i][j]);
//			printf("%d ",eagle[i][j]);
		}
//		printf("\n");
	}	
//	for(i=0;i<63;i++){
//		for(j=0;j<79;j++){
//			A[i][j]=a[i][j];
//		}
//	}	
	fclose(fp);
	
	fp=fopen("./ZJU.txt","r+");

	for(i=0;i<44;i++){
		for(j=0;j<167;j++){
			fscanf(fp,"%d",&zjulogo[i][j]);
//			printf("%d ",zjulogo[i][j]);
		}
//		printf("\n");
	}	
//	for(i=0;i<44;i++){
//		for(j=0;j<167;j++){
//			B[i][j]=b[i][j];
//		}
//	}
	fclose(fp);
}

void drawbg()
{
//	InitGraphics();
//	SetPenColor("black");
//	SetWindowSize(WindowX,WindowY);
//	SetPenSize(1);
//	registerTimerEvent(TimerEventProcess); 
	//InitConsole();
	
	DefineColor("Eagle",85/255.0,165/255.0,221/255.0);
	DefineColor("BackGround",248/255.0,246/255.0,242/255.0);
	double size=ScaleXInches(5);
	Size=size;	
	MovePen(0,0);
	X=ScaleXInches(250);
	Y=ScaleYInches(100);
//	startTimer(MY_ROTATE_TIMER, 50);
	bgdisplay();
	SetPenColor("black");
}

