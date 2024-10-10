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
#include <stdbool.h>

static void
print_bt_node(bt_node *node)
{
    if (node) {
        printf("%llu ", node->key);
    }
}

static void
test_binary_tree(bool is_bst)
{
    if (is_bst) {
        printf("\n\tTesting Binary Search Tree...");
    } else {
        printf("\n\tTesting Binary Tree...");
    }

    /*
     * BT below is used to test -
     *              50
     *      30              20
     *  67      54      23      87
     *
     * For BST, root remains 50, rest are
     * inserted per BST properties and tree
     * will look like below -
     *
     *                50
     *        30              67
     *    20      NULL       54      87
     * NULL  23
     */
    const int num_tree_elements = 7;
    uint64_t tree_elements[num_tree_elements] = {50, 30, 20, 67, 54, 23, 87};

    bt_node *root = NULL;

    for (int i = 0 ; i < num_tree_elements; i++ ) {
        if (is_bst) {
            insert_to_bst(&root, tree_elements[i]);
        } else {
            insert_to_bt(&root, tree_elements[i]);
        }
    }

    printf("\n\t\tIn Order B%sT Traversal: ", (is_bst?"S":""));
    in_order_traversal(root, print_bt_node);

    printf("\n\t\tPre Order B%sT Traversal: ", (is_bst?"S":""));
    pre_order_traversal(root, print_bt_node);

    printf("\n\t\tPost Order B%sT Traversal: ", (is_bst?"S":""));
    post_order_traversal(root, print_bt_node);

    printf("\n\t\tLevel Order B%sT Traversal: ", (is_bst?"S":""));
    level_order_traversal(root, print_bt_node);

    for (int i = 0; i < num_tree_elements; i++) {
        printf("\n\t\tDeleting tree element %llu", tree_elements[i]);
        if (is_bst) {
            delete_from_bst(&root, tree_elements[i]);
        } else {
            delete_from_bt(&root, tree_elements[i]);
        }
        if (root) {
            printf("\n\t\tTree After Delete of %llu - ", tree_elements[i]);
            level_order_traversal(root, print_bt_node);
        }
    }

    if (root == NULL) {
        printf("\n\t\tTree Delete Successful.");
    } else {
        printf("\n\t\tTree Delete Failed.");
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

    test_binary_tree(false);
    test_binary_tree(true);
    
    test_simple_q();

    return 0;
}

