#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash_table.h"
//have to be bigger than the alphabet
#define HT_PRIME_1 29
#define HT_PRIME_2 59

// init function for ht_item. allocates memory for key/value pair and stores
// it in the struct

static ht_item *ht_new_item(const char *k, const char *v)
{
    //get memory size of an ht_item
    ht_item *i = malloc(sizeof(ht_item));

    //take our k/v pair and copy them into our new ht_item
    i->key = strdup(k);
    i->value = strdup(v);

    return i;
}

// init our hash table
ht_hash_table *ht_new()
{
    ht_hash_table *ht = malloc(sizeof(ht_hash_table));

    ht->size = 53;
    ht->count = 0;
    //use calloc so it fills our new memory with 0'd bytes
    ht->items = calloc((size_t)ht->size, sizeof(ht_item *));

    return ht;
}

static void ht_del_item(ht_item* i)
{
    free(i->key);
    free(i->value);
    free(i);
}

void ht_del_hash_table(ht_hash_table *ht)
{
    for(int i = 0; i < ht->size; ++i)
    {
        ht_item *item = ht->items[i];
        if(item != NULL)
        {
            ht_del_item(item);

        }
    }
    free(ht->items);
    free(ht);
}

//hashing functions
int hash(const char *str, const int prime, const int num_buckets)
{
    long hash = 0;
    const int str_len = strnlen(str, sizeof(str));
    for(int i = 0; i < str_len; ++i)
    {
        hash += (long)pow(prime, str_len - (i + 1)) * str[i];
        hash = hash % num_buckets;
    }
    return (int)hash;
}
//taking a char and returning its ASCII representation
int char_code(char c)
{
    return (int)c;
}
//handle collisions using double hashing
static int ht_get_hash(const char *str, const int num_buckets, const int attempt)
{
    const int hash_a = hash(str, HT_PRIME_1, num_buckets);
    const int hash_b = hash(str, HT_PRIME_2, num_buckets);
    //add 1 to hash_b to make sure its not 0
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

void ht_insert(ht_hash_table *ht, const char *key, const char *value)
{
    ht_item *item = ht_new_item(key, value);
    int index = ht_get_hash(item->key, ht->size, 0);
    ht_item *cur_item = ht->items[index];
    int i = 1;
    //itr through until we find an empty bucket and insert
    while(cur_item != NULL)
    {
        index = ht_get_hash(item->key, ht->size, i);
        cur_item = ht->items[index];
        ++i;
    }
    //insert our new item
    ht->items[index] = item;
    ht->count++;
}