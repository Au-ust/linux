#include<stdio.h>
#include<pthread.h>
void* gopthread(void* arg){
   while(1){
    printf("pthread is running\n");
    sleep(1);
   }
}
int main(){
    pthread_t tid;
    int n=pthread_create(&tid,NULL,gopthread,(void*)"pthread 1");
    if(n!=0){
        perror("creat failed\n");
        return -1;
    }
    if(n==0){
        printf("main thread wait success\n");
    }

    return 0;
}