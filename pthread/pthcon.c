#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
typedef struct ThreadData{
    char name[20];
    int num;
}ThreadData;

void* gopthread(void* arg){
    int cnt=5;
    while(cnt--){
    printf("pthread is running\n");
    sleep(1);
   }
}
int main(){
    pthread_t tid;
    ThreadData *td=(ThreadData*)malloc(sizeof(ThreadData));
    strcpy(td->name,"thread-1");
    td->num=1;
    int n=pthread_create(&tid,NULL,gopthread,(void*)"pthread 1");
    if(n!=0){
        perror("creat failed\n");
        return -1;
    }
    n=pthread_join(tid,NULL);
    printf("n==%d\n",n);
    printf("maim pthread begin\n");
    if(n==0){
        printf("main thread wait success\n");
    }
    free(td)
;    return 0;
}