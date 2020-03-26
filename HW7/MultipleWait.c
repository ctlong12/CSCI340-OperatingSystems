#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *child(void* arg) {

    assert(pthread_mutex_lock(&mutex) == 0);
    pthread_cond_signal(&cond);
    
    pthread_mutex_unlock(&mutex);

    free(arg);
}

int main(int argc, char *argv[]) {


    pthread_t pth1;
    int *arg1 = malloc(sizeof(*arg1));
    pthread_t pth2;   
    int *arg2 = malloc(sizeof(*arg2));
    if (pthread_create(&pth1, NULL, child, arg1) != 0 || pthread_create(&pth2, NULL, child, arg2) != 0) {
        printf("Failed to create the thread\n");
        exit(1);
    }

    pthread_mutex_lock(&mutex);
    
    pthread_mutex_unlock(&mutex);


    assert(pthread_join(pth1, NULL) == 0);
    assert(pthread_join(pth2, NULL) == 0);

    printf("Hello from the thread!<%d>\n");    

    return 0;

}
