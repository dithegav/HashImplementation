#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rbtree.h"

tree_t* create_tree (){
    tree_t *tree ;

    tree = (tree_t *)malloc (sizeof(tree_t));
    if (tree == NULL){
        perror("ERROR");
        exit(-42);
    }

    tree->root = NULL;
    tree->nodes = 0;
    tree->min_height = 0;
    tree->max_height = 0;
    tree->mult_height = pow (2, tree->max_height);
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

void max_height (node_t *current, int *maxheight, int *tmp_height){

    if (current == NULL){
        return ;
    }

    if (current->left != NULL){
        *tmp_height+= 1;
        max_height (current->left, maxheight, tmp_height);
    }

    if (current->right != NULL){
        *tmp_height+= 1;
        max_height (current->right, maxheight, tmp_height);
    }

    if (*tmp_height > *maxheight){
        *maxheight = *tmp_height;
    }
    *tmp_height -= 1;
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

int btree_insert (tree_t *tree, int number){
    node_t *new_node, *tmp, *child, *curr, *curr1;
    node_t *Rfind, *found_it = NULL;
    int i = 0;

    find_value (tree->root, number, &found_it);
    
    if (found_it && found_it->value == number){
        //already exists
        return 0;
    }

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

    if (Rfind != NULL){
        if (number > Rfind->value){
            Rfind->right = new_node;
            child = Rfind->right;
        }
        else {
            //number < Rfind->left
            Rfind->left = new_node;
            child = Rfind->left;
        }

        //if new node is not the root
        //then do adjustments depending on the number that srand gave
        for (i=0; child->value != tree->root->value;){
            if ((rand() % 2) == 1){
                i++;
                tmp = child->parent;
                if ((tmp->right != NULL ) && (tmp->right->value == child->value)){
                    //left rotation
                    curr = child->left;
                    curr1 = tmp->parent;
                    child->left = tmp;
                    child->parent = tmp->parent;
                    tmp->parent = child;
                    tmp->right = curr;
                    if (curr != NULL){
                        curr->parent = tmp;
                    }
                }
                else {
                    //right rotation
                    curr = child->right;
                    curr1 = tmp->parent;
                    child->right = tmp;
                    child->parent = tmp->parent;
                    tmp->parent = child;
                    tmp->left = curr;
                    if (curr != NULL){
                        curr->parent = tmp;
                    }
                }

                if (curr1 != NULL && (curr1->right != NULL) && (curr1->right->value == tmp->value)){
                    child->parent->right = child;
                }
                else if (curr1 != NULL && (curr1->left != NULL) && (curr1->left->value == tmp->value)){
                    child->parent->left = child;
                }
                
                if (tree->root == tmp){     
                    tree->root = child;
                }
            }
            else{
                i++;
                break;
            }
        }
       
    }
    else {
        /*put in root cause tree is empty*/
        tree->root = new_node;
    }
    tree->nodes++;
    if (tree->nodes > tree->mult_height){
        tree->max_height++;
        tree->mult_height += pow (2, tree->max_height);
    }

    return 1;
}

int delete_value (tree_t *tree, int value){
    node_t *found_it = NULL, *tmp = NULL, *head_node=NULL, *mid_node, *curr, *curr1;
    int i=0;
    //den xreiazetai to number, xrhsimopoiw mono to etoimo value! na to allaksw

    find_value (tree->root, value, &found_it);

    if (found_it == NULL || found_it->value != value){
        //didnt find the value to delete
        return 0;
    }

    if (found_it->left != NULL && found_it->right != NULL){
        head_node = found_it;
        while (1){

            if ((rand() % 2) == 1){
                //rotation with right child
                mid_node = head_node->right;
                curr = mid_node->left;
                curr1 = head_node->parent;
                //tmp->right = child->left;
                mid_node->left = head_node;
                mid_node->parent = head_node->parent;
                head_node->parent = mid_node;
                head_node->right = curr;
                if (curr != NULL){
                    curr->parent = head_node;
                }
            }
            else {
                //rotation with left child
                mid_node = head_node->left;
                curr = mid_node->right;
                curr1 = head_node->parent;
                //tmp->left = child->right;
                mid_node->right = head_node;
                mid_node->parent = head_node->parent;
                head_node->parent = mid_node;
                head_node->left = curr;
                if (curr != NULL){
                    curr->parent = head_node;
                }            
            }

            if (curr1 != NULL && (curr1->right != NULL) && (curr1->right->value == head_node->value)){
                mid_node->parent->right = mid_node;
            }
            else if (curr1 != NULL && (curr1->left != NULL) && (curr1->left->value == head_node->value)){
                mid_node->parent->left = mid_node;
            }
            
            if (tree->root == head_node){     
                tree->root = mid_node;
            }            

            if (head_node->left == NULL || head_node->right == NULL){
                break;
            }
            i++;
        }
    }

    if (head_node != NULL){
        found_it = head_node;
    }

    tmp = found_it;
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
    }
    tmp = found_it;
    free(tmp);
    found_it = NULL;
        
    tree->nodes--;
    if (tree->nodes > 0 && tree->nodes < (tree->mult_height - pow (2, tree->max_height-1))){
        tree->mult_height -= pow (2, tree->max_height);
        tree->max_height--;
    }
    else if (tree->nodes == 0){
        tree->max_height = 0;
        tree->mult_height = pow (2, tree->max_height);
    }
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