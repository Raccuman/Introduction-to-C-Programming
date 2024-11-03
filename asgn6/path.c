#include "path.h"

//#include "graph.h"
//#include "stack.h"

#include <stdlib.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->vertices = stack_create(capacity);
    p->total_weight = 0;
    return p;
}

/////////////////////////////////// might have issues ///////////////////////////
void path_free(Path **pp) {
    stack_free(&((*pp)->vertices));
    free(*pp);
    *pp = NULL;
}
/////////////////////////////////////////////////////////////////////////////////

uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_distance(const Path *p) {
    return p->total_weight;
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    if (stack_size(p->vertices) == 0) {
        stack_push(p->vertices, val);
    } else {
        uint32_t intermediate;
        stack_peek(p->vertices, &intermediate);
        p->total_weight += graph_get_weight(g, intermediate, val);
        stack_push(p->vertices, val);
    }
}

void path_copy(Path *dst, const Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->total_weight = src->total_weight;
}

uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t ignorant_intermediate;
    if (stack_size(p->vertices) == 1) {
        stack_pop(p->vertices, &ignorant_intermediate);
        p->total_weight = 0;
    } else {
        uint32_t intermediate;
        stack_pop(p->vertices, &ignorant_intermediate);
        if (stack_size(p->vertices) > 0) {
            stack_peek(p->vertices, &intermediate);
            p->total_weight -= graph_get_weight(g, intermediate, ignorant_intermediate);
        }
    }
    return ignorant_intermediate;
}

/////////////////////////// there is one more function left to make, dont forget it!! //////////////
