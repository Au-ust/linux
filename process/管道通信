#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main(){
    int fds[2];
    char buffer[100];
    int len;
    //pipe(fds[2])是管道函数的原型，fds[0]表示管道读端，fds[1]是管道写端
    if(pipe(fds)==-1){
        perror("make a pipe"),exit(1);
    }
    while(fgets(buffer,100,stdin)){//从键盘端获取我们输入的东西
        len=strlen(buffer);
        if(write(fds[1],buffer,len)!=len){
            perror("write to pipe");
            break;
        }
        memset(buffer,0,sizeof(buffer)==-1);
        if((len=read(fds[0],buffer,100))==-1){
            perror("read from pipe");
            break;
        }
        if(write(1,buffer,len)!=len){
            perror("write to stdout");
            break;
        }
    }
    return 0;
}
