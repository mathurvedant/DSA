/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * DSA driver program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <binary_tree.h>
#include <getopt.h>

static void
print_BT_node(BTNode *node)
{
    if (node) {
        printf("%llu ", node->key);
    }
}

static void
test_binary_tree(void)
{
    printf("\n\tTesting Binary Tree...");
    BTNode *root = alloc_BT_node(50);
    BTNode *left = alloc_BT_node(30);
    BTNode *right = alloc_BT_node(20);

    root->left = left;
    root->right = right;

    printf("\n\t\tIn Order BT Traversal: ");
    in_order_traversal(root, print_BT_node);

    printf("\n\t\tPre Order BT Traversal: ");
    pre_order_traversal(root, print_BT_node);

    printf("\n\t\tPost Order BT Traversal: ");
    post_order_traversal(root, print_BT_node);

    printf("\n\t\tLevel Order BT Traversal: ");
    level_order_traversal(root, print_BT_node);

    printf("\n");
}

int main(void)
{
    printf("Welcome to DSA Driver Program!");

    test_binary_tree();

    return 0;
}

