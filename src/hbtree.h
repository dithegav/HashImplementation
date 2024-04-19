#ifndef HBTREE_H
#define HBTREE_T

typedef struct tree_node {
    struct tree_node *parent;
    struct tree_node *left;
    struct tree_node *right;
    int value;
    int height;
    int weight;
}node_t;

typedef struct tree {
    node_t *root;
    int nodes;
    int max_height;
}tree_t;

tree_t *create_tree();

int min_height (node_t *current);

void find_value (node_t *curr, int value, node_t **found_it);

node_t *findP_insert (tree_t *tree, int number);

int height (node_t *node);

int max1 (int num1, int num2);

void find_weight (node_t *node);

node_t *left_rotation (tree_t *tree, node_t *head_node);

node_t *right_rotation (tree_t *tree, node_t *head_node);

int find_balance (node_t *node);

int find_rotation (tree_t *tree, node_t *node);

void balance_changes (tree_t *tree, node_t *current, int diff_balance);

void fix_tree (tree_t *tree, node_t *node);

int btree_insert (tree_t *tree, int number);

int delete_value (tree_t *tree, int value);

void free_tree (node_t *node);

void pre_order (node_t *curr);

#endif