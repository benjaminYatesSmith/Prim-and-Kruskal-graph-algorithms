#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/graph.h"


void main() {
    graph_t graph=graph_new();
    graph = graph_read("../graphes/graphe0.txt");
    printf("==> test read random");
    assert (graph->data[0].edges->val.cost == 1);


}
