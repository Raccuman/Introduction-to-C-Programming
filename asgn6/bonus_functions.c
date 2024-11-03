#include "graph.h"
#include "path.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool all_visited(Graph *g) {
    int flag = 0;
    for (uint32_t l = 0; l < graph_vertices(g); l++) {
        if (graph_visited(g, l) == false) {
            flag += 1;
        }
    }
    if (flag > 0) {
        return false;
    }
    return true;
}

void dfs(uint32_t target, Graph *g, Path *winner, Path *temp) {
    graph_visit_vertex(g, target);
    for (uint32_t i = 0; i < (graph_vertices(g)); i++) {
        if ((graph_get_weight(g, target, i) != 0) && graph_visited(g, i)) {
            path_add(temp, i, g);
            dfs(i, g, winner, temp);
        }
        if (i == 0
            && all_visited(
                g)) { // if you go back to target, and you have visited everywhere, you can go there
            path_add(temp, i, g); // adds the start to the end of the path
            if (path_distance(temp) < path_distance(winner)) {
                path_copy(winner, temp);
            }
            path_remove(temp, g);
        }
        path_remove(temp, g);
    }
}

///////////////////////////////above functions found in graph.c ////////////////////////////////////
