#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
void handler(int sig){
    printf("get a sig,sig==%d\n",sig);
    fflush(stdout);
}
int main(){
    signal(3,handler);
    while(1){
        sleep(1);
        raise(3);//给当前进程发送信号3
    }
    return 0;
}