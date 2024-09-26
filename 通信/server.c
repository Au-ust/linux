
#include "comm.h"
int main(){
    umask(0);//防止设置权限时受umask影响
    //if(mkfifo(MY_FIFO,0666)<0){//创建管道文件
    //    perror("mkfifo");
    //    return 1;
    //}
    //printf("start");
    int fd=open(MY_FIFO,O_RDONLY);//打开文件
    if(fd<0){
        perror("open error");
    }
    //让我们的server提供读服务
    while(1){
        char buffer[64]={0};
        sleep(10);
        ssize_t s=read(fd,buffer,sizeof(buffer)-1);
        if(s>0){
            buffer[s]=0;
            printf("client say:");//读取结束
            printf("%s",buffer);
            //break;
        }else if(s==0){
             printf("Client disconnected...\n");
            break;
            break;
        }else{
            perror("read error");//处理error
        }

    }
    close(fd);    
}