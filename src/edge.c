#include <stdio.h>
#include <stdlib.h>

#include "edge.h"


edge_t edge_new(int id_departure, int id_arrival, double cost) {
  edge_t e;
  
  if ( id_departure < 0 || id_arrival < 0 || cost < 0) {
    fprintf(stderr, "edge_new : invalid parameters\n");
    e.id_departure = -1;
    e.id_arrival   = -1;
    e.cost         = -1;
    return e;
  }
  
  e.id_departure = id_departure ;
  e.id_arrival   = id_arrival ;
  e.cost         = cost ;
  
  return e;
}

int edge_is_valid(edge_t e) {
  return e.id_departure >= 0 && e.id_arrival >= 0 && e.cost >= 0;  
}

void edge_print(edge_t e) { 
  printf("[ Deperture:%ld ; Arrival:%ld ; Cost:%lf ]", 
    e.id_departure, 
    e.id_arrival, 
    e.cost);
}

