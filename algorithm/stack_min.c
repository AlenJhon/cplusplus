

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#define ALLOC_SIZE (512)

typedef int KEY_VALUE;

typedef struct _stack {
    KEY_VALUE *base;
    int top;
    int stack_size;
}stack;


int init_stack(stack *s, int size){

    if(!s) return -1;

    s->base = (KEY_VALUE*)calloc(size, sizeof(KEY_VALUE));
    assert(s->base);

    s->top = 0;
    s->stack_size = size;
    return 0;
}

void destroy_stack(stack *s){

    if(!s) return ;

    free(s->base);
    s->base = NULL;
    s->top = 0;
    s->stack_size = 0;
    
}

void push_stack(stack *s, KEY_VALUE data){

    if(s->top >= s->stack_size){
        s->base = (KEY_VALUE*)realloc(s->base, s->stack_size*2);
        assert(s->base);
        s->stack_size += ALLOC_SIZE;
    }

    s->base[s->top++] = data;

}

void pop_stack(stack *s, KEY_VALUE *data){

    // if(!s) return ;

    // if(!data) return;

    assert(s);
    assert(data);

    *data = s->base[--s->top];

}


bool empty_stack(stack *s){
    return s->top == 0 ? 1 : 0;
}

int size_stack(stack *s){
    return s->top;
}
KEY_VALUE* top_stack(stack *s){
    assert(s);
    if (empty_stack(s)){
        return NULL;
    }
    return &(s->base[s->top - 1]);
}


typedef struct _min_stack{
    stack a;
    stack b;
}MIN_STACK;

void init(MIN_STACK* s){
    
    init_stack(&s->a, ALLOC_SIZE);
    init_stack(&s->b, ALLOC_SIZE);
}
void destroy(MIN_STACK* s){
    destroy_stack(&s->a);
    destroy_stack(&s->b);
}

void push(MIN_STACK *s, KEY_VALUE data)
{
    push_stack(&s->a, data);

    KEY_VALUE* min = top_stack(&s->b);
    if (min && data > *min){
        push_stack(&s->b, *min);
    } else{
        push_stack(&s->b, data);
    }
}
void pop(MIN_STACK* s, KEY_VALUE* data){
    pop_stack(&s->a, data);

    KEY_VALUE tmp;
    pop_stack(&s->b, &tmp);
}

KEY_VALUE* stackmin(MIN_STACK* s){
    return top_stack(&s->b);
}

bool empty(MIN_STACK* s){
    return empty_stack(&s->a);
}

int main(void)
{

    // stack s;
    // init_stack(&s, ALLOC_SIZE);

    // for(int i = 0; i < 1000; i++){
    //     push_stack(&s, i+1);
    // }

    // KEY_VALUE data;
    // while(!empty_stack(&s)){
    //     pop_stack(&s, &data);// first out last in
    //     printf("%4d", data);
    // }
    // printf("\n");

    // destroy_stack(&s);

    MIN_STACK s;
    init(&s);
    for(int i = 0; i < 100; i++){
        push(&s, i-100);
    }
    printf("stackmin=%d\n", *stackmin(&s));
    KEY_VALUE data;
    int i = 0;
    while (!empty(&s)){
        pop(&s, &data);// first out last in
        printf("%4d", data);
        if (++i % 10 == 0){
            break;
        }
    }
    printf("stackmin=%d\n", *stackmin(&s));
    destroy(&s);

    return 0;
}
