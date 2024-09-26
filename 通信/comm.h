#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>        
#include <sys/stat.h>
#include <fcntl.h>
#define MY_FIFO "./fifo"
#include<sys/shm.h>
#define PATH_NAME "./"
#define PROJ_ID 0X6666
#define SIZE 4097