/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Hash Map Structure Operations Implementation.
 */

#include <hashmap.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

static int
mod_hash(uint64_t key, uint64_t buckets)
{
    return (key % buckets);
}

int
create_dsa_hash_map(hash_map_t **map, uint64_t num_buckets)
{
    int error = 0;
    hash_map_t *new_map = NULL;

    if (map == NULL) {
        error = EINVAL;
        goto done;
    }

    new_map = (hash_map_t *)malloc(sizeof(hash_map_t));
    if (new_map == NULL) {
        error = ENOMEM;
        *map = NULL;
        goto done;
    }

    new_map->buckets = (hash_map_bucket_t *)
                        malloc(num_buckets * sizeof(hash_map_bucket_t));
    if (new_map->buckets == NULL) {
        error = ENOMEM;
        free(new_map);
        *map = NULL;
        goto done;
    }

    new_map->num_buckets = num_buckets;
    for (int i = 0; i < num_buckets; i++) {
        bzero(&new_map->buckets[i], sizeof(hash_map_bucket_t));
    }

    *map = new_map;
done:
    return error;
}

int destroy_dsa_hash_map(hash_map_t *map)
{
    int error = 0;

    if (map == NULL) {
       error = EINVAL;
       goto done;
    }

    free(map->buckets);
    free(map);

done:
    return error;
}

int
dsa_hash_map_insert(hash_map_t *map, uint64_t key, uint64_t val)
{
    int error = 0;
    uint64_t temp_val = 0;
    uint64_t index = mod_hash(key, map->num_buckets);
    hash_map_bucket_t *curr_bucket = &map->buckets[index];
    if (curr_bucket == NULL) {
        error = EFAULT;
        goto done;
    }

    error = dsa_hash_map_lookup(map, key, &temp_val);
    if (error != ENOENT) {
        error = EEXIST;
        goto done;
    }

    error = insert_slist_head(&curr_bucket->bucket_head, key, val);

done:
    return error;
}

int
dsa_hash_map_delete(hash_map_t *map, uint64_t key)
{
    int error = 0;
    uint64_t index = mod_hash(key, map->num_buckets);
    hash_map_bucket_t *curr_bucket = &map->buckets[index];
    if (curr_bucket == NULL) {
        error = EFAULT;
        goto done;
    }

    error = slist_remove(&curr_bucket->bucket_head, key);

done:
    return error;
}


int
dsa_hash_map_lookup(hash_map_t *map, uint64_t key, uint64_t *val)
{
    int error = 0;
    uint64_t index = mod_hash(key, map->num_buckets);
    hash_map_bucket_t *curr_bucket = &map->buckets[index];
    slist_node_t *head = NULL;
    if (curr_bucket == NULL) {
        error = EFAULT;
        goto done;
    }
    head = curr_bucket->bucket_head;

    while (head != NULL) {
        if (head->key_node.key == key) {
            *val = head->key_node.val;
            goto done;
        }
        head = head->next;
    }

    if (head == NULL) {
        error = ENOENT;
    }

done:
    return error;
}

