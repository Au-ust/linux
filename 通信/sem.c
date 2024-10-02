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

int main(){
    //创建key
    int key=ftok(PATH_NAME,PROJ_ID);
    if(key==-1){
        perror("ftok");
        return 1;
    }
    //创建信号量
    int semid= semget(key,3,IPC_EXCL|IPC_CREAT);
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
    //获取信号量的值
    int val=semctl(semid,0,GETVAL);
    if(val<0){
        perror("semctl val");
        return -1;
    }
    printf("val==%d",val);
    //删除信号量
     result = semctl(semid, 0, IPC_RMID);
    if (result == -1) {
        perror("semctl del");
        return -1;
    }

    printf("key==%d,semid==%d\n",key,semid);
   
    
    return 0;
}
