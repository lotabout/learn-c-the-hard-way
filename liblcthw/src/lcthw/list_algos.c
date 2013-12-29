#include "list_algos.h"
#include <stdbool.h>

static void node_swap(node_t *a, node_t *b)
{
    void *tmp_val = a->data;
    a->data = b->data;
    b->data = tmp_val;
}

int list_bubble_sort(list_t *list, list_compare cmp)
{
    if (list_count(list) <= 1) {
        return 0;   // already sorted
    }

    bool sorted;
    do {
        sorted = true;

        node_t *cur;
        node_t *last = NULL;
        list_for_each(list, cur) {
            if (cur == last)
                break;
            if ((cur->next != list->head) && 
                cmp(cur->data, cur->next->data) > 0) {
                node_swap(cur, cur->next);
                sorted = false;
                last = cur;
            }
        }
    } while (!sorted);

    return 0;
}

list_t *list_merge(list_t *left, list_t *right, list_compare cmp)
{
    list_t *result = list_create();
    void *val = NULL;

    while ((list_count(left) > 0) || (list_count(right) > 0)) {
        if (list_count(left) > 0 && list_count(right) > 0) {
            if (cmp(list_first(left), list_first(right)) <= 0) {
                val = list_del_head(left);
            } else {
                val = list_del_head(right);
            }
            list_add_tail(result, val);
        } else if (list_count(left) > 0) {
            val = list_del_head(left);
            list_add_tail(result, val);
        } else {
            val = list_del_head(right);
            list_add_tail(result, val);
        }
    }

    return result;
}

list_t *list_merge_sort(list_t *list, list_compare cmp)
{
    if (list_count(list) <= 1) {
        return list;
    }

    list_t *left = list_create();
    list_t *right = list_create();

    int middle = list_count(list)/2;
    node_t *cur = NULL;
    list_for_each(list, cur) {
        list_t *target = (middle-- > 0)?left:right;
        list_add_tail(target, cur->data);
    }

    // recursively call merge_sort() to further split each sublist
    // until sublist size is 1
    list_t *sorted_left = list_merge_sort(left, cmp);
    list_t *sorted_right = list_merge_sort(right, cmp);

    if (sorted_left != left) {
        list_destroy(&left);
    }
    if (sorted_right != right) {
        list_destroy(&right);
    }

    return list_merge(sorted_left, sorted_right, cmp);
}
