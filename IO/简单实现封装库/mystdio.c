#include"mystdio.h"
ssize_t my_fwrite(myFILE* fp, const char* data, int len) {
	memcpy(fp->cache+fp->pos,data,len);//按字节拷贝，strcpy只能拷贝字符串，但是memcpy可以用于各种数据类型
	fp->pos = len;
	if ((fp->pos & FLUSH_LINE) && fp->cache[fp->pos - 1] == '\n') {
		my_fflush(fp);
	}
	return len;
}
void my_fflush(myFILE* fp) {
	write(fp->fileno, fp->cache, fp->pos);
	fp->pos = 0;
}
myFILE* my_fopen(const char* path, const char* flag) {
	int flag1 = 0;
	int iscreate = 0;
	mode_t mode = 0666;
	if (strcmp(flag, "r") == 0) {
		flag1 = (O_RDONLY);
	}
	else if (strcmp(flag, "w") == 0) {
		flag1 = (O_WRONLY | O_CREAT | O_TRUNC);
		iscreate = 1;
	}
	else if (strcmp(flag, "a") == 0) {
		flag1 = (O_WRONLY | O_CREAT | O_APPEND);
		iscreate = 1;
	}
	else {
		//nothing
	}
	int fd = 0;
	if (iscreate) {
		fd = open(path, flag1, mode);
	}
	else {
		fd = open(path, flag1);
	}
	if (fd < 0) {
		return NULL;
	}
	myFILE* fp = (myFILE*)malloc(sizeof(myFILE));//申请内存空间
	if (!fp) {
		return NULL;
	}
	fp->fileno = fd;
	fp->flags = FLUSH_LINE;
	fp->cap = LINE_SIZE;
	fp->pos = 0;
	return fp;//返回一个myFILE类型的指针
}

void my_fclose(myFILE* fp) {
	my_fflush(fp);
	close(fp->fileno);
	free(fp);
}
