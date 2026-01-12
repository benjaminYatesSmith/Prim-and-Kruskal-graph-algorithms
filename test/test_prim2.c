#include <stdio.h>
#include <stdlib.h>

#include "assert.h"
#include "tri_fusion.h"
#include "prim.h"
#include "graph.h"
#include "free.h"
#include "prim2.h"


int main() {
    char *fichier = "../graphes/graphe2.txt";
    graph_t graph = graph_read(fichier);

    if (test_prim2(graph)) {
        printf("\nTests du fichier test_prim.c passes avec succes\n");
    }
    list_edge_t sorted_edges = sorted_ascending_graph_merge(graph);
    int starting_vertex = sorted_edges->val.id_departure;
    list_edge_t acm=acm_prim2(starting_vertex, graph);

    printf("==> Test tout les sommets sont atteints\n");
    assert(test_prim2_each_vertex_reached(acm, graph));
    printf("<== Test passé avec succès\n");

    free_graph(graph);
    return 0;
}

int test_prim2(graph_t graph_toTest) {
    printf("\n\n Test de la fonction prim: \n");

    long int cout_totale = 0;
    //permet de commencer avec le sommet de départ de l'arête par lequel kruskal commencerait
    list_edge_t sorted_edges = sorted_ascending_graph_merge(graph_toTest);

    int starting_vertex = sorted_edges->val.id_departure;
    printf("\n\n l'ID de depart est %d\n", starting_vertex);

    list_edge_t acm = acm_prim2(starting_vertex, graph_toTest);

    printf("\n\nAretes de l'ACM:\n");
    list_edge_t current = acm;

    while (current != NULL) {
        printf("Edge de %ld a %ld avec cout %lf\n", current->val.id_departure, current->val.id_arrival, current->val.cost);
        cout_totale += current->val.cost;
        current = current->next;
    }

    printf("Le cout total de l'ACM = %ld\n", cout_totale);

    free_edge_list(acm);

    return 1;
}

int test_prim2_each_vertex_reached(list_edge_t ACM, graph_t graph_toTest){
    if(!list_edge_is_empty(ACM)){
        list_vertex_t sommet_reached = list_sommet_new(); 
        sommet_reached = list_sommet_add_first(sommet_reached, graph_toTest->data[ACM->val.id_departure]);
        sommet_reached = list_sommet_add_first(sommet_reached, graph_toTest->data[ACM->val.id_arrival]);
        int i = 2;
        while(!list_edge_is_empty(ACM)){
            if(!list_sommet_appartient(graph_toTest->data[ACM->val.id_arrival], sommet_reached)){
                sommet_reached = list_sommet_add_first(sommet_reached, graph_toTest->data[ACM->val.id_arrival]);
                i+=1;
            }
            if(!list_sommet_appartient(graph_toTest->data[ACM->val.id_departure], sommet_reached)){
                sommet_reached = list_sommet_add_first(sommet_reached, graph_toTest->data[ACM->val.id_departure]);
                i+=1;
            }
            ACM=ACM->next;
        }
        if(i!=graph_toTest->numOf_vertices-1){
            return 0;
        }
    }
    return 1;
}