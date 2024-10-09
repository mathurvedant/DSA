/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Binary Tree Data Structure Operations Implementation.
 */

#include <binary_tree.h>
#include <queue.h>
#include <stdlib.h>

void
in_order_traversal(bt_node *root, bt_traversalcb cb)
{
    if (NULL == root) {
        return;
    }

    in_order_traversal(root->left, cb);
    cb(root);
    in_order_traversal(root->right, cb);
}

void
pre_order_traversal(bt_node *root, bt_traversalcb cb)
{
    if (NULL == root) {
        return;
    }

    cb(root);
    pre_order_traversal(root->left, cb);
    pre_order_traversal(root->right, cb);
}

void
post_order_traversal(bt_node *root, bt_traversalcb cb)
{
    if (NULL == root) {
        return;
    }

    post_order_traversal(root->left, cb);
    post_order_traversal(root->right, cb);
    cb(root);
}

void
level_order_traversal(bt_node *root, bt_traversalcb cb)
{
    int error = 0;
    simple_q *q = NULL;
    const uint64_t q_max_size = 100;
    bt_node *temp = NULL;
    uint64_t dequeue_elem = -1;

    if (NULL == root) {
        goto done;
    }

    q = create_simple_q(q_max_size);
    if (q == NULL) {
        goto done;
    }

    temp = root;
    while (temp != NULL) {
        cb(temp);
        error = simple_q_enqueue(q, (uint64_t)(temp->left));
        if (error < 0) {
            goto done;
        }
        error = simple_q_enqueue(q, (uint64_t)(temp->right));
         if (error < 0) {
            goto done;
        }
        error = simple_q_dequeue(q, &dequeue_elem);
        if (error < 0) {
            goto done;
        }
        temp = (bt_node*)(dequeue_elem);
    }

done:
    if (q) {
        destroy_simple_q(q);
    }
}

bt_node*
alloc_bt_node(int key)
{
    bt_node *node = (bt_node *)malloc(sizeof(bt_node));
    if (node == NULL) {
        goto done;
    }

    node->key = key;
    node->left = NULL;
    node->right = NULL;

done:
    return node;
}

void
free_bt_node(bt_node *node)
{
    if (node) {
        free(node);
    }
}
