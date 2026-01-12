#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <edge.h>
#include <list_edge.h>

void test_list_edge_basic() {
  list_edge_t l;
  edge_t e;

  fprintf(stderr, "## Test des fonctions basiques du module list_edge\n");

  fprintf(stderr, "<= Test : une liste est bien vide après sa création\n");
  l = list_edge_new();
  assert( list_edge_is_empty(l) );
  assert( 0 == list_edge_length(l) );
  fprintf(stderr, "=> Test passé avec succès\n" );

  fprintf(stderr, "<= Test : après ajout d'élément(s) dans une liste, le nombre d'élément est correct\n");

  e = edge_new(1, 2, 3.5);
  l = list_edge_add_first(l, e);
  assert( ! list_edge_is_empty(l) );
  assert( 1 == list_edge_length(l) );

  e = edge_new(4, 5, 6.5);
  l = list_edge_add_first(l, e);
  assert( ! list_edge_is_empty(l) );
  assert( 2 == list_edge_length(l) );
  fprintf(stderr, "=> Test passé avec succès\n" );

  fprintf(stderr, "Affichage de la liste à 2 éléments : \n ");
  list_edge_print( l );
}

int main() {
  test_list_edge_basic();

  fprintf(stderr, "Tests du fichier 02_list_edge.c passés avec succès\n");

  return EXIT_SUCCESS;
}
