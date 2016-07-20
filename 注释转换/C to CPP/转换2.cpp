
#include<stdio.h>
#include<stdlib.h>

typedef enum                 //����״̬
	{
		NO_COMMENT_STATE,
		C_COMMENT_STATE,
		CPP_COMMENT_STATE,
		STRING_COMMENT_STATE,
		END_COMMENT_STATE
	}STATE_ENUM;

	typedef struct STATE_BASIC     //����״̬��
	{
		FILE * inputfile;
		FILE * outputfile;
		STATE_ENUM INSTANTLY;
	}STATE_BASIC;
	STATE_BASIC Now_state;
	STATE_BASIC Static_state;      //ȫ��״̬����
	

///////////////////////////////////////////////////////

void EventPro(char ch);     /*�¼�������*/
void EventProAtNo(char ch);   /*NO״̬�µĺ���*/
void EventProAtC(char ch);   /*C״̬�µĺ���*/
void EventProAtCpp(char ch);   /*CPP״̬�µĺ���*/
void EventProAtString(char ch);   /*String״̬�µĺ���*/

///////////////////////////////////////////////////////

/*״̬ת����������*/
void CommentCovert(FILE *fpIn,FILE *fpOut)             
{
	

	if(NULL == fpIn && NULL == fpOut)
	{
		printf("Error��information transter ��\n");
		exit(1);
	}

	//��ʼ��״̬��
	Now_state.inputfile = fpIn;
	Now_state.outputfile = fpOut;
	Now_state.INSTANTLY = NO_COMMENT_STATE;
	char ch;
	while(Now_state.INSTANTLY != END_COMMENT_STATE)    //��������������
	{
		ch = fgetc(Now_state.inputfile);
		EventPro(ch);
	}

}

void EventPro(char ch)
{
	switch(Now_state.INSTANTLY)
	{
	case NO_COMMENT_STATE:
		 EventProAtNo(ch);          
		break;
	case C_COMMENT_STATE:
		EventProAtC(ch);
		break;
	case CPP_COMMENT_STATE:
		EventProAtCpp(ch);
		break;
	case STRING_COMMENT_STATE:
		EventProAtString(ch);
		break;
	
	}
}



void EventProAtNo(char ch)
{
	char nextch;
	if('/' == ch)
	{
		fputc(ch,Now_state.outputfile);
		nextch = fgetc(Now_state.inputfile);
		switch(nextch)
		{
		case '/':
			     fputc(nextch,Now_state.outputfile);
				 Now_state.INSTANTLY = CPP_COMMENT_STATE;
			break;
		case '*':
				fputc('/',Now_state.outputfile);
				Now_state.INSTANTLY = C_COMMENT_STATE;
			break;
		default:
				fputc(nextch,Now_state.outputfile);
		break;
		}
		
	}
	else if (EOF == ch)
	{
		Now_state.INSTANTLY = END_COMMENT_STATE;
		fputc(ch,Now_state.outputfile);
	}
	else 
	{
		fputc(ch,Now_state.outputfile);
	}

}




void EventProAtC(char ch)
{
	char nextch;
	switch(ch)
	{
		
		case '*':
				nextch = fgetc(Now_state.inputfile);
				if('/' == nextch)
				{
					fputc(' ',Now_state.outputfile);
					fputc(' ',Now_state.outputfile);
					fputc('\n',Now_state.outputfile);        //��������� '*/' ������ʱ�ͻ���
					Now_state.INSTANTLY = NO_COMMENT_STATE;  //��Ϊ��һ���Ѿ���ע����
				}
			
			break;
		case '\n':
					fputc('\n',Now_state.outputfile);
					fputc('/',Now_state.outputfile);
					fputc('/',Now_state.outputfile);
			break;

		case '/':
				nextch = fgetc(Now_state.inputfile);
				if('/' == nextch || '*' == nextch)
				{
					fputc(' ',Now_state.outputfile);
					fputc(' ',Now_state.outputfile);				
				}
			
			break;
		case '"':
				fputc(ch,Now_state.outputfile);
				Static_state.INSTANTLY = Now_state.INSTANTLY;
				Now_state.INSTANTLY = STRING_COMMENT_STATE;
				
			break;	
		default:
				fputc(ch,Now_state.outputfile);
		break;
	}
}
void EventProAtCpp(char ch)
{
	char nextch;
	switch(ch)
	{
	
	case '\n':
			fputc(ch,Now_state.outputfile);
			Now_state.INSTANTLY = NO_COMMENT_STATE;	
		break;
	case EOF:
			fputc(ch,Now_state.outputfile);
			Now_state.INSTANTLY = END_COMMENT_STATE;	
		break;
	case '/':
			nextch = fgetc(Now_state.inputfile);
			if('/' == nextch || '*' == nextch)
			{
				fputc(' ',Now_state.outputfile);
				fputc(' ',Now_state.outputfile);				
			}
			
		break;
	case '*':
			nextch = fgetc(Now_state.inputfile);
			if('/' == nextch)
			{
				fputc(' ',Now_state.outputfile);
				fputc(' ',Now_state.outputfile);				
			}
			
		break;
	case '"':
			fputc(ch,Now_state.outputfile);
			Static_state.INSTANTLY = Now_state.INSTANTLY;
			Now_state.INSTANTLY = STRING_COMMENT_STATE;
		break;
	default:
			fputc(ch,Now_state.outputfile);
		break;

	}
}
void EventProAtString(char ch)
{
	switch(ch)
	{
	case '"':
			fputc('"',Now_state.outputfile);
			Now_state.INSTANTLY = Static_state.INSTANTLY;
		break;
	default:
			fputc(ch,Now_state.outputfile);
		break;
	}
}