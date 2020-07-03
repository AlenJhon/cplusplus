
#if 0
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
        s->base = (KEY_VALUE*)realloc(s->base, s->stack_size+ALLOC_SIZE);
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


int main(void){

    stack s;
    init_stack(&s, ALLOC_SIZE);

    for(int i = 0; i < 1000; i++){
        push_stack(&s, i+1);
    }

    KEY_VALUE data;
    while(!empty_stack(&s)){
        pop_stack(&s, &data);// first out last in
        printf("%4d", data);
    }
    printf("\n");

    destroy_stack(&s);



    return 0;
}

#endif




