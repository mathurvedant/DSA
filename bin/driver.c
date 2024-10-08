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
    BTNode *root = alloc_BT_node(50);
    BTNode *left = alloc_BT_node(30);
    BTNode *right = alloc_BT_node(20);

    root->left = left;
    root->right = right;

    printf("\nIn Order BT Traversal: \n");
    in_order_traversal(root, print_BT_node);

    printf("\nPre Order BT Traversal: \n");
    pre_order_traversal(root, print_BT_node);

    printf("\nPost Order BT Traversal: \n");
    post_order_traversal(root, print_BT_node);
}

int main(void)
{
    printf("\nWelcome to DSA Driver Program!\n");
    test_binary_tree();
}

