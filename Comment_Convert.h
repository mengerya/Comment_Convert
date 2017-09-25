
#ifndef __COMMENT_CONVERT_H__
#define __COMMENT_CONVERT_H__
enum Status
{
	NUL_STATUS,
	C_STATUS,
	CPP_STATUS,
	EOF_STATUS
};


void CommentConvert();
void DoConvertWork(FILE *pfIn,FILE *pfOut);
void DoWork(FILE *pfIn,FILE *pfOut,enum Status *status);
void DoNulWork(FILE* pfIn,FILE* pfOut,enum Status* status);
void DoCppWork(FILE* pfIn,FILE* pfOut,enum Status* status);


#endif //__COMMENT_CONVERT_H__ 
