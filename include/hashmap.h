/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Hash Map Data Structure Operations
 */

#pragma once

#include <linked_list.h>

typedef slist_node_t hash_map_elem_t;

typedef struct hash_map_bucket_ {
    hash_map_elem_t *bucket_head;
} hash_map_bucket_t;

typedef struct hash_map_ {
    uint64_t num_buckets;
    hash_map_bucket_t *buckets;
} hash_map_t;

int create_dsa_hash_map(hash_map_t **map, uint64_t num_buckets);
int destroy_dsa_hash_map(hash_map_t *map);

int dsa_hash_map_insert(hash_map_t *map, uint64_t key, uint64_t val);
int dsa_hash_map_delete(hash_map_t *map, uint64_t key);
int dsa_hash_map_lookup(hash_map_t *map, uint64_t key, uint64_t *val);
