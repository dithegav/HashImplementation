#include <stdio.h>
#include <stdlib.h>
#include "htable.h"

void hash_init (hash_t *hash){
    int **bucket;

    bucket = (int **) calloc(2, sizeof(int *));
    if (bucket == NULL){
        exit (42);
    }
    hash->ht = bucket;
}

int find_key (hash_t *hash, int value){
    int key=0, iterations=0, save_key=0;

    while(1){
        key = ((value+iterations) % hash->size);

        if (iterations > 0 && key == save_key){
            //not found
            return -1;
        }

        if (hash->ht[key] != NULL && hash->ht[key] != (int*)0x1 && *(hash->ht[key]) == value){
            //found value
            return key;
        }

        //if (hash->ht[key] == NULL || hash->ht[key] == (int*)0x1 || (*hash->ht[key]) != value){
        //add to iterations check for null places
        if (iterations == 0){
            save_key = key;
        }
        iterations++;
    }
}

int find_position (int size, int **help_ptr, int value){
    int key=0, iterations=0;

    while(1){
        key = ((value+iterations) % size);

        if (help_ptr[key] == NULL || help_ptr[key] == (int*)0x1){
            //found position
            break;
        }
        iterations++;
    }

    return key;
}

void rehash (hash_t **hash, int operation){
    int new_size=0, i=0, tmp=0, key=0, value=0;
    int **help_ptr, *free_bucket;

    if (operation == 1){
        new_size = 2 * (*hash)->size;
    }
    else {
        new_size = (*hash)->size / 2;
    }
    tmp = (*hash)->size;
    (*hash)->size = new_size;
    new_size = tmp;

    help_ptr = (int **) calloc ((*hash)->size, sizeof(int *));
    if (help_ptr == NULL){
        exit(42);
    }
    (*hash)->elements = 0;
    (*hash)->inserted = 0;
    (*hash)->deleted = 0;

    for (i=0; i < new_size; i++){
        if ((*hash)->ht[i] == NULL || (*hash)->ht[i] == (int*)0x1){
            continue;
        }

        value = *((*hash)->ht[i]);

        key = find_position((*hash)->size, help_ptr, value);

        help_ptr[key] = (int*) calloc (1, sizeof(int));
        *(help_ptr[key]) = value;
        (*hash)->inserted++;
        (*hash)->elements++;

        free_bucket = (*hash)->ht[i];
        free(free_bucket);
    }
    free((*hash)->ht);

    (*hash)->ht = help_ptr;
}

int insert_number (hash_t *hash, int value, int act_rehash){
    int funct_values=0, key=0;

    funct_values = find_key(hash, value);
    if (funct_values != -1){
        //already in hash
        return 0;
    }    
    
    if (act_rehash == 1){
        hash->load_factor = (double) hash->elements / hash->size;
        if (hash->load_factor >= 0.5){
            rehash (&hash, 1);
            //if we double the buckets its 1
        }
    }
    
    key = find_position(hash->size, hash->ht, value);
    
    hash->ht[key] = (int*)calloc(1, sizeof(int));
    *(hash->ht[key]) = value;
    hash->elements++;
    hash->inserted++;

    return 1;
}

int delete_number (hash_t *hash, int value, int act_rehash){
    int funct_values=0, key=0;

    funct_values = find_key(hash, value);
    if (funct_values == -1){
        //value does not exist
        return 0;
    }
    key = funct_values;
    
    free(hash->ht[key]);
    hash->ht[key] = (int*)0x1;
    hash->deleted++;
    hash->elements--;
    hash->inserted--;
    
    if (act_rehash == 1){
        hash->load_factor = (double) hash->elements/hash->size;
        if (hash->load_factor <= 0.125){
            rehash(&hash, 0);
            //make buckets half their size
        }
    }
    return 1;
    
}

void free_hash (hash_t *hash){
    int i=0;

    for (i=0 ; i < hash->size; i++){
        if (hash->ht[i] != NULL && hash->ht[i] != (int*)0x1){
            free(hash->ht[i]);
        }
    }
    free(hash->ht);

}