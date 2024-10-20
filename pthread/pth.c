#include<stdio.h>
#include<pthread.h>
int gval=100;
void* gopthread(void *arg){
    while(1){
        sleep(5); 
        printf("this is a pthread,pid==%d\n",getpid());
        int x=rand()%5;
        if(x==0){
            int *p=NULL;
            *p=100;//段错误，访问空指针
        }

    }
}

int main(){
    srand(time(NULL));
    pthread_t tid1;
    pthread_create(&tid1,NULL,gopthread,(void*)"thread-new");
    pthread_t tid2;
    pthread_create(&tid2,NULL,gopthread,(void*)"thread-new");
    pthread_t tid3;
    pthread_create(&tid3,NULL,gopthread,(void*)"thread-new");
    while(1){
        sleep(5);
        printf("main thread running...,pid==%d\n",getpid());
        printf("new thread running...,pid==%d, gval==%d,&gval==%p\n",getpid(),gval,&gval);
    }

    return 0;
}