#include "bonus_functions.h"
#include "graph.h"
#include "path.h"
#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "i:o:dh"

int main(int argc, char **argv) {
    bool directed = false; // by default all graphs are undirected

    // is stdout a file you can open for writing?? Or do you just use printf()
    FILE *fi = fopen("stdin", "r");
    FILE *fo = fopen("stdout", "w");
    int opt;

    // ignore the red lines in this section, just a warning????
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': fi = fopen(optarg, "w"); break;
        case 'o': fo = fopen(optarg, "w"); break; //write to output file function??
        case 'd': directed = true; break;
        case 'h':
            printf("help me\n");
            return 0;
            // got rid of the default, dont need it?
        }
    }

    uint32_t num_vertices = 0;
    uint32_t num_edges = 0;

    /////////////////////////// read in / graph make ///////////////////////////////////////////

    // reading in number of edges
    if (fscanf(fi, "%u\n", &num_vertices) != 1) {
        fprintf(stderr, "tsp: error reading number of vertices\n");
        exit(1);
    }

    char *names_array[num_vertices];
    Graph *graph = graph_create(num_vertices, directed);

    // reading in vertice names
    for (uint32_t j = 0; j < num_vertices; j++) {
        if (fscanf(fi, "%s\n", names_array[j]) != 1) {
            fprintf(stderr, "tsp: error reading names\n");
            exit(1);
        }
        graph_add_vertex(graph, names_array[j], j);
    }

    // reading in number of edges
    if (fscanf(fi, "%u\n", &num_edges) != 1) {
        fprintf(stderr, "tsp: error reading number of edges\n");
        exit(1);
    }

    uint32_t start_end_weight[num_edges][3]; // I want to make an array of arrays

    // reading in edge weights
    int l = 0;
    for (uint32_t k = 0; k < num_edges; k++) {
        while (l < 3) {
            // perhaps just dumb it straight into graph instead of temperarily storing it
            if (fscanf(fi, "%u", &start_end_weight[k][l]) != 1) {
                fprintf(stderr, "tsp: error reading edges with start end weight\n");
                exit(1);
            }
            l++;
        }
        graph_add_edge(
            graph, start_end_weight[k][0], start_end_weight[k][1], start_end_weight[k][2]);
        l = 0;
    }
    ///////////////////////////////////// end of read in / graph make ///////////////////////////////////////////////////
    if (fi != stdin) {
        fclose(fi);
    }

    //////////////////////////////////// dfs ////////////////////////////////////////////////

    Path *temp = path_create(num_vertices + 1); // plus one vecause start is visited twice
    Path *winner = path_create(num_vertices + 1);
    dfs(0, graph, winner, temp);
    ///////////////////////////////// writing out ///////////////////////////////////////////////////////
    if (path_distance(winner) > 0) {
        // if a winning path was found
        Path *print_copy = path_create(num_vertices + 1);
        path_copy(print_copy,
            winner); // if winnner is correct and has the target as the 1st and last value
        // it will copy backwards for printing
        fprintf(fo, "Alissa starts at:\n");
        for (uint32_t g = 0; g < path_vertices(winner); g++) {
            fprintf(fo, "%s\n", names_array[path_remove(print_copy, graph)]);
        }
        fprintf(fo, "Total Distance: ");
        fprintf(fo, "%d\n", path_distance(winner));
        path_free(&print_copy);
    } else {
        // if no path was found
        fprintf(fo, "No path found! Alissa is lost!\n");
    }

    graph_free(&graph);
    path_free(&temp);
    path_free(&winner);
    fclose(fi);
    fclose(fo);
    return 0;
}
