#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
int handler(int sig){
    printf("get a sig form myskill,sig==%d",sig);
}

int main(){
    signal(2,handler);//signal是个系统调用函数，第一个参数是输入的信号是几，第二个参数有三种类型
    //此处的类型为一个函数指针，在执行该语句的时候执行一个handler函数，这个函数是要自己声明的
    //格式为int handler(int sig)
    while(1){
        printf("a new process,pid==%d",getpid());
        sleep(1);
    }
    return 0;
}