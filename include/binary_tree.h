/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Binary Tree Data Structure Operations
 */

#include <stdint.h>

typedef struct bt_node_ {
    uint64_t key;
    struct bt_node_ *left;
    struct bt_node_ *right;
} bt_node;

typedef void (*bt_traversalcb)(bt_node *node);

void in_order_traversal(bt_node *root, bt_traversalcb cb);
void pre_order_traversal(bt_node *root, bt_traversalcb cb);
void post_order_traversal(bt_node *root, bt_traversalcb cb);
void level_order_traversal(bt_node *root, bt_traversalcb cb);

bt_node* alloc_bt_node(int key);
void free_bt_node(bt_node *node);











