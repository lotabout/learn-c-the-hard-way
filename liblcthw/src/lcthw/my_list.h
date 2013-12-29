#ifndef MY_LIST_H
#define MY_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <lcthw/dbg.h>      /* for debug */


/* An implementation of circular doubly linked list interface */

typedef struct _node_t {
    struct _node_t *next;
    struct _node_t *prev;
    void *data;
} node_t;

typedef struct _list_t {
    int count;
    node_t *head;
} list_t;

/* function used to free a list object */
typedef void (*free_func)(void *);

list_t *list_create();
void list_destroy(list_t **list_ptr);
void list_clear(list_t *list, free_func free);
void list_clear_destroy(list_t **list_ptr, free_func free);

extern inline int list_count(list_t *list) ;

extern inline void *list_first(list_t *list);

extern inline void *list_last(list_t *list);

void list_add_head(list_t *list, void *data);
void list_add_tail(list_t *list, void *data);
void *list_del_head(list_t *list);
void *list_del_tail(list_t *list);
void *list_remove(list_t *list, node_t *node);

//#define list_is_empty(list) ((list)==NULL || (list)->head == (list)->head->next)

extern inline bool list_is_empty(list_t *list);

#define list_for_each(list, cur) \
    for((cur) = (list)->head->next; (cur)!=(list)->head; (cur)=(cur)->next)

#define list_for_each_prev(list, cur) \
    for((cur) = (list)->head->prev; (cur)!=(list)->head; (cur)=(cur)->prev)

/* with _safe postfix indicate that this routine is against removal */
#define list_for_each_safe(list, cur, tmp) \
    for((cur) = (list)->head->prev, (tmp) = (cur)->next; \
        (cur)!=(list)->head; \
        (cur) = (tmp), (tmp)=(cur)->prev)

#define list_for_each_prev_safe(list, cur, tmp) \
    for((cur) = (list)->head->prev, (tmp) = (cur)->next; \
        (cur)!=(list)->head; \
        (cur) = (tmp), (tmp)=(cur)->prev)
    

#endif /* end of include guard: MY_LIST_H */
