#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
//创建线程属性的结构体
typedef struct{
    pthread_t tid;
    char* name[128];
    int running;
}Thread;
//线程执行的函数
void gopthread(void* args){
    Thread* thread=(Thread*)args;
    while(thread->running){
        printf("%s is running\n", thread->name);
        sleep(1);
    }
    return NULL;
}
//创建
void mypthread_Create(Thread *threads){
    threads->running=1;
    pthread_create(&threads->tid,NULL,gopthread,(void*)threads);//把参数作为结构体传入
}

//停止
void mypthread_Stop(Thread *threads){
    threads->running=0;
}

//等待
void mypthread_Join(Thread *threads){
    pthread_join(threads->tid,NULL);
}

int main(){
    Thread threads[SIZE];
    //创建线程
    for(int i=0;i<SIZE;i++){
        snprintf(threads[i].name,sizeof(threads[i].name),"thread-%d",i+1);
        mypthread_Create(&threads[i]);
    }
    sleep(5);//留给线程运行
    //停止线程
    for(int i=0;i<SIZE;i++){
        mypthread_Stop(&threads[i]);
    }
    //等待
     for(int i=0;i<SIZE;i++){
        mypthread_Join(&threads[i]);
    }
    return 0;
}