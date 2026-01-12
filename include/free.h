#ifndef FREE_H
#define FREE_H

#include "union_find.h"

void free_edge_list(list_edge_t edge_list);
void free_vertex(vertex_t* vertex);
void free_graph(graph_t graph);


#endif
