#include "stack.h"
#include <stdio.h>


#if 0
int stack_base_to_top(stack *ps) {
    int curtop;
    pop_stack(ps, &curtop);

    if (empty_stack(ps)) {
        return curtop;
    }

    int result = stack_base_to_top(ps);
    push_stack(ps, curtop);
    return result;
}

void reverse_stack(stack *ps) {

    int base = stack_base_to_top(ps);

    if (empty_stack(ps)) {
        return ;
    }

    reverse_stack(ps);

    push_stack(ps, base);
} 
#endif

int main() {

#if 0
    stack s;
    init_stack(&s, 512);

    for (int i = 0; i < 1000; i++)
    {
        push_stack(&s, i + 1);
    }

    int data;
    while (!empty_stack(&s))
    {
        pop_stack(&s, &data); // first out last in
        printf("%4d", data);
    }
    printf("\n");

    destroy_stack(&s);
#endif

    stack s;
    init_stack(&s, 512);
    for (int i = 0; i < 512; ++i)
    {
        push_stack(&s, i + 1);
    }

    // for (int i = 0; i < 10; ++i) {
    //    int base = stack_base_to_top(&s);
    //    printf("%4d", base);
    //    push_stack(&s, base);
    // }

    reverse_stack(&s);

    printf("reverse after ...\n");
    while (!empty_stack(&s)) {
        int curtop;
        pop_stack(&s, &curtop);
        printf("%4d", curtop);
    }
    printf("\n");

    return 0;
}