#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "free.h"


void free_edge_list(list_edge_t edge_list) {
    if(edge_list == NULL)
        return;

    while (edge_list != NULL) {
        list_edge_t temp = edge_list;
        edge_list = edge_list->next;
        free(temp);
    }
}


  void free_vertex(vertex_t* vertex) {
    if (vertex != NULL) {
        free_edge_list(vertex->edges); 
        vertex->edges = NULL; 
        free(vertex);
    }
  }

void free_graph(graph_t graph) {
    if (graph != NULL) {
        for (long int i = 0; i < graph->numOf_vertices; i++) {
            free_edge_list(graph->data[i].edges); // Libérer la mémoire des arêtes de chaque sommet
            graph->data[i].edges = NULL; //pour ne pas faire de double free
        }
        free(graph->data);
        graph->data = NULL; 
        free(graph); // Libérer la mémoire de la structure de graphe elle-même
        graph = NULL; 
    }
}