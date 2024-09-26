#include"comm.h"//client和server都包含fifo文件，上图可以通信
int main(){
    //printf("start");
    int fd=open(MY_FIFO,O_WRONLY);
    if (fd<0){
        perror("open error");
        return 1;
    }
    
    while(1){
        printf("请输入：");
        fflush(stdout);//刷新缓冲区
        char buffer[64]={0};
        ssize_t s=read(0,buffer,sizeof(buffer)-1);
        if(s>0){
            buffer[s]=0;
            printf("%s\n",buffer);
            
            write(fd,buffer,strlen(buffer));
        }
    }
    close(fd);
    return 1;
}