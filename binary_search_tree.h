#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

typedef struct _node {
    int item;
    struct _node *left;
    struct _node *right;
} t_node;
typedef struct {
    t_node *root;
} t_tree;
t_tree* create_tree();
t_node* create_node(int);
void destroy_tree(t_tree*);
int is_empty(t_tree*);
int insert(t_tree*, int);
int remove_node(t_tree*, int);
int height(t_tree*);
int total_nodes(t_tree*);
t_node* search(t_tree*, int);
void pre_order(t_node*);
void in_order(t_node*);
void post_order(t_node*);
void width_traversal(t_tree*);

#endif