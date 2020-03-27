#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//condition variable
int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

//update condition variable on exit
void thr_exit() {
    pthread_mutex_lock(&m);
    done = 1;
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
 }

void *child(void *arg) {
    printf("P1's child\n");
    thr_exit();
    return NULL;
 }

void thr_join() {
    pthread_mutex_lock(&m);
    //wait till the current thread is finished
    while (done == 0)
        pthread_cond_wait(&c, &m);
    pthread_mutex_unlock(&m);
}

int main(int argc, char *argv[]) {
    printf("P1: begin\n");
    pthread_t p;
    //start second thread which is child of first thread
    pthread_create(&p, NULL, &child, NULL);
    thr_join();
    printf("P1: end\n");
    return 0;
 }