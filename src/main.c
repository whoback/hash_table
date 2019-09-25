#include <stdio.h>

#include "hash_table.h"
#include <assert.h>

int main()
{
    ht_hash_table *ht;
    ht = ht_new();
    assert(ht->size == 53);
    ht_del_hash_table(ht);
    printf("success ht created and destroyed\n");
    return 0;
}