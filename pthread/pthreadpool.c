#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> 
//来写一个线程池，线程池需要一个存储任务的队列，线程池的容器,线程执行的任务
//任务队列创造
typedef struct task{
    void* arg;//指向指向函数的参数
    void(*run_task)(void*arg);//指向任务函数的指针
    struct task *next;  //next指针，指向下一个任务节点
}task;
//创建线程池
typedef struct thread_pool{
    task* first;//队列的开头
    task* end;//队列结尾
    int threadNum;//线程池数量
    int tasksize;//任务队列的大小
    pthread_mutex_t mutex_pool;//线程池的锁
    pthread_cond_t notempty;//确认队列是不是空
    pthread_t*threads;
    int shutdowm;//是否销毁线程池
}pthread_pool;
//创建接口

//执行任务
void* thread_work(void*arg){
    pthread_pool*pool=(pthread_pool*)arg;
    while (1) {
        pthread_mutex_lock(&pool->mutex_pool);

        // 如果没有任务且线程池未关闭，等待任务
        while (pool->tasksize == 0 && !pool->shutdowm) {
            pthread_cond_wait(&pool->notempty, &pool->mutex_pool);
        }

        // 如果线程池关闭且任务为空，退出线程
        if (pool->shutdowm && pool->tasksize == 0) {
            pthread_mutex_unlock(&pool->mutex_pool);
            pthread_exit(NULL);
        }

        // 获取任务
        task* t = pool->first;
        pool->first = t->next;
        if (pool->first == NULL) {
            pool->end = NULL;
        }
        pool->tasksize--;

        pthread_mutex_unlock(&pool->mutex_pool);

        // 执行任务
        t->run_task(t->arg);
        free(t);
    }
}
//给线程池添加任务
void addWork(pthread_pool* pool, void* arg, void(*run_task)(void*arg)){
    if(pool->shutdowm==1){//如果线程池已经关闭 
        return;
    }
    //初始化
    task* task_pool=(task*)malloc(sizeof(task));
    task_pool->arg=arg;
    task_pool->run_task=run_task;
    task_pool->next=NULL;
    //初始化完毕，锁！
    pthread_mutex_lock(&pool->mutex_pool);
    if(pool->first==NULL){//如果是第一个线程
        pool->first=task_pool;
        pool->end=task_pool;
    }else{
        pool->end->next=task_pool;//追加新节点
        pool->end=task_pool;//更新链表
    }
     pool->tasksize++;
     printf("添加任务中。。。\n");
    pthread_cond_signal(&pool->notempty);//唤醒阻塞的线程
    pthread_mutex_unlock(&pool->mutex_pool);//解锁

}

//初始化线程
pthread_pool* pthread_init(int number){
    pthread_pool *pool=(pthread_pool*)malloc(sizeof(pthread_pool));
    if(pool==NULL){
        perror("malloc error");
        return NULL;
    }
    //初始化线程池信息
    pool->threadNum=number;
    pool->first=NULL;
    pool->end=NULL;
    pool->tasksize=0;
    //初始化条件变量和互斥锁
    pthread_mutex_init(&pool->mutex_pool,NULL);
    pthread_cond_init(&pool->notempty,NULL);
    //初始化线程表
    pool->threads=(pthread_t*)malloc(number*sizeof(pthread_t));
    //生产线程
    for(int i=0;i<number;i++){
        pthread_t tid;
        printf("线程%d初始化中。。。\n",i+1);
        pthread_create(&tid,NULL,thread_work,pool);//传入你的线程池结构体
    }
    return pool;
}
//写个模拟任务吧
void run_task(void* arg){
    char* task_name = (char*)arg;
    printf("任务 %s 正在执行...\n", task_name);
    usleep(10);
}
//销毁线程
int pthread_destory(pthread_pool* pool){
    if(pool==NULL){
        return 0;
    }
    pool->shutdowm=1;
    for(int i=0;i<pool->threadNum;i++){
        pthread_cond_broadcast(&pool->notempty);//唤醒阻塞线程
        pthread_join(pool->threads[i], NULL);//分离线程
        printf("线程-%d正在销毁。。。\n",i+1);
    }
    pthread_mutex_destroy(&pool->mutex_pool);
    pthread_cond_destroy(&pool->notempty);
    //释放线程池
    free(pool);
    pool=NULL;
    return 0;
}

int main(){
    pthread_pool* pool=pthread_init(5);//创建5个线程
   // 添加任务到线程池
    for (int i = 0; i < 10; i++) {
        char* task_name = malloc(20);
        snprintf(task_name, 20, "任务-%d", i + 1);
        addWork(pool, task_name, run_task);
    }
    usleep(100);
    pthread_destory(pool);
    return 0;      
}