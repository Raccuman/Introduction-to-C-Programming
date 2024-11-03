#include "graph.h"
#include "path.h"

#include <inttypes.h>
#include <stdbool.h>

void dfs(uint32_t target, Graph *g, Path *winner, Path *temp);

bool all_visited(Graph *g);
