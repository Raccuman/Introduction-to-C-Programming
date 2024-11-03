#ifndef _LL

#define _LL

#include "item.h"

#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct Node Node;

struct Node {
    item data;
    Node *next;
};

typedef struct LL LL;
struct LL {
    Node *head;
};

LL *list_create(void);
bool list_add(LL *, item *);
item *list_find(LL *, bool (*)(item *, item *), item *);

void list_destroy(LL **);
void list_remove(LL *, bool (*)(item *, item *), item *);
int append(char *s, size_t size, char c);

#endif
