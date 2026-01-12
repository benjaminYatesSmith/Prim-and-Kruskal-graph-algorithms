#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "prim2.h"
#include "heap.h"

list_edge_t acm_prim2(int depart, graph_t graph)
{
    add_reverse_edges(graph);// Ajout des arêtes inverses pour rendre le graphe non orienté

    if (graph == NULL || graph->data == NULL)
        return NULL;

    for (int i = 0; i < graph->numOf_vertices; i++) {
        graph->data[i].cout = INT_MAX;// Initialisation des coûts à la plus grande valeur possible
        graph->data[i].previous_edge = edge_new(-1, -1, -1); //prebvious edge inconnue
    }//je suppose aussi qu'on ne peut pas avoir de cout négatif


    graph->data[depart].cout = 0;

    // Initialiser le tas binaire
    heap_t *Atraiter = create_heap(graph->numOf_vertices);
    insert_heap(Atraiter, depart, 0); // Ajoute le sommet de départ avec un coût de 0

    list_vertex_t Atteint = NULL;

    while (!is_heap_empty(Atraiter)) {
        heap_node_t min_node = extract_min(Atraiter); // Extraction du sommet de coût minimal
        long int u_id = min_node.vertex;
        vertex_t u = graph->data[u_id];

        Atteint = list_sommet_add_first(Atteint, u);

        // Parcours des arêtes sortantes de u
        list_edge_t pe = u.edges;
        while (pe != NULL) {
            vertex_t v = graph->data[pe->val.id_arrival];
            if (!list_sommet_appartient(v, Atteint) && pe->val.cost < v.cout) {
                // Mise à jour du coût et de l'arête précédente
                graph->data[pe->val.id_arrival].cout = pe->val.cost;
                graph->data[pe->val.id_arrival].previous_edge = pe->val;

                insert_heap(Atraiter, pe->val.id_arrival, pe->val.cost); // Ajout de v à Atraiter avec la nouvelle priorité
            }
            pe = pe->next;
        }
    }

    // Construction de la liste des arêtes de l'ACM
    list_edge_t ACM = list_edge_new();
    for (int k = 0; k < graph->numOf_vertices; k++) {
        if (edge_is_valid(graph->data[k].previous_edge)) {
            ACM = list_edge_add_first(ACM, graph->data[k].previous_edge);
        }
    }

    free_heap(Atraiter);
    return ACM;
}

void add_reverse_edges(graph_t graph) {
    for (int i = 0; i < graph->numOf_vertices; i++) {
        list_edge_t edge_list = graph->data[i].edges;
        while (edge_list != NULL) {
            edge_t edge = edge_list->val;
            edge_t reverse_edge = edge_new(edge.id_arrival, edge.id_departure, edge.cost);
            graph->data[edge.id_arrival].edges = list_edge_add_first(graph->data[edge.id_arrival].edges, reverse_edge);
            edge_list = edge_list->next;
        }
    }
}
