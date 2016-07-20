/*************************************
* 函数名  : 
* 功能描述:  
* 输入参数:
* 输出参数:
* 返回值  :
* 作者    : 石豪 
* 创建日期: 2015/10/29 8:12:56
*************************************/ 

#include<stdio.h>
#include<stdlib.h>

extern void CommentCovert(FILE *fpIn,FILE *fpOut);
void main()
{
	FILE *fpIn,*fpOut;
	char in[50];
	char out[50];
	printf("请输入打开文件位置：\n");
	gets(in);
	printf("请输入输出文件位置：\n");
	gets(out);
	fpIn = fopen(in,"r");
	{
		if(NULL == fpIn)
		{
			printf("Open file fail !\n");
			exit(1);
		}
	}

	fpOut = fopen(out,"w");
	{
		if(NULL == fpOut)
		{
			printf("Open file fail !\n");
			exit(1);
		}
	}

	CommentCovert(fpIn,fpOut);



	fclose(fpIn);
	fclose(fpOut);
}
