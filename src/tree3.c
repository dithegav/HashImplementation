#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

int main (int argc, char *argv []){
    tree_t *tree;
    node_t *found_it = NULL;
    char letter;
    int value = 0, funct_values=0, maxheight=0, tmp_height=0;


    srand(1638302658);
    
    tree = create_tree();

    do {
        maxheight = 0 ;
        tmp_height = 0;
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
                find_value (tree->root, value, &found_it);

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
                tree->min_height = min_height(tree->root);
                max_height (tree->root, &maxheight, &tmp_height);
                if (tree->root != NULL){
                    maxheight++;//for root
                }
                printf ("\nsize: %d, max_height: %d, min_height: %d\n", tree->nodes, maxheight, tree->min_height);
                pre_order(tree->root);
                printf ("\n\n");
                continue;
            }
            case 'q' : {
                free_tree (tree->root);
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