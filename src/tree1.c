#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hbtree.h"

int main (int argc, char *argv[]){
    tree_t *tree;
    node_t *found_it;
    char letter;
    int value=0, funct_values=0;

    tree = create_tree();    

    do {
        scanf (" -%c", &letter);
        value = 0;
        found_it = NULL;
        //printf ("\n");
        switch (letter){

            case 'i' : {
                scanf (" %d", &value);
                funct_values = btree_insert (tree, value);
                
                if (funct_values == 1){
                    printf ("\n%d I\n", value);
                }
                else if (funct_values == 0){
                    printf ("\n%d NI\n", value);
                }
                continue;
                
            }
            case 'f' : {
                scanf (" %d", &value);
                found_it = findP_insert (tree, value);

                if (found_it != NULL && found_it->value == value){
                    printf ("\n%d F\n", value);
                }
                else {
                    printf ("\n%d NF\n", value);
                }

                continue;
            }
            case 'd' : {
                scanf (" %d", &value);
                funct_values = delete_value (tree, value);

                if (funct_values == 1){
                    printf ("\n%d D\n", value);

                }
                else {
                    printf ("\n%d ND\n", value);
                }
                continue;
            }
            case 'p' : {
                int i=0, j=0;
                if (tree->root == NULL){
                    i=0;
                    j=0;
                }
                else {
                    j = min_height (tree->root);
                    i = tree->root->height;
                }
                printf ("\nsize: %d, max_height: %d, min_height: %d\n", tree->nodes, i, j);
                pre_order(tree->root);
                printf ("\n");
                continue;
            }
            case 'q' : {
                free_tree(tree->root);
                continue;
            }
            default : {

                continue;
            }
        }

    }while(letter != 'q');
    free(tree);
    return 0;
}   