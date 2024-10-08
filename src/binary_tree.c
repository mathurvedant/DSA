/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Binary Tree Data Structure Operations Implementation.
 */

#include <stdlib.h>
#include <binary_tree.h>

void
in_order_traversal(BTNode *root, BT_traversalcb cb)
{
    if (NULL == root) {
        return;
    }

    in_order_traversal(root->left, cb);
    cb(root);
    in_order_traversal(root->right, cb);
}

void
pre_order_traversal(BTNode *root, BT_traversalcb cb)
{
    if (NULL == root) {
        return;
    }

    cb(root);
    pre_order_traversal(root->left, cb);
    pre_order_traversal(root->right, cb);
}

void
post_order_traversal(BTNode *root, BT_traversalcb cb)
{
    if (NULL == root) {
        return;
    }

    post_order_traversal(root->left, cb);
    post_order_traversal(root->right, cb);
    cb(root);
}

void
level_order_traversal(BTNode *root, BT_traversalcb cb)
{
}

BTNode*
alloc_BT_node(int key)
{
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    if (node == NULL) {
        goto done;
    }

    node->key = key;
    node->left = NULL;
    node->right = NULL;

done:
    return node;
}

