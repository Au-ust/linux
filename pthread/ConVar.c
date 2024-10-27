#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> 
#define BUFFER_SIZE 5 // 缓冲区大小

int buffer[BUFFER_SIZE]; // 缓冲区
int count = 0;           // 当前缓冲区中数据数量
int in = 0;              // 生产者放入数据的位置
int out = 0;             // 消费者取数据的位置

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t cond_var=PTHREAD_COND_INITIALIZER;//pthread_cond_t 是 POSIX 线程库（Pthreads）中用于表示条件变量的数据类型，定义一个全局的变量
pthread_cond_t cond_empty=PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_full=PTHREAD_COND_INITIALIZER;//因为我们要用队列来存储，所以需要用条件变量确保队列的空/满

//int shared_data=0;删除设定的共享数据捏
void *producer(void* args){
    char* producer_name=(char*)args;
    while(1){
        pthread_mutex_lock(&mutex);//锁上
        int item=rand()%100;//随机生产数据
        while(count==BUFFER_SIZE){//缓冲区要是满了
            pthread_cond_wait(&cond_full,&mutex);//就等待
        }
        buffer[in]=item;
        in=(in+1)%BUFFER_SIZE;//确认新位置
        count++;
        printf("i'm a %s Producer data:%d\n",producer_name,item);
        pthread_cond_signal(&cond_empty);//通知消费者数据可用
        printf("-----------------------------------\n");
        pthread_mutex_unlock(&mutex);// 解锁互斥锁
        sleep(4); // 模拟生产耗时
    }
    return (void*)producer_name;
}
void *consumer(void *args) {
    char *consumer_name = (char *)args;

    while (1) {
        // 锁定互斥锁
        pthread_mutex_lock(&mutex);

        // 等待生产者生产数据
        while (count == 0) {
            // 等待条件变量，解锁互斥锁，进入等待状态
            pthread_cond_wait(&cond_empty, &mutex);
        }
        // 消费数据
        int item=buffer[out];
        out=(out+1)%BUFFER_SIZE;
        count--;
        printf("I'm %s Consumer consumed data: %d\n", consumer_name, item);
        printf("-----------------------------------\n");
        pthread_cond_signal(&cond_full); // 通知生产者有空位
        // 解锁互斥锁
        pthread_mutex_unlock(&mutex);

        // 模拟消费耗时
        sleep(4);
    }
    return (void*)consumer_name; 
}

int main(){
    int producer_thread_num=5;//生产者人数
    int consumer_thread_num=10;//消费者人数
    pthread_t  producers[producer_thread_num];
    pthread_t  consumers[consumer_thread_num];//线程们
    char *producer_names[producer_thread_num];
    char *consumer_names[consumer_thread_num];//名字们
    
    for(int i=0;i<producer_thread_num;i++){
        producer_names[i] = malloc(64);
        snprintf(producer_names[i],64,"producer-%d",i);
        if(pthread_create(&producers[i],NULL,producer,producer_names[i])!=0){
            perror("pthread_create producer failed");
            exit(EXIT_FAILURE);
        }
        consumers[i]=producers[i];
    }
    
    for (int i = 0; i < consumer_thread_num; i++)
    {
        // 创建消费者线程
        consumer_names[i] = malloc(64);
        sprintf(consumer_names[i], "consumer-%d", i + 1);
        if (pthread_create(&consumers[i], NULL, consumer, consumer_names[i]) != 0)
        {
            perror("pthread_create consumer failed");
            exit(EXIT_FAILURE);
        }
    }
    for(int i=0;i<producer_thread_num;i++){
        pthread_join(producers[i],NULL);
        printf("%s quit...\n",(char*)producer_names[i]);
        free(producer_names[i]);
    }
    for(int i=0;i<consumer_thread_num;i++){
        pthread_join(consumers[i],NULL);
        printf("%s quit...\n",(char*)consumer_names[i]);
        free(consumer_names[i]);
    }//线程退出
    // 销毁条件变量
    pthread_cond_destroy(&cond_empty);
    pthread_cond_destroy(&cond_full);
    // 销毁锁
    pthread_mutex_destroy(&mutex);
    return 0;
}