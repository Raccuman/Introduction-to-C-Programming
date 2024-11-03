#ifndef _HASH

#define _HASH

#include "item.h"
#include "ll.h"

typedef struct Hashtable Hashtable;

// a hashtable is basically a dictionary. this is where you make buckets??
struct Hashtable {
    // your datastructure here; this is just a placeholder
    LL *ll_array[10];

    // array of 10 linked lists
};

Hashtable *hash_create(void);

bool hash_put(Hashtable *, char *key, int val);

int *hash_get(Hashtable *, char *key);

void hash_destroy(Hashtable **);

#endif
