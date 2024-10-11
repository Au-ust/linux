#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char *argv[]){
    if(argc!=3){
        perror("kill false");
        return 1;
    }
    pid_t pid=atoi(argv[2]);
    int sig=atoi(argv[1]);
    kill(pid,sig);//啊啊啊啊，一开始写反参数的顺序了，气死了
    return 0;
}