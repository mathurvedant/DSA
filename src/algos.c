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

static void
swap(int64_t *a, int64_t *b)
{
    int64_t temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int64_t *arr, int len)
{
    for (int i = 0 ; i < len; i++) {
        for (int j = 0 ; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void selection_sort(int64_t *arr, int len)
{
    int min_idx = 0;

    for (int i = 0; i < len; i++) {
        min_idx = i;
        for (int j = i; j < len; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[i], &arr[min_idx]);
    }

}

// 3 5 7 0 2 8

void insertion_sort(int64_t *arr, int len)
{
    int j = 0;
    int64_t min = 0;

    for (int i = 1; i < len; i++) {
        min = arr[i];

        j = i - 1;
        while (j >= 0 && arr[j] > min) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = min;
    }
}

static int
quick_sort_partition(int64_t *arr, int low, int high)
{
    int64_t pivot = arr[high];

    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[j], &arr[i]);
        }
    }
    swap(&arr[i + 1], &arr[high]);

    return i + 1;

}

static void
quick_sort_helper(int64_t *arr, int low, int high)
{
    int pivot = 0;

    if (low < high) {
        pivot = quick_sort_partition(arr, low, high);
        quick_sort_helper(arr, low, pivot - 1);
        quick_sort_helper(arr, pivot + 1, high);
    }

}

void quick_sort(int64_t *arr, int len)
{
    quick_sort_helper(arr, 0, len - 1);
}

static void
merge(int64_t *arr, int low, int mid, int high)
{
    int len1 = mid - low + 1;
    int len2 = high - mid;
    int i, j, k = 0;

    int arr1[len1];
    int arr2[len2];

    for (i = 0; i < len1; i++) {
        arr1[i] = arr[low + i];
    }

    for (j = 0; j < len2; j++) {
        arr2[j] = arr[mid + j];
    }

    i = 0;
    j = 0;
    k = 0;
    while (i < len1 && j < len2) {
        if (arr1[i] < arr2[j]) {
            arr[k] = arr1[i];
            i++;
        } else {
            arr[k] = arr2[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        arr[k] = arr1[i];
        k++;
    }

    while (j < len2) {
        arr[k] = arr2[j];
        k++;
    }

}

static void
merge_sort_helper(int64_t *arr, int low, int high)
{
    if (low < high) {
        int mid = (low + (high - low) / 2);
        merge_sort_helper(arr, low, mid - 1);
        merge_sort_helper(arr, mid, high);
        merge(arr, low, mid, high);
    }
}

void merge_sort(int64_t *arr, int len)
{
    merge_sort_helper(arr, 0, len - 1);
}

