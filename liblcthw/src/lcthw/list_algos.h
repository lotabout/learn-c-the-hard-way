#ifndef LIST_ALGOS_H
#define LIST_ALGOS_H

#include <lcthw/my_list.h>
#include <lcthw/dbg.h>

typedef int (*list_compare)(const void *a, const void *b);

int list_bubble_sort(list_t *list, list_compare cmp);
list_t *list_merge_sort(list_t *list, list_compare cmp);

#endif /* end of include guard: LIST_ALGOS_H */
