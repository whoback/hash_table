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

//functions for actual hashing
int hash(const char *str, int prime, int num_buckets);
int char_code(char c);
static int ht_get_hash(const char *str, const int num_buckets, const int attempt);

//API
void ht_insert(ht_hash_table *ht, const char *key, const char *value);
void ht_delete(ht_hash_table *ht, const char *key);
char *ht_search(ht_hash_table *ht, const char *key);