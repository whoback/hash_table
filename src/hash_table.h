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
        ht_item **items;
} ht_hash_table;
// declare our funcs
static ht_item *ht_new_item(const char *k, const char *v);
ht_hash_table *ht_new();
static void ht_del_item(ht_item *i);
void ht_del_hash_table(ht_hash_table *ht);