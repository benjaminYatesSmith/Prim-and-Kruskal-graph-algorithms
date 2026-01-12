#include <stdio.h>
#include <stdlib.h>

#include "sommet.h"


vertex_t sommet_init(){
    vertex_t sommet;
    sommet.name = calloc(1,sizeof(char*));
    sommet.edges = list_edge_new();
    return sommet;
}

vertex_t sommet_new(char* nom, long int id, long int cout, edge_t previous_edge, double lat, double lon, list_edge_t arcs){
    vertex_t sommet  = sommet_init();
    sommet.name = nom;
    sommet.x = lat;
    sommet.y = lon;
    sommet.id = id;
    sommet.cout = cout;
    sommet.previous_edge = previous_edge;
    if (arcs!=NULL) {
        sommet.edges = arcs;
    }
    return sommet;
}

void sommet_print(vertex_t sommet){
    printf("(affichage sommet) \n");
    printf("latitude : %lf \n",sommet.x);
    printf("longitude : %lf \n",sommet.y);
    list_edge_print(sommet.edges);
}
