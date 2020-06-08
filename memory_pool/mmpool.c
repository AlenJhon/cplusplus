/*
//tcmalloc  msyql
// jemalloc 
ngnix 也用到了内存池

//大块内存 posix_memalign()
*/
#include <stdio.h>
#include <stdlib.h>

struct mp_large_s
{
    struct mp_large_s *next;
    void *alloc;
};

struct mp_node_s
{
    unsigned char *start;
    unsigned char *end;

    struct mp_node_s *next;
    int flag;
};

struct mp_pool_s
{
    size_t max;
    struct mp_node_s *current;
    struct mp_large_s *large;

    struct mp_node_s head[0];
};

struct mp_pool_s *mp_create_pool(size_t size){

}

void mp_destory_pool(struct mp_pool_s *pool) {
    struct mp_large_s *l;
    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
            free(l->alloc);
        }
    }
    struct mp_node_s *h = pool->head->next;
    
}

    // struct mp_node_s {

    // };

    // struct mp_large_s {

    // };

    // struct mp_bool_s
    // {
    //     size_t max;
    //     struct mp_node_s *current;
    //     struct mp_large_s * large;
    // };