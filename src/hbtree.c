#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hbtree.h"

tree_t* create_tree (){
    tree_t *tree ;

    tree = (tree_t *)malloc (sizeof(tree_t));
    if (tree == NULL){
        perror("ERROR");
        exit(-42);
    }

    tree->root = NULL;
    tree->nodes = 0;
    return tree;

}

int min_height (node_t *current) {
	int lheight, rheight;
	
	if (current == NULL) {
		return 0;
	}

	rheight = min_height(current->right);
	lheight = min_height(current->left);

    return ((rheight < lheight)? rheight+1 : lheight+1);
}

void find_value (node_t *curr, int value, node_t **found_it){
    if (curr == NULL){
        return;
    }
    
    if (curr->left != NULL){
        find_value (curr->left, value, found_it);
    }
    
    if (curr->right != NULL){
        find_value (curr->right, value, found_it);
    }

    if (curr->value == value){
        *found_it = curr;
    }

}

node_t* findP_insert (tree_t *tree, int number){
    node_t *curr;

    curr = tree->root;
    node_t *parent = curr;
    while (1){

        if (curr == NULL){
            break;
        }
        parent = curr;
        if (number < curr->value){
            curr = curr->left;
        }
        else if (number > curr->value){
            curr = curr->right;
        }
        else {
            return curr;
        }
    }

    if (curr == NULL){
        return parent;
    }
    return curr;

}

int height (node_t *node){

    if (node == NULL){
        return 0;
    }
    return node->height;
}

int max1 (int num1, int num2){

    return ((num1 > num2)? num1 : num2);
}

void find_weight (node_t *node){
//find the weight by calclating all the subtree's nodes
    int weight=0;

    if (node == NULL){
        return;
    }

    if (node->left != NULL){
        weight += node->left->weight;
    }

    if (node->right != NULL){
        weight += node->right->weight;
    }

    node->weight = weight + 1;
}

node_t  *left_rotation (tree_t *tree, node_t *head_node){
    node_t *mid_node, *curr, *curr1;

    mid_node = head_node->right;

    //move nodes
    curr = mid_node->left;
    curr1 = head_node->parent;
    mid_node->left = head_node;
    mid_node->parent = head_node->parent;
    head_node->parent = mid_node;
    head_node->right = curr;

    if (curr != NULL){
        curr->parent = head_node;
    }

    if (curr1 != NULL && (curr1->left != NULL) && (curr1->left->value == head_node->value)){
        mid_node->parent->left = mid_node;
    }
    else if (curr1 != NULL && (curr1->right != NULL) && (curr1->right->value == head_node->value)){
        mid_node->parent->right = mid_node;
    } 

    if (tree->root == head_node){
        tree->root = mid_node;
    }

    head_node->height = max1(height(head_node->left), height(head_node->right)) + 1;
    mid_node->height = max1(height(mid_node->left), height(mid_node->right)) + 1;

    find_weight(head_node);
    find_weight(mid_node);

    return mid_node;
}

node_t *right_rotation (tree_t *tree, node_t *head_node){
    node_t *mid_node, *curr, *curr1;

    mid_node = head_node->left;

    //move nodes
    curr = mid_node->right;
    curr1 = head_node->parent;
    mid_node->right = head_node;
    mid_node->parent = head_node->parent;
    head_node->parent = mid_node;
    head_node->left = curr;

    if (curr != NULL){
        curr->parent = head_node;
    }

    if (curr1 != NULL && (curr1->left != NULL) && (curr1->left->value == head_node->value)){
        mid_node->parent->left = mid_node;
    }
    else if (curr1 != NULL && (curr1->right != NULL) && (curr1->right->value == head_node->value)){
        mid_node->parent->right = mid_node;
    }  

    if (tree->root == head_node){
        tree->root = mid_node;
    }

    head_node->height = max1(height(head_node->left), height(head_node->right)) + 1;
    mid_node->height = max1(height(mid_node->left), height(mid_node->right)) + 1;

    find_weight(head_node);
    find_weight(mid_node);

    return mid_node;
}



int find_balance (node_t *node){
// give the diff of the childs from the node

    if (node == NULL){
        return 0;
    }

    return (height(node->left) > height(node->right)? (height(node->left) - height(node->right)) : (height(node->right) - height(node->left)));
}

int find_rotation (tree_t *tree, node_t *node){

    if (node != NULL){
        if (height(node->left) > height(node->right)){
            //right rotation
            return 1;
        }
        else if (height(node->left) < height(node->right)){
            //left rotation
            return 0;
        }
        else if (height(node->left) == height(node->right)){
            if (node->parent != NULL && node->parent->left != NULL && node->value == node->parent->left->value){
                //right rotation
                return 1;
            }
            else if(node->parent != NULL && node->parent->right != NULL && node->value == node->parent->right->value){
                //left rotation
                return 0;
            }
        }
    }

    if (node == tree->root){
        if (height(node->left) >= height(node->right)){
            //right rotation
            return 1;
        }
        else{
            //left rotation
            return 0;
        }
    }
    
    //fail
    return -1;
}

void balance_changes (tree_t *tree, node_t *current, int diff_balance){
    node_t *child;
    int double_rotate=0, rotate = 0;
    
    //unbalanced
    if (diff_balance > max1(1, floor(log2(current->weight)))){
        rotate = find_rotation (tree, current);
        if (rotate == 1){
            //left child
            double_rotate = find_rotation (tree, current->left);
            if (double_rotate == 1){
                //right rotation
                current = right_rotation(tree, current);

                diff_balance = find_balance(current->right);
                balance_changes (tree, current->right, diff_balance);

                diff_balance = find_balance(current);
                balance_changes(tree, current, diff_balance);
            }
            else if(double_rotate == 0){
                //double rotation
                //first leftrotation then rightrotation
                child = current->left;
                child = left_rotation(tree, child);
                
                diff_balance = find_balance(child->left);
                balance_changes (tree, child->left, diff_balance);

                diff_balance = find_balance(child);
                balance_changes (tree, child, diff_balance);

                current = right_rotation(tree, current);

                diff_balance = find_balance(current->right);
                balance_changes (tree, current->right, diff_balance);

                diff_balance = find_balance(current);
                balance_changes (tree, current, diff_balance);
            }
        }
        else if (rotate == 0){
            //right child
            double_rotate = find_rotation (tree, current->right);
            if (double_rotate == 0){
                //left rotation
                current = left_rotation(tree, current);

                diff_balance = find_balance(current->left);
                balance_changes (tree, current->left, diff_balance);

                diff_balance = find_balance(current);
                balance_changes (tree, current, diff_balance);
            }
            else if (double_rotate == 1){
                //doubke rotation
                //first right then left
                child = current->right;
                child = right_rotation(tree, child);

                diff_balance = find_balance(child->right);
                balance_changes (tree, child->right, diff_balance);

                diff_balance = find_balance(child);
                balance_changes (tree, child, diff_balance);

                current = left_rotation(tree, current);

                diff_balance = find_balance(current->left);
                balance_changes (tree, current->left, diff_balance);

                diff_balance = find_balance(current);
                balance_changes (tree, current, diff_balance);

            }
        }
    }

}

void fix_tree (tree_t *tree, node_t *node){
    node_t *current = node;
    int diff_balance=0;

    if (node == NULL){
        current = tree->root;
    }

    while (1){
        find_weight (current);
        current->height = max1(height(current->left), height(current->right)) + 1;

        diff_balance = find_balance (current);

        balance_changes(tree, current, diff_balance);
        find_weight(current);
        current->height = max1(height(current->left), height(current->right)) + 1;
        
        current = current->parent;
        if (current == NULL){
            return;
        }
    }

}

int btree_insert (tree_t *tree, int number){
    node_t *new_node;
    node_t *Rfind;

    Rfind = findP_insert(tree, number);
    if ((Rfind != NULL) && (Rfind->value == number)){
        return 0;
        /*key already exists*/
    }

    /*create the node for the tree*/
    new_node = (node_t *)malloc (sizeof(node_t));
    if (new_node == NULL){
        perror("ERROR");
        exit(-42);
    }
    new_node->parent = Rfind;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->value = number;
    new_node->height = 1;
    new_node->weight = 1;

    if (Rfind != NULL){
        if (number > Rfind->value){
            Rfind->right = new_node;
        }
        else {
            //number < Rfind->left
            Rfind->left = new_node;
        }

    }
    else {
        /*put in root cause tree is empty*/
        tree->root = new_node;
    }

    //fix tree after return
    fix_tree (tree, Rfind);

    tree->nodes++;
    return 1;
}

int delete_value (tree_t *tree, int value){
    node_t *current, *found_it, *tmp, *free_node;

    find_value(tree->root, value, &found_it);
    if (found_it == NULL || found_it->value != value){
        return 0;
    }

    if (found_it->left != NULL && found_it->right != NULL){
        for (current = found_it->right; current->left != NULL; current = current->left);
        found_it->value = current->value;
        current->value = value;
        tmp = found_it;
        found_it = current;
        current = tmp;
    }

    if (found_it->left != NULL){
        if (found_it->parent != NULL){
            if (found_it->parent->left != NULL && found_it->parent->left->value == value){
                found_it->parent->left = found_it->left;
                found_it->left->parent = found_it->parent;
            }
            else {
                found_it->parent->right = found_it->left;
                found_it->left->parent = found_it->parent;
            }
        }
        else {
            tree->root = found_it->left;
            tree->root->parent = NULL;
        }
        tmp = found_it->left;
    }
    else if (found_it->right != NULL){
        if (found_it->parent != NULL){
            if (found_it->parent->left != NULL && found_it->parent->left->value == value){
                found_it->parent->left = found_it->right;
                found_it->right->parent = found_it->parent;
            }
            else {
                found_it->parent->right = found_it->right;
                found_it->right->parent = found_it->parent;
            }
        }
        else {
            tree->root = found_it->right;
            tree->root->parent = NULL;            
        }
        tmp = found_it->right;
    }
    else {
        if (found_it->parent != NULL){
            if (found_it->parent->right != NULL && (found_it->parent->right->value == value)){
                found_it->parent->right = NULL;
            }
            else if (found_it->parent->left != NULL){
                found_it->parent->left = NULL;
            }
        }
        else {
            tree->root = NULL;
        }
        tmp = found_it->parent;
    }
    free_node = found_it;
    free(free_node);
    found_it = NULL;
    
    if (tree->root != NULL){
        fix_tree (tree, tmp);
    }

    tree->nodes--;
    return 1;
}

void free_tree (node_t *node){

    if (node == NULL){
        return ;
    }

    free_tree (node->left);

    free_tree (node->right);

    free (node);
}

void pre_order (node_t *curr) {
    if (curr == NULL) {
        return;
    }

    printf("%d ", curr->value);
    if (curr->left != NULL) {
        pre_order(curr->left);
    }
    if (curr->right != NULL) {
        pre_order(curr->right);
    }
}