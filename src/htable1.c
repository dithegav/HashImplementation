#include <stdio.h>
#include <stdlib.h>
#include "htable.h"

void print_hash (hash_t hash){
    int i=0;

    printf("\nSIZE: %d, INSERTED: %d, DELETED: %d\n", hash.size, hash.inserted, hash.deleted);
    for (i=0; i < hash.size; i++){
        printf("%3d ", i);
    }
    printf("\n");

    for (i=0; i < hash.size; i++){
        if (hash.ht[i] == NULL){
            printf ("  * ");
        }
        else if (hash.ht[i] == (int*)0x1){
            printf ("  # ");
        }
        else {
            printf ("%3d ", *(hash.ht[i]));
        }
    }
    printf("\n");
}

int main (int argc, char *argv[]){
    hash_t hash;
    char letter;
    int funct_values = 0, value=0, activate_rehash=1;

    hash.size = 2;
    hash.elements = 0;
    hash.load_factor = 0;
    hash.inserted = 0;
    hash.deleted = 0;
    hash_init(&hash);

    do {
        scanf (" -%c", &letter);
        value = 0;
        switch (letter){

            case 'i' : {
                scanf (" %d", &value);
                funct_values = insert_number(&hash, value, activate_rehash);
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
                funct_values = find_key (&hash, value);
                if (funct_values == 1){
                    printf ("\n%d F\n", value);
                }
                else {
                    printf ("\n%d NF\n", value);
                }
                continue;
            }
            case 'd' : {
                scanf (" %d", &value);
                funct_values = delete_number(&hash, value, activate_rehash);
                if (funct_values == 1){
                    printf ("\n%d D\n", value);
                }
                else {
                    printf ("\n%d ND\n", value);
                }
                continue;
            }
            case 'p' : {
                print_hash (hash);
                continue;
            }
            case 'r' : {
                //active or not rehash
                if (activate_rehash == 0){
                    printf ("\nREHASH: ON\n");
                    activate_rehash = 1;
                }
                else {
                    activate_rehash = 0;
                    printf ("\nREHASH: OFF\n");
                }
                continue;
            }
            case 'q' : {
                free_hash(&hash);
                continue;
            }
            default : {

                continue;
            }
        }

    }while(letter != 'q');

    return 0;
}