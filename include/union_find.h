#ifndef UNION_FIND_H
#define UNION_FIND_H

#include "tri_ordre_croissant_kruskal.h"
#include "tri_fusion.h"

void test_each_vertex_reached(list_edge_t acm, graph_t graph_toTest);
void test_fusion_deux_ensembles(graph_t graph_toTest, long int id_vertex1, long int id_vertex2);
int test_kruscal(graph_t graph_toTest);
//test_reproducibility_kruscal(graph_t graph);

vertex_t* find_parent(vertex_t* sommet);
long int fusion_deux_ensembles(vertex_t* root_depart, vertex_t* root_arrival);
list_edge_t union_find(graph_t graph, list_edge_t sorted_edges);
list_edge_t kruskal(graph_t graph);

#endif