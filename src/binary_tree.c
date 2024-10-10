/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Binary Tree Data Structure Operations Implementation.
 */

#include <binary_tree.h>
#include <queue.h>
#include <stdlib.h>
#include <errno.h>

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

static bt_node*
alloc_bt_node(uint64_t key)
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

static void
free_bt_node(bt_node *node)
{
    if (node) {
        free(node);
    }
}

static int
insert_bt_node(bt_node **root, bt_node *node)
{
    int error = 0;
    simple_q *q = NULL;
    const uint64_t q_max_size = 100;
    bt_node *temp = NULL;
    uint64_t dequeue_elem = -1;

    if (root == NULL || node == NULL) {
        error = EINVAL;
        goto done;
    }

    /* Empty tree */
    if (*root == NULL) {
        *root = node;
        goto done;
    }


    q = create_simple_q(q_max_size);
    if (q == NULL) {
        error = ENOMEM;
        goto done;
    }

    temp = *root;
    while (temp != NULL) {

        if (temp->left == NULL) {
            temp->left = node;
            goto done;
        } else if (temp->right == NULL) {
            temp->right = node;
            goto done;
        } else {
            error = simple_q_enqueue(q, (uint64_t)(temp->left));
            if (error < 0) {
                error = EFAULT;
                goto done;
            }
            error = simple_q_enqueue(q, (uint64_t)(temp->right));
             if (error < 0) {
                 error = EFAULT;
                goto done;
            }
            error = simple_q_dequeue(q, &dequeue_elem);
            if (error < 0) {
                error = EFAULT;
                goto done;
            }
            temp = (bt_node*)(dequeue_elem);
        }
    }

done:
    if (q) {
        destroy_simple_q(q);
    }
    return error;
}

int
insert_to_bt(bt_node **root, uint64_t key)
{
    int error = 0;

    bt_node *new_node = alloc_bt_node(key);
    if (new_node == NULL) {
        error = ENOMEM;
    }

    error = insert_bt_node(root, new_node);

    return error;
}

int
delete_from_bt(bt_node **root, uint64_t key)
{
    int error = 0;
    simple_q *q = NULL;
    const uint64_t q_max_size = 100;
    bt_node *temp = NULL;
    bt_node *del_node = NULL;
    bt_node *last_node = NULL;
    uint64_t dequeue_elem = -1;
    bool free_node = false;

    if (root == NULL) {
        error = EINVAL;
        goto done;
    }

    /* Empty Tree. */
    if (*root == NULL){
        error = EINVAL;
        goto done;
    }

    /* Only root node */
    if ((*root)->key == key) {
        free(*root);
        *root = NULL;
        goto done;
    }


    q = create_simple_q(q_max_size);
    if (q == NULL) {
        error = ENOMEM;
        goto done;
    }

    /* Traversal one to find node to delete and last node. */
    temp = *root;
    while (temp != NULL) {

        last_node = temp;

        if (temp->key == key) {
            del_node = temp;
        }

        error = simple_q_enqueue(q, (uint64_t)(temp->left));
        if (error < 0) {
            error = EFAULT;
            goto done;
        }
        error = simple_q_enqueue(q, (uint64_t)(temp->right));
        if (error < 0) {
            error = EFAULT;
            goto done;
        }
        error = simple_q_dequeue(q, &dequeue_elem);
        if (error < 0) {
            error = EFAULT;
            goto done;
        }
        temp = (bt_node*)(dequeue_elem);
    }

    del_node->key = last_node->key;

    /* Traversal two to delete last node. */
    temp = *root;
    while (temp != NULL) {

        if (temp == last_node) {
            free_node = true;
            goto done;
        }

        if (temp->left == last_node) {
            temp->left = NULL;
            free_node = true;
            goto done;
        } else {
            error = simple_q_enqueue(q, (uint64_t)(temp->left));
            if (error < 0) {
                error = EFAULT;
                goto done;
            }
        }

        if (temp->right == last_node) {
            temp->right = NULL;
            free_node = true;
            goto done;
        } else {
            error = simple_q_enqueue(q, (uint64_t)(temp->right));
            if (error < 0) {
                error = EFAULT;
                goto done;
            }
        }

        error = simple_q_dequeue(q, &dequeue_elem);
        if (error < 0) {
            error = EFAULT;
            goto done;
        }
        temp = (bt_node*)(dequeue_elem);
    }

done:
    if (q) {
        destroy_simple_q(q);
    }
    if (free_node) {
        free_bt_node(last_node);
    }
    return error;
}
