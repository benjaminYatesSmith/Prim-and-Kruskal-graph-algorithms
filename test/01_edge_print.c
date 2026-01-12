#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <edge.h>

void test_edge_new() {
  edge_t e ;

  fprintf(stderr, "## Test de la fonction edge_new\n");

  fprintf(stderr, "<= Test : créer un arc avec des valeurs valides fontionne correctement\n");
  e = edge_new(12, 13, 9.8);
  assert(e.id_departure == 12);
  assert(e.id_arrival   == 13);
  assert(e.cost         == 9.8);
  fprintf(stderr, "=> Test passé avec succès\n" );
}

void test_edge_is_valid() {
  edge_t e ;

  fprintf(stderr, "## Test de la fonction edge_is_valid\n");

  fprintf(stderr, "<= Test : un arc créé avec des valeur >= 0 est bien valide\n");
  e = edge_new(12, 13, 9.8);
  assert( edge_is_valid(e) );
  fprintf(stderr, "=> Test passé avec succès\n" );

  fprintf(stderr, "<= Test : un arc créé avec une valeur <0 est bien invalide\n");
  fprintf(stderr, "Un arc créé avec une valeur < 0 est bien considéré invalide\n");
  e = edge_new(-12, 13, 9.8);
  assert( ! edge_is_valid(e) );

  e = edge_new(12, -13, 9.8);
  assert( ! edge_is_valid(e) );

  e = edge_new(12, 13, -9.8);
  assert( ! edge_is_valid(e) );
  fprintf(stderr, "=> Test passé avec succès\n" );
}

int main() {
  test_edge_new();
  test_edge_is_valid();

  fprintf(stderr, "Tests du fichier 01_edge_print.c passés avec succès\n");

  return EXIT_SUCCESS;
}
