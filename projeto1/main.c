#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define M 5

volatile int i, j;

void *f_thread(void *v) {
    int thr_id;
    thr_id = *(int *) v;
    printf("Thread %d: i = %d.\n", thr_id, i);
    return NULL;
}

void test() {
    pthread_t thr[M];
    int n[M] = {0, 1, 2, 3, 4};

    for (i = 0; i < M; i++) {
        pthread_create(&thr[i], NULL, f_thread, (void *) &n[i]);
    }

    for (j = 0; j < M; j++) {
        pthread_join(thr[j], NULL);
    }
}

int main() {

    while (1) {
        printf("\n");
        test();
        fflush(stdout);
        sleep(1);
    }

    return 0;
}