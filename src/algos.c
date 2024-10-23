/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Various Computer Science Algorithms Implementation.
 */

#include <algos.h>
#include <stdio.h>

int
linear_search_arr(uint64_t *arr, int arr_len, uint64_t target)
{
    int index = -1;

    if (arr == NULL || arr_len == 0) {
        goto done;
    }

    for (int i = 0; i < arr_len; i++) {
        if (arr[i] == target) {
            index = i;
            break;
        }
    }

done:
    return index;
}


int
binary_search_arr(uint64_t *arr, int arr_len, uint64_t target)
{
    int index = -1;
    int mid = 0;
    int left = 0;
    int right = 0;

    if (arr == NULL || arr_len == 0) {
        goto done;
    }

    left = 0;
    right = arr_len -1;

    while (left <= right) {

        //mid = (left + right) / 2;
        mid = (left + (right - left) / 2);

        if (arr[mid] == target) {
            index = mid;
            goto done;
        }

        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

done:
    return index;
}
