#include<stdio.h>
#include<pthread.h>
int V;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void UP(int V){
    pthread_mutex_lock(&mutex);
        if(V!=0){
            V++;
        }else{
            pthread_cond_signal(&c);
        }
    pthread_mutex_unlock(&mutex);
}
void Down(int V){
    pthread_mutex_lock(&mutex);
        if(V!=0){
            V--;
        }else{
            while(V==0)pthread_cond_wait(&c,&mutex);
        }
    pthread_mutex_unlock(&mutex);
}