/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * DSA driver program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <hashmap.h>
#include <linked_list.h>
#include <binary_tree.h>
#include <queue.h>
#include <Stack.h>
#include <heap.h>
#include <graph.h>
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

    printf("\n\t\tLevel Order B%sT Traversal With Height: ", (is_bst?"S":""));
    level_order_traversal_with_height(root, print_bt_node);

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
        insert_slist_head(&head, i, 0);
    }

    printf("\n\t\tSLL after insert at head...");
    slist_foreach(head, print_slist_node);


    printf("\n\t\tInserting into SLL at Tail...");
    for (int i = 9; i >= 0; i--) {
        printf("\n\t\tInserting %d to SLL", i);
        insert_slist_tail(&head, i, 0);
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

static void
test_hash_map()
{
    int error = 0;
    hash_map_t *map = NULL;
    const int NUM_BUCKETS = 25;

    printf("\n\tTesting Hash Map...");

    error = create_dsa_hash_map(&map, NUM_BUCKETS);
    if (error || map == NULL) {
        printf("Failed to create hash map. Error: %d", error);
        goto done;
    }

    printf("\n\t\tInserting into hash map...");
    for (int i = 0, j = 200; i < NUM_BUCKETS; i++, j++) {
        printf("\n\t\tInserting key %d val %d", i, j);
        error = dsa_hash_map_insert(map, i, j);
        if (error != 0) {
            printf("\n\t\tHash Map Insert failed K:%d, V:%d Error:%d",
                    i, j, error);
        }
    }

    printf("\n\t\tInserting Duplicate Hash Map...");
    for (int i = 0, j = 300; i < NUM_BUCKETS; i++, j++) {
        printf("\n\t\tInserting Duplicate key %d val %d", i, j);
        error = dsa_hash_map_insert(map, i, j);
        if (error == EEXIST) {
            printf("\n\t\tDuplicate key %d rejected as expected.", i);
        } else {
            printf("\n\t\tDuplicate key %d accepted! Unexpected!.", i);
        }
    }

    printf("\n\t\tLooking up in hash map...");
    for (int i = 0, j = 200; i < NUM_BUCKETS; i++, j++) {
        uint64_t val = 0;
        printf("\n\t\tLooking up key %d", i);
        error = dsa_hash_map_lookup(map, i, &val);
        if (error != 0) {
            printf("\n\t\tLookup Failed. K:%d", i);
        } else {
            if (val == j) {
                printf("\n\t\tLookup Succeeded. K:%d, V:%llu", i, val);
            } else {
                printf("\n\t\tLookup Found incorrect value. K:%d, V:%llu Expected V:%d",
                        i, val, j);
            }
        }
    }

    printf("\n\t\tDeleting from hash map...");
    for (int i = 0 ; i < NUM_BUCKETS; i++) {
        printf("\n\t\tDeleting key %d", i);
        error = dsa_hash_map_delete(map, i);
        if (error != 0) {
            printf("\n\t\tDelete Failed. K:%d", i);
        }
    }


done:
    if (map != NULL) {
        destroy_dsa_hash_map(map);
    }
    printf("\n");
}

static void
print_graph_vertex(graph_vertex_t *v)
{
    if (v) {
        printf("%llu ", v->key);
    }
}


/*
 * Free 2D adjaceny matrix
 */
static void
free_adjm(int **adjm, int rows)
{
    if (adjm != NULL) {
        for (int i = 0; i < rows; i++) {
            if (adjm[i] != NULL) {
                free(adjm[i]);
            }
        }
        free(adjm);
    }
}

/*
 * Allocate a 2D adjacency matrix
 */
static int**
alloc_adjm(int rows, int cols)
{
    bool error = false;

    int **adjm = (int **)malloc(sizeof(int*) * rows);
    if (adjm == NULL) {
        printf("\n\tFailed to allocate ADJ Matrix");
        goto done;
    }

    for (int i = 0; i < rows; i++) {
        adjm[i] = (int *)malloc(sizeof(int) * cols);
        if (adjm[i] == NULL) {
            printf("\n\tFailed to allocate ADJ Matrix");
            error = true;
            goto done;
        }
    }

done:
    if (error) {
        free_adjm(adjm, rows);
    }
    return adjm;
}

/*
 * X |  0   1   2   3   4
 *------------------------
 * 0 |  0   0   1   0   0
 *
 * 1 |  0   0   0   1   1
 *
 * 2 |  1   0   0   1   0
 *
 * 3 |  0   1   1   0   1
 *
 * 4 |  0   1   0   1   0
 */
static void
test_graph_adjm_to_adjlist()
{
    graph_t *g = NULL;
    const int rows = 5;
    const int cols = 5;
    bool isdirected = false;
    int stackadjm[rows][cols] = {
                        {0, 0, 1, 0 ,0},
                        {0, 0, 0, 1, 1},
                        {1, 0, 0, 1, 0},
                        {0, 1, 1, 0, 1},
                        {0, 1, 0, 1, 0}
                     };

    printf("\n\tTesting ADJ Matrix to ADJ List for Graphs...");

    /*
     * Allocate a 2D array for adjm and populate using
     * stack 2D array.
     */
    int **adjm = alloc_adjm(rows, cols);
    if (adjm == NULL) {
        printf("\n\tFailed to allocate ADJ Matrix");
        goto done;
    }

    printf("\n\t\tAdjaceny Matrix -");
    for (int i = 0; i < rows; i++) {
        printf("\n\t\t\t");
        for (int j = 0; j < cols; j++) {
            adjm[i][j] = stackadjm[i][j];
            printf(" %d ", adjm[i][j]);
        }
    }


    g = graph_from_adjmatrix(adjm, 5, isdirected);
    if (g == NULL) {
        printf("\n\tFailed to create ADJ List from ADJ Matrix");
        goto done;
    }

    print_graph(g);
    printf("\n");

done:
    free_adjm(adjm, rows);
    if (g != NULL) {
        delete_graph(g);
    }
    printf("\n");
}


static void
test_graph_directed()
{
    int error = 0;
    graph_t *g = NULL;
    const uint64_t NUM_VERTICES = 10;
    bool directed = true;

    printf("\n\tTesting Directed Graphs...");

    printf("\n\t\tCreating Graph...");
    g = create_graph(NUM_VERTICES, directed);
    if (g == NULL) {
        printf("\n\t\tFailed to create graph!");
        goto done;
    }

    printf("\n\t\tAdding Vertices...");
    for (int i = 0; i < NUM_VERTICES; i++) {
        error = add_vertex(g, i);
        if (error) {
            printf("\n\t\t\tFailed to add vertex %d", i);
            goto done;
        }
        printf("\n\t\t\tAdded vertex %d", i);
    }

    printf("\n\t\tAdding Edges...");

    /*
     *
     *      Graph View Representation - Directed
     *      * mean down-ward arrow
     *
     *      8<------------- 5 -------------------> 6
     *      ^               ^                      ^
     *      |               |\                   / |
     *      |               |  \    /---------- /  |
     *      |          4<---0    \ *               |
     *      |          |    ^     1                |
     *      |          | ---|      \               |
     *      |          * |           *             |
     *      9 -------> 3 ----------> 2 ----------> 7
     */
    add_edge(g, 0, 5, 0);
    add_edge(g, 0, 4, 0);

    add_edge(g, 1, 5, 0);
    add_edge(g, 1, 2, 0);

    add_edge(g, 2, 7, 0);

    add_edge(g, 3, 0, 0);
    add_edge(g, 3, 2, 0);

    add_edge(g, 4, 3, 0);

    add_edge(g, 5, 6, 0);
    add_edge(g, 5, 8, 0);

    add_edge(g, 6, 1, 0);

    add_edge(g, 7, 6, 0);

    add_edge(g, 9, 3, 0);
    add_edge(g, 9, 8, 0);

    print_graph(g);
    printf("\n");

    printf("\n\t\tDepth First Traversal Start Vertex 0 - ");
    graph_dfs(g, 0, NULL, print_graph_vertex);
    printf("\n");

    printf("\n\t\tBreadth First Traversal Start Vertex 0 - ");
    graph_bfs(g, 0, print_graph_vertex);
    printf("\n");

    printf("\n\t\tDepth First Traversal Start Vertex 8 - ");
    graph_dfs(g, 8, NULL, print_graph_vertex);
    printf("\n");

    printf("\n\t\tBreadth First Traversal Start Vertex 8 - ");
    graph_bfs(g, 8, print_graph_vertex);
    printf("\n");

    printf("\n\t\tGraph Has Cycle - %s", has_cycle(g) ? "True" : "False");
    printf("\n");


done:
    if (g != NULL) {
        delete_graph(g);
    }
    printf("\n");

}

static void
test_graph_undirected()
{
    int error = 0;
    graph_t *g = NULL;
    const uint64_t NUM_VERTICES = 10;
    bool directed = false;

    printf("\n\tTesting Undirected Graphs...");

    printf("\n\t\tCreating Graph...");
    g = create_graph(NUM_VERTICES, directed);
    if (g == NULL) {
        printf("\n\t\tFailed to create graph!");
        goto done;
    }

    printf("\n\t\tAdding Vertices...");
    for (int i = 0; i < NUM_VERTICES; i++) {
        error = add_vertex(g, i);
        if (error) {
            printf("\n\t\t\tFailed to add vertex %d", i);
            goto done;
        }
        printf("\n\t\t\tAdded vertex %d", i);
    }

    printf("\n\t\tAdding Edges...");

    /*
     *
     *      Graph View Representation
     *
     *      8 ------------- 5 -------------------- 6
     *      |               |\                   / |
     *      |               |  \    /---------- /  |
     *      |          4----0    \ /               |
     *      |          |    |     1                |
     *      |          |----|      \               |
     *      |          |            \              |
     *      9 -------- 3 ----------- 2 ----------- 7
     */
    add_edge(g, 0, 5, 0);
    add_edge(g, 0, 4, 0);
    add_edge(g, 0, 3, 0);

    add_edge(g, 1, 5, 0);
    add_edge(g, 1, 6, 0);
    add_edge(g, 1, 2, 0);

    add_edge(g, 2, 7, 0);
    add_edge(g, 2, 3, 0);

    add_edge(g, 3, 4, 0);
    add_edge(g, 3, 9, 0);

    add_edge(g, 5, 6, 0);
    add_edge(g, 5, 8, 0);

    add_edge(g, 6, 7, 0);

    add_edge(g, 8, 9, 0);

    print_graph(g);
    printf("\n");

    printf("\n\t\tDepth First Traversal Start Vertex 0 - ");
    graph_dfs(g, 0, NULL, print_graph_vertex);
    printf("\n");

    printf("\n\t\tBreadth First Traversal Start Vertex 0 - ");
    graph_bfs(g, 0, print_graph_vertex);
    printf("\n");

    printf("\n\t\tDepth First Traversal Start Vertex 8 - ");
    graph_dfs(g, 8, NULL, print_graph_vertex);
    printf("\n");

    printf("\n\t\tBreadth First Traversal Start Vertex 8 - ");
    graph_bfs(g, 8, print_graph_vertex);
    printf("\n");

    printf("\n\t\tGraph Has Cycle - %s", has_cycle(g) ? "True" : "False");
    printf("\n");

    shortest_path_undirected(g, 9, 6);
    printf("\n");

    shortest_path_undirected(g, 5, 0);
    printf("\n");

    shortest_path_undirected(g, 0, 7);
    printf("\n");

    shortest_path_undirected(g, 1, 4);
    printf("\n");

done:
    if (g != NULL) {
        delete_graph(g);
    }
    printf("\n");
}

static void
test_graph_cycle_undirected_no()
{
    graph_t *g = NULL;
    const int rows = 5;
    const int cols = 5;
    bool cycle = false;
    bool isdirected = false;
    int stackadjm[rows][cols] = {
                        {0, 0, 1, 0 ,0},
                        {0, 0, 0, 1, 1},
                        {1, 0, 0, 1, 0},
                        {0, 1, 1, 0, 0},
                        {0, 1, 0, 0, 0}
                     };

    int **adjm = alloc_adjm(rows, cols);
    if (adjm == NULL) {
        printf("\n\tFailed to allocate ADJ Matrix");
        goto done;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            adjm[i][j] = stackadjm[i][j];
        }
    }

    g = graph_from_adjmatrix(adjm, 5, isdirected);
    if (g == NULL) {
        printf("\n\tFailed to create ADJ List from ADJ Matrix");
        goto done;
    }

    print_graph(g);
    printf("\n");

    cycle = has_cycle(g);
    if (cycle) {
        printf("\n\t\tUndirected Graph does not have cycle. False Detection!");
    } else {
        printf("\n\t\tUndirected Graph does not have cycle. No cycle detected as expected.");
    }

done:
    free_adjm(adjm, rows);
    if (g != NULL) {
        delete_graph(g);
    }
    printf("\n");
}

static void
test_graph_cycle_undirected_yes()
{
    graph_t *g = NULL;
    const int rows = 5;
    const int cols = 5;
    bool cycle = false;
    bool isdirected = false;
    int stackadjm[rows][cols] = {
                        {0, 0, 1, 0 ,0},
                        {0, 0, 0, 1, 1},
                        {1, 0, 0, 1, 0},
                        {0, 1, 1, 0, 1},
                        {0, 1, 0, 1, 0}
                     };

    int **adjm = alloc_adjm(rows, cols);
    if (adjm == NULL) {
        printf("\n\tFailed to allocate ADJ Matrix");
        goto done;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            adjm[i][j] = stackadjm[i][j];
        }
    }


    g = graph_from_adjmatrix(adjm, 5, isdirected);
    if (g == NULL) {
        printf("\n\tFailed to create ADJ List from ADJ Matrix");
        goto done;
    }

    print_graph(g);
    printf("\n");

    cycle = has_cycle(g);
    if (cycle) {
        printf("\n\t\tUndirected Graph has cycle. Detected cycle as expected.");
    } else {
        printf("\n\t\tUndirected Graph has cycle. Missed detecting a cycle!");
    }

done:
    free_adjm(adjm, rows);
    if (g != NULL) {
        delete_graph(g);
    }
    printf("\n");
}

static void
test_graph_cycle_directed_no()
{
    graph_t *g = NULL;
    const int rows = 5;
    const int cols = 5;
    bool cycle = false;
    bool isdirected = true;
    int stackadjm[rows][cols] = {
                        {0, 0, 1, 0 ,0},
                        {0, 0, 0, 1, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 1, 0, 1},
                        {0, 0, 0, 0, 0}
                     };

    int **adjm = alloc_adjm(rows, cols);
    if (adjm == NULL) {
        printf("\n\tFailed to allocate ADJ Matrix");
        goto done;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            adjm[i][j] = stackadjm[i][j];
        }
    }

    g = graph_from_adjmatrix(adjm, 5, isdirected);
    if (g == NULL) {
        printf("\n\tFailed to create ADJ List from ADJ Matrix");
        goto done;
    }

    print_graph(g);
    printf("\n");

    cycle = has_cycle(g);
    if (cycle) {
        printf("\n\t\tDirected Graph does not have cycle. False Detection!");
    } else {
        printf("\n\t\tDirected Graph does not have cycle. No cycle detected as expected.");
    }

done:
    free_adjm(adjm, rows);
    if (g != NULL) {
        delete_graph(g);
    }
    printf("\n");
}

static void
test_graph_cycle_directed_yes()
{
    graph_t *g = NULL;
    const int rows = 5;
    const int cols = 5;
    bool cycle = false;
    bool isdirected = true;
    int stackadjm[rows][cols] = {
                        {0, 0, 1, 0 ,0},
                        {0, 0, 0, 1, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 1, 0, 1},
                        {0, 1, 0, 0, 0}
                     };

    int **adjm = alloc_adjm(rows, cols);
    if (adjm == NULL) {
        printf("\n\tFailed to allocate ADJ Matrix");
        goto done;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            adjm[i][j] = stackadjm[i][j];
        }
    }


    g = graph_from_adjmatrix(adjm, 5, isdirected);
    if (g == NULL) {
        printf("\n\tFailed to create ADJ List from ADJ Matrix");
        goto done;
    }

    print_graph(g);
    printf("\n");

    cycle = has_cycle(g);
    if (cycle) {
        printf("\n\t\tDirected Graph has cycle. Detected cycle as expected.");
    } else {
        printf("\n\t\tDirected Graph has cycle. Missed detecting a cycle!");
    }

done:
    free_adjm(adjm, rows);
    if (g != NULL) {
        delete_graph(g);
    }
    printf("\n");
}

static void
test_graph_cycle()
{
    printf("\n\tTesting Graph Cycles...");

    test_graph_cycle_undirected_yes();
    test_graph_cycle_undirected_no();

    test_graph_cycle_directed_yes();
    test_graph_cycle_directed_no();
}

static void
test_graph_shortest_path()
{
    int error = 0;
    graph_t *g = NULL;
    const uint64_t NUM_VERTICES = 9;
    bool directed = false;

    printf("\n\tTesting Graph Shortest Path...");

    printf("\n\t\tCreating Graph...");
    g = create_graph(NUM_VERTICES, directed);
    if (g == NULL) {
        printf("\n\t\tFailed to create graph!");
        goto done;
    }

    printf("\n\t\tAdding Vertices...");
    for (int i = 0; i < NUM_VERTICES; i++) {
        error = add_vertex(g, i);
        if (error) {
            printf("\n\t\t\tFailed to add vertex %d", i);
            goto done;
        }
        printf("\n\t\t\tAdded vertex %d", i);
    }

    printf("\n\t\tAdding Edges...");

    add_edge(g, 0, 1, 4);
    add_edge(g, 0, 7, 8);

    add_edge(g, 1, 2, 8);
    add_edge(g, 1, 7, 11);

    add_edge(g, 2, 3, 7);
    add_edge(g, 2, 8, 2);
    add_edge(g, 2, 5, 4);

    add_edge(g, 3, 5, 14);
    add_edge(g, 3, 4, 9);

    add_edge(g, 4, 5, 10);

    add_edge(g, 5, 6, 2);

    add_edge(g, 6, 8, 6);
    add_edge(g, 6, 7, 1);

    add_edge(g, 7, 8, 7);

    print_graph(g);
    printf("\n");

    shortest_path_dijkstra(g, 0, 4);
    printf("\n");

    shortest_path_dijkstra(g, 0, 2);
    printf("\n");

    shortest_path_dijkstra(g, 7, 3);
    printf("\n");

    shortest_path_dijkstra(g, 4, 1);
    printf("\n");

    shortest_path_dijkstra(g, 8, 0);
    printf("\n");

done:
    if (g != NULL) {
        delete_graph(g);
    }
    printf("\n");
}

void
test_graph()
{
    test_graph_undirected();
    test_graph_directed();
    test_graph_adjm_to_adjlist();
    test_graph_cycle();
    test_graph_shortest_path();
}

static void
print_usage()
{
    printf("\ndsa_driver -[LMQSBHG]");
    printf("\n\t\t L - Test Linked Lists");
    printf("\n\t\t M - Test Hash Map");
    printf("\n\t\t Q - Test Queue");
    printf("\n\t\t S - Test Stack");
    printf("\n\t\t B - Test Binary Trees and BST");
    printf("\n\t\t H - Test Heap");
    printf("\n\t\t G - Test Graphs");
    printf("\n");
}

int main(int argc, char *argv[])
{
    int opt = 0;

    bool test_ll_f = false;
    bool test_map_f = false;
    bool test_queue_f = false;
    bool test_stack_f = false;
    bool test_binary_trees_f = false;
    bool test_heap_f = false;
    bool test_graph_f = false;

    printf("Welcome to DSA Driver Program!");

    while ((opt = getopt(argc, argv, "hLMQSBHG")) != -1) {
        switch (opt) {
            case 'L':
                test_ll_f = true;
                break;
            case 'M':
                test_map_f = true;
                break;
            case 'Q':
                test_queue_f = true;
                break;
            case 'S':
                test_stack_f = true;
                break;
            case 'B':
                test_binary_trees_f = true;
                break;
            case 'H':
                test_heap_f = true;
                break;
            case 'G':
                test_graph_f = true;
                break;
            case 'h':
                print_usage();
                break;
            default:
                printf("\nIncorrect option.");
                print_usage();
                goto done;
        }
    }

    if (test_ll_f) {
        test_linked_list();
    }

    if (test_map_f) {
        test_hash_map();
    }

    if (test_queue_f) {
        test_simple_q();
    }

    if (test_stack_f) {
        test_stack();
    }

    if (test_binary_trees_f) {
        test_binary_tree_wrapper();
    }

    if (test_heap_f) {
        test_min_heap();
        test_max_heap();
    }

    if (test_graph_f) {
        test_graph();
    }

done:
    return 0;
}

