#ifndef _PRIM2_H
#define _PRIM2_H

#include "graph.h"
#include "list_sommet.h"
#include "heap.h"

#include <limits.h>

int test_prim2(graph_t graph_toTest);

list_edge_t acm_prim2(int depart, graph_t graph);
void add_reverse_edges(graph_t graph);


#endif