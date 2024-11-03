#include "pq.h"

#include "node.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListElement ListElement;

struct ListElement {
    Node *tree;
    ListElement *next;
};

struct PriorityQueue {
    ListElement *list;
};

PriorityQueue *pq_create(void) {
    PriorityQueue *my_queue = calloc(1, sizeof(PriorityQueue));
    if (my_queue == 0) {
        return NULL;
        // not quite sure what fopen() returns if it does not work but should not be any of those.
    }
    return my_queue;
}

void pq_free(PriorityQueue **q) {
    ListElement *previous_element = NULL;
    ListElement *current_element = (*q)->list; // this line error
    if (current_element != NULL) {
        while (current_element->next != NULL) {
            previous_element = current_element;
            free(previous_element);
            current_element = current_element->next;
        }
        free(current_element);
    }
    free(*q);
    *q = NULL;
}

bool pq_is_empty(PriorityQueue *q) {
    if (q->list == NULL) {
        return true;
    }
    return false;
}

bool pq_size_is_1(PriorityQueue *q) {
    if (pq_is_empty(q)) {
        return false;
    } else if ((q->list)->next == NULL) {
        return true;
    }
    return false;
}

bool pq_less_than(ListElement *e1, ListElement *e2) {
    if ((e1->tree)->weight < (e2->tree)->weight) {
        return true;
    } else if ((e1->tree)->weight == (e2->tree)->weight) {
        if ((e1->tree)->symbol == (e2->tree)->symbol) {
            return true;
        }
        return false;
    } else {
        return false;
    }
}

// probably does not work
void enqueue(PriorityQueue *q, Node *tree) {
    ListElement *new_element = calloc(1, sizeof(ListElement));
    new_element->tree = tree;
    new_element->next = NULL;
    if (pq_is_empty(q)) {
        (q->list) = new_element;
        // to put the tree in first place
    } else if (pq_less_than(new_element, q->list)) {
        new_element->next = q->list;
        q->list = new_element;
    } else {
        ListElement *prev_element = q->list;
        while (true) {
            if ((prev_element)->next == NULL) {
                prev_element->next = new_element;
                break;
                // if new element is smaller than the current element
            } else if (pq_less_than(new_element, prev_element->next)) {
                new_element->next = prev_element->next;
                prev_element->next = new_element;
                break;
            }
            prev_element = prev_element->next;
        }
    }
}

Node *dequeue(PriorityQueue *q) {
    Node *returner = q->list->tree;
    ListElement *temp = q->list;
    q->list = q->list->next;
    free(temp);
    temp = NULL;
    return returner;
}

void pq_print(PriorityQueue *q) {
    assert(q != NULL);
    ListElement *e = q->list;
    int position = 1;
    while (e != NULL) {
        if (position++ == 1) {
            printf("=============================================\n");
        } else {
            printf("---------------------------------------------\n");
        }
        node_print_tree(e->tree);
        e = e->next;
    }
    printf("=============================================\n");
}

Node *for_left(PriorityQueue *cat) {
    return cat->list->tree->left;
}

uint32_t for_left_weight(PriorityQueue *cat) {
    return cat->list->tree->left->weight;
}

Node *for_right(PriorityQueue *cat) {
    return cat->list->tree->right;
}

uint32_t for_right_weight(PriorityQueue *cat) {
    return cat->list->tree->right->weight;
}
