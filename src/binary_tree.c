/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Binary Tree Data Structure Operations Implementation.
 */

#include <binary_tree.h>
#include <queue.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

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
        if (temp->left) {
            error = simple_q_enqueue(q, (uint64_t)(temp->left));
            if (error < 0) {
                goto done;
            }
        }
        if (temp->right) {
            error = simple_q_enqueue(q, (uint64_t)(temp->right));
             if (error < 0) {
                goto done;
            }
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
        node->key = 0;
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
        goto done;
    }

    error = insert_bt_node(root, new_node);

done:
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
    if (((*root)->key == key) &&
        ((*root)->left == NULL) &&
        ((*root)->right == NULL)) {
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

        if (temp->left) {
            error = simple_q_enqueue(q, (uint64_t)(temp->left));
            if (error < 0) {
                error = EFAULT;
                goto done;
            }
        }

        if (temp->right) {
            error = simple_q_enqueue(q, (uint64_t)(temp->right));
            if (error < 0) {
                error = EFAULT;
                goto done;
            }
        }

        error = simple_q_dequeue(q, &dequeue_elem);
        if (error < 0) {
            error = EFAULT;
            break;
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

bt_node *
insert_to_bst(bt_node **root, uint64_t key)
{
    bt_node *new_node = alloc_bt_node(key);
    if (new_node == NULL) {
        goto done;
    }

    if (root == NULL) {
        goto done;
    }


    if (*root == NULL) {
        *root = new_node;
        goto done;
    }

    if (key < (*root)->key) {
        (*root)->left = insert_to_bst(&((*root))->left, key);
    } else {
        (*root)->right = insert_to_bst(&((*root)->right), key);
    }

done:
    if (root) {
        return *root;
    } else {
        return NULL;
    }
}

static bt_node*
find_inorder_predecessor(bt_node *node)
{
    bt_node *pre = node->left;
    while (pre != NULL && pre->left != NULL) {
        pre = pre->left;
    }
    return pre;
}

static bt_node*
find_inorder_successor(bt_node *node)
{
    bt_node *successor = node->right;
    while (successor != NULL && successor->left != NULL) {
        successor = successor->left;
    }
    return successor;
}

bt_node*
delete_from_bst(bt_node **root, uint64_t key)
{
    bt_node *temp = NULL;

    if (root == NULL) {
        return NULL;
    }

    if (*root == NULL) {
        return NULL;
    }

    if ((*root)->key == key) {

        /* Leaf Node or only right child*/
        if ((*root)->left == NULL) {
            temp = (*root)->right;
            free_bt_node(*root);
            *root = NULL;
            return temp;
        }

        /* Has only left subtree only */
        if ((*root)->right == NULL) {
            temp = (*root)->left;
            free_bt_node(*root);
            *root = NULL;
            return temp;
        }

        /* Has both sub trees */
        temp = find_inorder_successor(*root);
        (*root)->key = temp->key;
        (*root)->right = delete_from_bst(&((*root)->right), temp->key);

    } else if (key < (*root)->key) {

        (*root)->left = delete_from_bst(&((*root)->left), key);

    } else {

        (*root)->right = delete_from_bst(&((*root)->right), key);

    }

    return (*root);
}
