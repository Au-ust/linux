#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
void catchSig(int signum)
{
    printf("get a signal:%d",signum);
}
int main()
{
    for(int sig = 1; sig <= 31; sig++) {
        signal(sig, catchSig);
    }
    while(1){
        sleep(1);
    }
    return 0;
}