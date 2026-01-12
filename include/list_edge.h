#ifndef _LIST_EDGE_H
#define _LIST_EDGE_H
#include <stdio.h>
#include <stdlib.h>
#include "edge.h"

// Définitinon du type liste d'arcs
typedef struct _link_edge {
  edge_t val; 
  struct _link_edge *next; 
}link_edge_t, *list_edge_t;


// Création d'une liste vide
list_edge_t list_edge_new();

// Retourne true si la liste l est vide
int list_edge_is_empty(list_edge_t l);

// Ajoute l'arc e à la liste l 
// et retourne la nouvelle liste, 
// ou NULL en cas d'erreur
list_edge_t list_edge_add_first(list_edge_t l, edge_t e);

// Retourne le nombre d'éléments de la liste l
size_t list_edge_length(list_edge_t l);

// Affiche les arcs de la liste l
void list_edge_print(list_edge_t l);

#endif
