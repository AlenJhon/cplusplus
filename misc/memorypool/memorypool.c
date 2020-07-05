#include <stdio.h> //printf
#include <stdlib.h> //posix_memalign   malloc free
#include <string.h> //memset
#include <unistd.h>
// #include <fcntl.h>


#define MP_ALIGNMENT            32
#define MP_PAGE_SIZE            4096
#define MP_MAX_ALLOC_FROM_POOL (MP_PAGE_SIZE-1)

#define MP_ALIGN(n, alignment)      (((n)+(alignment-1)) & ~(alignment-1))
#define MP_ALIGN_PTR(p, alignmetn)  (void *)(((size_t)(p)+(alignment-1)) & ~(alignment-1))

struct mp_large_s {
    struct mp_large_s *next;
    void *alloc;
};

struct mp_node_s {
    unsigned char       *last;
    unsigned char       *end;
    struct mp_node_s    *next;
    size_t              failed;
};

struct mp_pool_s {
    size_t max; //Boundary value
    struct mp_node_s    *current;
    struct mp_large_s   *large;
    struct mp_node_s    head[0]; //first mp_nodes_s
};

struct mp_pool_s *  mp_create_pool(size_t size);
void                mp_destory_pool(struct mp_pool_s *pool);
void                *mp_alloc(struct mp_pool_s *pool, size_t size);
void                *mp_nalloc(struct mp_pool_s *pool, size_t size);
void                *mp_calloc(struct mp_pool_s *pool, size_t size);
void                mp_free(struct mp_pool_s *pool, void *p);

struct mp_pool_s *mp_create_pool(size_t size) {
    struct mp_pool_s *p;
    int rv = posix_memalign((void **)&p, MP_ALIGNMENT, size + sizeof(struct mp_pool_s) + sizeof(struct mp_node_s));
    if (rv) {
        return NULL;
    }

    p->max = (size < MP_MAX_ALLOC_FROM_POOL) ? size : MP_MAX_ALLOC_FROM_POOL;
    p->current = p->head; // first mp_nodes_s
    p->large = NULL;

    p->head->last = (unsigned char *)p + sizeof(struct mp_pool_s) + sizeof(struct mp_node_s);
    p->head->end = p->head->last + size;
    p->head->failed = 0;

    return p;
}

void mp_destroy_pool(struct mp_pool_s *pool) {
    struct mp_node_s *h, *n;
    struct mp_large_s *l;

    //free large
    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
            free(l->alloc);
        }
    }

    //free node
    h = pool->head->next;
    while (h) {
        n = h->next;
        free(h);
        h = n;
    }

    //free mp_pool_s  first mp_node_s
    free(pool)
}

void mp_reset_pool(struct mp_pool_s *pool) {
    struct mp_node_s    *litle;
    struct mp_large_s   *large;

    for (large = pool->large; large; large = large->next) {
        if (large->alloc) {
            free(large->alloc);
        }
    }
    pool->large = NULL;

    for (litle = pool->head; litle; litle = litle->next) {
        litle->last = (unsigned char *)litle + sizeof(struct mp_node_s);
    }
}

static void *mp_alloc_block(struct mp_pool_s *pool, size_t size) {
    unsigned char *m;
    struct mp_node_s *h = pool->head;
    size_t psize = (size_t)(h->end - (unsigned char *)h);

    int rv = posix_memalign((void **)&m, MP_ALIGNMENT, psize);
    if (rv) {
        return NULL;
    }

    struct mp_node_s *p, *new_node, *current;
}


/*
 *
 * test code 
 * 
 */

int main()
{

    return 0;
}