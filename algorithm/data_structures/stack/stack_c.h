#ifndef __STACK_H__
#define __STACK_H__

/* 这是顺序栈的实现，栈中的每个元素是连续存储的
 * 初始构建栈先分配n个元素空间，
 * 空间用完了，则在另外一个地方寻找2*n的空间分配，再把已有的数据元素拷贝到新空间
 *
 * */

#include <assert.h> // assert
#include <stdlib.h>  //calloc realloc
#include <stdbool.h> // bool

#define FACTOR 2

typedef int KEY_VALUE;

typedef struct _stack
{
    KEY_VALUE *base;
    int top;
    int stack_size;
} stack;

int init_stack(stack *s, size_t size)
{
    if (!s)
        return -1;

    size = size == 0 ? 1 : size;

    s->base = (KEY_VALUE *)calloc(size, sizeof(KEY_VALUE));
    assert(s->base);

    s->top = 0;
    s->stack_size = size;
    return 0;
}

void destroy_stack(stack *s)
{

    if (!s)
        return;

    free(s->base);
    s->base = NULL;
    s->top = 0;
    s->stack_size = 0;
}

void push_stack(stack *s, KEY_VALUE data)
{

    if (s->top >= s->stack_size)
    {
        s->base = (KEY_VALUE *)realloc(s->base, s->stack_size * FACTOR);
        assert(s->base);
        s->stack_size *= FACTOR;
    }

    s->base[s->top++] = data;
}

void pop_stack(stack *s, KEY_VALUE *data)
{

    // if(!s) return ;

    // if(!data) return;

    assert(s);
    assert(data);

    *data = s->base[--s->top];
}

bool empty_stack(stack *s)
{
    return s->top == 0 ? 1 : 0;
}

int size_stack(stack *s)
{
    return s->top;
}

static int __stack_base_to_top(stack *s)
{
    int curtop;
    pop_stack(s, &curtop);

    if (empty_stack(s))
    {
        return curtop;
    }

    int result = __stack_base_to_top(s);
    push_stack(s, curtop);
    return result;
}

void reverse_stack(stack *s) {
    int base = __stack_base_to_top(s);

    if (empty_stack(s))
    {
        return;
    }

    reverse_stack(s);

    push_stack(s, base);
}


#endif //__STACK_H__
