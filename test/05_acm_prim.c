#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/prim.h"
#include "tri_fusion.h"

void main() {
    graph_t graph0 = graph_read("../graphes/graphe0.txt");
    graph_t graph1 = graph_read("../graphes/graphe1.txt");
    graph_t graph2 = graph_read("../graphes/graphe2.txt");

    printf("==> Test ACM de l'algo Prim sur != graphes\n");
    
    list_edge_t sorted_edges = sorted_ascending_graph_merge(graph0);
    int starting_vertex = sorted_edges->val.id_departure;
    printf("le starting vertex est %d\n", starting_vertex);
    list_edge_t acm00 = acm_prim(starting_vertex, graph0);


    sorted_edges = sorted_ascending_graph_merge(graph1);
    starting_vertex = sorted_edges->val.id_departure;
    printf("le starting vertex est %d\n", starting_vertex);
    list_edge_t acm1A = acm_prim(starting_vertex, graph1);


    sorted_edges = sorted_ascending_graph_merge(graph2);
    starting_vertex = sorted_edges->val.id_departure;
    printf("le starting vertex est %d\n", starting_vertex);
    list_edge_t acm2S0 = acm_prim(starting_vertex, graph2);

    // print des arrêtes de l'ACM
    list_edge_print(acm1A);

    // calcul du coût des ACM
    int som00 = 0;
    int som1A = 0;
    int som2S0 = 0;
    
    for(int i = 0; i<list_edge_length(acm00); i++){
        som00+=acm00->val.cost;
        acm00=acm00->next;
    }

    for(int k = 0; k<list_edge_length(acm1A); k++){
        som1A+=acm1A->val.cost;
        acm1A=acm1A->next;
    } 

    for(int p = 0; p<list_edge_length(acm2S0); p++){
        som2S0+=acm2S0->val.cost;
        acm2S0=acm2S0->next;
    }

    printf("La somme des coûts de l'arc courant minimal 00 vaut %d\n",som00);

    printf("La somme des coûts de l'arc courant minimal 1A vaut %d\n",som1A);

    printf("La somme des coûts de l'arc courant minimal 2S0 vaut %d\n",som2S0);
}
