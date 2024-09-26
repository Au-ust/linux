#include"comm.h"
int main(){
    umask(0);
    key_t key=ftok(PATH_NAME,PROJ_ID);
    if(key<0){
        perror("key");
       return 1;
    }
    int shmid=shmget(key,SIZE,IPC_CREAT|IPC_EXCL|0666);
    if(shmid<0){
        perror("shmget");
        return 1;
    }
    printf("key:%u,shmid:%d\n",key,shmid);
    sleep(5);
    char *mat=shmat(shmid,NULL,0);
    if(mat==(char*)-1){
        perror("shmat");
    }
    printf("attaches shm success\n");
    sleep(5);
    shmdt(mat);
    printf("detaches shm success\n");
    shmctl(shmid,IPC_RMID,NULL);
    printf("key:0x%X,shmid->%d->shm delete succes!\n",key,shmid);
    sleep(5);//此时已经删掉了

    return 0;
}