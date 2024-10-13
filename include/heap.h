/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Heap Data Structure Operations
 */

#include <stdint.h>

typedef enum heap_type_ {
    MIN_HEAP = 1,
    MAX_HEAP = 2,
} heap_type_e;

typedef struct heap_elem_ {
    uint64_t key;
} heap_elem_t;


typedef struct heap_ {
    heap_type_e h_type;
    heap_elem_t *h_arr;
    uint64_t h_capacity;
    uint64_t h_curr_size;
} heap_t;

heap_t* create_heap(heap_type_e type, uint64_t size);
int destroy_heap(heap_t *h);

int insert_heap(heap_t *h, heap_elem_t *elem);
int delete_heap(heap_t *h, heap_elem_t *elem);

heap_elem_t *get_min(heap_t *h);
heap_elem_t *get_max(heap_t *h);

int delete_min(heap_t *h, heap_elem_t **min);
int delete_max(heap_t *h, heap_elem_t **max);

void print_heap(heap_t *h);
