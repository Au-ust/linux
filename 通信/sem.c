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
#include <errno.h>
#define PATH_NAME "./"
#define PROJ_ID 0X6667

union semun{
    int val;
    struct semid_ds *buf;
};//联合体，联合体内的成员共享同一块空间
/*struct sembuf{
    unsigned short sem_num;//信号量的索引
    short sem_op;//信号量操作，<0则表示P，>0则表示V,0表示等待
    short sem_flg;//操作标志,IPC_NOWAIT(非阻塞)和SEM_UNDO(系统恢复时撤销操作)
};
*/
void mysemop(int num,int op,int semid){
    struct sembuf buf;
    buf.sem_num=num;
    buf.sem_op=op;
    buf.sem_flg=0;
    semop(semid,&buf,1);
}

int main(){
    //创建key
    int key=ftok(PATH_NAME,PROJ_ID);
    if(key==-1){
        perror("ftok");
        return 1;
    }
    //创建信号量
    int semid= semget(key,2,IPC_EXCL|IPC_CREAT|0666);
    if(semid<0){
        if(errno==17){
            semget(key,2,0666);
        }else{
             perror("semget");
             exit(0);
            }
     }
    printf("key==%d\nsemid==%d\n",key,semid);
    //设置信号量的值
    union semun sem;
    sem.val=0;
    int result=semctl(semid,0,SETVAL,sem);
    if(result<0){
        perror("semctl");
        return -1;
    }
    sem.val=10;
    result=semctl(semid,1,SETVAL,sem);
    if(result<0){
        perror("semctl");
        return -1;
    }
    //对信号量进行PV操作
    int i=6;
    while(i--){
        mysemop(1,-1,semid);
        printf("sem==%d\n",semctl(semid,1,GETVAL));//获取信号量的值
    }
    //删除信号量
    result = semctl(semid, 0, IPC_RMID);
    if (result <0) {
        perror("semctl del");
        return -1;
    }
 
    return 0;
}
