/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Heap Data Structure Operations Implementation.
 */

#include <heap.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>

static bool
is_heap_full(heap_t * h)
{
    return (h->h_curr_size == h->h_capacity);
}

static bool
is_heap_empty(heap_t *h)
{
    return (h->h_curr_size == 0);
}

static bool
is_min_heap(heap_t *h)
{
    return (h->h_type == MIN_HEAP);
}

static bool
is_max_heap(heap_t *h)
{
    return (h->h_type == MAX_HEAP);
}

static int
heap_parent(int i)
{
    return ((i-1) / 2);
}

static int
heap_left_child(int i)
{
    return (2*i + 1);
}

static int
heap_right_child(int i)
{
    return (2*i + 2);
}

static void
swap_heap_elements(heap_elem_t *a, heap_elem_t *b)
{
    heap_elem_t temp = {0};

    temp.key = a->key;
    a->key = b->key;
    b->key = temp.key;
}

static void
min_heapify(heap_t *h, int index)
{
    heap_elem_t *parent = &h->h_arr[index];
    heap_elem_t *left = &h->h_arr[heap_left_child(index)];
    heap_elem_t *right = &h->h_arr[heap_right_child(index)];
    heap_elem_t *smallest = parent;
    int smallest_index = index;

    if (index > h->h_curr_size - 1) {
        return;
    }

    if ((heap_left_child(index) <= h->h_curr_size - 1) &&
        (smallest->key > left->key)) {
        smallest = left;
        smallest_index = heap_left_child(index);
    }

    if ((heap_right_child(index) <= h->h_curr_size - 1) &&
        (smallest->key > right->key)) {
        smallest = right;
        smallest_index = heap_right_child(index);
    }

    if (smallest != parent) {
        swap_heap_elements(parent, smallest);
        min_heapify(h, smallest_index);
    }
}

static void
max_heapify(heap_t *h, int index)
{
    heap_elem_t *parent = &h->h_arr[index];
    heap_elem_t *left = &h->h_arr[heap_left_child(index)];
    heap_elem_t *right =& h->h_arr[heap_right_child(index)];
    heap_elem_t *largest = parent;
    int largest_index = index;

    if (index > h->h_curr_size - 1) {
        return;
    }

    if ((heap_left_child(index) <= h->h_curr_size - 1) &&
        (largest->key < left->key)) {
        largest = left;
        largest_index = heap_left_child(index);
    }

    if ((heap_right_child(index) <= h->h_curr_size - 1) &&
        (largest->key < right->key)) {
        largest = right;
        largest_index = heap_right_child(index);
    }

    if (largest != parent) {
        swap_heap_elements(parent, largest);
        max_heapify(h, largest_index);
    }
}


static void
heapify(heap_t *h, int index)
{
    if (is_min_heap(h)) {
        min_heapify(h, index);
        goto done;
    }

    if (is_max_heap(h)) {
        max_heapify(h, index);
        goto done;
    }

done:
    return;
}

heap_t*
create_heap(heap_type_e type, uint64_t size)
{
    heap_t *new_heap = NULL;

    new_heap = (heap_t*)malloc(sizeof(heap_t));
    if (new_heap == NULL) {
        goto done;
    }

    new_heap->h_arr = (heap_elem_t *)malloc(size * sizeof(heap_elem_t));
    if (new_heap->h_arr == NULL) {
        free(new_heap);
        new_heap = NULL;
        goto done;
    }

    new_heap->h_type = type;
    new_heap->h_capacity = size;
    new_heap->h_curr_size = 0;

done:
    return new_heap;
}

int
destroy_heap(heap_t *h)
{
    free(h->h_arr);
    free(h);

    return 0;
}

int
insert_heap(heap_t *h, heap_elem_t *elem)
{
    int error = 0;
    int index = h->h_curr_size;

    if (is_heap_full(h)) {
        error = EFAULT;
        goto done;
    }

    h->h_arr[index] = *elem;
    h->h_curr_size++;

    while (index != 0) {
        int parent_index = heap_parent(index);
        if (is_max_heap(h)) {
            if (h->h_arr[index].key > h->h_arr[parent_index].key) {
                swap_heap_elements(&h->h_arr[index], &h->h_arr[parent_index]);
            }
        } else if (is_min_heap(h)) {
            if (h->h_arr[index].key < h->h_arr[parent_index].key) {
                swap_heap_elements(&h->h_arr[index], &h->h_arr[parent_index]);
            }
        }
        index = parent_index;
    }

done:
    return error;
}

int
delete_heap(heap_t *h, heap_elem_t *elem)
{
    int error = 0;
    int elem_index = 0;

    if (is_heap_empty(h)) {
        error = EFAULT;
        goto done;
    }

    if (h->h_curr_size == 1) {
        h->h_curr_size--;
        goto done;
    }

    for (elem_index = 0; elem_index < h->h_curr_size; elem_index++) {
        if (h->h_arr[elem_index].key == elem->key) {
            break;
        }
    }

    swap_heap_elements(&h->h_arr[h->h_curr_size - 1], &h->h_arr[elem_index]);
    h->h_curr_size--;
    heapify(h, 0);

done:
    return error;
}

heap_elem_t*
get_min(heap_t *h)
{
    if (is_heap_empty(h)) {
        return NULL;
    }

    return &h->h_arr[0];
}

heap_elem_t*
get_max(heap_t *h)
{
    if (is_heap_empty(h)) {
        return NULL;
    }

    return &h->h_arr[0];
}

int
delete_min(heap_t *h, heap_elem_t **min)
{

    *min = get_min(h);
    return delete_heap(h, *min);
}

int
delete_max(heap_t *h, heap_elem_t **max)
{
    *max = get_max(h);
    return delete_heap(h, *max);
}

void
print_heap(heap_t *h)
{
    if (is_heap_empty(h)) {
        printf("Heap Empty");
        return;
    }

    for (int i = 0; i < h->h_curr_size; i++) {
        printf("%llu ", h->h_arr[i].key);
    }
}
