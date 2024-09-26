#include"comm.h"
int main(){
    key_t key=ftok(PATH_NAME,PROJ_ID);
    if(key<0){
        perror("ftok");
        return 1;
    }
    printf("%u\n",key);
    int shmid=shmget(key,SIZE,IPC_CREAT);
    //和server的形成规则相同，代表是同一块共享内存
    if(shmid<0){
        perror("shmget");
        return 1;
    }
    char *shm =shmat(shmid, NULL, 0);   
    if (shm == (char *) -1) {
        perror("shmat");
        return 1;
    }


    printf("client process attaches success!\n");   
    char c='A';
    while(c<='Z'){
        shm[c-'A']=c;
        c++;
        shm[c-'A']=0;
        sleep(2);
    }    
    shmdt(shm);
    printf("client process detaches success\n");
    //client去挂接，server负责删除


}