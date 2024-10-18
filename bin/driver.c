/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * DSA driver program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <linked_list.h>
#include <binary_tree.h>
#include <queue.h>
#include <Stack.h>
#include <heap.h>
#include <getopt.h>
#include <assert.h>
#include <stdbool.h>
#include <errno.h>

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

static void
delete_heap_min_max(heap_t *h)
{
    heap_elem_t *del_elem = NULL;

    if (h->h_type == MIN_HEAP) {
        delete_min(h, &del_elem);
    }

    if (h->h_type == MAX_HEAP){
        delete_max(h, &del_elem);
    }
}

static void
print_heap_min_max(heap_t *h)
{
    heap_elem_t *min_max = NULL;

    if (h->h_type == MIN_HEAP){
        min_max= get_min(h);
        if (min_max) {
            printf("\n\t\t\tHeap Min: %llu", min_max->key);
        } else {
            printf("\n\t\t\tHeap Empty");
        }
    }

    if (h->h_type == MAX_HEAP){
        min_max = get_max(h);
        if (min_max) {
            printf("\n\t\t\tHeap Max: %llu", min_max->key);
        } else {
            printf("\n\t\t\tHeap Empty");
        }
    }
}

static void
test_heap_common(heap_type_e type)
{
    const uint64_t heap_size = 15;

    heap_t *h = create_heap(type, heap_size);
    if (h == NULL) {
        printf("\n\t\tFailed to allocate heap");
        goto done;
    }

    for (int i = 0 ; i < heap_size; i++) {
        heap_elem_t elem = {0};
        elem.key = i + 10;
        printf("\n\t\tInserting Element %llu to heap", elem.key);
        insert_heap(h, &elem);
        print_heap_min_max(h);
        printf("\n\t\t\tHeap after insert: ");
        print_heap(h);
    }

    for (int i = 0 ; i < heap_size; i++) {
        printf("\n\t\tDeleting root %d time from heap", i + 1);
        delete_heap_min_max(h);
        print_heap_min_max(h);
        printf("\n\t\t\tHeap after delete: ");
        print_heap(h);
    }

    for (int i = 0 ; i < heap_size; i++) {
        heap_elem_t elem = {0};
        elem.key = i + 10;
        printf("\n\t\tInserting Element %llu to heap", elem.key);
        insert_heap(h, &elem);
        print_heap_min_max(h);
        printf("\n\t\t\tHeap after insert: ");
        print_heap(h);
    }

    for (int i = 0 ; i < heap_size; i++) {
        heap_elem_t elem = {0};
        elem.key = i + 10;
        printf("\n\t\tDeleting element %d time from heap", i + 10);
        delete_heap(h, &elem);
        print_heap_min_max(h);
        printf("\n\t\t\tHeap after delete: ");
        print_heap(h);
    }


done:
    if (h) {
        destroy_heap(h);
    }
    printf("\n");
}

static void
test_min_heap()
{
    printf("\n\tTesting MIN Heap...");
    test_heap_common(MIN_HEAP);
}

static void
test_max_heap()
{
    printf("\n\tTesting MAX Heap...");
    test_heap_common(MAX_HEAP);
}

static void
print_dlist_node(dlist_node_t *node)
{
    if (node != NULL) {
        printf("%llu ", node->key_node.key);
    }
}

static void
print_slist_node(slist_node_t *node)
{
    if (node != NULL) {
        printf("%llu ", node->key_node.key);
    }
}


static void
test_singly_linked_list()
{
    int error = 0;

    printf("\n\tTesting Singly Linked List...");

    slist_node_t *head = NULL;

    printf("\n\t\tInserting into SLL at head...");
    for (int i = 10; i <= 20; i++) {
        printf("\n\t\tInserting %d to SLL", i);
        insert_slist_head(&head, i);
    }

    printf("\n\t\tSLL after insert at head...");
    slist_foreach(head, print_slist_node);


    printf("\n\t\tInserting into SLL at Tail...");
    for (int i = 9; i >= 0; i--) {
        printf("\n\t\tInserting %d to SLL", i);
        insert_slist_tail(&head, i);
    }

    printf("\n\t\tSLL after insert at tail...");
    slist_foreach(head, print_slist_node);

    printf("\n\t\tDeleting random node 99...");
    error = slist_remove(&head, 99);
    if (error != 0) {
        if (error == ENOENT) {
            printf("\n\t\tDelete Failed as Expected.");
        } else {
            printf("\n\t\tDelete Failed Unexpectedly %d", error);
        }
    } else {
        printf("\n\t\tDelete Passed Unexpectedly");
    }

    for (int i = 0; i <= 20; i++) {
        printf("\n\t\tDeleting %d from SLL", i);
        error = slist_remove(&head, i);
        if (error != 0) {
            printf("\n\t\tDelete Failed Unexpectedly %d."
                    " Element %d", error, i);
        }
    }

    printf("\n\t\tSLL after delete...");
    if ((error = slist_foreach(head, print_slist_node)) == ENOENT) {
        printf("Empty List");
    }

    printf("\n");
}

static void
test_doubly_linked_list()
{
    int error = 0;

    printf("\n\tTesting Doubly Linked List...");

    dlist_node_t *head = NULL;

    printf("\n\t\tInserting into DLL at head...");
    for (int i = 10; i <= 20; i++) {
        printf("\n\t\tInserting %d to DLL", i);
        insert_dlist_head(&head, i);
    }

    printf("\n\t\tDLL after insert at head...");
    dlist_foreach(head, print_dlist_node);


    printf("\n\t\tInserting into DLL at Tail...");
    for (int i = 9; i >= 0; i--) {
        printf("\n\t\tInserting %d to DLL", i);
        insert_dlist_tail(&head, i);
    }

    printf("\n\t\tDLL after insert at tail...");
    dlist_foreach(head, print_dlist_node);

    printf("\n\t\tDeleting random node 99...");
    error = dlist_remove(&head, 99);
    if (error != 0) {
        if (error == ENOENT) {
            printf("\n\t\tDelete Failed as Expected.");
        } else {
            printf("\n\t\tDelete Failed Unexpectedly %d", error);
        }
    } else {
        printf("\n\t\tDelete Passed Unexpectedly");
    }

    for (int i = 0; i <= 20; i++) {
        printf("\n\t\tDeleting %d from DLL", i);
        error = dlist_remove(&head, i);
        if (error != 0) {
            printf("\n\t\tDelete Failed Unexpectedly %d."
                    " Element %d", error, i);
        }
    }

    printf("\n\t\tDLL after delete...");
    if ((error = dlist_foreach(head, print_dlist_node)) == ENOENT) {
        printf("Empty List");
    }

    printf("\n");
}

static void
test_linked_list()
{
    test_singly_linked_list();
    test_doubly_linked_list();
}

int main(void)
{
    printf("Welcome to DSA Driver Program!");

    test_binary_tree_wrapper();
    test_simple_q();
    test_stack();
    test_min_heap();
    test_max_heap();
    test_linked_list();

    return 0;
}

