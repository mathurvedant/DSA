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
void level_order_traversal_with_height(bt_node *root, bt_traversalcb cb);


int insert_to_bt(bt_node **root, uint64_t key);
int delete_from_bt(bt_node **root, uint64_t key);

bt_node* insert_to_bst(bt_node **root, uint64_t key);
bt_node* delete_from_bst(bt_node **root, uint64_t key);



