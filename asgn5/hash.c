// time to make and figure out hash table stuff
#include "hash.h"

#include "badhash.h"
#include "item.h"
#include "ll.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// not quite sure about this one, might not work. tells us where we can find our 2 buckets
Hashtable *hash_create(void) {
    //allocates memory for, and initialises a hash table.
    Hashtable *t = (Hashtable *) malloc(sizeof(Hashtable));
    if (t == NULL) {
        return NULL;
    }
    // array, 10 items
    int j = 0;
    while (j < 10) {
        (*t).ll_array[j] = list_create();
        j += 1;
    }

    return t;
}

bool hash_put(Hashtable *t, char *key, int val) {
    // stores the key and the value in the propper bucket. if there is a pre-existing
    // value with that key, our new value overwrites the old one
    item newbie;
    strncpy(newbie.key, key, (size_t) 255);
    newbie.id = val;
    //
    int thing = (int) (*key);
    // atoi is not working because the key does not end with
    LL *bucket = t->ll_array[(thing) % 10];
    //
    list_remove(bucket, cmp, &newbie);
    return list_add(bucket, &newbie);
}

int *hash_get(Hashtable *t, char *key) {
    //  returns a pointer to the int that is the value for that key
    int *bad_return = 0;
    //
    int thing = (int) (*key);
    LL *bucket = t->ll_array[thing % 10];

    // you cant do *key because that only passes in the first letter, cause that is where the location is pointing to
    // figure out how to get the full char from the pointer
    ///////////////////////////////////////////////////////////////////////////////////

    item temp_item;
    strncpy(temp_item.key, key, (size_t) 255);
    ///////////////////////////////////////////////////////////////////////////////
    item *found_item = (list_find(bucket, cmp, &temp_item));
    if (found_item == NULL) {
        return bad_return;
    }
    // finding the right key, returning the wrong number
    return &(found_item->id);
}

void hash_destroy(Hashtable **t) {
    int k = 0;
    while (k < 10) {
        list_destroy(&((*t)->ll_array[k]));
        k += 1;
    }
    free(*t);
    *t = NULL;
}
