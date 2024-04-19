#ifndef RBTREE_H
#define RBTREE_H

typedef struct tree_node {
    struct tree_node *parent;
    struct tree_node *left;
    struct tree_node *right;
    int value;
}node_t;

typedef struct tree {
    node_t *root;
    int nodes;
    int min_height;
    int max_height;
    int mult_height;
}tree_t;

tree_t* create_tree();

int min_height (node_t *current);

void max_height (node_t *current, int *maxheight, int *tmp_height);

node_t* findP_insert(tree_t *tree, int number);

void find_value (node_t *curr, int value, node_t **found_it);

int btree_insert (tree_t *tree, int number);

int delete_value (tree_t *tree, int value);

void free_tree (node_t *node);

void pre_order (node_t *curr);

#endif