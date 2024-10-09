/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Queue Data Structure Operations
 */

#include <stdint.h>
#include <stdbool.h>

typedef struct simple_queue_ {
    uint64_t front;
    uint64_t rear;
    uint64_t max_size;
    uint64_t curr_size;
    uint64_t *arr;
} simple_q;

simple_q* create_simple_q(uint64_t size);
void destroy_simple_q(simple_q *q);

int simple_q_enqueue(simple_q *q, uint64_t key);
int simple_q_dequeue(simple_q *q, uint64_t *out);
bool simple_q_is_full(simple_q *q);
bool simple_q_is_empty(simple_q *q);
void print_simple_q(simple_q *q);
void print_simple_q_info(simple_q *q);
