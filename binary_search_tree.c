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

int is_empty(t_tree *tree) {
    return tree == NULL || tree->root == NULL;
}

int insert(t_tree *tree, int item) {
    if (tree == NULL) {
        return -1;
    }

    t_node *new_node = create_node(item);

    if (new_node == NULL) {
        return -1;
    }

    t_node **aux = &(tree->root);

    while (*aux != NULL) {
        if ((*aux)->item == item) {
            free(new_node);
            return 0;
        }

        aux = item > (*aux)->item ? &((*aux)->right) : &((*aux)->left);
    }

    *aux = new_node;

    return 1;
}

int remove_node(t_tree *tree, int item) {
    if (tree == NULL) {
        return 0;
    }

    t_node **aux = &(tree->root);

    while (*aux != NULL && (*aux)->item != item) {
        aux = item > (*aux)->item ? &((*aux)->right) : &((*aux)->left);
    }

    if (*aux == NULL) {
        return 0;
    }

    if ((*aux)->left == NULL || (*aux)->right == NULL) {
        t_node *temp = (*aux)->right == NULL ? (*aux)->left : (*aux)->right;

        free(*aux);
        *aux = temp;

        return 1;
    }

    t_node **predecessor = &((*aux)->left);

    while ((*predecessor)->right != NULL) {
        predecessor = &((*predecessor)->right);
    }

    (*aux)->item = (*predecessor)->item;

    t_node *temp = (*predecessor)->left;

    free(*predecessor);
    *predecessor = temp;

    return 1;
}

static int height_recursive(t_node *root) {
    if (root == NULL) {
        return 0;
    }

    int left_height = 1 + height_recursive(root->left);
    int right_height = 1 + height_recursive(root->right);

    return left_height > right_height ? left_height : right_height;
}

int height(t_tree *tree) {
    return tree == NULL ? 0 : height_recursive(tree->root);
}

static int total_nodes_recursive(t_node *root) {
    if (root == NULL) {
        return 0;
    }

    return 1 + total_nodes_recursive(root->left) + total_nodes_recursive(root->right);
}

int total_nodes(t_tree *tree) {
    return tree == NULL ? 0 : total_nodes_recursive(tree->root);
}

t_node* search(t_tree *tree, int item) {
    if (tree == NULL) {
        return NULL;
    }

    t_node *current = tree->root;

    while (current != NULL && current->item != item) {
        current = item > current->item ? current->right : current->left;
    }

    return current;
}

void pre_order(t_node *root) {
    if (root == NULL) {
        return;
    }

    printf("%d\t", root->item);
    pre_order(root->left);
    pre_order(root->right);
}

void in_order(t_node *root) {
    if (root == NULL) {
        return;
    }

    in_order(root->left);
    printf("%d\t", root->item);
    in_order(root->right);
}

void post_order(t_node *root) {
    if (root == NULL) {
        return;
    }

    post_order(root->left);
    post_order(root->right);
    printf("%d\t", root->item);
}

void width_traversal(t_tree *tree) {
    if (is_empty(tree)) {
        return;
    }

    int tree_size = total_nodes(tree);

    int queue_size = (tree_size + 1) / 2;
    t_node **queue = malloc(sizeof(t_node*) * queue_size);

    if (queue == NULL) {
        return;
    }

    int start = 0;
    int end = 0;

    queue[end++] = tree->root;

    for(int i = 0; i < tree_size; i++) {
        t_node *current = queue[start];
        start = (start + 1) % queue_size;

        printf("%d\t", current->item);

        if (current->left != NULL) {
            queue[end] = current->left;
            end = (end + 1) % queue_size;
        }

        if (current->right != NULL) {
            queue[end] = current->right;
            end = (end + 1) % queue_size;
        }
    }

    printf("\n");

    free(queue);
}
