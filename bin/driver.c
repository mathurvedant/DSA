/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * DSA driver program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <binary_tree.h>
#include <queue.h>
#include <Stack.h>
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
test_binary_tree(uint64_t *tree_elements, int num_tree_elements, bool is_bst)
{
    if (is_bst) {
        printf("\n\tTesting Binary Search Tree...");
    } else {
        printf("\n\tTesting Binary Tree...");
    }

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

static void
test_binary_tree_wrapper() {
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
     *    20      NULL    54      87
     * NULL  23
     */
    const int num_tree_elements = 7;
    uint64_t tree_elements[num_tree_elements] = {50, 30, 20, 67, 54, 23, 87};
    uint64_t tree_elements_skewed_1[num_tree_elements] = {1, 2, 3, 4, 5, 6, 7};
    uint64_t tree_elements_skewed_2[num_tree_elements] = {7, 6, 5, 4, 3, 2, 1};

    test_binary_tree(tree_elements, num_tree_elements, false);
    test_binary_tree(tree_elements, num_tree_elements, true);

    test_binary_tree(tree_elements_skewed_1, num_tree_elements, false);
    test_binary_tree(tree_elements_skewed_1, num_tree_elements, true);

    test_binary_tree(tree_elements_skewed_2, num_tree_elements, false);
    test_binary_tree(tree_elements_skewed_2, num_tree_elements, true);
}

static void
test_stack()
{
    printf("\n\tTesting Stack...");

    const uint64_t stack_capacity = 15;
    const uint64_t run_capacity = 10;
    uint64_t elem = -1;
    dsa_stack_t *s = create_dsa_stack(stack_capacity);
    if (s == NULL) {
        printf("\n\t\tFailed to allocate stack");
        goto done;
    }

    for (int i = 0; i < run_capacity; i++) {
        printf("\n\t\tPushing %d ", i);
        dsa_stack_push(s, i);
    }

    if (dsa_stack_is_full(s)) {
        printf("\n\t\tStack is full.");
    } else {
        printf("\n\t\tStack is not full.");
    }

    dsa_stack_top(s, &elem);
    printf("\n\t\tTop element = %llu", elem);

    for (int i = 0; i < run_capacity; i++) {
        uint64_t pop_elem = -1;
        dsa_stack_pop(s, &pop_elem);
        printf("\n\t\tPopping %llu ", pop_elem);
    }

    if (dsa_stack_is_empty(s)) {
        printf("\n\t\tStack is empty.");
    }

done:
    if (s) {
        destroy_dsa_stack(s);
    }
    printf("\n");
    return;
}

int main(void)
{
    printf("Welcome to DSA Driver Program!");

    test_binary_tree_wrapper();
    test_simple_q();
    test_stack();

    return 0;
}

