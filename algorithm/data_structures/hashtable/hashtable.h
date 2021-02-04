/**
 * 该实现方式是在 <<算法精解C语言描述>> 一书中
*/

#ifndef CHTBL_H
#define CHTBL_H

#include <stdlib.h>
#include "../list/allist.h"

typedef struct CHTbl_
{
    int     buckets;//桶的数量
    int     (*h)(const void* key);//hash 函数指针
    int     (*match)(const void* key1, const void* key2);//比较元素函数指针
    void    (*destroy)(void* data);//销毁函数指针
    int     size;//当前元素个数
    PLIST   table;//桶
}CHTbl;

/* Public Interface */
int chtbl_init(CHTbl* htbl, int buckets, int (*h)(const void* key), int (*match)(const void* key1, const void* key2), void (*destory)(void* data));
void chtbl_destroy(CHTbl* htbl);
int chtbl_insert(CHTbl* htbl, const void* data);
int chtbl_remove(CHTbl* htbl, void** data);
int chtbl_lookup(const CHTbl* htbl, void** data);

#define chtbl_size(htbl) ((htbl)->size)

#endif // CHTBL_H