#include <stdio.h>
#include <sys/time.h>

int counter;
#define MAX_COUNT_INC 80000000


#if 0
// #include <time.h>
int single_thread() {
    // clock_t c = clock();
    struct timeval stv, etv;
    gettimeofday(&stv, NULL);
    for (int i = 0; i < MAX_COUNT_INC; ++i) {
        ++counter;
    }
    gettimeofday(&etv, NULL);
    printf("single_thread inc: %d used %dms \n", MAX_COUNT_INC, (etv.tv_sec * 1000 + etv.tv_usec / 1000) - (stv.tv_sec * 1000 + stv.tv_usec / 1000) );
    //single_thread inc: 80000000 used 183ms
    // printf("single_thread inc :%d mili-seconds:%d \n", MAX_COUNT_INC, clock() - c);
    return 0;
}
#endif

#if 1
#include <unistd.h>
#include <pthread.h>
pthread_rwlock_t rwlock;
/*
* API
* pthread_rwlock_init()
* pthread_rwlock_destroy()
* pthread_rwlock_wrlock()
* pthread_rwlock_rdlock()
* pthread_rwlock_unlock()
* 
* 内部使用自旋锁机制spin_lock
*/
void *rwlock_write_worker(void *arg) {

    // clock_t startclock = clock();
    struct timeval stv, etv;
    gettimeofday(&stv, NULL);
    for (int i = 0; i < (MAX_COUNT_INC/8); ++i) {
        pthread_rwlock_wrlock(&rwlock);
        ++counter;
        pthread_rwlock_unlock(&rwlock);
    }
    gettimeofday(&etv, NULL);
    printf("rwlock_write_worker pid:%ld inc: %d used %dms \n", pthread_self(), MAX_COUNT_INC/8, (etv.tv_sec * 1000 + etv.tv_usec / 1000) - (stv.tv_sec * 1000 + stv.tv_usec / 1000));
    // printf("pid:%d mili-seconds:%d", getpid(), clock() - startclock);
    return 0;
}

int mutli_thread() {
    int i = 0;
    pthread_rwlock_init(&rwlock, NULL);
    pthread_t tid[4];

    for (i = 0; i < 4; ++i) {
        pthread_create(&tid[i], NULL, rwlock_write_worker, NULL);
    }

    for (i = 0; i < 4; ++i) {
        pthread_join(tid[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);
    return 0;
}
#endif

int main() {

    // single_thread();
    mutli_thread();

    return 0;
}