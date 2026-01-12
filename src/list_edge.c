#include <stdio.h>
#include <stdlib.h>

#include "list_edge.h"

list_edge_t list_edge_new() { 
  return NULL; 
}

int list_edge_is_empty(list_edge_t l) {
  return NULL == l;
}

list_edge_t list_edge_add_first(list_edge_t l, edge_t e) {
  list_edge_t p = calloc( 1, sizeof(*p) );
  if(NULL == p) {
    fprintf(stderr, "list_edge_add_first : error allocating list link\n");
    return NULL;
  }
  
  p->val  = e;
  p->next = l;
  return p;
}

size_t list_edge_length(list_edge_t l) {
  size_t len = 0;
  list_edge_t p;
  for( p=l; NULL != p ; p = p->next ) {
    len ++;
  }
  return len;
}

void list_edge_print(list_edge_t l) {
  list_edge_t p;
  printf("( ");
  p = l;
  while ( NULL != p ) {
    edge_print(p->val);
    printf( " " );
    p = p->next;
  }
  printf(")\n");
}

