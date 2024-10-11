/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Stack Structure Operations Implementation.
 */

#include <Stack.h>
#include <queue.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

dsa_stack_t *
create_dsa_stack(uint64_t capacity)
{
    dsa_stack_t *s = (dsa_stack_t *)malloc(sizeof(dsa_stack_t));
    if (s == NULL) {
        goto done;
    }

    s->elements = (uint64_t*)malloc(capacity * sizeof(uint64_t));
    if (s->elements == NULL) {
        free(s);
        s = NULL;
        goto done;
    }

    s->capacity = capacity;
    s->curr_size = 0;
    s->top = NULL;

done:
    return s;
}

int
destroy_dsa_stack(dsa_stack_t *s)
{
    int error = 0;

    if (s == NULL) {
        error = EINVAL;
        goto done;
    }

    free(s->elements);
    free(s);

done:
    return error;
}

int
dsa_stack_push(dsa_stack_t *s, uint64_t key)
{
    int error = 0;

    if (s == NULL) {
        error = EINVAL;
        goto done;
    }

    if (dsa_stack_is_full(s)) {
        error = EFAULT;
        goto done;
    }

    s->elements[s->curr_size] = key;
    s->top = &s->elements[s->curr_size];
    s->curr_size++;

done:
    return error;
}

int
dsa_stack_pop(dsa_stack_t *s, uint64_t *key)
{
    int error = 0;

    if (s == NULL) {
        error = EINVAL;
        goto done;
    }

    if (dsa_stack_is_empty(s)) {
        error = EFAULT;
        goto done;
    }

    *key = *s->top;
    s->curr_size--;
    s->top = &s->elements[s->curr_size - 1];

done:
    return error;
}

int
dsa_stack_top(dsa_stack_t *s, uint64_t *key)
{
    int error = 0;

    if (s == NULL) {
        error = EINVAL;
        goto done;
    }

    if (dsa_stack_is_empty(s)) {
        error = EFAULT;
        goto done;
    }

    *key = *s->top;

done:
    return error;
}

bool
dsa_stack_is_empty(dsa_stack_t *s)
{
    return (s->curr_size == 0);
}

bool
dsa_stack_is_full(dsa_stack_t *s)
{
    return (s->curr_size == s->capacity);
}
