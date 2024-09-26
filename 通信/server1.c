#include"comm.h"
int main(){
    key_t key=ftok(PATH_NAME,PROJ_ID);
    if(key<0){
        perror("ftok");
        return 1;
    }
    int shmid=shmget(key,SIZE,IPC_CREAT|0666|IPC_EXCL);
    if(shmid<0){
        perror("shmget");
        return 1;
    }
    printf("key:%u,shmid:%d",key,shmid);
    printf("attaches shm success \n");  
    char *shm=(char *)shmat(shmid,NULL,0);
    if(shm==(char *)-1){
        perror("shmat");
        return 1;
    }
    //开始通信
    while(1){
        sleep(1);
        printf("%s\n",shm);
    }
    shmctl(shmid,IPC_RMID,NULL);
    printf("delete");

}