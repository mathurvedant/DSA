/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Binary Tree Data Structure Operations
 */

#include <stdint.h>

typedef struct BTNode_ {
    uint64_t key;
    struct BTNode_ *left;
    struct BTNode_ *right;
} BTNode;

typedef void (*BT_traversalcb)(BTNode *node);

void in_order_traversal(BTNode *root, BT_traversalcb cb);
void pre_order_traversal(BTNode *root, BT_traversalcb cb);
void post_order_traversal(BTNode *root, BT_traversalcb cb);
void level_order_traversal(BTNode *root, BT_traversalcb cb);

BTNode* alloc_BT_node(int key);












