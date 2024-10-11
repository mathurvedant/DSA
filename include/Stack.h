/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Stack Data Structure Operations
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct dsa_stack_ {
    uint64_t capacity;
    uint64_t curr_size;
    uint64_t *top;
    uint64_t *elements;
} dsa_stack_t;

dsa_stack_t *create_dsa_stack(uint64_t capacity);
int destroy_dsa_stack(dsa_stack_t *s);

int dsa_stack_push(dsa_stack_t *s, uint64_t key);
int dsa_stack_pop(dsa_stack_t *s, uint64_t *key);
int dsa_stack_top(dsa_stack_t *s, uint64_t *key);
bool dsa_stack_is_empty(dsa_stack_t *s);
bool dsa_stack_is_full(dsa_stack_t *s);
