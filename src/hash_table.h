// hash table structures

// each ht_item will store a key/value pair
typedef struct{
        char *key;
        char *value;
} ht_item;

//store an array of pointers to ht_items
//in addition to metadata about our hash table

typedef struct{
        int size;
        int count;
        ht_items **items;
} ht_hash_table;
