#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "union_find.h"
#include "free.h"


list_edge_t kruskal(graph_t graph)
{
    if(graph == NULL)
        return NULL;

    if(graph->data == NULL)
        return NULL;

    for (int i = 0; i < graph->numOf_vertices; i++){
        graph->data[i].nb_sommet_dans_ensemble = 1;//initialement, il y a un sommet par ensemble
        graph->data[i].parent = &graph->data[i];//chaque sommet est son propre représentant
    }

    list_edge_t sorted_edges = sorted_ascending_graph_merge(graph);
    list_edge_t acm = union_find(graph, sorted_edges);

    free_edge_list(sorted_edges);

    return acm;
}

list_edge_t union_find(graph_t graph, list_edge_t sorted_edges) {
    if (graph == NULL || sorted_edges == NULL)
        return NULL;

    list_edge_t acm = NULL; // Liste des arêtes de l'ACM
    int numOf_verticies_inSet = 0;

    while (sorted_edges != NULL && numOf_verticies_inSet < graph->numOf_vertices) {
        int vertex_ind_depart = sorted_edges->val.id_departure;
        int vertex_ind_arrival = sorted_edges->val.id_arrival;

        vertex_t* root_depart = find_parent(&graph->data[vertex_ind_depart]);
        vertex_t* root_arrival = find_parent(&graph->data[vertex_ind_arrival]);

        if (root_depart != root_arrival) {
            numOf_verticies_inSet = fusion_deux_ensembles(root_depart, root_arrival);

            // Ajoute l'arête à l'ACM
            list_edge_t new_edge = (list_edge_t)malloc(sizeof(link_edge_t));
            if (new_edge == NULL) {
                perror("Erreur d'allocation mémoire");
                exit(EXIT_FAILURE);
            }
            new_edge->val = sorted_edges->val;
            new_edge->next = acm;
            acm = new_edge;
        }

        sorted_edges = sorted_edges->next;
    }

    return acm;
}

long int fusion_deux_ensembles(vertex_t* root_depart, vertex_t* root_arrival) {
    if (root_depart == NULL || root_arrival == NULL)
        return 0;

    if (root_depart != root_arrival) {
        if (root_depart->nb_sommet_dans_ensemble <= root_arrival->nb_sommet_dans_ensemble) {
            root_depart->parent = root_arrival; // On met le plus petit dans le plus grand
            root_arrival->nb_sommet_dans_ensemble += root_depart->nb_sommet_dans_ensemble;
            return root_arrival->nb_sommet_dans_ensemble;
        } else {
            root_arrival->parent = root_depart;
            root_depart->nb_sommet_dans_ensemble += root_arrival->nb_sommet_dans_ensemble;
            return root_depart->nb_sommet_dans_ensemble;
        }
    }
    return root_depart->nb_sommet_dans_ensemble;
}

vertex_t* find_parent(vertex_t* sommet) {
    if (sommet->parent == sommet)// si il est le représentant se son ensemble
        return sommet;

    //on utilise la récursivité pour améliorer l'efficacité de find parent (compression de chemin)
    if (sommet != sommet->parent)
        sommet->parent = find_parent(sommet->parent); 

    return sommet->parent;
}

