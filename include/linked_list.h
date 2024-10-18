/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Linked List Data Structure Operations
 */

#pragma once

#include <stdint.h>

typedef struct ll_node_key_ {
    uint64_t key;
    uint64_t val; // For hash map use only.
} ll_node_key_t;

typedef struct slist_node_ {
    ll_node_key_t key_node;
    struct slist_node_ *next;
} slist_node_t;

typedef struct dlist_node_ {
    ll_node_key_t key_node;
    struct dlist_node_ *prev;
    struct dlist_node_ *next;
} dlist_node_t;

typedef void (*sll_traversalcb)(slist_node_t *node);
typedef void (*dll_traversalcb)(dlist_node_t *node);

int insert_slist_head(slist_node_t **head, uint64_t key, uint64_t val);
int insert_slist_tail(slist_node_t **head, uint64_t key, uint64_t val);
int slist_remove(slist_node_t **head, uint64_t key);
int slist_foreach(slist_node_t *head, sll_traversalcb cb);

int insert_dlist_head(dlist_node_t **head, uint64_t key);
int insert_dlist_tail(dlist_node_t **head, uint64_t key);
int dlist_remove(dlist_node_t **head, uint64_t key);
int dlist_foreach(dlist_node_t *head, dll_traversalcb cb);

