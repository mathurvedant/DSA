/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Algorithms driver program.
 */

#include <algos.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <errno.h>


static int
qsort_compare(const void *a, const void *b)
{
    uint64_t x = *(uint64_t *)(a);
    uint64_t y = *(uint64_t*)(b);

    return x - y;
}

static void
test_search(void)
{
    printf("\n\tTesting Searching Algorithms...");

    int ARR_SIZE = 100;
    uint64_t linear_arr[ARR_SIZE];
    uint64_t sorted_arr[ARR_SIZE];
    int target_index = 59;
    uint64_t linear_target = linear_arr[target_index];
    uint64_t sorted_target = sorted_arr[target_index];

    for (int i = 0; i < ARR_SIZE; i++) {
        linear_arr[i] = rand();
    }

    for (int i = 0; i < ARR_SIZE; i++) {
        sorted_arr[i] = rand();
    }
    qsort(sorted_arr, ARR_SIZE, sizeof(uint64_t), qsort_compare);

    linear_target = linear_arr[target_index];
    sorted_target = sorted_arr[target_index];

    printf("\n\t\tLinear Search for %llu gives index %d", linear_target,
            linear_search_arr(linear_arr, ARR_SIZE, linear_target));

    printf("\n\t\tBinary Search for %llu gives index %d", sorted_target,
            binary_search_arr(sorted_arr, ARR_SIZE, sorted_target));

    printf("\n");
}

int main(void)
{
    printf("\nWelcome to Algorithms Driver Program!");

    test_search();

    return 0;
}
