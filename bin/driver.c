/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * DSA driver program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <binary_tree.h>
#include <queue.h>
#include <getopt.h>
#include <assert.h>

static void
print_bt_node(bt_node *node)
{
    if (node) {
        printf("%llu ", node->key);
    }
}

static void
test_binary_tree(void)
{
    printf("\n\tTesting Binary Tree...");

    /*
     * BT below is used to test -
     *              50
     *      30              20
     *  67      54      23      87
     *
     */

    bt_node *root = alloc_bt_node(50);
    bt_node *left = alloc_bt_node(30);
    bt_node *right = alloc_bt_node(20);
    bt_node *left_l = alloc_bt_node(67);
    bt_node *left_r = alloc_bt_node(54);
    bt_node *right_l = alloc_bt_node(23);
    bt_node *right_r = alloc_bt_node(87);


    if (root == NULL || left == NULL || right == NULL ||
        left_l == NULL || left_r == NULL || right_l == NULL ||
        right_r == NULL) {
        goto done;
    }

    root->left = left;
    root->right = right;

    left->left = left_l;
    left->right = left_r;

    right->left = right_l;
    right->right = right_r;

    printf("\n\t\tIn Order BT Traversal: ");
    in_order_traversal(root, print_bt_node);

    printf("\n\t\tPre Order BT Traversal: ");
    pre_order_traversal(root, print_bt_node);

    printf("\n\t\tPost Order BT Traversal: ");
    post_order_traversal(root, print_bt_node);

    printf("\n\t\tLevel Order BT Traversal: ");
    level_order_traversal(root, print_bt_node);

done:
    if (left_l) {
        free_bt_node(left_l);
    }

    if (left_r) {
        free_bt_node(left_r);
    }

    if (right_l) {
        free_bt_node(right_l);
    }

    if (left_r) {
        free_bt_node(right_r);
    }

    if (left) {
        free_bt_node(left);
    }

    if (right) {
        free_bt_node(right);
    }

    if (root) {
        free_bt_node(root);
    }

    printf("\n");
    return;
}

static void
test_simple_q(void)
{
    printf("\n\tTesting Simple Queue...");

    int error = 0;
    const uint64_t max_size = 5;
    uint64_t dequeue_elem = -1;
    simple_q *q = create_simple_q(max_size);
    if (q == NULL) {
        goto done;
    }

    printf("\n\t\tTesting Enqueue...");
    for (int i = 1; i <= max_size; i++) {
        error = simple_q_enqueue(q, i);
        if (error < 0) {
            printf("\n\t\tError enqueuing!");
            goto done;
        }
    }
    printf("\n\t\tSimple Queue After Enqueue: ");
    print_simple_q(q);

    printf("\n\t\tTesting Enqueue on Full...");
    error = simple_q_enqueue(q, 99);
    assert(error < 0);
    if (error < 0) {
        printf("\n\t\tFailed to Enqueue 99.");
    }

    printf("\n\t\tTesting Dequeue...");
    for (int i = 1; i <= max_size; i++) {
        error = simple_q_dequeue(q, &dequeue_elem);
        if (error < 0) {
            printf("\n\t\tError dequeuing!");
            goto done;
        }
        assert(dequeue_elem == i);
    }
    printf("\n\t\tSimple Queue After Dequeue: ");
    print_simple_q(q);


    printf("\n\t\tTesting Dequeue on Empty...");
    error = simple_q_dequeue(q, &dequeue_elem);
    assert(error < 0);
    if (error < 0) {
        printf("\n\t\tFailed to Dequeue.");
    }


done:
    if (q) {
        printf("\n\t\tFinal Queue State: ");
        print_simple_q(q);
        printf("\n\t\tFinal Queue Info: ");
        print_simple_q_info(q);
        destroy_simple_q(q);
    }
    printf("\n");
    return;
}

int main(void)
{
    printf("Welcome to DSA Driver Program!");

    test_binary_tree();

    test_simple_q();

    return 0;
}

