#ifndef _EDGE_H
#define _EDGE_H

// Definition du type arc
typedef struct {
  long int id_departure, id_arrival;
  double cost; 
} edge_t;

// Retourne un arc correctement formé,

// ou en cas d'erreur un arc avec :
//    id_departure == -1
//    id_arrival   == -1
//    cost         == -1
// Erreurs : 
//  - si cost < 0 (on ne manipule que des graphes à valuation positive)
//  - si id_departure < 0
//  - si id_arrival < 0
edge_t edge_new(int id_departure, int id_arrival, double cost);

// Retourne "vrai" si l'arc e est valide (tous champs > 0) 
// Retourne 0 sinon
int edge_is_valid(edge_t e);

// Affiche l'arc e
void edge_print(edge_t e);


#endif
