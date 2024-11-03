#include "item.h"

#include <stdio.h>
#include <string.h>

// implementation of the cmp() function on items, for when items are ints
//// new my addition, swapped for compairing ints to keys
bool cmp(item *i1, item *i2) {
    item temp_item;
    strncpy(temp_item.key, (i1)->key, (size_t) 255);
    if (0 == (strcmp(temp_item.key, (*i2).key))) {
        return true;
    }
    return false;
}
