#include <stdio.h>
#include <stdlib.h>

#include "../include/tri_ordre_croissant_kruskal.h"


list_edge_t sorted_ascending_graph(graph_t graph_a_trier) {
    list_edge_t sorted_edges = NULL;
    for (long int i = 0; i < graph_a_trier->numOf_vertices; i++) {
        vertex_t sommet = graph_a_trier->data[i];
        parcours_list_pour_trie(sommet.edges, &sorted_edges);
    }
    return sorted_edges;
}

void parcours_list_pour_trie(list_edge_t list, list_edge_t* sorted_edge) {
    if (list == NULL) {
        return;
    }

    list_edge_t current_node = list;
    list_edge_t next_node = NULL;

    while (current_node != NULL) {
        next_node = current_node->next;
        insert_sorted_edge(sorted_edge, current_node);
        current_node = next_node;
    }
}

void insert_sorted_edge(list_edge_t* list, list_edge_t new_node) {
    new_node->next = NULL;

    // Insertion en tête de liste si la liste est vide ou si le nouvel élément a un coût inférieur à la tête
    if (*list == NULL || new_node->val.cost < (*list)->val.cost) {
        new_node->next = *list;
        *list = new_node;
    } else {
        // Recherche de la position d'insertion
        link_edge_t* current = *list;
        while (current->next != NULL && current->next->val.cost <= new_node->val.cost) {
            current = current->next;
        }

        new_node->next = current->next;
        current->next = new_node;
    }
}


