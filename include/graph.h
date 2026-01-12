#ifndef _GRAPH_H
#define _GRAPH_H

#include "sommet.h"

// Type graphe : essentiellement un tableau de sommets
// Notez qu’on propose de definir le type graph t comme un type pointeur.
typedef struct {
    long int numOf_vertices; // nombre de sommets
    long int numOf_egdes; // nombre d’arcs
    vertex_t* data; // tableau des sommets, alloué dynamiquement
} * graph_t;

graph_t graph_read(char* nom_fichier);

int graph_is_empty(graph_t g);

graph_t graph_new();


#endif