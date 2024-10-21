#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void*  gopthread(void* args){
    char* name=(char*)args;
     
        printf("%s pthread is running\n",name);
        sleep(1);
    
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