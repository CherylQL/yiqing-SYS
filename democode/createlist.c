#include "import.h"


//创建链表 
Pnode Insert(Pnode head,Pnode num){
	if(head==NULL){
		return num;
	}
	Pnode p = head;
	while(p->next){
		p = p->next;
	}
	p->next = num;
	return head;
} 
Pnode Createlist(){
	Pnode head = NULL,p;
	int count = 1;
	while(1){
		p = (Pnode)malloc(sizeof(struct node));
		printf("请输入data%d：",count); 
		scanf("%lf",&p->data);
		if(p->data==-1){
			break;
		}
		printf("请输入date%d：",count); 
		scanf("%s",&p->date[0]);
		count++;
		p->next=NULL;
		head = Insert(head,p);
	}
	return head;
}

//计算链表长度 
int countnum(Pnode head,double* max,double* min){
	int count = 0;
	if(head == NULL)return 0;
//	printf("%d",head->data);
	*max = head->data;
	*min = head->data;
	Pnode p = head;
	while(p){
		if(p->data>*max)*max = p->data;
		if(p->data<*min)*min = p->data;
		p = p->next;
		count++;
	}
//	printf("%lf %lf\n",*max,*min);
	return count;
}

//计算data总和
double getsum(Pnode head){
	if(head==NULL)return 0;
	Pnode p = head;
	double sum = 0;
	while(p){
//		printf("%lf\n",p->data);
		sum = sum+p->data;
		p = p->next;
	}
	return sum;
} 



/*外部读入数据*/
 Pnode Readlist(int j)       /*i是城市编号，简单点可以是对应的城市按钮序号*/
 {
 	int i,totalnumber,addnumber,month,day;
 	double data;
 	string date[20];
		Pnode head,p,tail;
		head=(Pnode)malloc(sizeof(struct node));
		head->next=NULL;
		tail=head;
		FILE *fp;             
		
		switch(j) /*加入相应的地址*/ 
		{
			case 1:
	    		if ( (fp = fopen("E:\\1.txt", "rt")) == NULL ) /*判断文件是否正确打开*/ 
        		puts("Fail to open file!");
        		exit(0);
        		break;
			case 2:
	    		if ( (fp = fopen("E:\\3.txt", "rt")) == NULL ) 
        	   {
				puts("Fail to open file!");
        		exit(0);
				}
        		break;
			case 3:
	    		if ( (fp = fopen("E:\\3.txt", "rt")) == NULL ) 
        	   {
				puts("Fail to open file!");
        		exit(0);
				}
				break;
			case 4:
	    		if ( (fp = fopen("E:\\3.txt", "rt")) == NULL ) 
        	   {
				puts("Fail to open file!");
        		exit(0);
				}
				break;
			default :break;									        	
    }
    
 
    while(2==fscanf(fp,"%lf%s",&data,&date[0]))
		{
		p=(Pnode)malloc(sizeof(struct node));
		p->data=data;
		strcpy(p->date,date);
		tail->next=p;
		tail=p;	
		}
		tail->next=NULL;
		return head->next;                    /*返回无节点的链表*/ 
	if(fclose(fp))   /*判断文件是否正确关闭*/ 
	{
		"关闭失败"; 
	}
  } 

/*删除某个结点的数据             此节点已存在*/
Pnode del(Pnode head,string date)
  {
  	Pnode pre,tail;
  	pre=head;
  	if(strcmp(pre->date,date) == 0)
  	{
  		return head->next;
	  }
	  else
	  {
	  
	tail=pre->next;
	while( 1 )
	{
		if( strcmp(tail->date,date) == 0)
		break;
		pre=pre->next;
		tail=tail->next;
	}
	pre->next=tail->next;
	return head;
	}
  	
}


Pnode add(Pnode head)
{
	Pnode p,tail;
	int count=1;
	tail=head;
	while(tail->next)
	{
		tail=tail->next;
	}
	
	while(1){
		p = (Pnode)malloc(sizeof(struct node));
		printf("请输入data%d：",count); 
		scanf("%lf",&p->data);
		if(p->data==-1){
			break;
		}
		printf("请输入date%d：",count); 
		scanf("%s",&p->date[0]);
		count++;
		tail->next=p;
		tail=tail->next;
	}
	
	tail->next=NULL;
	return head;
 } 


  /*实现未来的数据预测*/
   Pnode predict(Pnode head ,  int yixue , int liudongxing)
   {                              /*yixue  两个选项   优良/较差  输入为 0/1    liudongxing 1-9 */
   	int i=1,count=0,day=0;
   	double k1,k2,k3,xishu;
   	Pnode p=head,new=head,newnode;
      	while(new->next)            /*数一下链表中有多少个数据*/
   	    {
   		count++;
   		new=new->next;
	    }            /*最终指向最后一个结点*/
	    while(i!=count-2)
	    {
	   	p=p->next;
	   	i++;
	    }
   	for(;day<30;day++)
   	{
   		if(day==0)                                               /*增长率计算*/
	    {		   
   	     	k1=p->next->data  -   p->data;
   		    k2=p->next->next->data  -  p->next->data;
   	    }
		else  
   		{
   			k1=k2;
   			k2=p->next->next->data -  p->next->data;
		}
		   
		   p=p->next;
		   
		   
		   
		     /*系数处理*/ 
		if(yixue==0)  /*优良*/ 
		{
			xishu=2.0*liudongxing*1.0/9.0;
		}
		else
		{
			xishu=3.0*liudongxing*1.0/9.0;
		}
		if(k2<0)
   		k3=(k2+(k2-k1)*xishu > 0) ?(k2+(k2-k1)*xishu)*(-1) : k2+(k2-k1)*xishu;
   		else
   		k3=k2+(k2-k1)*xishu;
   		
   		
   		
   		newnode=(Pnode )malloc(sizeof(struct node));              /*创建新节点  录入 月 日 患者情况*/
   		if(p->next->next->data==0)
	    newnode->data=0;
	    else
	   	newnode->data=(p->next->next->data + k3  > 0) ? p->next->next->data + k3 : 0 ;
   		
   		
   		
   		if(day==0) 
   		strcpy(newnode->date,"预测");
   		else
		strcpy(newnode->date,"");    
   	//	if((new->date[0])%2==1||new->date[0]==8)  /*3月  5月 7,8 是大月  后面的不考虑了*/
   	/*	 {
   		 	if(new->day<31)
   		 	{
			newnode->month=new->month;
			newnode->day= new->day + 1;
			}
			 
			 else
			 {
			 newnode->month=new->month  + 1;
			newnode->day=1;	
			 }
		}
		else
		{
		if(new->day<30)
   		 	{
			newnode->month=new->month;
			newnode->day= new->day + 1;
			}
			 
			 else
			 {
			 newnode->month=new->month  + 1;
			 newnode->day=1;	
			 }	
		}*/ 
		
		new->next=newnode;
		new=new->next; 
	}
	new->next=NULL;
	return head;
	} 

 
