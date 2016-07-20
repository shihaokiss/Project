
#include<stdio.h>
#include<stdlib.h>

typedef enum                 //定义状态
	{
		NO_COMMENT_STATE,
		C_COMMENT_STATE,
		CPP_COMMENT_STATE,
		STRING_COMMENT_STATE,
		END_COMMENT_STATE
	}STATE_ENUM;

	typedef struct STATE_BASIC     //定义状态基
	{
		FILE * inputfile;
		FILE * outputfile;
		STATE_ENUM INSTANTLY;          
	}STATE_BASIC;
	STATE_BASIC Now_state;
	STATE_BASIC Static_state;      //全局状态常量
	

///////////////////////////////////////////////////////

void EventPro(char ch);     /*事件处理函数*/
void EventProAtNo(char ch);   /*NO状态下的函数*/
void EventProAtC(char ch);   /*C状态下的函数*/
void EventProAtCpp(char ch);   /*CPP状态下的函数*/
void EventProAtString(char ch);   /*String状态下的函数*/

///////////////////////////////////////////////////////

/*状态转换的主函数*/
void CommentCovert(FILE *fpIn,FILE *fpOut)             
{
	

	if(NULL == fpIn && NULL == fpOut)
	{
		printf("Error：information transter ！\n");
		exit(1);
	}

	//初始化状态基
	Now_state.inputfile = fpIn;
	Now_state.outputfile = fpOut;
	Now_state.INSTANTLY = NO_COMMENT_STATE;
	char ch;
	while(Now_state.INSTANTLY != END_COMMENT_STATE)    //整个函数的心脏
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
		case '/':Now_state.INSTANTLY = CPP_COMMENT_STATE;
			     fputc('*',Now_state.outputfile);
			break;
		case '*':Now_state.INSTANTLY = C_COMMENT_STATE;
				fputc(nextch,Now_state.outputfile);
			break;
		default:
				fputc(nextch,Now_state.outputfile);
		break;
		}
		
	}
	else if('"' == ch)
	{
	fputc(ch,Now_state.outputfile);
	Static_state.INSTANTLY = Now_state.INSTANTLY;
	Now_state.INSTANTLY = STRING_COMMENT_STATE;
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
					fputc(ch,Now_state.outputfile);
					fputc(nextch,Now_state.outputfile);
					Now_state.INSTANTLY = NO_COMMENT_STATE;
				}
					else
				{
					fputc(ch,Now_state.outputfile);
					fseek(Now_state.inputfile,-1,SEEK_CUR);
				}
			
			
			break;
		case '/':
				nextch = fgetc(Now_state.inputfile);
				if('/' == nextch || '*' == nextch)
				{
					fputc(' ',Now_state.outputfile);
					fputc(' ',Now_state.outputfile);				
				}
				else
				{
					fputc(ch,Now_state.outputfile);
					fseek(Now_state.inputfile,-1,SEEK_CUR);
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
			fputc('*',Now_state.outputfile);
			fputc('/',Now_state.outputfile);
			fputc(ch,Now_state.outputfile);
			Now_state.INSTANTLY = NO_COMMENT_STATE;	
		break;
	case EOF:
			fputc('*',Now_state.outputfile);
			fputc('/',Now_state.outputfile);
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
			else
			{
				fputc(ch,Now_state.outputfile);
				fseek(Now_state.inputfile,-1,SEEK_CUR);
			}
			
			
		break;
	case '*':
			nextch = fgetc(Now_state.inputfile);
			if('/' == nextch)
			{
				fputc(' ',Now_state.outputfile);
				fputc(' ',Now_state.outputfile);				
			}
			else
			{
				fputc(ch,Now_state.outputfile);
				fseek(Now_state.inputfile,-1,SEEK_CUR);
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
void EventProAtString(char ch)             //处理字符串模式的函数
{
	char nextch;
	if(Static_state.INSTANTLY == C_COMMENT_STATE || Static_state.INSTANTLY == CPP_COMMENT_STATE)
	{                     
		switch(ch)
		{
		case '*':
				nextch = fgetc(Now_state.inputfile);
				if('/' == nextch)
				{
					fputc(ch,Now_state.outputfile);
					fputc(' ',Now_state.outputfile);
					fputc(nextch,Now_state.outputfile);
				}
				else
				{
					fputc(ch,Now_state.outputfile);
					fseek(Now_state.inputfile,-1,SEEK_CUR);
				}
			break;
				
		case '"':
				fputc('"',Now_state.outputfile);
				Now_state.INSTANTLY = Static_state.INSTANTLY;
			break;
		default:
				fputc(ch,Now_state.outputfile);
			break;
		}

	}
	else if(Static_state.INSTANTLY == NO_COMMENT_STATE)
	{
		switch(ch)
		{
		case '/':
				nextch = fgetc(Now_state.inputfile);
				if('/' == nextch)
				{
					fputc(ch,Now_state.outputfile);
					fputc(' ',Now_state.outputfile);
					fseek(Now_state.inputfile,-1,SEEK_CUR);
				}
				else if('*' == nextch)
				{
					fputc(ch,Now_state.outputfile);
					fputc(' ',Now_state.outputfile);
					fputc(nextch,Now_state.outputfile);
				}
				else
				{
					fputc(ch,Now_state.outputfile);
					fseek(Now_state.inputfile,-1,SEEK_CUR);
				}
			break;
				
		case '"':
				fputc('"',Now_state.outputfile);
				Now_state.INSTANTLY = Static_state.INSTANTLY;
			break;
		default:
				fputc(ch,Now_state.outputfile);
			break;
		}
	}

}
