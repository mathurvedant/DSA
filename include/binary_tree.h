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

BTNode *in_order_traversal(BTNode *root);
BTNode *pre_order_traversal(BTNode *root);
BTNode *post_order_traversal(BTNode *root);
BTNode *level_order_traversal(BTNode *root);













