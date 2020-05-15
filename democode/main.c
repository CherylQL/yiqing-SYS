#include "import.h"

#define R  2.0
#define Ox winwidth*3/4
#define Oy winwidth/3 

typedef MCIERROR WINAPI (*PLAYSOUND)(LPCSTR, HMODULE,DWORD);




double max;
double min;
double dx = 2.5; 
double dy = 2.5;

bool isSelected = FALSE; 
bool isMove = FALSE; 
// ȫ�ֱ���
double winwidth, winheight;   // ���ڳߴ�
static int    show_more_buttons = 0; // ��ʾ���ఴť
static int    draw_edit=0;
static int    sel1=0;
static int    sel2=0;
int zhexian=0;
int yidong=0;
int bingzhuang = 0;
int backtomenu=0;
int zhuzhuang = 0;
int menu = 1;

// �û����ַ��¼���Ӧ����
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI�ַ�����
	display(); //ˢ����ʾ
}

// �û��ļ����¼���Ӧ����
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); // GUI��ȡ����
	display(); // ˢ����ʾ
}

// �û�������¼���Ӧ����
void MouseEventProcess(int x, int y, int button, int event)
{
	if(yidong)
		MouseEventProcess1(x,y,button,event); 
	
	uiGetMouse(x,y,button,event); //GUI��ȡ���
	display(); // ˢ����ʾ
}

// �û����������
// ����ʼ��ִ��һ��
void Main() 
{
	// ��ʼ�����ں�ͼ��ϵͳ
	SetWindowTitle("�������ݷ�������ӻ�����");
	readmatrix();
	//SetWindowSize(10, 10); // ��λ - Ӣ��
	//SetWindowSize(15, 10);
	//SetWindowSize(10, 20);  // �����Ļ�ߴ粻�����򰴱�����С
    InitGraphics();
	// ��ô��ڳߴ�
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();

	// ע��ʱ����Ӧ����
	registerCharEvent(CharEventProcess); // �ַ�
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���


	// �򿪿���̨���������������Ϣ�����ڵ���
//	 InitConsole(); 
    display();
	drawbg();
}

#if defined(DEMO_MENU)
// �˵���ʾ����
void drawMenu()
{ 
	static char * menuListFile[] = {"�ļ�", 
        "�½�  |Ctrl-N",
		"��  |Ctrl-O", 
		"����  |Ctrl-S",
        "�˳�  |Ctrl-E"};
	static char * menuListEdit[] = {"�༭",
		"����",
		"����",
		"ɾ��"};
	static char * menuListDraw[] = {"ͼ��",
		"����ͼ��",
		"ͼ����" , 
		"����"};
    static char * menuListAbout[] = {"����",
        "���ڱ����",
        "ʹ�÷���",
		"music"};
	static char * selectedLabel = NULL;

	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH*1.5; // �ؼ��߶�
	double w = TextStringWidth(menuListFile[1]); // �ؼ����
	double wlist = TextStringWidth(menuListAbout[1])*1.2;
	double xindent = winheight/20; // ����
	int  selection;
	string jicun[20]; 
	
	// menu bar
	drawMenuBar(0,y-h,winwidth,h);
	// File �˵�
	selection = menuList(GenUIID(0), x, y-h, w, wlist, h, menuListFile, sizeof(menuListFile)/sizeof(menuListFile[0]));
	if( selection>0 ) selectedLabel = menuListFile[selection];
	FILE *fp1;
	if(selection==2){
  //  system("start D��\\hello.txt");
  //  fp1=fopen("D:\\hello.txt","r");
	  tmp=Readlist(2);     /*��Ҫ��ַ*/
	  tmp=predict(tmp,1,9); 
	}
	if(selection==3){
    fclose(fp1);
	}
	if( selection==4 )
		exit(-1); // choose to exit
	
	// �༭ �˵�
	selection = menuList(GenUIID(0),x+w,y-h, w, wlist, h, menuListEdit,sizeof(menuListEdit)/sizeof(menuListEdit[0]));
	if( selection>0 ) selectedLabel = menuListEdit[selection];
    if(selection==1){
    	    InitConsole(); 
    		tmp = Createlist(); /*�����µ�����*/
    }
    if(selection==2)
    {
    	InitConsole();    /* ��������*/ 
    	tmp=add(tmp);
	}
    if(selection==3)
    {
    	InitConsole();       /* ɾ��ĳ������*/ 
    	scanf("%s",&jicun);
    	
    	tmp=del(tmp,jicun);
    	
	}
    //�˵�����
    if(!zhexian&&!zhuzhuang&&!bingzhuang){
	    drawLabel(winwidth*3/8,winheight*3/4, "�������ݷ�������ӻ�����"); 
	}
	//ͼ��˵� 
    menuListDraw[1] = show_more_buttons ? "���ݿ��ӻ� | Ctrl-T" : "���ݿ��ӻ� | Ctrl-T";
    menuListDraw[2] = draw_edit ? "ͼ����" : "ͼ����";
	selection = menuList(GenUIID(0),x+2*w,y-h, w, wlist, h, menuListDraw,sizeof(menuListDraw)/sizeof(menuListDraw[0]));
	if( selection>0 ) selectedLabel = menuListDraw[selection]; 
	if( selection==1 )
	show_more_buttons = ! show_more_buttons;
	if( selection==2 )
	draw_edit = ! draw_edit;

	// ���� �˵�
	selection = menuList(GenUIID(0),x+3*w,y-h, w, wlist, h, menuListAbout,sizeof(menuListAbout)/sizeof(menuListAbout[0]));
	if( selection>0 ) selectedLabel = menuListAbout[selection];
        if( selection==1) {
        	sel1=!sel1;
		
        } 
        if(sel1)
            drawBox(winwidth/2.5+winwidth/6,winheight/4,winwidth/3,winheight/8,0,"���ڱ������",'L',"Blue");
        if( selection==2) {
        sel2=!sel2;
		}
		if(sel2)
        drawBox(winwidth/2.5+winwidth/6,winheight/8,winwidth/3,winheight/8,0,"ʹ�÷�����",'L',"Blue");
      
    if( selection==3 ){
    	HMODULE hLib;
        hLib = LoadLibrary("Winmm.dll");
        if (hLib == 0)
        return 1;
        PLAYSOUND PlaySound = (PLAYSOUND)GetProcAddress(hLib, "PlaySound");
        if (PlaySound == 0)
        return 2;
        PlaySound("D:music.wav", 0, SND_ASYNC|SND_LOOP);
        system("pause");
        PlaySound(NULL, 0, SND_PURGE);
        FreeLibrary(hLib);
	} 
	
	if(!zhexian&&!zhuzhuang&&!bingzhuang){
		// ��ʾ�˵����н��
		x = winwidth/2;
		y = winheight/8;
		SetPenColor("Blue");
		drawLabel(x*7/8,y-=h, "ʵʱ״̬:");
		SetPenColor("Red");
		drawLabel(x+xindent,y, selectedLabel);	
	}
}
#endif // #if defined(DEMO_MENU)



#if defined(DEMO_BUTTON)
// ��ť��ʾ����
void drawButtons()
{
	double fH = GetFontHeight();
	double h = fH*2;  // �ؼ��߶�
	double x = winwidth/2.5;  
	double y = winheight/6*3-h; 
	double w = winwidth/6; // �ؼ����
	if (button(GenUIID(0), x, y, w, h, show_more_buttons ? "���ӻ�ģ��" : "���ӻ�ģ��"))
		show_more_buttons = ! show_more_buttons;
	
//	char name6[128]; sprintf(name6, "��յ�ǰ����");
//	if(button(GenUIID(0), x , y - h*4, w, h, name6)) {
//		tmp = NULL;
//	}
	
	if( show_more_buttons ) {
		char name1[128]; sprintf(name1, "����ͼ");
		char name2[128]; sprintf(name2, "��״ͼ");
		char name3[128]; sprintf(name3, "��״ͼ");

	   if(button(GenUIID(0), x + w*1.2, y , w, h, name1)){
	   		zhexian= 1;
	   		menu = 0;
	   		isSelected = FALSE;
	    }else if(button(GenUIID(0), x + w*1.2, y - h*2, w, h, name2)){
			zhuzhuang = 1;
			menu = 0;
			isSelected = FALSE;
//			yidong = 1;
		}else if(button(GenUIID(0), x + w*1.2, y - h*4, w, h, name3)){
			bingzhuang = 1;
			menu = 0;
		}
	}
	

}
#endif // #if defined(DEMO_BUTTON)



void display()
{
	double fH = GetFontHeight();
	double h = fH*2;  // �ؼ��߶�
	double x = winwidth/2.5;  
	double y = winheight/6*3-h; 
	double w = winwidth/6; // �ؼ����
	
	char name4[128];sprintf(name4, "���ز˵�");
//	char name5[128];sprintf(name5, "ֹͣѡ��");	
//	Pnode selectdot;
	// ����
	DisplayClear();
	drawbg();
	if(menu){
		yidong = 0;
		// ���ƺʹ���˵�
		drawMenu();
		// ��ť
		drawButtons();	
	}
	
	//����ͼ 
	if(zhexian){
		DisplayClear();
		drawbg();	 
		drawMenu();
		int count;
//	        double max;double min;	
		if(tmp==NULL){
			DrawCoor(dx,dy);
		}else{
			yidong = 1;
			line = tmp;
        	count = countnum(line,&max,&min);
      		DrawCoor(dx,dy); 
     		DrawLinear(line,count,&max,&min);	
		}
		
     	if(button(GenUIID(0), winwidth/15, 2*y , w, h, name4)){
			isSelected = FALSE;
			zhexian = 0;
			menu = 1;
		};
	}
	
	//��״ͼ
	if(zhuzhuang){
		DisplayClear();	 
		drawbg();
		drawMenu(); 
		int count;
//	        double max;double min;	
        if(tmp==NULL){
        	DrawCoor(dx,dy); 
		}else{
			yidong = 1;
			square = tmp;
        	count = countnum(square,&max,&min);
      		DrawCoor(dx,dy); 
     		DrawSquare(square,count,&max,&min);	
		}
		if(button(GenUIID(0), winwidth/15, 2*y , w, h, name4)){
//			yidong = !yidong;
			isSelected = FALSE;
			zhuzhuang = 0;
			menu = 1;
		};
//		if(button(GenUIID(0), winwidth/15, y , w, h, name5)){
//			yidong = !yidong;
//			if(yidong){
//				isSelected = FALSE;
//				zhuzhuang = 0;
//				menu = 1;
//			}
//		};
	} 
	
	
	//��״ͼ 
	if(bingzhuang){
		DisplayClear();
		drawbg();
		drawMenu();
		int count;
		double sum;
		if(tmp==NULL){
			MovePen(Ox, Oy);
			DrawEllipticalArc(R, R, 0.0, 360.0);
		}else{
			circle = tmp;
			sum = getsum(circle);
			count = countnum(circle,&max,&min);
			printf("%d %lf\n",count,sum);
			DrawCircle(circle,count,sum);	
		}
		
		if(button(GenUIID(0), winwidth/15, y , w, h, name4)){
			bingzhuang = 0;
			menu = 1;
		};
	}
	
	if(isSelected){
		if(zhexian){
			Lighten(currentdot);	
		}else if(zhuzhuang){
			LightenSquare(currentdot);
		}
	}

}

