#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void ToHex(unsigned long tid,char*buffer){
    snprintf(buffer,128,"0x%lx",( unsigned long)tid);
}


void* gothread(void* arg){
    while(1){
        char buffer[128];
        ToHex((unsigned long)pthread_self,buffer);
        printf("arg %s is running\n",buffer);
        sleep(1);
    }
}


int main(){
    pthread_t tid;
    pthread_create(&tid,NULL,gothread,(void*)"thread-1");
    char buffer[128];
    ToHex((unsigned long)tid,buffer);
    printf("new thread tid:%s\n",buffer);
    pthread_join(tid,NULL);
    return 0;
    }