#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define MAXSIZE 5

/*管理员结构体*/
typedef struct {
char guanliyuanbianhao[20];        /*管理员编号*/
char guanliyuanmima[20];        /*管理员的密码*/
char xing[20];      /*管理员的姓*/
char ming[20];      /*管理员的名*/
char xingbie[10];         /*管理员的性别*/
char lianxifangshi[20];      /*管理员联系方式*/
}guanliyuan;
guanliyuan gly;

/*已注册用户链表的结构*/
typedef struct yonghunode{
char zhanghao[20];        /*用户的账号*/
char mima[20];            /*用户的密码*/
char yonghuxing[20];      /*用户的姓*/
char yonghuming[20];      /*用户的名*/
char xingbie[10];         /*用户的性别*/
char zhengjianleixing[20];   /*证件类型*/
char zhengjianhao[20];       /*证件号*/
char lianxifangshi[20];      /*用户联系方式*/
struct yonghunode *next;
}lyhnode,*pyhnode,*linklistyh;
linklistyh yh;


/*客户信息链表的结构*/
typedef struct man{
char man_time[20];        /*订票时间*/
char man_trainnum[20];    /*车次编号*/
char man_name[20];        /*订票人姓名*/
char phone[20];           /*订票人联系方式*/
char ic[20];              /*证件号*/
char order_num[30];       /*订单号*/
char man_start[20];           /*起点站*/
char man_arrive[20];          /*终点站*/
int man_box[20];              /*车厢号*/   
int man_table[20];            /*座位号*/
double man_count[20];         /*票价的折扣*/
int money;                /*票价*/
int amount;               /*订票数*/
struct man *next;
}manlinklist,*pman,*linklistman; 

/*车票信息链表的结构*/
typedef struct tickets{
int tickets_num;          /*车票编号*/
int tickets_box;          /*车厢号*/
int tickets_table;        /*座位号*/
double count;              /*票价折扣*/  
struct tickets *next;
}ticketslinklist,*ptickets,*linklisttickets;


/*站点的结构*/
typedef struct station{
char sta_name[20];        /*车站名称*/ 
char arrivetime[20];      /*到站时间*/
char starttime[20];       /*出站时间*/
int sta_money;            /*从起点到该站的票价*/
int mileage;              /*里程*/
     
}stationlinklist;

/*车次信息的结构*/
typedef struct train{
char train_num[20];               /*车次编号*/
char train_starttime[20];         /*出发时间*/
char train_start[20];             /*出发站*/
char train_arrive[20];            /*终点站*/
char train_arrivetime[20];        /*到达时间*/ 
int  train_box;                   /*车厢数*/
int  train_table;                 /*每节车厢座位数*/
int  train_tickets;               /*剩余票数*/ 
int  train_mileage;               /*起点到终点的距离*/ 
stationlinklist station[5];          /*站点结构体*/
linklistman h_man;                /*客户信息域,指向客户信息链表的头指针*/
linklisttickets h_tickets;        /*车票信息域,指向车票信息链表的头指针*/

}traininfo;

traininfo trin[MAXSIZE];          /*定义一个有MAXSIZE个元素的结构体数组*/

/********************************************************************************************************************************/

void mainmenu();                      /*火车票管理系统主菜单*/ 
                 
void searchmenu();                    /*查询信息的子菜单*/

int guanliyuan1();               /*初始化管理员结构体*/

void guanliyuadenglu();          /*管理员登录*/

int yonghuinitlist();     /*初始化已注册客户信息链表*/

void zhuceyonghu(linklistyh h);        /*新用户注册函数*/

void bianliyonghu();          /*遍历注册用户链表*/

void yonghudenglu(linklistyh h);      /*用户登录*/

void zhucezhinan();                   /*新用户注册指南*/

int maninitlist(linklistman *h);      /*初始化客户信息链表*/

int manlistinsert(linklistman h);      /*客户信息插入*/

int ticketsinitlist(linklisttickets *h);  /*车票信息链表的初始化*/

int ticketslistinsert(linklisttickets h,int tickets_num,int tickets_box,int tickets_table,double count);  /*车票信息链表的插入*/

void traverselisttickets(linklisttickets h);   /*遍历车票信息链表*/

void save();     /*信息保存函数*/

void createtraininfo();    /*火车票信息录入*/

int showmessage();     /*显示载入车次信息的原始数据*/

int showmessage1();    /*载入车次信息数据*/

void createtickets();    /*载入车票信息数据*/

void searchbynumber();    /*按车次编号查询*/

void searchbyaddress();    /*按终点站查询*/

void traversemanlinklist();    /*客户信息链表遍历*/

void pointhead();          /*初始化单链表并用车次信息结构中的客户信息域,指向客户信息链表的头指针*/

void reservemenu();           /*订票系统的主菜单*/

void traverselistticketsadd(linklisttickets h,int box,int table);    /*遍历票价单链表并删除相应结点*/

void reservebynumber();         /*按车次订票函数*/

void returnticketsmenu();           /*退票系统的主菜单*/

void traverselistmanadd(linklistman h,char man_name[20],char ic[20]);       /*遍历乘客信息表并删除相应结点*/

void traversemanlinklistadd2(linklistman h,char man_name[20],char ic[20]);   /*客户信息链表遍历找到相应的相应的乘客并输出该乘客信息*/

void returntickets();           /*退票函数*/
/********************************************************************************************************************************/

/*系统主菜单*/                            
void menu()
{
system("color 1f");           /*使面呈蓝色*/
system("mode con: cols=150 lines=1000");   /*调整大小*/
int choice;
printf("\n欢迎您进入系统主菜单\n");
printf("\n日期: 2015/6/20\n\n");
printf("***********************************************************************************\n\n");
printf("                            1.录入班次信息....................\n\n         ");
printf("                   2.浏览班次信息....................\n\n         ");
printf("                   3.用户登录........................\n\n         ");
printf("                   4.注册新用户......................\n\n         ");
printf("                   5.注册指南........................\n\n        ");
printf("                    6.管理员登录........................\n\n        ");
printf("                    7.退出系统..............\n        ");
printf("\n***********************************************************************************\n\n");
printf("请选择您所需要的功能:(1,2,3,4,5,6)\n");
scanf("%d",&choice);
switch(choice)
{
case 1:
	{
       showmessage1();         /*载入数据的函数*/
	   createtickets();        /*初始化车票信息*/
       pointhead();            /*初始化客户信息链表*/
	   yonghuinitlist();       /*初始化已注册客户信息链表*/
	   guanliyuan1();          /*初始化管理员信息*/
	   printf("\n按任意键返回系统主菜单\n");
	   getch();
	   menu();
	}
	 break;

case 2:
	{
      system("cls"); 
	  showmessage();          /*显示所有车次信息*/
      printf("\n按任意键返回系统主菜单\n");
      getch();
	  menu();
	}
	 break;
case 3:
	{
      yonghudenglu(yh);          /*用户登录*/
	  printf("\n按任意键返回系统主菜单\n");
      getch();
	  menu();
	}
	  break;
case 4:
	{
      zhuceyonghu(yh);            /*注册信息*/
	 
	}
	  break;
case 5:
	{
      zhucezhinan();            /*新用户注册指南*/
	  printf("\n按任意键返回系统主菜单\n");
      getch();
	  menu();
	}
	  break;
case 6:
	{
			 system("cls"); 
       guanliyuadenglu();            /*管理员登录*/
	  printf("\n按任意键返回系统主菜单\n");
      getch();
	  menu();
	}
	  break;
case 7:
	 system("cls"); 
	 printf("\n\n\n\n\n----------------------------感谢您使用本系统,欢迎您再次使用!----------------------------\n\n\n\n\n\n\n\n");
	 exit(0);
	break;
default:
	{
		printf("输入错误!!请确保您的输入为:(1,2,3,4,5,6)\n");
        printf("\n按任意键返回系统主菜单\n");
        getch();
	    menu();
	}
	break;
}       
}

/*管理员登录主菜单*/                            
void guanlimenu()
{
system("color 1f");           /*使面呈蓝色*/
system("mode con: cols=150 lines=1000");   /*调整大小*/
int choice;
printf("\n欢迎您进入管理员主菜单\n");
printf("\n日期: 2015/6/20\n\n");
printf("***********************************************************************************\n\n");
printf("                            1.浏览订票信息....................\n\n         ");
printf("                   2.浏览注册信息....................\n\n         ");

printf("                   3.返回系统主菜单..............\n        ");
printf("\n***********************************************************************************\n\n");
printf("请选择您所需要的功能:(1,2,3)\n");
scanf("%d",&choice);
switch(choice)
{
case 1:
	{
       traversemanlinklist();          /*管理员查看订票信息*/
	   printf("\n按任意键返回系统主菜单\n");
	   getch();
	   menu();
	}
	 break;

case 2:
	{
		 system("cls"); 
	 bianliyonghu();      /*浏览注册信息*/
      printf("\n按任意键返回系统主菜单\n");
      getch();
	  menu();
	}
	 break;




case 3:
	{
		 printf("\n按任意键返回系统主菜单\n");
        getch();
	    menu();
	}
	 
	break;
default:
	{
		printf("输入错误!!请确保您的输入为:(1,2,3,4,5,6)\n");
        printf("\n按任意键返回系统主菜单\n");
        getch();
	    menu();
	}
	break;
}       
}

 /*火车票管理系统主菜单*/                            
void mainmenu()
{
system("color 1f");           /*使面呈蓝色*/
system("mode con: cols=150 lines=1000");   /*调整大小*/
int choice;
printf("\n欢迎您进入火车票订票系统主菜单\n");
printf("\n日期: 2015/6/20\n\n");
printf("***********************************************************************************\n\n");
printf("                            1.浏览班次信息....................\n\n         ");
printf("                   2.查询行车路线....................\n\n         ");
printf("                   3.售票系统........................\n\n         ");
printf("                   4.退票系统........................\n\n        ");
printf("                    5.退出火车票管理系统..............\n        ");
printf("\n***********************************************************************************\n\n");
printf("请选择您所需要的功能:(1,2,3,4,5)\n");
scanf("%d",&choice);
switch(choice)
{


case 1:
	{
	  showmessage();          /*显示所有车次信息*/
      printf("\n按任意键返回主菜单\n");
      getch();
	  mainmenu();
	}
	 break;
case 2:
	{
      searchmenu();           /*进入查询子菜单*/
	  printf("\n按任意键返回主菜单\n");
      getch();
	  mainmenu();
	}
	  break;
case 3:
	{
      reservemenu();            /*进入订票系统主菜单*/
	  printf("\n按任意键返回主菜单\n");
      getch();
	  mainmenu();
	}
	  break;
case 4:
	{
      returnticketsmenu();            /*进入订票系统主菜单*/
	  printf("\n按任意键返回主菜单\n");
      getch();
	  mainmenu();
	}
	  break;
case 5:
	{
      
	  printf("\n按任意键返回系统主菜单\n");
      getch();
	  menu();
	}
	  break;

default:
	{
		printf("输入错误!!请确保您的输入为:(1,2,3,4,5)\n");
        printf("\n按任意键返回主菜单\n");
        getch();
	    mainmenu();
	}
	break;
}       
}

/*初始化管理员结构体*/
int guanliyuan1()
{
strcpy(gly.guanliyuanbianhao,"9527");
strcpy(gly.guanliyuanmima,"s13384964093");
strcpy(gly.xing,"石");
strcpy(gly.ming,"豪");
strcpy(gly.xingbie,"男");
strcpy(gly.lianxifangshi,"13384964093");
return 0;
}
 
/*管理员登录*/
void guanliyuadenglu()
{
char guanliyuanbianhao[20];        /*管理员编号*/
char guanliyuanmima[20];        /*管理员的密码*/
char xing[20];      /*管理员的姓*/
char ming[20];      /*管理员的名*/
char xingbie[10];         /*管理员的性别*/

	printf("\n请输入您的编号:\n\n");
    scanf("%s",guanliyuanbianhao);
	printf("\n请输入您的密码:\n\n");
    scanf("%s",guanliyuanmima);
	printf("\n请输入您的姓氏:\n\n");
    scanf("%s",xing);
	printf("\n请输入您的名:\n\n");
    scanf("%s",ming);
	printf("\n请输入您的性别:\n\n");
    scanf("%s",xingbie);

if(strcmp(gly.guanliyuanbianhao,guanliyuanbianhao)==0&&strcmp(gly.guanliyuanmima,guanliyuanmima)==0&&strcmp(gly.xing,xing)==0&&strcmp(gly.ming,ming)==0&&strcmp(gly.xingbie,xingbie)==0)
{
	printf("\n登录成功!按任意键进入管理系统主页面\n\n");
	getchar();
	getchar();
    guanlimenu();
}


else 
     {

	printf("\n\n\n\n您输入的管员信息有误!!!!");
	printf("\n登录失败!按任意键返回系统主页面\n\n");
	getchar();
	getchar();
	menu();
     }

}



/*初始化注册用户单链表*/
int yonghuinitlist()
{   
	linklistyh h;
	h=(linklistyh)malloc(sizeof(lyhnode));
	if(!h)
	{
		printf("初始化错误!");
		return 0;
	}
	(h)->next=NULL;
	yh=h;                       /*用yh当做注册客户链表的头结点*/
	return 1;
} 

/*新用户注册函数*/
void zhuceyonghu(linklistyh h)
{
system("color 1f");           /*使面呈蓝色*/
system("mode con: cols=150 lines=1000");   /*调整大小*/
printf("*******************************欢迎您进入用户注册页面*******************************\n\n\n");
pyhnode p=h,q;
int i=0,choice;
char zhanghao[20];        /*用户的账号*/
char mima[20];            /*用户的密码*/
char yonghuxing[20];      /*用户的姓*/
char yonghuming[20];      /*用户的名*/
char xingbie[10];         /*用户的性别*/
char zhengjianleixing[20];   /*证件类型*/
char zhengjianhao[20];       /*证件号*/
char lianxifangshi[20];      /*用户联系方式*/

printf("请输入您要注册的账号(十位数)\n\n");
scanf("%s",zhanghao);
while(p)                                           /*遍历已注册乘客链表,查找是否有重名的*/
{
	if(strcmp(p->zhanghao,zhanghao)==0)
	{
		printf("该账号名已存在,请您重新注册!!\n\n");
       	printf("按任意键返回系统主菜单!!\n\n");
		getchar();
		getchar();
		menu();
	}
	p=p->next;
}
printf("\n请输入您的密码\n\n");
scanf("%s",mima);
printf("\n请输入您的姓氏\n\n");
scanf("%s",yonghuxing);
printf("\n请输入您的名\n\n");
scanf("%s",yonghuming);
printf("\n请输入您的性别\n\n");
scanf("%s",xingbie);
printf("\n请输入您的证件类型\n\n");
scanf("%s",zhengjianleixing);
printf("\n请输入您的证件号\n\n");
scanf("%s",zhengjianhao);
printf("\n请输入您的联系方式\n\n");
scanf("%s",lianxifangshi);

printf("\n\n\n\n请核对您的注册信息:\n");

printf("\n*******************************************************************************************************\n\n");
printf("\n    账号        密码       您的姓    您的名    性别     证件类型      证件号             联系方式\n");
printf("\n%s   %s      %s       %s       %s       %s    %s    %s\n",zhanghao,mima,yonghuxing,yonghuming,xingbie,zhengjianleixing,zhengjianhao,lianxifangshi);
printf("\n*******************************************************************************************************\n\n");
printf("\n是否确定注册:(1-确定,0-取消)\n");
scanf("%d",&choice);

if(choice==0)                    /*如果用户检查出有输入的错误则可以退回主菜单重新注册*/
{
	printf("按任意键返回系统主菜单!!\n\n");
		getchar();
		menu();
}
 
else if(choice==1)		
{ 
	q=(pyhnode)malloc(sizeof(lyhnode));        /*节点信息录入*/

	strcpy(q->zhanghao,zhanghao); 
	strcpy(q->mima,mima);
	strcpy(q->yonghuxing,yonghuxing);
	strcpy(q->yonghuming,yonghuming);
	strcpy(q->xingbie,xingbie);
	strcpy(q->zhengjianleixing,zhengjianleixing);
	strcpy(q->zhengjianhao,zhengjianhao);
	strcpy(q->lianxifangshi,lianxifangshi);
	q->next=h->next;
	
	h->next=q;
}
  if(strcmp(q->xingbie,"男")==0)
printf("\n尊敬的%s先生,您已注册成功!\n",q->yonghuxing);
else  printf("\n尊敬的%s女士,您已注册成功!\n",q->yonghuxing);
 printf("\n按任意键返回系统主菜单\n");
        getch();
	    menu();
}

/*用户登录*/
void yonghudenglu(linklistyh h)
{
system("color 1f");           /*使面呈蓝色*/
system("mode con: cols=150 lines=1000");   /*调整大小*/
printf("*******************************欢迎您进入用户登录页面*******************************\n\n\n");
pyhnode p=h;
int i=0;
char zhanghao[20];        /*用户的账号*/
char mima[20];            /*用户的密码*/
printf("请输入您的账号\n\n");
scanf("%s",zhanghao);
printf("\n请输入您的密码\n\n");
scanf("%s",mima);
  while(p)                      /*遍历注册信息表匹配信息*/
  {
	  if(strcmp(p->zhanghao,zhanghao)==0&&strcmp(p->mima,mima)==0)
	  {
		  if(strcmp(p->xingbie,"男")==0)
		  {
			 
			  printf("\n尊敬的%s先生,您已登录成功!!\n",p->yonghuxing);
              printf("\n按任意键进入订票系统主菜单!!\n");
	          getchar();
			  getchar();
	          mainmenu();
		  }
		  else
		  {
			  printf("\n尊敬的%s女士,您已登录成功!!\n",p->yonghuxing);
              printf("\n按任意键进入订票系统主菜单!!\n");
	          getchar();
			  getchar();
	          mainmenu();
		  }
          i++;
	  }
	  p=p->next;
  }
  if(i==0)
  {
	 printf("\n\n您输入的账号或密码有误!!!请您核实后在登录\n\n");
     printf("按任意键返回系统主菜单!!\n\n");
	 getchar();
	 getchar();
	 menu();
  }
 printf("\n按任意键返回系统主菜单\n");
        getch();
	    menu();
}

/*遍历注册用户链表*/
void bianliyonghu()
{
   pyhnode p=yh->next;
   int i=0,choice;
	while(p)
	{
       printf("\n*******************************************************************************************************\n\n");
printf("\n    账号        密码       您的姓    您的名    性别     证件类型      证件号             联系方式\n");
printf("\n%s   %s      %s       %s       %s       %s    %s    %s\n",p->zhanghao,p->mima,p->yonghuxing,p->yonghuming,p->xingbie,p->zhengjianleixing,p->zhengjianhao,p->lianxifangshi);
printf("\n*******************************************************************************************************\n\n\n\n\n\n\n");
p=p->next;
i++;
	}
	if(i==0)
		printf("\n\n-----------------暂时还没有乘客注册信息-----------------\n\n");
	else
			printf("\n\n-----------------已有%d位客户注册-----------------\n\n",i);
		printf("\n\n\n");
	printf("是否继续查询(1-确定 2-取消)\n");
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("\n\n按任意键返回管理员登录页面\n");
	    getchar();
	    getchar();
    	guanlimenu();
	}
	else 
	{
        printf("\n\n按任意键返回系统主页面\n");
	    getchar();
		getchar();
    	menu();
	}
}

/*新用户注册指南*/
void zhucezhinan()
{
  system("color 1f");           /*使面呈蓝色*/
system("mode con: cols=150 lines=1000");   /*调整大小*/
printf("*******************************欢迎您进入用户注册指南页面*******************************\n\n\n");
	printf("\t\t\t1.进入本系统后点击进入注册新用户选项\n\n");
    printf("\t\t\t2.逐一填写系统所提示的信息\n\n");
	printf("\t\t\t3.核对注册信息的准确性和完整性\n\n");
    printf("\t\t\t4.提交用户注册信息\n\n");
	printf("\n按任意键返回系统主菜单\n");
        getch();
	    menu();
}


/*初始化客户信息链表*/
int maninitlist(linklistman *h)
{
	*h=(linklistman)malloc(sizeof(manlinklist));
	if(!h)
	{
		printf("初始化错误!");
		return 0;
	}
	(*h)->next=NULL;
	return 1;

} 

/*客户信息插入*/
int manlistinsert(linklistman h)
{
	pman p;
	char man_time[20],man_trainnum[20],man_name[20],phone[20],ic[20],order_num[30],man_start[20],man_arrive[20];
	int i,man_box[20],man_table[20],man_count[20],money,amount;
     printf("请输入: 订票时间    车次编号   订票人姓名   订票人联系方式   证件号   订单号   起点站   终点站   票价   订票数\n");
       scanf("%s %s %s %s %s %s %s %s %d %d",man_time,man_trainnum,man_name,phone,ic,order_num,man_start,man_arrive,&money,&amount);
	 	for(i=0;i<amount;i++)
		{
			printf("车厢号   座位号   折扣\n");
			scanf("%d %d %lf",&man_box[i],&man_table[i],&man_count[i]);
		}
	p=(pman)malloc(sizeof(manlinklist));
	strcpy(p->man_time,man_time);
	strcpy(p->man_trainnum,man_trainnum);
	strcpy(p->man_name,man_name);
	strcpy(p->phone,phone);
	strcpy(p->ic,ic);
	strcpy(p->order_num,order_num);
    strcpy(p->man_start,man_start);
	strcpy(p->man_arrive,man_arrive);
	for(i=0;i<amount;i++)
	{
		p->man_box[i]=man_box[i];
     	p->man_table[i]=man_table[i];
    	p->man_count[i]=man_count[i];
	}
	p->money=money;
	p->amount=amount;
	p->next=h->next;
	h->next=p;
	return 1;

}



/*客户信息链表遍历*/
void traversemanlinklist()
{
	int i,j=0,k=0,l,m=0,n,choice;         /*i代表车次循环中的变量，j是一个计数器看是否乘客信息是否为空*/
    for(i=0;i<MAXSIZE;i++)         /*k是营业额累计器，l是座位数变量，m是售票量累加器，n是每个车次乘客累加器*/
    {
	 printf("\n\n车次编号:%s\n\n\n",trin[i].train_num);
	pman p=trin[i].h_man->next;
     n=0;
	while(p)
	{
       
		printf("\n\n订票乘客的信息:\n\n\n");
	    printf("***************************************************************************************************************************************************\n\n\n");
       	printf("订票时间    车次编号   订票人姓名     起点站   终点站    票价   订票数   订票人联系方式            证件号                       订单号      \n\n");
	    printf(" %s       %s    %s          %s     %s     %d     %d        %s       %s       %s\n\n",p->man_time,p->man_trainnum,p->man_name,p->man_start,p->man_arrive,p->money,p->amount,p->phone,p->ic,p->order_num);
	   printf("****************************************************************************************************************************************************\n\n\n");
      k+=p->money;
	  m+=p->amount;
		printf("\n该乘客的订票信息:\n\n");
		printf("**************************\n\n");
       	for(l=0;l<p->amount;l++)
		{
			printf("车厢号   座位号   折扣\n\n");
			printf("  %d        %d      %-5.2lf\n\n",p->man_box[l],p->man_table[l],p->man_count[l]);
		}
		p=p->next;
		j++;
		printf("**************************\n\n\n");
		n++;
	}
     if(n==0)
		 printf("\n\n----------------------------暂无乘客信息!----------------------------\n\n");
	}
		
		if(j==0)
		printf("\n\n\n对不起暂时没有乘客信息!!!");
		printf("\n\n\n--------------今日共售出%d张票--------------\n",m);
		printf("\n\n\n--------------今日营业额为%d元--------------\n\n\n",k);
	printf("\n\n\n");
	printf("是否继续查询(1-确定 2-取消)\n");
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("\n\n按任意键返回管理员登录页面\n");
	    getchar();
	    getchar();

    	guanlimenu();
	}
	else 
	{
        printf("\n\n按任意键返回管理员登录页面\n");
	    getchar();
		getchar();

    	menu();
	}

}

/*客户信息链表遍历找到相应的相应的乘客并输出该乘客信息*/
void traversemanlinklistadd2(linklistman h,char man_name[20],char ic[20])
{
 pman p=h->next;
 int k=0,i;
	while(p)
	{
	   if((!strcmp(man_name,p->man_name))&&(!strcmp(ic,p->ic)))    /*如果有该乘客的信息*/
	   {
          
		printf("\n\n订票乘客的信息:\n\n\n");
	    printf("***************************************************************************************************************************************************\n\n\n");
       	printf("订票时间    车次编号   订票人姓名     起点站   终点站    票价   订票数   订票人联系方式            证件号                       订单号      \n\n");
	    printf(" %s       %s    %s          %s     %s     %d     %d        %s       %s       %s\n\n",p->man_time,p->man_trainnum,p->man_name,p->man_start,p->man_arrive,p->money,p->amount,p->phone,p->ic,p->order_num);
	   printf("****************************************************************************************************************************************************\n\n\n");
       
		printf("\n该乘客的订票信息:\n\n");
		printf("**************************\n\n");
       	for(i=0;i<p->amount;i++)
		{
			printf("车厢号   座位号   折扣\n\n");
			printf("  %d        %d      %-5.2lf\n\n",p->man_box[i],p->man_table[i],p->man_count[i]);
		}
		printf("**************************\n\n\n");
		   
		k++;
		break;
	   }
      	p=p->next;
	}
	if(k==0)
		printf("\n没有该用户的订票信息!!\n");

}

/*遍历乘客信息表并删除相应结点*/
void traverselistmanadd(linklistman h,char man_name[20],char ic[20])
{ 

pman p=h,q;
while(p)
{



	if((!strcmp(man_name,p->next->man_name))&&(!strcmp(ic,p->next->ic)))
	{
		 q=p->next;
	     p->next=q->next;
         free(q);
		 break;
	}

	p=p->next;
   

}
   
}


/*初始化单链表并用车次信息结构中的客户信息域,指向客户信息链表的头指针*/
void pointhead()
{
	int i=0;
 traininfo *info;              /*定义一个指向车次信息结构体的指针info*/
	info=trin;                    /*info指向车次信息结构体数组的首元素*/
    while(i<MAXSIZE)
	{
       linklistman h;         /*定义车票信息链表头结点的指针*/
        maninitlist(&h);       /*初始化链表*/
	   info->h_man=h;         /*将info中的h_tickets设置为车票信息链表的头指针*/
	   i++;
	   info++;
	   }
}



/*车票信息链表的初始化*/
int ticketsinitlist(linklisttickets *h)
{

	*h=(linklisttickets)malloc(sizeof(ticketslinklist));
	if(!h)
	{
		printf("初始化错误!");
		return 0;
	}
	(*h)->next=NULL;
	return 1;

}

/*车票信息链表的插入*/
int ticketslistinsert(linklisttickets h,int tickets_num,int tickets_box,int tickets_table,double count)
{
	ptickets p;
    p=(ptickets)malloc(sizeof(ticketslinklist));
	p->tickets_num=tickets_num;
	p->tickets_box=tickets_box;
	p->tickets_table=tickets_table;
	p->count=count;
	p->next=h->next;
	h->next=p;
	return 1;

}


/*遍历车票信息链表*/
void traverselisttickets(linklisttickets h)
{ 
	int i=1,j=0;
ptickets p=h->next;
while(p)
{
	printf("车票编号   车厢号   座位号   票价折扣 :");
printf("   %d     %d    %d    %-5.2lf       ",p->tickets_num,p->tickets_box,p->tickets_table,p->count);
p=p->next;

if(i%2==0)
printf("\n\n");
i++;
j++;
}
printf("\n\n-----共%d张票-----\n\n",j);
printf("\n");
}

/*遍历票价单链表并删除相应结点*/
void traverselistticketsadd(linklisttickets h,int box,int table)
{ 

ptickets p=h,q;
while(p)
{


	if((p->next->tickets_box==box)&&(p->next->tickets_table==table))
	{
		 q=p->next;
	     p->next=q->next;
         free(q);
		 break;
	}

	p=p->next;
   

}
   
}



/*信息保存函数*/
void save()
{
	int i;
	FILE *fp; 
	if((fp=fopen("stu.dat","wb"))==NULL)   /*wb是为了输出数据，打开一个二进制文件如果指定文件不存在，则建立新的文件*/
	{
		printf("打开文件失败!!\n");
		return ;
	}
for(i=0;i<MAXSIZE;i++)
	if(fwrite(&trin[i],sizeof(struct  train),1,fp)!=1)
	printf("flie write error\n");
	fclose(fp);
}

/*火车票信息录入*/
void createtraininfo()
{   

	traininfo *info;              /*定义一个指向车票信息结构体的指针info*/
    int i=0;
	info=trin;                    /*info指向结构体数组中第一个元素*/
	while(i<MAXSIZE)              /*录入火车票信息*/
	{
       printf("\n车次编号   出发时间   出发站   到达站   到达时间   车厢数   每节车厢座位数   剩余票数  起点到终点的距离(km)   站点信息  \n\n");
	   scanf("%s %s %s %s %s %d %d %d %d %s %s %s %d %d %s %s %s %d %d %s %s %s %d %d %s %s %s %d %d %s %s %s %d %d",info->train_num,info->train_starttime,info->train_start,info->train_arrive,info->train_arrivetime,&info->train_box,&info->train_table,&info->train_tickets,&info->train_mileage,info->station[0].sta_name,info->station[0].arrivetime,info->station[0].starttime,&info->station[0].sta_money,&info->station[0].mileage,info->station[1].sta_name,info->station[1].arrivetime,info->station[1].starttime,&info->station[1].sta_money,&info->station[1].mileage,info->station[2].sta_name,info->station[2].arrivetime,info->station[2].starttime,&info->station[2].sta_money,&info->station[2].mileage,info->station[3].sta_name,info->station[3].arrivetime,info->station[3].starttime,&info->station[3].sta_money,&info->station[3].mileage,info->station[4].sta_name,info->station[4].arrivetime,info->station[4].starttime,&info->station[4].sta_money,&info->station[4].mileage);
	   save();
       i++;
	   info++;
	}
   
}

/*显示载入车次信息的原始数据*/

int showmessage()
{	traininfo *info;              /*定义一个指向车次信息结构体的指针info*/
    int i=0;
	info=trin;   
	
for(i=0;i<MAXSIZE;i++)
	 {    
		
	if(i<=1)
	{
			printf("********************************************************************************************************************\n\n");
        printf(" 车次      出发时间    出发站     终点站     到达时间     车厢数     座位数     剩余票数      起点到终点的距离(km)\n\n ");
     	printf("%s   %s      %s      %s       %s           %d         %d          %d              %d\n\n\n",info[i].train_num,info[i].train_starttime,info[i].train_start,info[i].train_arrive,info[i].train_arrivetime,info[i].train_box,info[i].train_table,info[i].train_tickets,info[i].train_mileage);
		printf("    站名:     %s        %s        %s        %s        %s\n",info[i].station[0].sta_name,info[i].station[1].sta_name,info[i].station[2].sta_name,info[i].station[3].sta_name,info[i].station[4].sta_name);
        printf("到站时间:    %s        %s         %s       %s         %s\n",info[i].station[0].arrivetime,info[i].station[1].arrivetime,info[i].station[2].arrivetime,info[i].station[3].arrivetime,info[i].station[4].arrivetime);  
        printf("出站时间:    %s        %s         %s       %s         %s\n",info[i].station[0].starttime,info[i].station[1].starttime,info[i].station[2].starttime,info[i].station[3].starttime,info[i].station[4].starttime);  
        printf("票价(元):      %d           %d            %d         %d           %d\n",info[i].station[0].sta_money,info[i].station[1].sta_money,info[i].station[2].sta_money,info[i].station[3].sta_money,info[i].station[4].sta_money);  
        printf("里程(km):      %d           %d           %d         %d          %d\n",info[i].station[0].mileage,info[i].station[1].mileage,info[i].station[2].mileage,info[i].station[3].mileage,info[i].station[4].mileage);
		printf("\n********************************************************************************************************************\n\n\n\n\n\n\n\n"); 
		getch();
	}
	else 
	{
      printf("********************************************************************************************************************\n\n");
        printf(" 车次      出发时间    出发站     终点站     到达时间     车厢数     座位数     剩余票数      起点到终点的距离(km)\n\n ");
     	printf("%s   %s      %s      %s       %s           %d         %d          %d              %d\n\n\n",info[i].train_num,info[i].train_starttime,info[i].train_start,info[i].train_arrive,info[i].train_arrivetime,info[i].train_box,info[i].train_table,info[i].train_tickets,info[i].train_mileage);
		printf("    站名:     %s        %s          %s        %s          %s\n",info[i].station[0].sta_name,info[i].station[1].sta_name,info[i].station[2].sta_name,info[i].station[3].sta_name,info[i].station[4].sta_name);
        printf("到站时间:    %s        %s         %s       %s         %s\n",info[i].station[0].arrivetime,info[i].station[1].arrivetime,info[i].station[2].arrivetime,info[i].station[3].arrivetime,info[i].station[4].arrivetime);  
        printf("出站时间:    %s        %s         %s       %s         %s\n",info[i].station[0].starttime,info[i].station[1].starttime,info[i].station[2].starttime,info[i].station[3].starttime,info[i].station[4].starttime);  
        printf("票价(元):      %d           %d            %d         %d           %d\n",info[i].station[0].sta_money,info[i].station[1].sta_money,info[i].station[2].sta_money,info[i].station[3].sta_money,info[i].station[4].sta_money);  
        printf("里程(km):      %d           %d           %d         %d           %d\n",info[i].station[0].mileage,info[i].station[1].mileage,info[i].station[2].mileage,info[i].station[3].mileage,info[i].station[4].mileage);
		printf("\n********************************************************************************************************************\n\n\n\n\n\n\n\n"); 
		getch();
	}
	 }               /*在屏幕上输出文件中的数据*/

		return 0;
}

/*载入车次信息数据*/
int showmessage1()
{	traininfo *info;              /*定义一个指向车次信息结构体的指针info*/
    int i=0;
	info=trin;   

		FILE *fp;                 /*fp为指向文件的指针*/
	if((fp=fopen("stu.dat","rb"))==NULL)      /*fopen为打开文件函数*/
	{
		printf("打开文件失败!!\n");
		return 0;
	}
	 for(i=0;i<MAXSIZE;i++)
	 {    
			fread(&info[i],sizeof(struct train),1,fp);       /*读取文件信息*/
       
	 }               /*在屏幕上输出文件中的数据*/
		fclose(fp);  /*关闭文件防止文件丢失*/

		return 0;
}



/*载入车票信息数据*/
void createtickets()
{
	int i=0,j,k,m=1;
	
	double count;
    traininfo *info,*p;              /*定义一个指向车次信息结构体的指针info*/
	info=trin;                    /*info指向车次信息结构体数组的首元素*/

    while(i<MAXSIZE)
	{
       linklisttickets h;         /*定义车票信息链表头结点的指针*/
       ticketsinitlist(&h);       /*初始化链表*/
	   info->h_tickets=h;         /*将info中的h_tickets设置为车票信息链表的头指针*/
	   i++;
	   info++;
	   }
   p=trin;
   i=0;
    while(i<MAXSIZE)
	{
      
		for(j=1;j<=p->train_box;j++)
			for(k=1;k<=p->train_table;k++)
			{
             if(k<=3)
              count=0.7;
			 else count=1.0;
			 ticketslistinsert(p->h_tickets,m,j,k,count);    /*调用车票信息链表的插入函数*/
			 m++;
			}
			i++;
			p++;
	}
}


/*按车次编号查询*/
void searchbynumber()
{
 traininfo *info;              /*定义一个指向车次信息结构体的指针info*/
 info=trin;                    /*info指向车次信息结构体数组的首元素*/
 int choice;
 char number[10];
 int i=0,j=0;
 printf("请输入车次编号:\n");
 scanf("%s",number);
 while(i<MAXSIZE)
 {
	  if(!strcmp(number,info[i].train_num))       /*如果找到给车次信息则输出*/
	 {
		printf("\n车次信息:\n\n\n");
		printf("********************************************************************************************************************\n\n");
        printf(" 车次      出发时间    出发站     终点站     到达时间     车厢数     座位数     剩余票数      起点到终点的距离(km)\n\n ");
     	printf("%s   %s      %s      %s       %s           %d         %d          %d              %d\n\n\n",info[i].train_num,info[i].train_starttime,info[i].train_start,info[i].train_arrive,info[i].train_arrivetime,info[i].train_box,info[i].train_table,info[i].train_tickets,info[i].train_mileage);
		printf("    站名:     %s        %s        %s        %s        %s\n",info[i].station[0].sta_name,info[i].station[1].sta_name,info[i].station[2].sta_name,info[i].station[3].sta_name,info[i].station[4].sta_name);
        printf("到站时间:    %s        %s         %s       %s         %s\n",info[i].station[0].arrivetime,info[i].station[1].arrivetime,info[i].station[2].arrivetime,info[i].station[3].arrivetime,info[i].station[4].arrivetime);  
        printf("出站时间:    %s        %s         %s       %s         %s\n",info[i].station[0].starttime,info[i].station[1].starttime,info[i].station[2].starttime,info[i].station[3].starttime,info[i].station[4].starttime);  
        printf("票价(元):      %d           %d            %d         %d           %d\n",info[i].station[0].sta_money,info[i].station[1].sta_money,info[i].station[2].sta_money,info[i].station[3].sta_money,info[i].station[4].sta_money);  
        printf("里程(km):      %d           %d           %d         %d          %d\n",info[i].station[0].mileage,info[i].station[1].mileage,info[i].station[2].mileage,info[i].station[3].mileage,info[i].station[4].mileage);
		printf("\n********************************************************************************************************************\n\n\n\n\n\n\n\n"); 
		
		printf("剩余票信息:\n\n\n");
       
		getch();
        printf("*********************************************************************************************************************************************\n\n\n");
        traverselisttickets(info[i].h_tickets);      /*输出该车次剩余票的信息*/
	    printf("********************************************************************************************************************************************\n\n");
      
		j++;
	 }
	 i++;
	 
 }
 if(j==0)
 {
	 printf("对不起,没有与您输入信息匹配的车次!\n");
	 printf("\n按任意键返回查询子菜单\n");
	 getch();
	 searchmenu();
 }
 else
 {          printf("是否继续查询:(1-确定,2-取消)\n");
            scanf("%d",&choice);
            switch(choice)
			{
			case 1:
				{
				     printf("按任意键返回查询子菜单:\n");
		             getch();
		             searchmenu();                      /*查询子菜单函数*/
				}
				      break;
			case 2:
				{
                      printf("\n按任意键返回主菜单\n");
	                  getch();
	                  mainmenu();                       /*查询主菜单*/
				}
				    break;
        	default:
				{
		             printf("输入错误!!确保您的输入为(1,2)\n");
		             printf("按任意键返回查询子菜单\n");
			         getch();
			         searchmenu();                   /*查询子菜单函数*/
			}
		    break;


			}
		   
}
		   
}

/*按终点站查询*/
void searchbyaddress()
{
 traininfo *info;              /*定义一个指向车次信息结构体的指针info*/
 info=trin;                    /*info指向车次信息结构体数组的首元素*/
  int choice;
 char name1[20];
 char name2[20];
 int i=0,j=0,k=0;
 printf("请输入您所在城市的名称:");
 scanf("%s",name1);
 printf("\n\n\n请输入您要抵达城市的名称:");
 scanf("%s",name2);
 while(i<MAXSIZE)
 {
	 for(j=0;j<5;j++)
	 {
		 if(!strcmp(name1,info[i].station[j].sta_name))
           while(j<5)
		   {
			          if(!strcmp(name2,info[i].station[j].sta_name))
		 {
		printf("\n车次信息:\n\n\n");
		printf("********************************************************************************************************************\n\n");
        printf(" 车次      出发时间    出发站     终点站     到达时间     车厢数     座位数     剩余票数      起点到终点的距离(km)\n\n ");
     	printf("%s   %s      %s      %s       %s           %d         %d          %d              %d\n\n\n",info[i].train_num,info[i].train_starttime,info[i].train_start,info[i].train_arrive,info[i].train_arrivetime,info[i].train_box,info[i].train_table,info[i].train_tickets,info[i].train_mileage);
		printf("    站名:     %s        %s        %s        %s        %s\n",info[i].station[0].sta_name,info[i].station[1].sta_name,info[i].station[2].sta_name,info[i].station[3].sta_name,info[i].station[4].sta_name);
        printf("到站时间:    %s        %s         %s       %s         %s\n",info[i].station[0].arrivetime,info[i].station[1].arrivetime,info[i].station[2].arrivetime,info[i].station[3].arrivetime,info[i].station[4].arrivetime);  
        printf("出站时间:    %s        %s         %s       %s         %s\n",info[i].station[0].starttime,info[i].station[1].starttime,info[i].station[2].starttime,info[i].station[3].starttime,info[i].station[4].starttime);  
        printf("票价(元):      %d           %d            %d         %d           %d\n",info[i].station[0].sta_money,info[i].station[1].sta_money,info[i].station[2].sta_money,info[i].station[3].sta_money,info[i].station[4].sta_money);  
        printf("里程(km):      %d           %d           %d         %d          %d\n",info[i].station[0].mileage,info[i].station[1].mileage,info[i].station[2].mileage,info[i].station[3].mileage,info[i].station[4].mileage);
		printf("\n********************************************************************************************************************\n\n\n\n\n\n\n\n"); 
		   printf("剩余票信息:\n\n\n");
		 printf("*********************************************************************************************************************************************\n\n\n");
         traverselisttickets(info[i].h_tickets);      /*输出该车次剩余票的信息*/
		 printf("*********************************************************************************************************************************************\n\n\n");
       
		printf("\n\n\n");
	    k++;
		getch();
		 }
		    j++;
		   }
	 }
	 i++;
 }
 if(k==0)
 {
	 printf("\n对不起,没有与您输入信息匹配的车次!\n");
	 printf("\n按任意键返回查询子菜单\n");
	 getch();
	 searchmenu();
 }
  else
 {          printf("是否继续查询:(1-确定,2-取消)\n");
            scanf("%d",&choice);
            switch(choice)
			{
			case 1:
				{
				     printf("按任意键返回查询子菜单:\n");
		             getch();
		             searchmenu();                      /*查询子菜单函数*/
				}
				      break;
			case 2:
				{
                      printf("\n按任意键返回主菜单\n");
	                  getch();
	                  mainmenu();                       /*查询主菜单*/
				}
				    break;
        	default:
				{
		             printf("输入错误!!确保您的输入为(1,2)\n");
		             printf("按任意键返回查询子菜单\n");
			         getch();
			         searchmenu();                   /*查询子菜单函数*/
				}
		    break;


			}
		   
}

}






/*查询信息的主菜单*/
void searchmenu()
{
	system("color 1f");           /*使面呈蓝色*/
    system("mode con: cols=150  lines=1000");   /*调整大小*/
	int choice;
printf("\n火车票查询系统主菜单\n");
printf("\n日期: 2015/6/20\n\n");
printf("***********************************************************************************\n\n");

    printf("              1.按班次号查询........................\n\n");
	printf("              2.按起点与终点查询....................\n\n");
	printf("              3.返回主菜单..........................\n\n");
printf("***********************************************************************************\n");
	printf("\n请选择您所需要的功能:(1,2,3)\n");
	scanf("%d",&choice);
	switch(choice)
	{
	case 1:searchbynumber();break;          /*调用按班次号查询函数*/
	case 2:searchbyaddress();break;         /*调用按终点查询函数*/
	
	case 3:{
		    printf("按任意键返回主菜单:\n");
		    getch();
		    mainmenu();                      /*主菜单函数*/
		   }
		   break;
	default:{
		      printf("输入错误!!确保您的输入为(1,2,3)\n");
		      printf("按任意键返回主菜单\n");
			  getch();
			  mainmenu();                   /*主菜单函数*/
			}
		    break;

	}
}





/*订票系统的主菜单*/
void reservemenu()
{
	system("color 1f");           /*使面呈蓝色*/
    system("mode con: cols=150  lines=1000");   /*调整大小*/
	int choice;
printf("\n火车票订票系统主菜单\n");
printf("\n日期: 2015/6/20\n\n");
printf("***********************************************************************************\n\n");

    printf("              1.订票业务........................\n\n");
	printf("              2.返回主菜单..........................\n\n");
printf("***********************************************************************************\n");
	printf("\n请选择您所需要的功能:(1,2)\n");
	scanf("%d",&choice);
	switch(choice)
	{
	case 1:reservebynumber();break;          /*调用按班次号订票函数*/

	case 2:{
		    printf("按任意键返回主菜单:\n");
		    getch();
		    mainmenu();                      /*主菜单函数*/
		   }
		   break;
	default:{
		      printf("输入错误!!确保您的输入为(1,2)\n");
		      printf("按任意键返回订票系统主菜单\n");
			  getch();
			   mainmenu();                /*订票系统主菜单函数*/
			}
		    break;

	}
}

/*按车次订票函数*/
void reservebynumber()
{ 
	char train_num[20],man_start[20],man_arrive[20],man_time[20],man_trainnum[20],man_name[20],phone[20],ic[20];
	int i=0,j=0,choice1,choice2,choice3,amount,choice_box,choice_table,stationmoneya,stationmoneys,stationmileagea,stationmileages,mileage,man_box[20],man_table[20];
    double choice_count,man_count[20],count=0,money;
	traininfo *info,*p;                              /*info为指向车次信息的指针*/
	info=trin;                                    /*info指向frin[5]结构体数组的第一个元素即frin[0]*/
    printf("请输入车次编号:\n");
	scanf("%s",train_num);
    
    
    while(i<MAXSIZE)
 {
	  if(!strcmp(train_num,info[i].train_num))       /*如果找到给车次信息则输出*/
	 {
		printf("\n车次信息:\n\n\n");
      	if(i<=1)
	{
			printf("********************************************************************************************************************\n\n");
        printf(" 车次      出发时间    出发站     终点站     到达时间     车厢数     座位数     剩余票数      起点到终点的距离(km)\n ");
     	printf("%s   %s      %s      %s       %s           %d         %d          %d              %d\n\n\n",info[i].train_num,info[i].train_starttime,info[i].train_start,info[i].train_arrive,info[i].train_arrivetime,info[i].train_box,info[i].train_table,info[i].train_tickets,info[i].train_mileage);
		printf("    站名:     %s        %s        %s        %s        %s\n",info[i].station[0].sta_name,info[i].station[1].sta_name,info[i].station[2].sta_name,info[i].station[3].sta_name,info[i].station[4].sta_name);
        printf("到站时间:    %s        %s         %s       %s         %s\n",info[i].station[0].arrivetime,info[i].station[1].arrivetime,info[i].station[2].arrivetime,info[i].station[3].arrivetime,info[i].station[4].arrivetime);  
        printf("出站时间:    %s        %s         %s       %s         %s\n",info[i].station[0].starttime,info[i].station[1].starttime,info[i].station[2].starttime,info[i].station[3].starttime,info[i].station[4].starttime);  
        printf("票价(元):      %d           %d            %d         %d           %d\n",info[i].station[0].sta_money,info[i].station[1].sta_money,info[i].station[2].sta_money,info[i].station[3].sta_money,info[i].station[4].sta_money);  
        printf("里程(km):      %d           %d           %d         %d          %d\n",info[i].station[0].mileage,info[i].station[1].mileage,info[i].station[2].mileage,info[i].station[3].mileage,info[i].station[4].mileage);
		printf("\n********************************************************************************************************************\n\n\n\n\n\n\n\n"); 
	
	}
	else 
	{
      printf("********************************************************************************************************************\n\n");
        printf(" 车次      出发时间    出发站     终点站     到达时间     车厢数     座位数     剩余票数      起点到终点的距离(km)\n ");
     	printf("%s   %s      %s      %s       %s           %d         %d          %d              %d\n\n\n",info[i].train_num,info[i].train_starttime,info[i].train_start,info[i].train_arrive,info[i].train_arrivetime,info[i].train_box,info[i].train_table,info[i].train_tickets,info[i].train_mileage);
		printf("    站名:     %s        %s          %s        %s          %s\n",info[i].station[0].sta_name,info[i].station[1].sta_name,info[i].station[2].sta_name,info[i].station[3].sta_name,info[i].station[4].sta_name);
        printf("到站时间:    %s        %s         %s       %s         %s\n",info[i].station[0].arrivetime,info[i].station[1].arrivetime,info[i].station[2].arrivetime,info[i].station[3].arrivetime,info[i].station[4].arrivetime);  
        printf("出站时间:    %s        %s         %s       %s         %s\n",info[i].station[0].starttime,info[i].station[1].starttime,info[i].station[2].starttime,info[i].station[3].starttime,info[i].station[4].starttime);  
        printf("票价(元):      %d           %d            %d         %d           %d\n",info[i].station[0].sta_money,info[i].station[1].sta_money,info[i].station[2].sta_money,info[i].station[3].sta_money,info[i].station[4].sta_money);  
        printf("里程(km):      %d           %d           %d         %d           %d\n",info[i].station[0].mileage,info[i].station[1].mileage,info[i].station[2].mileage,info[i].station[3].mileage,info[i].station[4].mileage);
		printf("\n********************************************************************************************************************\n\n\n\n\n\n\n\n"); 
		
	}	
	    printf("剩余票信息:\n\n\n");
        getch();
		printf("*********************************************************************************************************************************************\n\n\n");
        traverselisttickets(info[i].h_tickets);      /*输出该车次剩余票的信息*/
	    printf("*********************************************************************************************************************************************\n\n\n");
      	j++;
		p=&info[i];                                     /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	    break;
	 }
	 i++;
	 
 }
      
	if(j==0)
 
	printf("对不起,没有与您输入信息匹配的车次!\n");

	printf("温馨提示:\n\n");
	printf("*************************************\n");
	printf("*                                   *");
	printf("\n*  如果您没找到您要查找的班次信息,  *\n");
	printf("*                                   *");
    printf("\n*  或者您要找的列车已发出或者余票   *\n");
    printf("*                                   *");
    printf("\n*  额小于您要订票额,建议您按照起    *\n");
    printf("*                                   *");
    printf("\n*  点与终点查询浏览班次信息选择其   *\n");
    printf("*                                   *");
    printf("\n*  它班次的列车!谢谢和作!!          *\n");
    printf("*                                   *");
    printf("\n*************************************\n\n\n");


	printf("是否转到查询主菜单(1-确定,0-取消):\n");
	scanf("%d",&choice1);
	if(choice1!=0)
	{
	 printf("按任意键返回查询主菜单\n");
	 getch();
	 searchmenu();                 /*查询系统主菜单函数*/
	}
    printf("\n\n\n请输入: 订票时间    车次编号   订票人姓名   订票人联系方式   证件号   起点站   终点站   订票数\n\n");
    scanf("%s %s %s %s %s %s %s %d",man_time,man_trainnum,man_name,phone,ic,man_start,man_arrive,&amount);
	printf("\n\n请您在剩余票中选择您喜欢的车厢号、座位号、折扣:\n\n");
	for(i=0;i<amount;i++)                  /*乘客输入要订购的座位号*/
	{
     printf("车厢号  座位号  折扣\n");
	 scanf("%d %d %lf",&choice_box,&choice_table,&choice_count);
     man_box[i]=choice_box;
	 man_table[i]=choice_table;
     man_count[i]=choice_count;
     count+=choice_count;                  /*打折数累加*/
	 p->train_tickets--;                /*班次信息中剩余票数减一*/
	 traverselistticketsadd(p->h_tickets,choice_box,choice_table); 
	}


	for(i=0;i<5;i++)
	{
		if(0==strcmp(p->station[i].sta_name,man_start))
		{

          stationmoneys=p->station[i].sta_money;
		  stationmileages=p->station[i].mileage;
		}
		
	}


	for(j=0;j<5;j++)
	{
		 
		if(0==strcmp(p->station[j].sta_name,man_arrive))
		{
		
			stationmoneya=p->station[j].sta_money;
			stationmileagea=p->station[j].mileage;
		}
	}



    money=(stationmoneya-stationmoneys)*count;                 /*得到客户信息中的票价*/
    mileage=(stationmileagea-stationmileages);
	printf("\n您共需支付%d元\n\n",(int)money);
	printf("\n是否确定支付(1-确定,0-取消)\n\n");
	scanf("%d",&choice2);
		if(choice2==0)
	{
	 printf("按任意键返回火车管理系统主菜单\n");
	 getch();
	 mainmenu();                 /*火车管理系统主菜单函数*/
	}


   

      /*在客户信息链表中插入一个结点*/
	pman q;
	q=(pman)malloc(sizeof(manlinklist));
	strcpy(q->man_time,man_time);
	strcpy(q->man_trainnum,man_trainnum);
	strcpy(q->man_name,man_name);
	strcpy(q->phone,phone);
	strcpy(q->ic,ic);
	strcat(man_trainnum,ic);                                    /*得到客户信息中的订单号（车次号+身份证号）*/
	strcpy(q->order_num,man_trainnum);
    strcpy(q->man_start,man_start);
	strcpy(q->man_arrive,man_arrive);
	for(i=0;i<amount;i++)
	{
		q->man_box[i]=man_box[i];
     	q->man_table[i]=man_table[i];
    	q->man_count[i]=man_count[i];
	}
	q->money=(int)money;
	q->amount=amount;
	q->next=p->h_man->next;
	p->h_man->next=q;
	printf("\n\n\n\n\n-------------您订票已成功!请您在该班次列车出发前30分钟进站候车感谢您使用--------------\n\n\n\n");
	
     for(i=0;i<amount;i++)
	 {
printf("\n\n******************************************************\n");
printf("*                                                    *\n");
printf("    车次编号:%s                               \n",train_num);
printf("*                                                    *\n");
printf("                                                    \n");
printf("*                                                    *\n");
printf("               %s----------%s                    \n",man_start,man_arrive);
printf("*                                                    *\n");
printf("                  (全程%dkm)                       \n",mileage);
printf("*                                                    *\n");
printf("                                                    \n");
printf("*           车厢号:%d       座位号:%d                  *\n",man_box[i],man_table[i]);
printf("                                                    \n");
printf("*                                                    *\n");
printf("        订单号:%s           \n",man_trainnum);
printf("*                                                    *\n");
printf("                             日期: 2015/6/20         \n");
printf("******************************************************\n\n\n\n");
  
	 }

 printf("是否浏览乘客信息(1-乘客信息,2-返回车票管理系统主菜单)\n");
            scanf("%d",&choice3);
            switch(choice3)
			{
			case 1:
				{
				     printf("按任意键查询乘客信息:\n");
		             getch();
				     traversemanlinklistadd2(p->h_man,man_name,ic);
					                      /*查询乘客信息*/
					  printf("\n按任意键返回车票管理系统主菜单\n");
	                  getch();
	                  mainmenu();                      /*返回车票管理系统主菜单*/
				}
				break;
			case 2:
				{
                      printf("\n按任意键返回车票管理系统主菜单\n");
	                  getch();
	                  mainmenu();                      /*返回车票管理系统主菜单*/
				}
				    break;

		
        	default:
				{
		             printf("输入错误!!确保您的输入为(1,2,3)\n");
		             printf("按任意键返回车票管理系统主菜单\n");
			         getch();
			         mainmenu();                   /*查询子菜单函数*/
				}
		    break;


			}

   


}




/*退票系统的主菜单*/
void returnticketsmenu()
{
	system("color 1f");           /*使面呈蓝色*/
    system("mode con: cols=150  lines=1000");   /*调整大小*/
	int choice;
printf("\n火车票订票系统主菜单\n");
printf("\n日期: 2015/6/20\n\n");
printf("***********************************************************************************\n\n");

    printf("              1.退票业务........................\n\n");
	printf("              2.返回主菜单..........................\n\n");
printf("***********************************************************************************\n");
	printf("\n请选择您所需要的功能:(1,2)\n");
	scanf("%d",&choice);
	switch(choice)
	{
	case 1:returntickets();break;          /*调用按班次号订票函数*/

	case 2:{
		    printf("按任意键返回主菜单:\n");
		    getch();
		    mainmenu();                      /*主菜单函数*/
		   }
		   break;
	default:{
		      printf("输入错误!!确保您的输入为(1,2)\n");
		      printf("按任意键返回订票系统主菜单\n");
			  getch();
			   mainmenu();                 /*退票系统主菜单函数*/
			}
		    break;

	}
}

/*退票函数*/
void returntickets()
{   
	traininfo *info,*q;                              /*info为指向车次信息的指针*/
	info=trin;                                    /*info指向frin[5]结构体数组的第一个元素即frin[0]*/
    char man_name[20],ic[20],man_trainnum[20],man_start[20],man_arrive[20];
	int a,b,c,k=0,i=0,j=0,money,man_box,man_table,choice3;
	double count;
	printf("\n\n请输入您的姓名、证件号、车次编号、起点、终点、车厢号、座位号、折扣\n\n");
	scanf("%s %s %s %s %s %d %d %lf",man_name,ic,man_trainnum,man_start,man_arrive,&man_box,&man_table,&count);

    while(i<MAXSIZE)
 {
	  if(!strcmp(man_trainnum,info[i].train_num))       /*如果找到给车次信息则输出*/
	 {
	
	    j++;
		q=&info[i];                                     /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	    break;
	 }
	 i++;
	 
 }
    
	 
 
 if(j==0)
 {
	 printf("对不起,没有与您输入信息匹配的车次!\n");
	 printf("\n按任意键返回主菜单\n");
	 getch();
	 mainmenu();
 }

/*验证乘客信息*/
 pman p=q->h_man->next;
	while(p)
	{
	if((!strcmp(man_name,p->man_name))&&(!strcmp(ic,p->ic)))    /*如果有该乘客的信息*/
	{
     if(p->amount==1)                                           /*如果该乘客只订了一张票*/
     traverselistmanadd(q->h_man,man_name,ic);          /*删除该乘客的信息*/
     else {
		    
		   for(i=0;i<p->amount;i++)                             /*如果该乘客定了不止一张票,则删除该座位号,该乘客订票数减一*/
		   {
			   if((p->man_box[i]==man_box)&&(p->man_table[i]==man_table))
			   {
				   p->man_box[i]=p->man_box[p->amount-1];
			
                  p->man_table[i]=p->man_table[p->amount-1];

				  p->man_count[i]=p->man_count[p->amount-1];
			   }
		   }
		   p->amount--;

	      }
       k++;
	   break;
	}               
		p=p->next;
	}

if(k!=0)                  /*如果该客户信息匹配成功*/
{
	/*求出退的金额*/
for(i=0;i<5;i++)
	{
		if(0==strcmp(q->station[i].sta_name,man_start))
		{

          a=q->station[i].sta_money;
		}
		
	}


	for(j=0;j<5;j++)
	{
		 
		if(0==strcmp(q->station[j].sta_name,man_arrive))
		{
		
			b=q->station[j].sta_money;
		}
	}

	 money=(int)((b-a)*count);

	 p->money-=money;         /*如果该乘客订购票不只一张,则成功退一张之后票价应减相应钱数*/
/*在车票链表中增加一个结点*/
 c=q->h_tickets->next->tickets_num;     /*c+1为该车票的编号*/
 ticketslistinsert(q->h_tickets,c+1,man_box,man_table,count);


 
 /*在车次信息中剩余票数加一*/
 q->train_tickets++;
printf("\n\n\n\n\n\n-----------------退票成功!退给您%d元,欢迎您再次使用,谢谢!------------------\n\n\n",money);
 printf("是否浏览该车次乘客信息(1-乘客信息,2-返回车票管理系统主菜单)\n");
            scanf("%d",&choice3);
            switch(choice3)
			{
			case 1:
				{
				     printf("按任意键查询乘客信息:\n");
		             getch();
					 traversemanlinklistadd2(q->h_man,man_name,ic);                    /*查询乘客信息*/
					  printf("\n按任意键返回车票管理系统主菜单\n");
	                  getch();
	                  mainmenu();                      /*返回车票管理系统主菜单*/
				}
				break;
			case 2:
				{
                      printf("\n按任意键返回车票管理系统主菜单\n");
	                  getch();
	                  mainmenu();                      /*返回车票管理系统主菜单*/
				}
				    break;

		
        	default:
				{
		             printf("输入错误!!确保您的输入为(1,2,3)\n");
		             printf("按任意键返回车票管理系统主菜单\n");
			         getch();
			         mainmenu();                   /*查询子菜单函数*/
				}
		    break;


			}
 
}
else {
printf("\n\n没有找到该用户的信息!!\n\n"); 
      printf("\n\n按任意键返回车票管理系统主菜单\n\n");
       
      getchar();
	  mainmenu();
     }
   
}


int main()
{  
	menu();

  return 1;
}




