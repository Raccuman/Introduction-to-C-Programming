#include "ll.h"

#include <ctype.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

LL *list_create() {
    LL *l = (LL *) malloc(sizeof(LL));
    if (l == NULL) {
        return NULL;
    }
    l->head = NULL;
    return l;
}

// does it always add the new word to the end of the linked list?? Cant we just add it in
// withought having to put it at the end??

bool list_add(LL *l, item *i) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n == NULL) {
        return false;
    }
    n->data = *i;
    n->next = NULL;
    // if there are no nodes in the list
    if (l->head == NULL) {
        l->head = n;
        return true;
        // if there are nodes //
    } else {
        Node *tail = l->head;
        ///////
        n->next = tail;
        l->head = n;
        //////
        return true;
    }
}

item *list_find(LL *l, bool (*cmp)(item *, item *), item *i) {
    // returns a pointer to the item in the list
    Node *n = l->head;
    while (n != NULL) {
        if (cmp(&n->data, i)) {
            return &n->data;
        }
        n = n->next;
    }
    return NULL;
}

////////////////////////////////////// my stuff ////////////////////////////////////////

void list_remove(LL *l, bool (*cmp)(item *, item *), item *i) {
    Node *n = l->head;
    Node *previous_location = NULL;

    while (n != NULL) {
        if (cmp(&n->data, i)) {
            if (n == l->head) {
                l->head = n->next;
            } else {
                previous_location->next = n->next;
            }
            free(n);
            break;
        }
        previous_location = n; // does not work if you are trying to remove the 1st node
        n = n->next;
    }
}

void list_destroy(LL **l) {
    Node *n = (*l)->head;
    Node *temp;

    while (n != NULL) {
        temp = n->next;
        free(n);
        n = temp;
    }
    free(*l);
    *l = NULL;
}

/// ////////////////////////////taken from https://stackoverflow.com/questions/19891962/c-how-to-append-a-char-to-char
int append(char *s, size_t size, char c) {
    if (strlen(s) + 1 >= size) {
        return 1;
    }
    unsigned long len = strlen(s);
    s[len] = c;
    s[len + 1] = '\0';
    return 0;
}
/////////////////////////////////////////////////////////////////////////
