#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>        
#include <sys/stat.h>
#include <fcntl.h>
int main(){
    int fd1=open("log.txt",O_WRONLY|O_CREAT,0644);
    if(fd1<0){
        perror("open");
        return 1;
    }
    int fd2=open("log.txt",O_RDWR|O_CREAT,0644);
    if(fd2<0){
        perror("open");
        return 1;
    }
    printf("fd1==%d\nfd2==%d\n",fd1,fd2);
    return 0;
}