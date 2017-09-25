#include"CommentConvert.h"
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
void DoNulWork(FILE* pfIn,FILE* pfOut,enum Status* status)
{
	int first = 0;
	int second = 0;
	first = fgetc(pfIn);
	switch(first)
	{
	case '/':
		second = fgetc(pfIn);
		switch(second)
		{
		case '*':
			fputc('/',pfOut);
			fputc('/',pfOut);
			*status = C_STATUS;
			break;
		case '/':
			fputc(first,pfOut);
			fputc(second,pfOut);
			*status = CPP_STATUS;
			break;
		default:
			fputc(first,pfOut);
			fputc(second,pfOut);
			break;
		}
		break;
	case EOF:
		*status = EOF_STATUS;
		break;
	default:
		fputc(first,pfOut);
		break;
	}
}

void DoCWork(FILE* pfIn,FILE* pfOut,enum Status* status)
{
	int first = 0;
	int second = 0;
	int third = 0;
	first = fgetc(pfIn);
	switch(first)
	{
	case '*':
		second = fgetc(pfIn);
		switch(second)
		{
		case '/':
			*status = NUL_STATUS;
			break;
		case '*':
			ungetc(second,pfIn);
			second = fgetc(pfIn);
			switch(second)
			{
			case '/':
				*status = NUL_STATUS;
				break;
			default:
				fputc(first,pfOut);
			    fputc(second,pfOut);
				break;
			}
			break;
		default:
			fputc(first,pfOut);
			fputc(second,pfOut);
			break;
		}
		break;
	case '\n':
		fputc(first,pfOut);
		*status = NUL_STATUS;
		break;
	default:
		fputc(first,pfOut);
		break;
	}
}
void DoCppWork(FILE* pfIn,FILE* pfOut,enum Status* status)
{
	int first = 0;
	int second = 0;
	first = fgetc(pfIn);
	switch(first)
	{
	case '\n':
		fputc(first,pfOut);
		*status = NUL_STATUS;
		break;
	case EOF:
		*status = EOF_STATUS;
		break;
	default:
		fputc(first,pfOut);
		break;
	}
}
void DoConvertWork(FILE* pfIn,FILE* pfOut)
{
	enum Status status = NUL_STATUS;
	while(status != EOF_STATUS)
	{
		switch(status)
		{
		case NUL_STATUS:
			DoNulWork(pfIn,pfOut,&status);
			break;
		case C_STATUS:
			DoCWork(pfIn,pfOut,&status);
			break;
		case CPP_STATUS:
			DoCppWork(pfIn,pfOut,&status);
			break;
		}
	}
}

void CommentConvert()
{
	FILE* pfread = NULL;
	FILE* pfwrite = NULL;
	pfread = fopen("input.c","r");
	if(NULL == pfread)
	{
		perror("open file for read");
		exit(EXIT_FAILURE);
	}
	pfwrite = fopen("output.c","w");
	if(NULL == pfwrite)
	{
		fclose(pfread);
		perror("open file for write");
		exit(EXIT_FAILURE);
	}
	DoConvertWork(pfread,pfwrite);
	fclose(pfread);
	fclose(pfwrite);
}
