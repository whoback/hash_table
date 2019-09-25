#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

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