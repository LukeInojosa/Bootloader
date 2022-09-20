#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define LEFT (i+NUM_PHILOSOPHER-1) % NUM_PHILOSOPHER        // indicates left fork
#define RIGHT (i+NUM_PHILOSOPHER-1) % NUM_PHILOSOPHER       // indicates right fork
#define NUM_PHILOSOPHER 5

// different status for each philosopher
int THINKING = 0;
int HUNGRY = 1;
int EATING = 2;
int statusPhilosopher[NUM_PHILOSOPHER];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condPhilosopher[NUM_PHILOSOPHER];

void* test (int i) {        // testing if forks are available, if so, starts eating
    if (statusPhilosopher[i] == HUNGRY && statusPhilosopher[LEFT] != EATING && statusPhilosopher[RIGHT] != EATING) {
        statusPhilosopher[i] = EATING;
        // when finishes eating, sends signal to i philosopher that was sleeping 
        pthread_cond_signal(&condPhilosopher[i]);
    }
}

void get_forks(int i) {
    pthread_mutex_lock(&mutex);
    printf("\t\t%d is hungry\n", i);
    statusPhilosopher[i] = HUNGRY;
    test(i);
    // if tested and can't eat (is hungry) philosopher has to wait
    if(statusPhilosopher[i] == HUNGRY) pthread_cond_wait(&condPhilosopher[i], &mutex);    
    pthread_mutex_unlock(&mutex);
}

void put_forks(int i) {
    pthread_mutex_lock(&mutex);
    statusPhilosopher[i] = THINKING;
    // testing if left and right forks are being used
    test(LEFT);
    test(RIGHT);
    pthread_mutex_unlock(&mutex);
}

void eat (int i) {
    printf("\t\t\t\t%d is eating\n", i);
    sleep(1);
}

void think (int i) {
    printf("%d is thinking\n", i);
    sleep(1);
}

void* philosopher (void* arg) {
    int i = *(int*) arg;
    printf("Philosopher %d has entered the room\n", i);
    while(1) {
        think(i);
        get_forks(i);
        eat(i);
        put_forks(i);
    }
}

int main() {
    pthread_t th[NUM_PHILOSOPHER];
    for (int i = 0; i < NUM_PHILOSOPHER; i++) {
        pthread_cond_init(&condPhilosopher[i], NULL);
    }
    
    for (int i = 0; i < NUM_PHILOSOPHER; i++) {
        int* arg = malloc(sizeof(int));
        *arg = i;
        if (pthread_create(&th[i], NULL, &philosopher, arg) != 0) perror("Failed to create thread\n");
    }
    for (int i = 0; i < NUM_PHILOSOPHER; i++) {
        if (pthread_join(th[i], NULL) != 0) perror("Failed to join thread\n");
    }
    return 0;
}