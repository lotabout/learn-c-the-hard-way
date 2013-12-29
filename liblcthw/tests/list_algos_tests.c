#include "minunit.h"
#include <lcthw/list_algos.h>
#include <lcthw/list.h>
#include <assert.h>
#include <string.h>

char *values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS"};

#define NUM_VALUES 5

list_t *create_words()
{
    int i = 0;
    list_t *words = list_create();

    for (i = 0; i < NUM_VALUES; i++) {
        list_add_tail(words, values[i]);
    }

    return words;
}

int is_sorted(list_t *words)
{
    node_t *cur;
    list_for_each(words, cur) {
        if ((cur->next != words->head) && 
            strcmp((char *)cur->data, (char *)cur->next->data) > 0) {
            debug("%s %s", (char *)cur->data, (char *)cur->next->data);
            return 0;
        }
    }

    return 1;
}

char *test_bubble_sort()
{
    list_t *words = create_words();

    // should work on a list that needs sorting
    int rc = list_bubble_sort(words, (list_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed.");
    mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

    // should work on a already sorted list
    rc = list_bubble_sort(words, (list_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort of already sorted failed.");
    mu_assert(is_sorted(words), "Words are not sorted if already bubble sorted.");

    list_destroy(&words);

    // should work on an empty list.
    words = create_words();
    rc = list_bubble_sort(words, (list_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort of on empty list.");
    mu_assert(is_sorted(words), "Words should be sorted if empty.");

    list_destroy(&words);

    return NULL;
}

char *test_merge_sort()
{
    list_t *words = create_words();

    // should work on a list that needs sorting
    list_t *res = list_merge_sort(words, (list_compare)strcmp);
    mu_assert(is_sorted(res), "Words are not sorted after merge sort.");

    list_t *res2 = list_merge_sort(res, (list_compare)strcmp);
    mu_assert(is_sorted(res2), "Should still be sorted after merge sort.");

    list_destroy(&res2);
    list_destroy(&res);

    list_destroy(&words);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);

    return NULL;
}

RUN_TESTS(all_tests);
