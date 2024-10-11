#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
int main(int argc,char *argv[]){
    if(argc!=3){
        perror("kill false");
        return 1;
    }
    pid_t pid=stoi(argv[2]);
    int sig=stoi(argv[1]);
    kill(sig,pid);
    return 0;
}