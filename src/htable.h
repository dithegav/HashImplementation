#ifndef HTABLE_H
#define HTABLE_H

typedef struct hash {
    int size;
    double load_factor;
    int elements;
    int **ht;
    int inserted;
    int deleted;
}hash_t;

void hash_init (hash_t *hash);

int find_key (hash_t *hash, int value);

int find_position (int size, int **help_ptr, int value);

void rehash (hash_t **hash, int operation);

int insert_number (hash_t *hash, int value, int act_rehash);

int delete_number (hash_t *hash, int value, int act_rehash);

void free_hash (hash_t *hash);

#endif