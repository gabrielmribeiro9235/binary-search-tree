#include<stdio.h>
#include<stdlib.h>
#include"binary_search_tree.h"

t_tree* create_tree() {
    t_tree *tree = malloc(sizeof(t_tree));

    if (tree == NULL) {
        return NULL;
    }

    tree->root = NULL;

    return tree;
}

t_node* create_node(int item) {
    t_node *node = malloc(sizeof(t_node));

    if (node == NULL) {
        return NULL;
    }

    node->item = item;
    node->left = NULL;
    node->right = NULL;

    return node;
}

static void destroy_branch(t_node *root) {
    if (root == NULL) {
        return;
    }

    destroy_branch(root->left);
    destroy_branch(root->right);
    free(root);
}

void destroy_tree(t_tree *tree) {
    if (tree == NULL) {
        return;
    }

    destroy_branch(tree->root);
    free(tree);
}
