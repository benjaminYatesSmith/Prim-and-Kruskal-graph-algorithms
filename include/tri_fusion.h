#ifndef TRI_FUSION_H
#define TRI_FUSION_H

#include "graph.h"

void test_sorted_ascending_graph_fusion(graph_t graph_toTest);

list_edge_t creationOf_array_from_graph(graph_t graph);
void split_list_inHalf(list_edge_t root, list_edge_t* split_front, list_edge_t* split_back);
list_edge_t sorted_merge(list_edge_t list1, list_edge_t list2);
void merge_sort(list_edge_t* list_toSort);
list_edge_t sorted_ascending_graph_merge(graph_t graphTo_sort);

#endif
