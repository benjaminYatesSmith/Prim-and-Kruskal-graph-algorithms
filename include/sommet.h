#ifndef _SOMMET_H
#define _SOMMET_H

#include "list_edge.h"

// Type sommet : propriétés du sommet + liste des arcs sortant du sommet
typedef struct vertex {
    char* name; // nom donné au sommet
    double x,y; // coordonnées latitude et longitude du sommet
    long int id, cout;
    edge_t previous_edge;
    list_edge_t edges; // liste des arcs qui partent de ce sommet
    //ce qui suit est pour kruscal
    long int nb_sommet_dans_ensemble; //!! Il faudra initialiser cette variable à 1 
    struct vertex* parent;
} vertex_t;


// Création d'un nouveau sommet
vertex_t sommet_new(char* nom, long int id, long int cout, edge_t previous_edge, double lat, double lon, list_edge_t arcs);

// Impression du sommet
void sommet_print(vertex_t sommet);

// Initialisation sommet
vertex_t sommet_init();






#endif