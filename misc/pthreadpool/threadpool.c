#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include "automic.h"


#define WORKER_STATE_EXIT 1
#define PTR(st) &(st)

typedef void (* job_callback_func) (void *arg);


//insert first
#define LL_ADD(item, list) do { \
    item->prev = NULL;          \
    item->next = list;          \
    if (list != NULL)           \
        list->prev = item;      \
    list = item;                \
} while (0)

#define LL_REMOVE(item, list) do {      \
    if (item->prev != NULL)             \
        item->prev->next = item->next;  \
    if (item->next != NULL)             \
        item->next->prev = item->prev;  \
    if (list == item)                   \
        list = item->next;              \
    item->prev = item->next = NULL;     \
} while(0)

struct worker {
    pthread_t   threadid;
    int         terminate; // 1 exist, state flag

    struct manager *pool;
    struct worker  *prev;
    struct worker  *next;
};


struct job {
    // void (*cb) (void *arg);
    job_callback_func cb;
    void *user_data;
    // int need_free;

    struct job *prev;
    struct job *next;
};

struct manager {
    struct worker   *workers;
    struct job      *jobs;

    pthread_mutex_t jobs_mutex;
    pthread_cond_t  jobs_cond;

    /*
    * idle / sum > 80% need free thread
    * idle / sum < 40% need malloc thread
    */
    int idle_workers; 
    int total_workers;
} ;

typedef struct manager thread_pool;



void show_pool_idle(thread_pool *pool) {
    printf("total_workers: %d , idle_workers:%d , 1.0*idle_workers/total_workers = %0.3f \n", pool->total_workers, pool->idle_workers, 1.0*pool->idle_workers / pool->total_workers);
}

void show_jobs(struct job *j, const char *tag) {
    return ;
    struct job *it;
    printf("%s :", tag);
    for( it = j; it != NULL; it = it->next) {
        printf("user_data: %04d ", *(int *)it->user_data);
    }
    printf("\n");
}

void *worker_entry(void *arg) {
    struct worker *w = (struct worker*)arg;
    thread_pool   *pool = w->pool; 

    static tick = 0;
    
    while(1) {

        show_jobs(pool->jobs,  "worker_entry 93");

        pthread_mutex_lock(PTR(pool->jobs_mutex));
        if (pool->jobs == NULL) {
            if (w->terminate == WORKER_STATE_EXIT) {
                break;
            }
            pthread_cond_wait(PTR(pool->jobs_cond), PTR(pool->jobs_mutex)); // 在等待的时候锁已经释放了，等唤醒了再上锁
        }
        if (w->terminate == WORKER_STATE_EXIT) {
            pthread_mutex_unlock(PTR(pool->jobs_mutex));
            break;
        }

        struct job *job_node = pool->jobs;
        if (job_node != NULL) {
            show_jobs(pool->jobs, "LL_REMOVE before ");
            LL_REMOVE(job_node, pool->jobs); // remove first
            show_jobs(pool->jobs, "LL_REMOVE after ");
        }
        pthread_mutex_unlock(PTR(pool->jobs_mutex));

        if (job_node == NULL) {
            continue;
        }

        __sync_fetch_and_sub(PTR(pool->idle_workers), 1);
        // printf("user_data:%04d\n", *(int *)job_node->user_data);
        job_node->cb(job_node);
        // lxx_atomic_add(PTR(pool->idle_workers), -1);
        lxx_atomic_add(PTR(pool->idle_workers), 1);
        

        lxx_atomic_add(PTR(tick), 1);
        if (tick % 100 == 0) {
            show_pool_idle(pool);
        }

        // free(job_node);

        // threadpool_aux(pool);
    }

    free(w);
    pthread_exit(NULL);
}



int threadpool_create_workers(thread_pool *pool, int n) {
    int i = 0;
    for (i = 0; i < n; ++i) {
        struct worker *w = (struct worker *)malloc( sizeof(struct worker) );
        if (w == NULL) {
            perror("malloc failed .");
            return -1;
        }
        memset( w, 0, sizeof(struct worker) );
        w->pool = pool;

        int rv = pthread_create( PTR(w->threadid), NULL, worker_entry, (void *)w);
        if (rv) {
            perror("pthread_create failed.");
            struct worker *sw = pool->workers;
            for (sw = pool->workers; w != NULL; w = w->next) {
                w->terminate = WORKER_STATE_EXIT;
            }
            return -1;
        }

        LL_ADD(w, pool->workers);
    }

     lxx_atomic_add(PTR(pool->idle_workers), n);
    // pool->idle_workers += worker_num;
    pool->total_workers += n;

    return 0;
}

int threadpool_add_workers(thread_pool *pool) {
    threadpool_create_workers(pool,  (pool->total_workers / 4) < 1 ? 1 : (pool->total_workers / 4));

    return 0;
}

bool is_ext_workers(thread_pool *pool) {
    return 100.0*pool->idle_workers / pool->total_workers < 40.0;
}
bool is_free_workers(thread_pool *pool) {
    return 100.0*pool->idle_workers / pool->total_workers > 60.0;
}


int threadpool_free_workers(thread_pool *pool) {
    int free_num = (pool->total_workers / 4) < 1 ? 0 : (pool->total_workers / 4);
    
    int i = 0;
    struct worker *w = NULL;
    for (i = 0, w = pool->workers; w != NULL && i < free_num; w->next, ++i) {
        w->terminate = WORKER_STATE_EXIT;
    }

    return 0;
}

int threadpool_aux(thread_pool *pool) {
    if (is_ext_workers(pool)) {
        threadpool_add_workers(pool);
    }

    if (is_free_workers(pool)) {
        threadpool_free_workers(pool);
    }
    return 0;
}


int threadpool_create(thread_pool *pool, int worker_num) {
    if (pool == NULL) return -1;
    if (worker_num < 1) worker_num = 1;
    memset(pool, 0, sizeof(thread_pool));

    pthread_mutex_t blank_mutex = PTHREAD_MUTEX_INITIALIZER;
    memcpy(PTR(pool->jobs_mutex), PTR(blank_mutex), sizeof(pthread_mutex_t));
    // pool->jobs_mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;
    memcpy(PTR(pool->jobs_cond), PTR(blank_cond), sizeof(pthread_cond_t));
    // pool->jobs_cond = PTHREAD_COND_INITIALIZER;


    threadpool_create_workers(pool, worker_num);

    // int i = 0;
    // for (i = 0; i < worker_num; ++i) {
    //     struct worker *w = (struct worker *)malloc( sizeof(struct worker) );
    //     if (w == NULL) {
    //         perror("malloc failed .");
    //         return -1;
    //     }
    //     memset( w, 0, sizeof(struct worker) );
    //     w->pool = pool;

    //     int rv = pthread_create( PTR(w->threadid), NULL, worker_entry, (void *)w);
    //     if (rv) {
    //         perror("pthread_create failed.");
    //         struct worker *sw = pool->workers;
    //         for (sw = pool->workers; w != NULL; w = w->next) {
    //             w->terminate = WORKER_STATE_EXIT;
    //         }
    //         return -1;
    //     }

    //     LL_ADD(w, pool->workers);
    // }

    // pool->idle_workers = worker_num;
    // pool->total_workers = worker_num;
    return 0;
}

int threadpool_destory(thread_pool *pool) {
    struct worker *w = NULL;
    for (w = pool->workers; w != NULL; w->next) {
        w->terminate = WORKER_STATE_EXIT;
    }

    pthread_mutex_lock(PTR(pool->jobs_mutex));
    pool->workers = NULL;
    pthread_cond_broadcast(PTR(pool->jobs_cond));
    pthread_mutex_unlock(PTR(pool->jobs_mutex));

    return 0;
}

//内部不管理 struct job *j 指向的内存
int threadpool_push_job(thread_pool *pool, struct job *j) {

    pthread_mutex_lock(PTR(pool->jobs_mutex));
    LL_ADD(j, pool->jobs);

    pthread_cond_signal(PTR(pool->jobs_cond)); //唤醒等待的线程
    pthread_mutex_unlock(PTR(pool->jobs_mutex));
}






//test
#if 1
#define WORKER_NUM 10
#define TASK_NUM 1000

void task_callback(void *userdata) {

    struct job *task = (struct job *)userdata;
	int index = *(int*)task->user_data;

	printf("index : %04d, selfid : %lu\n", index, pthread_self());
	
	// free(task->user_data);
	// free(task);
}


//test 
int main() {

	thread_pool pool_instance;

	threadpool_create(PTR(pool_instance), WORKER_NUM);

#if 1
    int i = 0;

    int *puser_data = (int *)calloc(TASK_NUM, sizeof(int));
    struct job *ptasks = (struct job *)calloc(TASK_NUM, sizeof(struct job));

    // int *puser_data = (int *)malloc(TASK_NUM * sizeof(int));
    // memset(puser_data, 0, TASK_NUM * sizeof(int));
    // struct job *ptasks = (struct job *)malloc(TASK_NUM * sizeof(struct job));
    // memset(ptasks, 0, TASK_NUM * sizeof(struct job));


    // printf("sizeof(int) = %d\n", sizeof(int));

    // for (i = 0; i < TASK_NUM; ++i) {
    //     printf("puser_data[%d]=%04d\n", i, *(puser_data+i));
    // }
    struct job *tmptasks = NULL;
    int *tmpud = NULL;
    for (i = 0; i < TASK_NUM; ++i) {
        // user_data[i] = i + 1;
        // puser_data[i] = i + 1;
        // *(puser_data + i) = i + 1;

        tmpud = puser_data + i;
        // printf("puser_data:%X puser_data+%d:%x\n", puser_data, i, tmpud);
        tmptasks = ptasks + i;

        tmptasks->cb = task_callback;
        tmptasks->user_data = (void *)tmpud;
        // tmptasks->user_data = malloc(sizeof(int));
        *(int*)tmptasks->user_data = i+100;
        // printf("insert user_data :%04d\n", *(int *)((ptasks + i)->user_data));
        
        threadpool_push_job(PTR(pool_instance), tmptasks);

        // show_jobs(pool_instance.jobs, "threadpool_push_job after .");
    }

    // show_jobs(pool_instance.jobs);
    // printf("push finish ...\n");
    // for (i = 0; i < TASK_NUM; ++i) {
    //     printf("puser_data[%d]=%04d\n", i, *(puser_data+i));
    // }

#endif

#if 0
	int i = 0;
	for (i = 0; i < TASK_NUM; i ++) {
		struct job *task = (struct job*)malloc(sizeof(struct job));
		if (task == NULL) {
			perror("malloc");
			exit(1);
		}
		
		task->cb = task_callback;
		task->user_data = malloc(sizeof(int));
		*(int*)task->user_data = i;

		threadpool_push_job(PTR(pool_instance), task);
		
	}
#endif

	getchar();
	printf("\n");

    free(puser_data);
    free(ptasks);
    return 0;
}

#endif
