/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Queue Data Structure Operations Implementation.
 */

#include <queue.h>
#include <stdlib.h>
#include <stdio.h>

simple_q*
create_simple_q(uint64_t size)
{
    if (size < 1 ) {
        return NULL;
    }

    simple_q *newq = (simple_q*)malloc(sizeof(simple_q));
    if (newq == NULL) {
        return NULL;
    }

    newq->arr = (uint64_t*)malloc(sizeof(uint64_t) * size);
    if (newq->arr == NULL) {
        free(newq);
        return NULL;
    }

    newq->front = 0;
    newq->rear = 0;
    newq->size = size;

    return newq;
}


void
destroy_simple_q(simple_q *q)
{
    free(q->arr);
    free(q);
}

int
simple_q_enqueue(simple_q *q, uint64_t key)
{
    int error = 0;
    if (simple_q_is_full(q)) {
        error = -1;
        goto done;
    }

    q->arr[(q->rear++ % q->size)] = key;

done:
    return error;
}

int
simple_q_dequeue(simple_q *q, uint64_t *out)
{
    int error = 0;
    if (simple_q_is_empty(q)) {
        error = -1;
        goto done;
    }

    *out = q->arr[(q->front++ % q->size)];

done:
    return error;
}

bool
simple_q_is_full(simple_q *q)
{
    if (q->front < q->rear) {
        return (q->rear - q->front + 1 == q->size);
    } else {
        return (q->front - q->rear + 1 == q->size);
    }
}

bool
simple_q_is_empty(simple_q *q)
{
    return (q->front == q->rear);
}

void
print_simple_q(simple_q *q)
{
    for (int i = 0; i < q->size; i++) {
        printf("%llu ", q->arr[i]);
    }

}
