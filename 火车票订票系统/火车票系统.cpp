#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define MAXSIZE 5

/*����Ա�ṹ��*/
typedef struct {
char guanliyuanbianhao[20];        /*����Ա���*/
char guanliyuanmima[20];        /*����Ա������*/
char xing[20];      /*����Ա����*/
char ming[20];      /*����Ա����*/
char xingbie[10];         /*����Ա���Ա�*/
char lianxifangshi[20];      /*����Ա��ϵ��ʽ*/
}guanliyuan;
guanliyuan gly;

/*��ע���û�����Ľṹ*/
typedef struct yonghunode{
char zhanghao[20];        /*�û����˺�*/
char mima[20];            /*�û�������*/
char yonghuxing[20];      /*�û�����*/
char yonghuming[20];      /*�û�����*/
char xingbie[10];         /*�û����Ա�*/
char zhengjianleixing[20];   /*֤������*/
char zhengjianhao[20];       /*֤����*/
char lianxifangshi[20];      /*�û���ϵ��ʽ*/
struct yonghunode *next;
}lyhnode,*pyhnode,*linklistyh;
linklistyh yh;


/*�ͻ���Ϣ����Ľṹ*/
typedef struct man{
char man_time[20];        /*��Ʊʱ��*/
char man_trainnum[20];    /*���α��*/
char man_name[20];        /*��Ʊ������*/
char phone[20];           /*��Ʊ����ϵ��ʽ*/
char ic[20];              /*֤����*/
char order_num[30];       /*������*/
char man_start[20];           /*���վ*/
char man_arrive[20];          /*�յ�վ*/
int man_box[20];              /*�����*/   
int man_table[20];            /*��λ��*/
double man_count[20];         /*Ʊ�۵��ۿ�*/
int money;                /*Ʊ��*/
int amount;               /*��Ʊ��*/
struct man *next;
}manlinklist,*pman,*linklistman; 

/*��Ʊ��Ϣ����Ľṹ*/
typedef struct tickets{
int tickets_num;          /*��Ʊ���*/
int tickets_box;          /*�����*/
int tickets_table;        /*��λ��*/
double count;              /*Ʊ���ۿ�*/  
struct tickets *next;
}ticketslinklist,*ptickets,*linklisttickets;


/*վ��Ľṹ*/
typedef struct station{
char sta_name[20];        /*��վ����*/ 
char arrivetime[20];      /*��վʱ��*/
char starttime[20];       /*��վʱ��*/
int sta_money;            /*����㵽��վ��Ʊ��*/
int mileage;              /*���*/
     
}stationlinklist;

/*������Ϣ�Ľṹ*/
typedef struct train{
char train_num[20];               /*���α��*/
char train_starttime[20];         /*����ʱ��*/
char train_start[20];             /*����վ*/
char train_arrive[20];            /*�յ�վ*/
char train_arrivetime[20];        /*����ʱ��*/ 
int  train_box;                   /*������*/
int  train_table;                 /*ÿ�ڳ�����λ��*/
int  train_tickets;               /*ʣ��Ʊ��*/ 
int  train_mileage;               /*��㵽�յ�ľ���*/ 
stationlinklist station[5];          /*վ��ṹ��*/
linklistman h_man;                /*�ͻ���Ϣ��,ָ��ͻ���Ϣ�����ͷָ��*/
linklisttickets h_tickets;        /*��Ʊ��Ϣ��,ָ��Ʊ��Ϣ�����ͷָ��*/

}traininfo;

traininfo trin[MAXSIZE];          /*����һ����MAXSIZE��Ԫ�صĽṹ������*/

/********************************************************************************************************************************/

void mainmenu();                      /*��Ʊ����ϵͳ���˵�*/ 
                 
void searchmenu();                    /*��ѯ��Ϣ���Ӳ˵�*/

int guanliyuan1();               /*��ʼ������Ա�ṹ��*/

void guanliyuadenglu();          /*����Ա��¼*/

int yonghuinitlist();     /*��ʼ����ע��ͻ���Ϣ����*/

void zhuceyonghu(linklistyh h);        /*���û�ע�ắ��*/

void bianliyonghu();          /*����ע���û�����*/

void yonghudenglu(linklistyh h);      /*�û���¼*/

void zhucezhinan();                   /*���û�ע��ָ��*/

int maninitlist(linklistman *h);      /*��ʼ���ͻ���Ϣ����*/

int manlistinsert(linklistman h);      /*�ͻ���Ϣ����*/

int ticketsinitlist(linklisttickets *h);  /*��Ʊ��Ϣ����ĳ�ʼ��*/

int ticketslistinsert(linklisttickets h,int tickets_num,int tickets_box,int tickets_table,double count);  /*��Ʊ��Ϣ����Ĳ���*/

void traverselisttickets(linklisttickets h);   /*������Ʊ��Ϣ����*/

void save();     /*��Ϣ���溯��*/

void createtraininfo();    /*��Ʊ��Ϣ¼��*/

int showmessage();     /*��ʾ���복����Ϣ��ԭʼ����*/

int showmessage1();    /*���복����Ϣ����*/

void createtickets();    /*���복Ʊ��Ϣ����*/

void searchbynumber();    /*�����α�Ų�ѯ*/

void searchbyaddress();    /*���յ�վ��ѯ*/

void traversemanlinklist();    /*�ͻ���Ϣ�������*/

void pointhead();          /*��ʼ���������ó�����Ϣ�ṹ�еĿͻ���Ϣ��,ָ��ͻ���Ϣ�����ͷָ��*/

void reservemenu();           /*��Ʊϵͳ�����˵�*/

void traverselistticketsadd(linklisttickets h,int box,int table);    /*����Ʊ�۵�����ɾ����Ӧ���*/

void reservebynumber();         /*�����ζ�Ʊ����*/

void returnticketsmenu();           /*��Ʊϵͳ�����˵�*/

void traverselistmanadd(linklistman h,char man_name[20],char ic[20]);       /*�����˿���Ϣ��ɾ����Ӧ���*/

void traversemanlinklistadd2(linklistman h,char man_name[20],char ic[20]);   /*�ͻ���Ϣ��������ҵ���Ӧ����Ӧ�ĳ˿Ͳ�����ó˿���Ϣ*/

void returntickets();           /*��Ʊ����*/
/********************************************************************************************************************************/

/*ϵͳ���˵�*/                            
void menu()
{
system("color 1f");           /*ʹ�����ɫ*/
system("mode con: cols=150 lines=1000");   /*������С*/
int choice;
printf("\n��ӭ������ϵͳ���˵�\n");
printf("\n����: 2015/6/20\n\n");
printf("***********************************************************************************\n\n");
printf("                            1.¼������Ϣ....................\n\n         ");
printf("                   2.��������Ϣ....................\n\n         ");
printf("                   3.�û���¼........................\n\n         ");
printf("                   4.ע�����û�......................\n\n         ");
printf("                   5.ע��ָ��........................\n\n        ");
printf("                    6.����Ա��¼........................\n\n        ");
printf("                    7.�˳�ϵͳ..............\n        ");
printf("\n***********************************************************************************\n\n");
printf("��ѡ��������Ҫ�Ĺ���:(1,2,3,4,5,6)\n");
scanf("%d",&choice);
switch(choice)
{
case 1:
	{
       showmessage1();         /*�������ݵĺ���*/
	   createtickets();        /*��ʼ����Ʊ��Ϣ*/
       pointhead();            /*��ʼ���ͻ���Ϣ����*/
	   yonghuinitlist();       /*��ʼ����ע��ͻ���Ϣ����*/
	   guanliyuan1();          /*��ʼ������Ա��Ϣ*/
	   printf("\n�����������ϵͳ���˵�\n");
	   getch();
	   menu();
	}
	 break;

case 2:
	{
      system("cls"); 
	  showmessage();          /*��ʾ���г�����Ϣ*/
      printf("\n�����������ϵͳ���˵�\n");
      getch();
	  menu();
	}
	 break;
case 3:
	{
      yonghudenglu(yh);          /*�û���¼*/
	  printf("\n�����������ϵͳ���˵�\n");
      getch();
	  menu();
	}
	  break;
case 4:
	{
      zhuceyonghu(yh);            /*ע����Ϣ*/
	 
	}
	  break;
case 5:
	{
      zhucezhinan();            /*���û�ע��ָ��*/
	  printf("\n�����������ϵͳ���˵�\n");
      getch();
	  menu();
	}
	  break;
case 6:
	{
			 system("cls"); 
       guanliyuadenglu();            /*����Ա��¼*/
	  printf("\n�����������ϵͳ���˵�\n");
      getch();
	  menu();
	}
	  break;
case 7:
	 system("cls"); 
	 printf("\n\n\n\n\n----------------------------��л��ʹ�ñ�ϵͳ,��ӭ���ٴ�ʹ��!----------------------------\n\n\n\n\n\n\n\n");
	 exit(0);
	break;
default:
	{
		printf("�������!!��ȷ����������Ϊ:(1,2,3,4,5,6)\n");
        printf("\n�����������ϵͳ���˵�\n");
        getch();
	    menu();
	}
	break;
}       
}

/*����Ա��¼���˵�*/                            
void guanlimenu()
{
system("color 1f");           /*ʹ�����ɫ*/
system("mode con: cols=150 lines=1000");   /*������С*/
int choice;
printf("\n��ӭ���������Ա���˵�\n");
printf("\n����: 2015/6/20\n\n");
printf("***********************************************************************************\n\n");
printf("                            1.�����Ʊ��Ϣ....................\n\n         ");
printf("                   2.���ע����Ϣ....................\n\n         ");

printf("                   3.����ϵͳ���˵�..............\n        ");
printf("\n***********************************************************************************\n\n");
printf("��ѡ��������Ҫ�Ĺ���:(1,2,3)\n");
scanf("%d",&choice);
switch(choice)
{
case 1:
	{
       traversemanlinklist();          /*����Ա�鿴��Ʊ��Ϣ*/
	   printf("\n�����������ϵͳ���˵�\n");
	   getch();
	   menu();
	}
	 break;

case 2:
	{
		 system("cls"); 
	 bianliyonghu();      /*���ע����Ϣ*/
      printf("\n�����������ϵͳ���˵�\n");
      getch();
	  menu();
	}
	 break;




case 3:
	{
		 printf("\n�����������ϵͳ���˵�\n");
        getch();
	    menu();
	}
	 
	break;
default:
	{
		printf("�������!!��ȷ����������Ϊ:(1,2,3,4,5,6)\n");
        printf("\n�����������ϵͳ���˵�\n");
        getch();
	    menu();
	}
	break;
}       
}

 /*��Ʊ����ϵͳ���˵�*/                            
void mainmenu()
{
system("color 1f");           /*ʹ�����ɫ*/
system("mode con: cols=150 lines=1000");   /*������С*/
int choice;
printf("\n��ӭ�������Ʊ��Ʊϵͳ���˵�\n");
printf("\n����: 2015/6/20\n\n");
printf("***********************************************************************************\n\n");
printf("                            1.��������Ϣ....................\n\n         ");
printf("                   2.��ѯ�г�·��....................\n\n         ");
printf("                   3.��Ʊϵͳ........................\n\n         ");
printf("                   4.��Ʊϵͳ........................\n\n        ");
printf("                    5.�˳���Ʊ����ϵͳ..............\n        ");
printf("\n***********************************************************************************\n\n");
printf("��ѡ��������Ҫ�Ĺ���:(1,2,3,4,5)\n");
scanf("%d",&choice);
switch(choice)
{


case 1:
	{
	  showmessage();          /*��ʾ���г�����Ϣ*/
      printf("\n��������������˵�\n");
      getch();
	  mainmenu();
	}
	 break;
case 2:
	{
      searchmenu();           /*�����ѯ�Ӳ˵�*/
	  printf("\n��������������˵�\n");
      getch();
	  mainmenu();
	}
	  break;
case 3:
	{
      reservemenu();            /*���붩Ʊϵͳ���˵�*/
	  printf("\n��������������˵�\n");
      getch();
	  mainmenu();
	}
	  break;
case 4:
	{
      returnticketsmenu();            /*���붩Ʊϵͳ���˵�*/
	  printf("\n��������������˵�\n");
      getch();
	  mainmenu();
	}
	  break;
case 5:
	{
      
	  printf("\n�����������ϵͳ���˵�\n");
      getch();
	  menu();
	}
	  break;

default:
	{
		printf("�������!!��ȷ����������Ϊ:(1,2,3,4,5)\n");
        printf("\n��������������˵�\n");
        getch();
	    mainmenu();
	}
	break;
}       
}

/*��ʼ������Ա�ṹ��*/
int guanliyuan1()
{
strcpy(gly.guanliyuanbianhao,"9527");
strcpy(gly.guanliyuanmima,"s13384964093");
strcpy(gly.xing,"ʯ");
strcpy(gly.ming,"��");
strcpy(gly.xingbie,"��");
strcpy(gly.lianxifangshi,"13384964093");
return 0;
}
 
/*����Ա��¼*/
void guanliyuadenglu()
{
char guanliyuanbianhao[20];        /*����Ա���*/
char guanliyuanmima[20];        /*����Ա������*/
char xing[20];      /*����Ա����*/
char ming[20];      /*����Ա����*/
char xingbie[10];         /*����Ա���Ա�*/

	printf("\n���������ı��:\n\n");
    scanf("%s",guanliyuanbianhao);
	printf("\n��������������:\n\n");
    scanf("%s",guanliyuanmima);
	printf("\n��������������:\n\n");
    scanf("%s",xing);
	printf("\n������������:\n\n");
    scanf("%s",ming);
	printf("\n�����������Ա�:\n\n");
    scanf("%s",xingbie);

if(strcmp(gly.guanliyuanbianhao,guanliyuanbianhao)==0&&strcmp(gly.guanliyuanmima,guanliyuanmima)==0&&strcmp(gly.xing,xing)==0&&strcmp(gly.ming,ming)==0&&strcmp(gly.xingbie,xingbie)==0)
{
	printf("\n��¼�ɹ�!��������������ϵͳ��ҳ��\n\n");
	getchar();
	getchar();
    guanlimenu();
}


else 
     {

	printf("\n\n\n\n������Ĺ�Ա��Ϣ����!!!!");
	printf("\n��¼ʧ��!�����������ϵͳ��ҳ��\n\n");
	getchar();
	getchar();
	menu();
     }

}



/*��ʼ��ע���û�������*/
int yonghuinitlist()
{   
	linklistyh h;
	h=(linklistyh)malloc(sizeof(lyhnode));
	if(!h)
	{
		printf("��ʼ������!");
		return 0;
	}
	(h)->next=NULL;
	yh=h;                       /*��yh����ע��ͻ������ͷ���*/
	return 1;
} 

/*���û�ע�ắ��*/
void zhuceyonghu(linklistyh h)
{
system("color 1f");           /*ʹ�����ɫ*/
system("mode con: cols=150 lines=1000");   /*������С*/
printf("*******************************��ӭ�������û�ע��ҳ��*******************************\n\n\n");
pyhnode p=h,q;
int i=0,choice;
char zhanghao[20];        /*�û����˺�*/
char mima[20];            /*�û�������*/
char yonghuxing[20];      /*�û�����*/
char yonghuming[20];      /*�û�����*/
char xingbie[10];         /*�û����Ա�*/
char zhengjianleixing[20];   /*֤������*/
char zhengjianhao[20];       /*֤����*/
char lianxifangshi[20];      /*�û���ϵ��ʽ*/

printf("��������Ҫע����˺�(ʮλ��)\n\n");
scanf("%s",zhanghao);
while(p)                                           /*������ע��˿�����,�����Ƿ���������*/
{
	if(strcmp(p->zhanghao,zhanghao)==0)
	{
		printf("���˺����Ѵ���,��������ע��!!\n\n");
       	printf("�����������ϵͳ���˵�!!\n\n");
		getchar();
		getchar();
		menu();
	}
	p=p->next;
}
printf("\n��������������\n\n");
scanf("%s",mima);
printf("\n��������������\n\n");
scanf("%s",yonghuxing);
printf("\n������������\n\n");
scanf("%s",yonghuming);
printf("\n�����������Ա�\n\n");
scanf("%s",xingbie);
printf("\n����������֤������\n\n");
scanf("%s",zhengjianleixing);
printf("\n����������֤����\n\n");
scanf("%s",zhengjianhao);
printf("\n������������ϵ��ʽ\n\n");
scanf("%s",lianxifangshi);

printf("\n\n\n\n��˶�����ע����Ϣ:\n");

printf("\n*******************************************************************************************************\n\n");
printf("\n    �˺�        ����       ������    ������    �Ա�     ֤������      ֤����             ��ϵ��ʽ\n");
printf("\n%s   %s      %s       %s       %s       %s    %s    %s\n",zhanghao,mima,yonghuxing,yonghuming,xingbie,zhengjianleixing,zhengjianhao,lianxifangshi);
printf("\n*******************************************************************************************************\n\n");
printf("\n�Ƿ�ȷ��ע��:(1-ȷ��,0-ȡ��)\n");
scanf("%d",&choice);

if(choice==0)                    /*����û�����������Ĵ���������˻����˵�����ע��*/
{
	printf("�����������ϵͳ���˵�!!\n\n");
		getchar();
		menu();
}
 
else if(choice==1)		
{ 
	q=(pyhnode)malloc(sizeof(lyhnode));        /*�ڵ���Ϣ¼��*/

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
  if(strcmp(q->xingbie,"��")==0)
printf("\n�𾴵�%s����,����ע��ɹ�!\n",q->yonghuxing);
else  printf("\n�𾴵�%sŮʿ,����ע��ɹ�!\n",q->yonghuxing);
 printf("\n�����������ϵͳ���˵�\n");
        getch();
	    menu();
}

/*�û���¼*/
void yonghudenglu(linklistyh h)
{
system("color 1f");           /*ʹ�����ɫ*/
system("mode con: cols=150 lines=1000");   /*������С*/
printf("*******************************��ӭ�������û���¼ҳ��*******************************\n\n\n");
pyhnode p=h;
int i=0;
char zhanghao[20];        /*�û����˺�*/
char mima[20];            /*�û�������*/
printf("�����������˺�\n\n");
scanf("%s",zhanghao);
printf("\n��������������\n\n");
scanf("%s",mima);
  while(p)                      /*����ע����Ϣ��ƥ����Ϣ*/
  {
	  if(strcmp(p->zhanghao,zhanghao)==0&&strcmp(p->mima,mima)==0)
	  {
		  if(strcmp(p->xingbie,"��")==0)
		  {
			 
			  printf("\n�𾴵�%s����,���ѵ�¼�ɹ�!!\n",p->yonghuxing);
              printf("\n����������붩Ʊϵͳ���˵�!!\n");
	          getchar();
			  getchar();
	          mainmenu();
		  }
		  else
		  {
			  printf("\n�𾴵�%sŮʿ,���ѵ�¼�ɹ�!!\n",p->yonghuxing);
              printf("\n����������붩Ʊϵͳ���˵�!!\n");
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
	 printf("\n\n��������˺Ż���������!!!������ʵ���ڵ�¼\n\n");
     printf("�����������ϵͳ���˵�!!\n\n");
	 getchar();
	 getchar();
	 menu();
  }
 printf("\n�����������ϵͳ���˵�\n");
        getch();
	    menu();
}

/*����ע���û�����*/
void bianliyonghu()
{
   pyhnode p=yh->next;
   int i=0,choice;
	while(p)
	{
       printf("\n*******************************************************************************************************\n\n");
printf("\n    �˺�        ����       ������    ������    �Ա�     ֤������      ֤����             ��ϵ��ʽ\n");
printf("\n%s   %s      %s       %s       %s       %s    %s    %s\n",p->zhanghao,p->mima,p->yonghuxing,p->yonghuming,p->xingbie,p->zhengjianleixing,p->zhengjianhao,p->lianxifangshi);
printf("\n*******************************************************************************************************\n\n\n\n\n\n\n");
p=p->next;
i++;
	}
	if(i==0)
		printf("\n\n-----------------��ʱ��û�г˿�ע����Ϣ-----------------\n\n");
	else
			printf("\n\n-----------------����%dλ�ͻ�ע��-----------------\n\n",i);
		printf("\n\n\n");
	printf("�Ƿ������ѯ(1-ȷ�� 2-ȡ��)\n");
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("\n\n����������ع���Ա��¼ҳ��\n");
	    getchar();
	    getchar();
    	guanlimenu();
	}
	else 
	{
        printf("\n\n�����������ϵͳ��ҳ��\n");
	    getchar();
		getchar();
    	menu();
	}
}

/*���û�ע��ָ��*/
void zhucezhinan()
{
  system("color 1f");           /*ʹ�����ɫ*/
system("mode con: cols=150 lines=1000");   /*������С*/
printf("*******************************��ӭ�������û�ע��ָ��ҳ��*******************************\n\n\n");
	printf("\t\t\t1.���뱾ϵͳ��������ע�����û�ѡ��\n\n");
    printf("\t\t\t2.��һ��дϵͳ����ʾ����Ϣ\n\n");
	printf("\t\t\t3.�˶�ע����Ϣ��׼ȷ�Ժ�������\n\n");
    printf("\t\t\t4.�ύ�û�ע����Ϣ\n\n");
	printf("\n�����������ϵͳ���˵�\n");
        getch();
	    menu();
}


/*��ʼ���ͻ���Ϣ����*/
int maninitlist(linklistman *h)
{
	*h=(linklistman)malloc(sizeof(manlinklist));
	if(!h)
	{
		printf("��ʼ������!");
		return 0;
	}
	(*h)->next=NULL;
	return 1;

} 

/*�ͻ���Ϣ����*/
int manlistinsert(linklistman h)
{
	pman p;
	char man_time[20],man_trainnum[20],man_name[20],phone[20],ic[20],order_num[30],man_start[20],man_arrive[20];
	int i,man_box[20],man_table[20],man_count[20],money,amount;
     printf("������: ��Ʊʱ��    ���α��   ��Ʊ������   ��Ʊ����ϵ��ʽ   ֤����   ������   ���վ   �յ�վ   Ʊ��   ��Ʊ��\n");
       scanf("%s %s %s %s %s %s %s %s %d %d",man_time,man_trainnum,man_name,phone,ic,order_num,man_start,man_arrive,&money,&amount);
	 	for(i=0;i<amount;i++)
		{
			printf("�����   ��λ��   �ۿ�\n");
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



/*�ͻ���Ϣ�������*/
void traversemanlinklist()
{
	int i,j=0,k=0,l,m=0,n,choice;         /*i������ѭ���еı�����j��һ�����������Ƿ�˿���Ϣ�Ƿ�Ϊ��*/
    for(i=0;i<MAXSIZE;i++)         /*k��Ӫҵ���ۼ�����l����λ��������m����Ʊ���ۼ�����n��ÿ�����γ˿��ۼ���*/
    {
	 printf("\n\n���α��:%s\n\n\n",trin[i].train_num);
	pman p=trin[i].h_man->next;
     n=0;
	while(p)
	{
       
		printf("\n\n��Ʊ�˿͵���Ϣ:\n\n\n");
	    printf("***************************************************************************************************************************************************\n\n\n");
       	printf("��Ʊʱ��    ���α��   ��Ʊ������     ���վ   �յ�վ    Ʊ��   ��Ʊ��   ��Ʊ����ϵ��ʽ            ֤����                       ������      \n\n");
	    printf(" %s       %s    %s          %s     %s     %d     %d        %s       %s       %s\n\n",p->man_time,p->man_trainnum,p->man_name,p->man_start,p->man_arrive,p->money,p->amount,p->phone,p->ic,p->order_num);
	   printf("****************************************************************************************************************************************************\n\n\n");
      k+=p->money;
	  m+=p->amount;
		printf("\n�ó˿͵Ķ�Ʊ��Ϣ:\n\n");
		printf("**************************\n\n");
       	for(l=0;l<p->amount;l++)
		{
			printf("�����   ��λ��   �ۿ�\n\n");
			printf("  %d        %d      %-5.2lf\n\n",p->man_box[l],p->man_table[l],p->man_count[l]);
		}
		p=p->next;
		j++;
		printf("**************************\n\n\n");
		n++;
	}
     if(n==0)
		 printf("\n\n----------------------------���޳˿���Ϣ!----------------------------\n\n");
	}
		
		if(j==0)
		printf("\n\n\n�Բ�����ʱû�г˿���Ϣ!!!");
		printf("\n\n\n--------------���չ��۳�%d��Ʊ--------------\n",m);
		printf("\n\n\n--------------����Ӫҵ��Ϊ%dԪ--------------\n\n\n",k);
	printf("\n\n\n");
	printf("�Ƿ������ѯ(1-ȷ�� 2-ȡ��)\n");
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("\n\n����������ع���Ա��¼ҳ��\n");
	    getchar();
	    getchar();

    	guanlimenu();
	}
	else 
	{
        printf("\n\n����������ع���Ա��¼ҳ��\n");
	    getchar();
		getchar();

    	menu();
	}

}

/*�ͻ���Ϣ��������ҵ���Ӧ����Ӧ�ĳ˿Ͳ�����ó˿���Ϣ*/
void traversemanlinklistadd2(linklistman h,char man_name[20],char ic[20])
{
 pman p=h->next;
 int k=0,i;
	while(p)
	{
	   if((!strcmp(man_name,p->man_name))&&(!strcmp(ic,p->ic)))    /*����иó˿͵���Ϣ*/
	   {
          
		printf("\n\n��Ʊ�˿͵���Ϣ:\n\n\n");
	    printf("***************************************************************************************************************************************************\n\n\n");
       	printf("��Ʊʱ��    ���α��   ��Ʊ������     ���վ   �յ�վ    Ʊ��   ��Ʊ��   ��Ʊ����ϵ��ʽ            ֤����                       ������      \n\n");
	    printf(" %s       %s    %s          %s     %s     %d     %d        %s       %s       %s\n\n",p->man_time,p->man_trainnum,p->man_name,p->man_start,p->man_arrive,p->money,p->amount,p->phone,p->ic,p->order_num);
	   printf("****************************************************************************************************************************************************\n\n\n");
       
		printf("\n�ó˿͵Ķ�Ʊ��Ϣ:\n\n");
		printf("**************************\n\n");
       	for(i=0;i<p->amount;i++)
		{
			printf("�����   ��λ��   �ۿ�\n\n");
			printf("  %d        %d      %-5.2lf\n\n",p->man_box[i],p->man_table[i],p->man_count[i]);
		}
		printf("**************************\n\n\n");
		   
		k++;
		break;
	   }
      	p=p->next;
	}
	if(k==0)
		printf("\nû�и��û��Ķ�Ʊ��Ϣ!!\n");

}

/*�����˿���Ϣ��ɾ����Ӧ���*/
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


/*��ʼ���������ó�����Ϣ�ṹ�еĿͻ���Ϣ��,ָ��ͻ���Ϣ�����ͷָ��*/
void pointhead()
{
	int i=0;
 traininfo *info;              /*����һ��ָ�򳵴���Ϣ�ṹ���ָ��info*/
	info=trin;                    /*infoָ�򳵴���Ϣ�ṹ���������Ԫ��*/
    while(i<MAXSIZE)
	{
       linklistman h;         /*���峵Ʊ��Ϣ����ͷ����ָ��*/
        maninitlist(&h);       /*��ʼ������*/
	   info->h_man=h;         /*��info�е�h_tickets����Ϊ��Ʊ��Ϣ�����ͷָ��*/
	   i++;
	   info++;
	   }
}



/*��Ʊ��Ϣ����ĳ�ʼ��*/
int ticketsinitlist(linklisttickets *h)
{

	*h=(linklisttickets)malloc(sizeof(ticketslinklist));
	if(!h)
	{
		printf("��ʼ������!");
		return 0;
	}
	(*h)->next=NULL;
	return 1;

}

/*��Ʊ��Ϣ����Ĳ���*/
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


/*������Ʊ��Ϣ����*/
void traverselisttickets(linklisttickets h)
{ 
	int i=1,j=0;
ptickets p=h->next;
while(p)
{
	printf("��Ʊ���   �����   ��λ��   Ʊ���ۿ� :");
printf("   %d     %d    %d    %-5.2lf       ",p->tickets_num,p->tickets_box,p->tickets_table,p->count);
p=p->next;

if(i%2==0)
printf("\n\n");
i++;
j++;
}
printf("\n\n-----��%d��Ʊ-----\n\n",j);
printf("\n");
}

/*����Ʊ�۵�����ɾ����Ӧ���*/
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



/*��Ϣ���溯��*/
void save()
{
	int i;
	FILE *fp; 
	if((fp=fopen("stu.dat","wb"))==NULL)   /*wb��Ϊ��������ݣ���һ���������ļ����ָ���ļ������ڣ������µ��ļ�*/
	{
		printf("���ļ�ʧ��!!\n");
		return ;
	}
for(i=0;i<MAXSIZE;i++)
	if(fwrite(&trin[i],sizeof(struct  train),1,fp)!=1)
	printf("flie write error\n");
	fclose(fp);
}

/*��Ʊ��Ϣ¼��*/
void createtraininfo()
{   

	traininfo *info;              /*����һ��ָ��Ʊ��Ϣ�ṹ���ָ��info*/
    int i=0;
	info=trin;                    /*infoָ��ṹ�������е�һ��Ԫ��*/
	while(i<MAXSIZE)              /*¼���Ʊ��Ϣ*/
	{
       printf("\n���α��   ����ʱ��   ����վ   ����վ   ����ʱ��   ������   ÿ�ڳ�����λ��   ʣ��Ʊ��  ��㵽�յ�ľ���(km)   վ����Ϣ  \n\n");
	   scanf("%s %s %s %s %s %d %d %d %d %s %s %s %d %d %s %s %s %d %d %s %s %s %d %d %s %s %s %d %d %s %s %s %d %d",info->train_num,info->train_starttime,info->train_start,info->train_arrive,info->train_arrivetime,&info->train_box,&info->train_table,&info->train_tickets,&info->train_mileage,info->station[0].sta_name,info->station[0].arrivetime,info->station[0].starttime,&info->station[0].sta_money,&info->station[0].mileage,info->station[1].sta_name,info->station[1].arrivetime,info->station[1].starttime,&info->station[1].sta_money,&info->station[1].mileage,info->station[2].sta_name,info->station[2].arrivetime,info->station[2].starttime,&info->station[2].sta_money,&info->station[2].mileage,info->station[3].sta_name,info->station[3].arrivetime,info->station[3].starttime,&info->station[3].sta_money,&info->station[3].mileage,info->station[4].sta_name,info->station[4].arrivetime,info->station[4].starttime,&info->station[4].sta_money,&info->station[4].mileage);
	   save();
       i++;
	   info++;
	}
   
}

/*��ʾ���복����Ϣ��ԭʼ����*/

int showmessage()
{	traininfo *info;              /*����һ��ָ�򳵴���Ϣ�ṹ���ָ��info*/
    int i=0;
	info=trin;   
	
for(i=0;i<MAXSIZE;i++)
	 {    
		
	if(i<=1)
	{
			printf("********************************************************************************************************************\n\n");
        printf(" ����      ����ʱ��    ����վ     �յ�վ     ����ʱ��     ������     ��λ��     ʣ��Ʊ��      ��㵽�յ�ľ���(km)\n\n ");
     	printf("%s   %s      %s      %s       %s           %d         %d          %d              %d\n\n\n",info[i].train_num,info[i].train_starttime,info[i].train_start,info[i].train_arrive,info[i].train_arrivetime,info[i].train_box,info[i].train_table,info[i].train_tickets,info[i].train_mileage);
		printf("    վ��:     %s        %s        %s        %s        %s\n",info[i].station[0].sta_name,info[i].station[1].sta_name,info[i].station[2].sta_name,info[i].station[3].sta_name,info[i].station[4].sta_name);
        printf("��վʱ��:    %s        %s         %s       %s         %s\n",info[i].station[0].arrivetime,info[i].station[1].arrivetime,info[i].station[2].arrivetime,info[i].station[3].arrivetime,info[i].station[4].arrivetime);  
        printf("��վʱ��:    %s        %s         %s       %s         %s\n",info[i].station[0].starttime,info[i].station[1].starttime,info[i].station[2].starttime,info[i].station[3].starttime,info[i].station[4].starttime);  
        printf("Ʊ��(Ԫ):      %d           %d            %d         %d           %d\n",info[i].station[0].sta_money,info[i].station[1].sta_money,info[i].station[2].sta_money,info[i].station[3].sta_money,info[i].station[4].sta_money);  
        printf("���(km):      %d           %d           %d         %d          %d\n",info[i].station[0].mileage,info[i].station[1].mileage,info[i].station[2].mileage,info[i].station[3].mileage,info[i].station[4].mileage);
		printf("\n********************************************************************************************************************\n\n\n\n\n\n\n\n"); 
		getch();
	}
	else 
	{
      printf("********************************************************************************************************************\n\n");
        printf(" ����      ����ʱ��    ����վ     �յ�վ     ����ʱ��     ������     ��λ��     ʣ��Ʊ��      ��㵽�յ�ľ���(km)\n\n ");
     	printf("%s   %s      %s      %s       %s           %d         %d          %d              %d\n\n\n",info[i].train_num,info[i].train_starttime,info[i].train_start,info[i].train_arrive,info[i].train_arrivetime,info[i].train_box,info[i].train_table,info[i].train_tickets,info[i].train_mileage);
		printf("    վ��:     %s        %s          %s        %s          %s\n",info[i].station[0].sta_name,info[i].station[1].sta_name,info[i].station[2].sta_name,info[i].station[3].sta_name,info[i].station[4].sta_name);
        printf("��վʱ��:    %s        %s         %s       %s         %s\n",info[i].station[0].arrivetime,info[i].station[1].arrivetime,info[i].station[2].arrivetime,info[i].station[3].arrivetime,info[i].station[4].arrivetime);  
        printf("��վʱ��:    %s        %s         %s       %s         %s\n",info[i].station[0].starttime,info[i].station[1].starttime,info[i].station[2].starttime,info[i].station[3].starttime,info[i].station[4].starttime);  
        printf("Ʊ��(Ԫ):      %d           %d            %d         %d           %d\n",info[i].station[0].sta_money,info[i].station[1].sta_money,info[i].station[2].sta_money,info[i].station[3].sta_money,info[i].station[4].sta_money);  
        printf("���(km):      %d           %d           %d         %d           %d\n",info[i].station[0].mileage,info[i].station[1].mileage,info[i].station[2].mileage,info[i].station[3].mileage,info[i].station[4].mileage);
		printf("\n********************************************************************************************************************\n\n\n\n\n\n\n\n"); 
		getch();
	}
	 }               /*����Ļ������ļ��е�����*/

		return 0;
}

/*���복����Ϣ����*/
int showmessage1()
{	traininfo *info;              /*����һ��ָ�򳵴���Ϣ�ṹ���ָ��info*/
    int i=0;
	info=trin;   

		FILE *fp;                 /*fpΪָ���ļ���ָ��*/
	if((fp=fopen("stu.dat","rb"))==NULL)      /*fopenΪ���ļ�����*/
	{
		printf("���ļ�ʧ��!!\n");
		return 0;
	}
	 for(i=0;i<MAXSIZE;i++)
	 {    
			fread(&info[i],sizeof(struct train),1,fp);       /*��ȡ�ļ���Ϣ*/
       
	 }               /*����Ļ������ļ��е�����*/
		fclose(fp);  /*�ر��ļ���ֹ�ļ���ʧ*/

		return 0;
}



/*���복Ʊ��Ϣ����*/
void createtickets()
{
	int i=0,j,k,m=1;
	
	double count;
    traininfo *info,*p;              /*����һ��ָ�򳵴���Ϣ�ṹ���ָ��info*/
	info=trin;                    /*infoָ�򳵴���Ϣ�ṹ���������Ԫ��*/

    while(i<MAXSIZE)
	{
       linklisttickets h;         /*���峵Ʊ��Ϣ����ͷ����ָ��*/
       ticketsinitlist(&h);       /*��ʼ������*/
	   info->h_tickets=h;         /*��info�е�h_tickets����Ϊ��Ʊ��Ϣ�����ͷָ��*/
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
			 ticketslistinsert(p->h_tickets,m,j,k,count);    /*���ó�Ʊ��Ϣ����Ĳ��뺯��*/
			 m++;
			}
			i++;
			p++;
	}
}


/*�����α�Ų�ѯ*/
void searchbynumber()
{
 traininfo *info;              /*����һ��ָ�򳵴���Ϣ�ṹ���ָ��info*/
 info=trin;                    /*infoָ�򳵴���Ϣ�ṹ���������Ԫ��*/
 int choice;
 char number[10];
 int i=0,j=0;
 printf("�����복�α��:\n");
 scanf("%s",number);
 while(i<MAXSIZE)
 {
	  if(!strcmp(number,info[i].train_num))       /*����ҵ���������Ϣ�����*/
	 {
		printf("\n������Ϣ:\n\n\n");
		printf("********************************************************************************************************************\n\n");
        printf(" ����      ����ʱ��    ����վ     �յ�վ     ����ʱ��     ������     ��λ��     ʣ��Ʊ��      ��㵽�յ�ľ���(km)\n\n ");
     	printf("%s   %s      %s      %s       %s           %d         %d          %d              %d\n\n\n",info[i].train_num,info[i].train_starttime,info[i].train_start,info[i].train_arrive,info[i].train_arrivetime,info[i].train_box,info[i].train_table,info[i].train_tickets,info[i].train_mileage);
		printf("    վ��:     %s        %s        %s        %s        %s\n",info[i].station[0].sta_name,info[i].station[1].sta_name,info[i].station[2].sta_name,info[i].station[3].sta_name,info[i].station[4].sta_name);
        printf("��վʱ��:    %s        %s         %s       %s         %s\n",info[i].station[0].arrivetime,info[i].station[1].arrivetime,info[i].station[2].arrivetime,info[i].station[3].arrivetime,info[i].station[4].arrivetime);  
        printf("��վʱ��:    %s        %s         %s       %s         %s\n",info[i].station[0].starttime,info[i].station[1].starttime,info[i].station[2].starttime,info[i].station[3].starttime,info[i].station[4].starttime);  
        printf("Ʊ��(Ԫ):      %d           %d            %d         %d           %d\n",info[i].station[0].sta_money,info[i].station[1].sta_money,info[i].station[2].sta_money,info[i].station[3].sta_money,info[i].station[4].sta_money);  
        printf("���(km):      %d           %d           %d         %d          %d\n",info[i].station[0].mileage,info[i].station[1].mileage,info[i].station[2].mileage,info[i].station[3].mileage,info[i].station[4].mileage);
		printf("\n********************************************************************************************************************\n\n\n\n\n\n\n\n"); 
		
		printf("ʣ��Ʊ��Ϣ:\n\n\n");
       
		getch();
        printf("*********************************************************************************************************************************************\n\n\n");
        traverselisttickets(info[i].h_tickets);      /*����ó���ʣ��Ʊ����Ϣ*/
	    printf("********************************************************************************************************************************************\n\n");
      
		j++;
	 }
	 i++;
	 
 }
 if(j==0)
 {
	 printf("�Բ���,û������������Ϣƥ��ĳ���!\n");
	 printf("\n����������ز�ѯ�Ӳ˵�\n");
	 getch();
	 searchmenu();
 }
 else
 {          printf("�Ƿ������ѯ:(1-ȷ��,2-ȡ��)\n");
            scanf("%d",&choice);
            switch(choice)
			{
			case 1:
				{
				     printf("����������ز�ѯ�Ӳ˵�:\n");
		             getch();
		             searchmenu();                      /*��ѯ�Ӳ˵�����*/
				}
				      break;
			case 2:
				{
                      printf("\n��������������˵�\n");
	                  getch();
	                  mainmenu();                       /*��ѯ���˵�*/
				}
				    break;
        	default:
				{
		             printf("�������!!ȷ����������Ϊ(1,2)\n");
		             printf("����������ز�ѯ�Ӳ˵�\n");
			         getch();
			         searchmenu();                   /*��ѯ�Ӳ˵�����*/
			}
		    break;


			}
		   
}
		   
}

/*���յ�վ��ѯ*/
void searchbyaddress()
{
 traininfo *info;              /*����һ��ָ�򳵴���Ϣ�ṹ���ָ��info*/
 info=trin;                    /*infoָ�򳵴���Ϣ�ṹ���������Ԫ��*/
  int choice;
 char name1[20];
 char name2[20];
 int i=0,j=0,k=0;
 printf("�����������ڳ��е�����:");
 scanf("%s",name1);
 printf("\n\n\n��������Ҫ�ִ���е�����:");
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
		printf("\n������Ϣ:\n\n\n");
		printf("********************************************************************************************************************\n\n");
        printf(" ����      ����ʱ��    ����վ     �յ�վ     ����ʱ��     ������     ��λ��     ʣ��Ʊ��      ��㵽�յ�ľ���(km)\n\n ");
     	printf("%s   %s      %s      %s       %s           %d         %d          %d              %d\n\n\n",info[i].train_num,info[i].train_starttime,info[i].train_start,info[i].train_arrive,info[i].train_arrivetime,info[i].train_box,info[i].train_table,info[i].train_tickets,info[i].train_mileage);
		printf("    վ��:     %s        %s        %s        %s        %s\n",info[i].station[0].sta_name,info[i].station[1].sta_name,info[i].station[2].sta_name,info[i].station[3].sta_name,info[i].station[4].sta_name);
        printf("��վʱ��:    %s        %s         %s       %s         %s\n",info[i].station[0].arrivetime,info[i].station[1].arrivetime,info[i].station[2].arrivetime,info[i].station[3].arrivetime,info[i].station[4].arrivetime);  
        printf("��վʱ��:    %s        %s         %s       %s         %s\n",info[i].station[0].starttime,info[i].station[1].starttime,info[i].station[2].starttime,info[i].station[3].starttime,info[i].station[4].starttime);  
        printf("Ʊ��(Ԫ):      %d           %d            %d         %d           %d\n",info[i].station[0].sta_money,info[i].station[1].sta_money,info[i].station[2].sta_money,info[i].station[3].sta_money,info[i].station[4].sta_money);  
        printf("���(km):      %d           %d           %d         %d          %d\n",info[i].station[0].mileage,info[i].station[1].mileage,info[i].station[2].mileage,info[i].station[3].mileage,info[i].station[4].mileage);
		printf("\n********************************************************************************************************************\n\n\n\n\n\n\n\n"); 
		   printf("ʣ��Ʊ��Ϣ:\n\n\n");
		 printf("*********************************************************************************************************************************************\n\n\n");
         traverselisttickets(info[i].h_tickets);      /*����ó���ʣ��Ʊ����Ϣ*/
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
	 printf("\n�Բ���,û������������Ϣƥ��ĳ���!\n");
	 printf("\n����������ز�ѯ�Ӳ˵�\n");
	 getch();
	 searchmenu();
 }
  else
 {          printf("�Ƿ������ѯ:(1-ȷ��,2-ȡ��)\n");
            scanf("%d",&choice);
            switch(choice)
			{
			case 1:
				{
				     printf("����������ز�ѯ�Ӳ˵�:\n");
		             getch();
		             searchmenu();                      /*��ѯ�Ӳ˵�����*/
				}
				      break;
			case 2:
				{
                      printf("\n��������������˵�\n");
	                  getch();
	                  mainmenu();                       /*��ѯ���˵�*/
				}
				    break;
        	default:
				{
		             printf("�������!!ȷ����������Ϊ(1,2)\n");
		             printf("����������ز�ѯ�Ӳ˵�\n");
			         getch();
			         searchmenu();                   /*��ѯ�Ӳ˵�����*/
				}
		    break;


			}
		   
}

}






/*��ѯ��Ϣ�����˵�*/
void searchmenu()
{
	system("color 1f");           /*ʹ�����ɫ*/
    system("mode con: cols=150  lines=1000");   /*������С*/
	int choice;
printf("\n��Ʊ��ѯϵͳ���˵�\n");
printf("\n����: 2015/6/20\n\n");
printf("***********************************************************************************\n\n");

    printf("              1.����κŲ�ѯ........................\n\n");
	printf("              2.��������յ��ѯ....................\n\n");
	printf("              3.�������˵�..........................\n\n");
printf("***********************************************************************************\n");
	printf("\n��ѡ��������Ҫ�Ĺ���:(1,2,3)\n");
	scanf("%d",&choice);
	switch(choice)
	{
	case 1:searchbynumber();break;          /*���ð���κŲ�ѯ����*/
	case 2:searchbyaddress();break;         /*���ð��յ��ѯ����*/
	
	case 3:{
		    printf("��������������˵�:\n");
		    getch();
		    mainmenu();                      /*���˵�����*/
		   }
		   break;
	default:{
		      printf("�������!!ȷ����������Ϊ(1,2,3)\n");
		      printf("��������������˵�\n");
			  getch();
			  mainmenu();                   /*���˵�����*/
			}
		    break;

	}
}





/*��Ʊϵͳ�����˵�*/
void reservemenu()
{
	system("color 1f");           /*ʹ�����ɫ*/
    system("mode con: cols=150  lines=1000");   /*������С*/
	int choice;
printf("\n��Ʊ��Ʊϵͳ���˵�\n");
printf("\n����: 2015/6/20\n\n");
printf("***********************************************************************************\n\n");

    printf("              1.��Ʊҵ��........................\n\n");
	printf("              2.�������˵�..........................\n\n");
printf("***********************************************************************************\n");
	printf("\n��ѡ��������Ҫ�Ĺ���:(1,2)\n");
	scanf("%d",&choice);
	switch(choice)
	{
	case 1:reservebynumber();break;          /*���ð���κŶ�Ʊ����*/

	case 2:{
		    printf("��������������˵�:\n");
		    getch();
		    mainmenu();                      /*���˵�����*/
		   }
		   break;
	default:{
		      printf("�������!!ȷ����������Ϊ(1,2)\n");
		      printf("����������ض�Ʊϵͳ���˵�\n");
			  getch();
			   mainmenu();                /*��Ʊϵͳ���˵�����*/
			}
		    break;

	}
}

/*�����ζ�Ʊ����*/
void reservebynumber()
{ 
	char train_num[20],man_start[20],man_arrive[20],man_time[20],man_trainnum[20],man_name[20],phone[20],ic[20];
	int i=0,j=0,choice1,choice2,choice3,amount,choice_box,choice_table,stationmoneya,stationmoneys,stationmileagea,stationmileages,mileage,man_box[20],man_table[20];
    double choice_count,man_count[20],count=0,money;
	traininfo *info,*p;                              /*infoΪָ�򳵴���Ϣ��ָ��*/
	info=trin;                                    /*infoָ��frin[5]�ṹ������ĵ�һ��Ԫ�ؼ�frin[0]*/
    printf("�����복�α��:\n");
	scanf("%s",train_num);
    
    
    while(i<MAXSIZE)
 {
	  if(!strcmp(train_num,info[i].train_num))       /*����ҵ���������Ϣ�����*/
	 {
		printf("\n������Ϣ:\n\n\n");
      	if(i<=1)
	{
			printf("********************************************************************************************************************\n\n");
        printf(" ����      ����ʱ��    ����վ     �յ�վ     ����ʱ��     ������     ��λ��     ʣ��Ʊ��      ��㵽�յ�ľ���(km)\n ");
     	printf("%s   %s      %s      %s       %s           %d         %d          %d              %d\n\n\n",info[i].train_num,info[i].train_starttime,info[i].train_start,info[i].train_arrive,info[i].train_arrivetime,info[i].train_box,info[i].train_table,info[i].train_tickets,info[i].train_mileage);
		printf("    վ��:     %s        %s        %s        %s        %s\n",info[i].station[0].sta_name,info[i].station[1].sta_name,info[i].station[2].sta_name,info[i].station[3].sta_name,info[i].station[4].sta_name);
        printf("��վʱ��:    %s        %s         %s       %s         %s\n",info[i].station[0].arrivetime,info[i].station[1].arrivetime,info[i].station[2].arrivetime,info[i].station[3].arrivetime,info[i].station[4].arrivetime);  
        printf("��վʱ��:    %s        %s         %s       %s         %s\n",info[i].station[0].starttime,info[i].station[1].starttime,info[i].station[2].starttime,info[i].station[3].starttime,info[i].station[4].starttime);  
        printf("Ʊ��(Ԫ):      %d           %d            %d         %d           %d\n",info[i].station[0].sta_money,info[i].station[1].sta_money,info[i].station[2].sta_money,info[i].station[3].sta_money,info[i].station[4].sta_money);  
        printf("���(km):      %d           %d           %d         %d          %d\n",info[i].station[0].mileage,info[i].station[1].mileage,info[i].station[2].mileage,info[i].station[3].mileage,info[i].station[4].mileage);
		printf("\n********************************************************************************************************************\n\n\n\n\n\n\n\n"); 
	
	}
	else 
	{
      printf("********************************************************************************************************************\n\n");
        printf(" ����      ����ʱ��    ����վ     �յ�վ     ����ʱ��     ������     ��λ��     ʣ��Ʊ��      ��㵽�յ�ľ���(km)\n ");
     	printf("%s   %s      %s      %s       %s           %d         %d          %d              %d\n\n\n",info[i].train_num,info[i].train_starttime,info[i].train_start,info[i].train_arrive,info[i].train_arrivetime,info[i].train_box,info[i].train_table,info[i].train_tickets,info[i].train_mileage);
		printf("    վ��:     %s        %s          %s        %s          %s\n",info[i].station[0].sta_name,info[i].station[1].sta_name,info[i].station[2].sta_name,info[i].station[3].sta_name,info[i].station[4].sta_name);
        printf("��վʱ��:    %s        %s         %s       %s         %s\n",info[i].station[0].arrivetime,info[i].station[1].arrivetime,info[i].station[2].arrivetime,info[i].station[3].arrivetime,info[i].station[4].arrivetime);  
        printf("��վʱ��:    %s        %s         %s       %s         %s\n",info[i].station[0].starttime,info[i].station[1].starttime,info[i].station[2].starttime,info[i].station[3].starttime,info[i].station[4].starttime);  
        printf("Ʊ��(Ԫ):      %d           %d            %d         %d           %d\n",info[i].station[0].sta_money,info[i].station[1].sta_money,info[i].station[2].sta_money,info[i].station[3].sta_money,info[i].station[4].sta_money);  
        printf("���(km):      %d           %d           %d         %d           %d\n",info[i].station[0].mileage,info[i].station[1].mileage,info[i].station[2].mileage,info[i].station[3].mileage,info[i].station[4].mileage);
		printf("\n********************************************************************************************************************\n\n\n\n\n\n\n\n"); 
		
	}	
	    printf("ʣ��Ʊ��Ϣ:\n\n\n");
        getch();
		printf("*********************************************************************************************************************************************\n\n\n");
        traverselisttickets(info[i].h_tickets);      /*����ó���ʣ��Ʊ����Ϣ*/
	    printf("*********************************************************************************************************************************************\n\n\n");
      	j++;
		p=&info[i];                                     /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	    break;
	 }
	 i++;
	 
 }
      
	if(j==0)
 
	printf("�Բ���,û������������Ϣƥ��ĳ���!\n");

	printf("��ܰ��ʾ:\n\n");
	printf("*************************************\n");
	printf("*                                   *");
	printf("\n*  �����û�ҵ���Ҫ���ҵİ����Ϣ,  *\n");
	printf("*                                   *");
    printf("\n*  ������Ҫ�ҵ��г��ѷ���������Ʊ   *\n");
    printf("*                                   *");
    printf("\n*  ��С����Ҫ��Ʊ��,������������    *\n");
    printf("*                                   *");
    printf("\n*  �����յ��ѯ��������Ϣѡ����   *\n");
    printf("*                                   *");
    printf("\n*  ����ε��г�!лл����!!          *\n");
    printf("*                                   *");
    printf("\n*************************************\n\n\n");


	printf("�Ƿ�ת����ѯ���˵�(1-ȷ��,0-ȡ��):\n");
	scanf("%d",&choice1);
	if(choice1!=0)
	{
	 printf("����������ز�ѯ���˵�\n");
	 getch();
	 searchmenu();                 /*��ѯϵͳ���˵�����*/
	}
    printf("\n\n\n������: ��Ʊʱ��    ���α��   ��Ʊ������   ��Ʊ����ϵ��ʽ   ֤����   ���վ   �յ�վ   ��Ʊ��\n\n");
    scanf("%s %s %s %s %s %s %s %d",man_time,man_trainnum,man_name,phone,ic,man_start,man_arrive,&amount);
	printf("\n\n������ʣ��Ʊ��ѡ����ϲ���ĳ���š���λ�š��ۿ�:\n\n");
	for(i=0;i<amount;i++)                  /*�˿�����Ҫ��������λ��*/
	{
     printf("�����  ��λ��  �ۿ�\n");
	 scanf("%d %d %lf",&choice_box,&choice_table,&choice_count);
     man_box[i]=choice_box;
	 man_table[i]=choice_table;
     man_count[i]=choice_count;
     count+=choice_count;                  /*�������ۼ�*/
	 p->train_tickets--;                /*�����Ϣ��ʣ��Ʊ����һ*/
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



    money=(stationmoneya-stationmoneys)*count;                 /*�õ��ͻ���Ϣ�е�Ʊ��*/
    mileage=(stationmileagea-stationmileages);
	printf("\n������֧��%dԪ\n\n",(int)money);
	printf("\n�Ƿ�ȷ��֧��(1-ȷ��,0-ȡ��)\n\n");
	scanf("%d",&choice2);
		if(choice2==0)
	{
	 printf("����������ػ𳵹���ϵͳ���˵�\n");
	 getch();
	 mainmenu();                 /*�𳵹���ϵͳ���˵�����*/
	}


   

      /*�ڿͻ���Ϣ�����в���һ�����*/
	pman q;
	q=(pman)malloc(sizeof(manlinklist));
	strcpy(q->man_time,man_time);
	strcpy(q->man_trainnum,man_trainnum);
	strcpy(q->man_name,man_name);
	strcpy(q->phone,phone);
	strcpy(q->ic,ic);
	strcat(man_trainnum,ic);                                    /*�õ��ͻ���Ϣ�еĶ����ţ����κ�+���֤�ţ�*/
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
	printf("\n\n\n\n\n-------------����Ʊ�ѳɹ�!�����ڸð���г�����ǰ30���ӽ�վ�򳵸�л��ʹ��--------------\n\n\n\n");
	
     for(i=0;i<amount;i++)
	 {
printf("\n\n******************************************************\n");
printf("*                                                    *\n");
printf("    ���α��:%s                               \n",train_num);
printf("*                                                    *\n");
printf("                                                    \n");
printf("*                                                    *\n");
printf("               %s----------%s                    \n",man_start,man_arrive);
printf("*                                                    *\n");
printf("                  (ȫ��%dkm)                       \n",mileage);
printf("*                                                    *\n");
printf("                                                    \n");
printf("*           �����:%d       ��λ��:%d                  *\n",man_box[i],man_table[i]);
printf("                                                    \n");
printf("*                                                    *\n");
printf("        ������:%s           \n",man_trainnum);
printf("*                                                    *\n");
printf("                             ����: 2015/6/20         \n");
printf("******************************************************\n\n\n\n");
  
	 }

 printf("�Ƿ�����˿���Ϣ(1-�˿���Ϣ,2-���س�Ʊ����ϵͳ���˵�)\n");
            scanf("%d",&choice3);
            switch(choice3)
			{
			case 1:
				{
				     printf("���������ѯ�˿���Ϣ:\n");
		             getch();
				     traversemanlinklistadd2(p->h_man,man_name,ic);
					                      /*��ѯ�˿���Ϣ*/
					  printf("\n����������س�Ʊ����ϵͳ���˵�\n");
	                  getch();
	                  mainmenu();                      /*���س�Ʊ����ϵͳ���˵�*/
				}
				break;
			case 2:
				{
                      printf("\n����������س�Ʊ����ϵͳ���˵�\n");
	                  getch();
	                  mainmenu();                      /*���س�Ʊ����ϵͳ���˵�*/
				}
				    break;

		
        	default:
				{
		             printf("�������!!ȷ����������Ϊ(1,2,3)\n");
		             printf("����������س�Ʊ����ϵͳ���˵�\n");
			         getch();
			         mainmenu();                   /*��ѯ�Ӳ˵�����*/
				}
		    break;


			}

   


}




/*��Ʊϵͳ�����˵�*/
void returnticketsmenu()
{
	system("color 1f");           /*ʹ�����ɫ*/
    system("mode con: cols=150  lines=1000");   /*������С*/
	int choice;
printf("\n��Ʊ��Ʊϵͳ���˵�\n");
printf("\n����: 2015/6/20\n\n");
printf("***********************************************************************************\n\n");

    printf("              1.��Ʊҵ��........................\n\n");
	printf("              2.�������˵�..........................\n\n");
printf("***********************************************************************************\n");
	printf("\n��ѡ��������Ҫ�Ĺ���:(1,2)\n");
	scanf("%d",&choice);
	switch(choice)
	{
	case 1:returntickets();break;          /*���ð���κŶ�Ʊ����*/

	case 2:{
		    printf("��������������˵�:\n");
		    getch();
		    mainmenu();                      /*���˵�����*/
		   }
		   break;
	default:{
		      printf("�������!!ȷ����������Ϊ(1,2)\n");
		      printf("����������ض�Ʊϵͳ���˵�\n");
			  getch();
			   mainmenu();                 /*��Ʊϵͳ���˵�����*/
			}
		    break;

	}
}

/*��Ʊ����*/
void returntickets()
{   
	traininfo *info,*q;                              /*infoΪָ�򳵴���Ϣ��ָ��*/
	info=trin;                                    /*infoָ��frin[5]�ṹ������ĵ�һ��Ԫ�ؼ�frin[0]*/
    char man_name[20],ic[20],man_trainnum[20],man_start[20],man_arrive[20];
	int a,b,c,k=0,i=0,j=0,money,man_box,man_table,choice3;
	double count;
	printf("\n\n����������������֤���š����α�š���㡢�յ㡢����š���λ�š��ۿ�\n\n");
	scanf("%s %s %s %s %s %d %d %lf",man_name,ic,man_trainnum,man_start,man_arrive,&man_box,&man_table,&count);

    while(i<MAXSIZE)
 {
	  if(!strcmp(man_trainnum,info[i].train_num))       /*����ҵ���������Ϣ�����*/
	 {
	
	    j++;
		q=&info[i];                                     /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	    break;
	 }
	 i++;
	 
 }
    
	 
 
 if(j==0)
 {
	 printf("�Բ���,û������������Ϣƥ��ĳ���!\n");
	 printf("\n��������������˵�\n");
	 getch();
	 mainmenu();
 }

/*��֤�˿���Ϣ*/
 pman p=q->h_man->next;
	while(p)
	{
	if((!strcmp(man_name,p->man_name))&&(!strcmp(ic,p->ic)))    /*����иó˿͵���Ϣ*/
	{
     if(p->amount==1)                                           /*����ó˿�ֻ����һ��Ʊ*/
     traverselistmanadd(q->h_man,man_name,ic);          /*ɾ���ó˿͵���Ϣ*/
     else {
		    
		   for(i=0;i<p->amount;i++)                             /*����ó˿Ͷ��˲�ֹһ��Ʊ,��ɾ������λ��,�ó˿Ͷ�Ʊ����һ*/
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

if(k!=0)                  /*����ÿͻ���Ϣƥ��ɹ�*/
{
	/*����˵Ľ��*/
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

	 p->money-=money;         /*����ó˿Ͷ���Ʊ��ֻһ��,��ɹ���һ��֮��Ʊ��Ӧ����ӦǮ��*/
/*�ڳ�Ʊ����������һ�����*/
 c=q->h_tickets->next->tickets_num;     /*c+1Ϊ�ó�Ʊ�ı��*/
 ticketslistinsert(q->h_tickets,c+1,man_box,man_table,count);


 
 /*�ڳ�����Ϣ��ʣ��Ʊ����һ*/
 q->train_tickets++;
printf("\n\n\n\n\n\n-----------------��Ʊ�ɹ�!�˸���%dԪ,��ӭ���ٴ�ʹ��,лл!------------------\n\n\n",money);
 printf("�Ƿ�����ó��γ˿���Ϣ(1-�˿���Ϣ,2-���س�Ʊ����ϵͳ���˵�)\n");
            scanf("%d",&choice3);
            switch(choice3)
			{
			case 1:
				{
				     printf("���������ѯ�˿���Ϣ:\n");
		             getch();
					 traversemanlinklistadd2(q->h_man,man_name,ic);                    /*��ѯ�˿���Ϣ*/
					  printf("\n����������س�Ʊ����ϵͳ���˵�\n");
	                  getch();
	                  mainmenu();                      /*���س�Ʊ����ϵͳ���˵�*/
				}
				break;
			case 2:
				{
                      printf("\n����������س�Ʊ����ϵͳ���˵�\n");
	                  getch();
	                  mainmenu();                      /*���س�Ʊ����ϵͳ���˵�*/
				}
				    break;

		
        	default:
				{
		             printf("�������!!ȷ����������Ϊ(1,2,3)\n");
		             printf("����������س�Ʊ����ϵͳ���˵�\n");
			         getch();
			         mainmenu();                   /*��ѯ�Ӳ˵�����*/
				}
		    break;


			}
 
}
else {
printf("\n\nû���ҵ����û�����Ϣ!!\n\n"); 
      printf("\n\n����������س�Ʊ����ϵͳ���˵�\n\n");
       
      getchar();
	  mainmenu();
     }
   
}


int main()
{  
	menu();

  return 1;
}




