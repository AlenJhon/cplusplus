
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef int KEY_VALUE;

#define ALLOC_SIZE (512)


typedef struct _queue_note{
    struct _queue_note *next;
    KEY_VALUE key;
}queue_note;

typedef struct _queue
{
    queue_note *front;
    queue_note *rear;
    int queue_size;
}queue;


void init_queue(queue *q){

    assert(q);

    q->front = q->rear = NULL;
    q->queue_size = 0;
}

void destroy_queue(queue *q){

    assert(q);

    queue_note *iter;
    queue_note *next;

    iter = q->front;
    while(iter){
        next = iter->next;

        free(iter);
        iter = next;
    }

    q->front = q->rear = NULL;
    q->queue_size = 0;

}

void push_queue(queue *q, KEY_VALUE data){

    assert(q);

    if(q->rear){

        queue_note *node = (queue_note*)calloc(1, sizeof(queue_note));
        assert(node);

        node->key = data;
        node->next = NULL;

        q->rear->next = node;
        q->rear = node;

    }else{

        queue_note *node = (queue_note*)calloc(1, sizeof(queue_note));
        assert(node);

        node->key = data;
        node->next = NULL;

        q->front = q->rear = node;

    }
    q->queue_size += 1;
}

void pop_queue(queue *q, KEY_VALUE *key){

    assert(q);
    assert(key);
    assert(q->front != NULL);

    if (q->front == q->rear){
        *key = q->front->key;

        free(q->front);
        q->front = q->rear = NULL;

    }else{
        queue_note *next = q->front->next;

        *key = q->front->key;
        free(q->front);

        q->front = next;
    }

    q->queue_size -= 1;

}


int size_queue(queue *q){
    assert(q);

    return q->queue_size;
}

int empty_queue(queue *q){
    assert(q);

    return q->rear == NULL ? 1 : 0;
}



int main(void){

    queue q;

    init_queue(&q);

    for(int i = 0; i < 1000; i++){
        push_queue(&q, i+1);
    }

    KEY_VALUE key;
    while(!empty_queue(&q)){
        pop_queue(&q, &key);
        // printf("%4d"); 无意中 没有给占位符赋值这样编译能通过也能输出，只是数值不是预期的都是-1
        printf("%4d", key);
    }
    printf("\n");

    return 0;
}



