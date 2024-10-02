#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>        
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sem.h>
#define MY_FIFO "./fifo"
#include<sys/shm.h>
#define PATH_NAME "./"
#define PROJ_ID 0X6667
#define SIZE 4097

union semun{
    int val;
    struct semid_ds *buf;
};//联合体，联合体内的成员共享同一块空间
struct sembuf{
    unsigned short sem_num;//信号量的索引
    short sem_op;//信号量操作，<0则表示P，>0则表示V,0表示等待
    short sem_flg;//操作标志,IPC_NOWAIT(非阻塞)和SEM_UNDO(系统恢复时撤销操作)
};



int main(){
    //创建key
    int key=ftok(PATH_NAME,PROJ_ID);
    if(key==-1){
        perror("ftok");
        return 1;
    }
    //创建信号量
    int semid= semget(key,3,IPC_EXCL|IPC_CREAT|0666);
    if(semid<0){
        perror("semget");
        return -1;
     }
    //设置信号量的值
    union semun argv;
    argv.val=1;
    int result=semctl(semid,0,SETVAL,argv);
    if(result<0){
        perror("semctl");
        return -1;
    }
    //等待信号量的值为0
    struct sembuf sop;
    sop.sem_num=0;
    sop.sem_op=0;
    sop.sem_flg=0;
    result=semop(semid,&sop,1);
    if(result<0){
        perror("semop");
        return -1;
    }
    printf("Semaphore operation complete.\n");
    //对信号量进行P操作
    sop.sem_op=-1;
    result=semop(semid,&sop,1);
      if(result<0){
        perror("semop");
        return -1;
    }
    //进行V操作
    sop.sem_op=1;
    result=sempo(semid,&sop,1);
      if(result<0){
        perror("semop");
        return -1;
    }
    //删除信号量
     result = semctl(semid, 0, IPC_RMID);
    if (result == -1) {
        perror("semctl del");
        return -1;
    }
 
    
    printf("key==%d\nsemid==%d\n",key,semid);
   
    
    return 0;
}
