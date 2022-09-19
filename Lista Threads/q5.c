// https://en.wikipedia.org/wiki/Dining_philosophers_problem
#include <stdio.h>
#include <pthread.h>

int NUM_PHILOSOPHER = 5;
int THINKING = 0;
int HUNGRY = 1;
int EATING = 2;

pthread_mutex_t mutexFilosofos[numFilosofos];

get_forks(int i) {
    pthread_mutex_lock(&mutexFilosofos[i]);
    pthread_mutex_unlock(&mutexFilosofos[i]);
}

void* filosofos (void* arg) {
    int i = *(int*) arg;
    while(1) {
        think(i);
        get_forks(i);
        eat(i);
        put_forks(i);
    }
}

int main() {
    pthread_t th[numFilosofos];
    for (int i = 0; i < numFilosofos; i++) {
        int* arg = malloc(sizeof(int));
        *arg = i;
        if (pthread_create(&th[i], NULL, &filosofos, arg) != 0) perror("Failed to create thread\n");
    }
    for (int i = 0; i < numFilosofos; i++) {
        if (pthread_join(th[i], NULL) != 0) perror("Failed to join thread\n");
    }
    return 0;
}