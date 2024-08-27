#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>


#define LINE_SIZE 1024
#define FLUSH_NOW 1
#define FLUSH_LINE 2
#define FLUSH_FULL 4

struct _myFILE {
	unsigned int flags;
	int fileno;
	char cache[LINE_SIZE];
	int cap;
	int pos;
};//定义我们的文件结构体，相当于C里的FILE
typedef struct _myFILE myFILE;
ssize_t my_fwrite(myFILE*p,const char* data,int len);
myFILE* my_fopen(const char* path, const char* flag);
void my_fclose(myFILE* fp);
void my_fflush(myFILE* fp);
