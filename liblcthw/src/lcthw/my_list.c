#include "my_list.h"
#include <malloc.h>

list_t *list_create()
{
    list_t *tmp = (list_t *)malloc(sizeof(*tmp));
    check_mem(tmp);
    
    node_t *head = (node_t *)malloc(sizeof(*head));
    check_mem(head);

    tmp->head = head;
    tmp->head->data = NULL;
    tmp->head->next = tmp->head;
    tmp->head->prev = tmp->head;

    return tmp;
error:
    if (tmp)
        free(tmp);
    return NULL;
}

void list_destroy(list_t **list_ptr)
{
    check(list_ptr && *list_ptr, "Invalid pointer to list.");

    list_t *list = *list_ptr;
    node_t *cur = NULL;
    list_for_each(list, cur) {
        list_remove(list, cur);
    }

    free(list->head);
    free(list);
    list = NULL;

error:
    return;
}

void list_clear(list_t *list, free_func free)
{
    check(list, "Invalid list to clear");
    node_t *cur;
    list_for_each(list, cur) {
        free(cur->data);
    }

error:
    return;
}

void list_clear_destroy(list_t **list_ptr, free_func free)
{
    check(list_ptr && *list_ptr, "Invalid pointer to list.");
    list_clear(*list_ptr, free);
    list_destroy(list_ptr);

error:
    return;
}

void list_add_head(list_t *list, void *data)
{
    check(list, "Invalid list to add to.");

    node_t *new = (node_t *) malloc(sizeof(*new)); 
    check_mem(new);

    new->data = data;
    new->next = list->head->next;
    new->prev = list->head;
    list->head->next->prev = new;
    list->head->next = new;

    list->count ++;

error:
    return;
}

void list_add_tail(list_t *list, void *data)
{
    check(list, "Invalid list to add to.");

    node_t *new = (node_t *) malloc(sizeof(*new)); 
    check_mem(new);

    new->data = data;
    new->next = list->head;
    new->prev = list->head->prev;
    list->head->prev->next = new;
    list->head->prev = new;

    list->count ++;

error:
    return;
}

void *list_del_head(list_t *list)
{
    check(list, "Invalid list.");
    check(!list_is_empty(list), "delete from an empty list");

    node_t *first = list->head->next;
    void *data = list_remove(list, first);

    return data;
error:
    return NULL;
}


void *list_del_tail(list_t *list)
{
    check(list, "Invalid list.");
    check(!list_is_empty(list), "delete from an empty list");

    node_t *last = list->head->prev;
    void *data = list_remove(list, last);

    return data;
error:
    return NULL;

}

void *list_remove(list_t *list, node_t *node)
{
    check(list && node, "Invalid list.");
    void *data = node->data;

    node->prev->next = node->next;
    node->next->prev = node->prev;

    free(node);
    list->count --;
    return data;

error:
    return NULL;
}
