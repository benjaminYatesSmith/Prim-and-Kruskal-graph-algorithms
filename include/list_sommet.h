#ifndef _LIST_SOMMET_H
#define _LIST_SOMMET_H

#include "sommet.h"



// Définitinon du type liste de sommets
typedef struct _link_vertex {
  vertex_t sommet; 
  struct _link_vertex *next; 
} * list_vertex_t;

// Création d'une liste vide
list_vertex_t list_sommet_new();

// Retourne true si la liste l est vide
int list_sommet_is_empty(list_vertex_t l);

// Ajoute le sommet s à la liste l 
// et retourne la nouvelle liste, 
// ou NULL en cas d'erreur
list_vertex_t list_sommet_add_first(list_vertex_t l, vertex_t s);

list_vertex_t list_sommet_add_last(list_vertex_t l, vertex_t s);

// recherche du sommet avec le cout minimal parmis une liste de sommets
// puis, retourne ce sommet
vertex_t list_sommet_rech_cout_min(list_vertex_t l);

// retourne 1 si le sommet v appartient a la liste l
int list_sommet_appartient(vertex_t v, list_vertex_t l);
list_vertex_t list_sommet_remove(list_vertex_t l, vertex_t sommet);

#endif