/*************************************
* ������  : 
* ��������:  
* �������:
* �������:
* ����ֵ  :
* ����    : ʯ�� 
* ��������: 2015/10/29 8:12:56
*************************************/ 

#include<stdio.h>
#include<stdlib.h>

extern void CommentCovert(FILE *fpIn,FILE *fpOut);
void main()
{
	FILE *fpIn,*fpOut;
	char in[50];
	char out[50];
	printf("��������ļ�λ�ã�\n");
	gets(in);
	printf("����������ļ�λ�ã�\n");
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
