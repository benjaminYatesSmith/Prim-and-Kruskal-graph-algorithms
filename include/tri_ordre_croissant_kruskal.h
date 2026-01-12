#ifndef _TRI_ORDRE_CROISSANT_KRUSKAL_H
#define _TRI_ORDRE_CROISSANT_KRUSKAL_H

#include "graph.h"

void test_sorted_ascending_graph(graph_t graph_toTest);

void insert_sorted_edge(list_edge_t* list, list_edge_t new_node);
void parcours_list_pour_trie(list_edge_t list, list_edge_t* sorted_edge);
list_edge_t sorted_ascending_graph(graph_t graph_a_trier);



#endif