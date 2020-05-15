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
// 全局变量
double winwidth, winheight;   // 窗口尺寸
static int    show_more_buttons = 0; // 显示更多按钮
static int    draw_edit=0;
static int    sel1=0;
static int    sel2=0;
int zhexian=0;
int yidong=0;
int bingzhuang = 0;
int backtomenu=0;
int zhuzhuang = 0;
int menu = 1;

// 用户的字符事件响应函数
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI字符输入
	display(); //刷新显示
}

// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); // GUI获取键盘
	display(); // 刷新显示
}

// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event)
{
	if(yidong)
		MouseEventProcess1(x,y,button,event); 
	
	uiGetMouse(x,y,button,event); //GUI获取鼠标
	display(); // 刷新显示
}

// 用户主程序入口
// 仅初始化执行一次
void Main() 
{
	// 初始化窗口和图形系统
	SetWindowTitle("疫情数据分析与可视化工具");
	readmatrix();
	//SetWindowSize(10, 10); // 单位 - 英寸
	//SetWindowSize(15, 10);
	//SetWindowSize(10, 20);  // 如果屏幕尺寸不够，则按比例缩小
    InitGraphics();
	// 获得窗口尺寸
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();

	// 注册时间响应函数
	registerCharEvent(CharEventProcess); // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标


	// 打开控制台，方便输出变量信息，便于调试
//	 InitConsole(); 
    display();
	drawbg();
}

#if defined(DEMO_MENU)
// 菜单演示程序
void drawMenu()
{ 
	static char * menuListFile[] = {"文件", 
        "新建  |Ctrl-N",
		"打开  |Ctrl-O", 
		"保存  |Ctrl-S",
        "退出  |Ctrl-E"};
	static char * menuListEdit[] = {"编辑",
		"读入",
		"增加",
		"删除"};
	static char * menuListDraw[] = {"图像",
		"生成图像",
		"图像处理" , 
		"保存"};
    static char * menuListAbout[] = {"帮助",
        "关于本软件",
        "使用方法",
		"music"};
	static char * selectedLabel = NULL;

	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH*1.5; // 控件高度
	double w = TextStringWidth(menuListFile[1]); // 控件宽度
	double wlist = TextStringWidth(menuListAbout[1])*1.2;
	double xindent = winheight/20; // 缩进
	int  selection;
	string jicun[20]; 
	
	// menu bar
	drawMenuBar(0,y-h,winwidth,h);
	// File 菜单
	selection = menuList(GenUIID(0), x, y-h, w, wlist, h, menuListFile, sizeof(menuListFile)/sizeof(menuListFile[0]));
	if( selection>0 ) selectedLabel = menuListFile[selection];
	FILE *fp1;
	if(selection==2){
  //  system("start D：\\hello.txt");
  //  fp1=fopen("D:\\hello.txt","r");
	  tmp=Readlist(2);     /*需要地址*/
	  tmp=predict(tmp,1,9); 
	}
	if(selection==3){
    fclose(fp1);
	}
	if( selection==4 )
		exit(-1); // choose to exit
	
	// 编辑 菜单
	selection = menuList(GenUIID(0),x+w,y-h, w, wlist, h, menuListEdit,sizeof(menuListEdit)/sizeof(menuListEdit[0]));
	if( selection>0 ) selectedLabel = menuListEdit[selection];
    if(selection==1){
    	    InitConsole(); 
    		tmp = Createlist(); /*输入新的链表*/
    }
    if(selection==2)
    {
    	InitConsole();    /* 增加数据*/ 
    	tmp=add(tmp);
	}
    if(selection==3)
    {
    	InitConsole();       /* 删除某个数据*/ 
    	scanf("%s",&jicun);
    	
    	tmp=del(tmp,jicun);
    	
	}
    //菜单标题
    if(!zhexian&&!zhuzhuang&&!bingzhuang){
	    drawLabel(winwidth*3/8,winheight*3/4, "疫情数据分析与可视化工具"); 
	}
	//图像菜单 
    menuListDraw[1] = show_more_buttons ? "数据可视化 | Ctrl-T" : "数据可视化 | Ctrl-T";
    menuListDraw[2] = draw_edit ? "图像处理" : "图像处理";
	selection = menuList(GenUIID(0),x+2*w,y-h, w, wlist, h, menuListDraw,sizeof(menuListDraw)/sizeof(menuListDraw[0]));
	if( selection>0 ) selectedLabel = menuListDraw[selection]; 
	if( selection==1 )
	show_more_buttons = ! show_more_buttons;
	if( selection==2 )
	draw_edit = ! draw_edit;

	// 帮助 菜单
	selection = menuList(GenUIID(0),x+3*w,y-h, w, wlist, h, menuListAbout,sizeof(menuListAbout)/sizeof(menuListAbout[0]));
	if( selection>0 ) selectedLabel = menuListAbout[selection];
        if( selection==1) {
        	sel1=!sel1;
		
        } 
        if(sel1)
            drawBox(winwidth/2.5+winwidth/6,winheight/4,winwidth/3,winheight/8,0,"关于本软件：",'L',"Blue");
        if( selection==2) {
        sel2=!sel2;
		}
		if(sel2)
        drawBox(winwidth/2.5+winwidth/6,winheight/8,winwidth/3,winheight/8,0,"使用方法：",'L',"Blue");
      
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
		// 显示菜单运行结果
		x = winwidth/2;
		y = winheight/8;
		SetPenColor("Blue");
		drawLabel(x*7/8,y-=h, "实时状态:");
		SetPenColor("Red");
		drawLabel(x+xindent,y, selectedLabel);	
	}
}
#endif // #if defined(DEMO_MENU)



#if defined(DEMO_BUTTON)
// 按钮演示程序
void drawButtons()
{
	double fH = GetFontHeight();
	double h = fH*2;  // 控件高度
	double x = winwidth/2.5;  
	double y = winheight/6*3-h; 
	double w = winwidth/6; // 控件宽度
	if (button(GenUIID(0), x, y, w, h, show_more_buttons ? "可视化模型" : "可视化模型"))
		show_more_buttons = ! show_more_buttons;
	
//	char name6[128]; sprintf(name6, "清空当前数据");
//	if(button(GenUIID(0), x , y - h*4, w, h, name6)) {
//		tmp = NULL;
//	}
	
	if( show_more_buttons ) {
		char name1[128]; sprintf(name1, "折线图");
		char name2[128]; sprintf(name2, "柱状图");
		char name3[128]; sprintf(name3, "饼状图");

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
	double h = fH*2;  // 控件高度
	double x = winwidth/2.5;  
	double y = winheight/6*3-h; 
	double w = winwidth/6; // 控件宽度
	
	char name4[128];sprintf(name4, "返回菜单");
//	char name5[128];sprintf(name5, "停止选择");	
//	Pnode selectdot;
	// 清屏
	DisplayClear();
	drawbg();
	if(menu){
		yidong = 0;
		// 绘制和处理菜单
		drawMenu();
		// 按钮
		drawButtons();	
	}
	
	//折线图 
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
	
	//柱状图
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
	
	
	//饼状图 
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

