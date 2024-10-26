#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int tickets=10;
pthread_mutex_t gmutex=PTHREAD_MUTEX_INITIALIZER;

void*  gopthread(void* args){
    char* name=(char*)args;
    while(1){
        pthread_mutex_lock(&gmutex);//检查票数和买票的线程应该在同一个锁内
        if(tickets>0){   
            tickets--;
            printf("%s pthread pay a ticket,remain %d\n",name,tickets);
            pthread_mutex_unlock(&gmutex);
        }
        else{
            pthread_mutex_unlock(&gmutex);//没票了，锁上
            pthread_exit(args);
            break;
        }
        sleep(1);
    }
    return args;
}


int main(){
    char names[10][128];
    pthread_t tids[10];
    for(int i=0;i<10;i++){
        snprintf(names[i],sizeof(names[i]),"thread-%d",i);
        pthread_create(&tids[i], NULL,gopthread,names[i]);
    }
    
     for(int i=0;i<10;i++){
        void* name=NULL;
        pthread_join(tids[i],&name);
        printf("%s quit...\n",(char*)name);
    }
    
    return 0;
}