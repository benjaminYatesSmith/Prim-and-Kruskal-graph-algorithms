#include "prim.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

list_edge_t acm_prim(int depart, graph_t graph){

    // initialisation des deux listes de sommets
    list_vertex_t Atraiter = list_sommet_new();
    list_vertex_t Atteint = list_sommet_new();

    // initialisation des couts des sommets à (+inf=INT_MAX)
    // et 
    // initialisation liste des previous edges

    list_edge_t previous_edge = list_edge_new();
    for(int i = 0; i<graph->numOf_vertices; i++){
        edge_t inconnu = edge_new(graph->numOf_vertices-i, graph->numOf_vertices+1, INT_MAX);
        previous_edge = list_edge_add_first(previous_edge, inconnu);
        graph->data[i].cout = INT_MAX;
    }

    // initialisation coût sommet de départ à zéro
    graph->data[depart].cout = 0;

    // ajout du sommet de départ dans Atraiter
    Atraiter = list_sommet_add_first(Atraiter, graph->data[depart]);
    while(!list_sommet_is_empty(Atraiter)){
        vertex_t u = list_sommet_rech_cout_min(Atraiter);
        Atteint = list_sommet_add_first(Atteint, u);
        list_edge_t pe = u.edges;
        while(!list_edge_is_empty(pe)){
            if(!list_sommet_appartient(graph->data[pe->val.id_arrival], Atteint)){ 
                if( (graph->data[pe->val.id_arrival].cout > pe->val.cost+u.cout) || (pe->val.cost==INT_MAX) ){
                    graph->data[pe->val.id_arrival].cout = pe->val.cost + u.cout;

                    // previous_edge(v) = u
                    graph->data[pe->val.id_arrival].previous_edge = pe->val;

                    Atraiter = list_sommet_add_last(Atraiter, graph->data[pe->val.id_arrival]);
                }
                
            }
            pe=pe->next;
        }   
        Atraiter = Atraiter->next;
    }
    // Construction de la liste comportant les arrêtes de l'ACM
    list_edge_t ACM = list_edge_new();
    for(int k = 0; k<graph->numOf_vertices; k++){
        if(edge_is_valid(graph->data[k].previous_edge)){
            ACM = list_edge_add_first(ACM, graph->data[k].previous_edge);
        }
    }

    // Libération mémoire (check avec Valgrind)
    
    //free(pe);
    // à travailler
    //free(Atraiter->edges);
    //free(Atteint->edges);
    //free(Atteint);
    //free(Atraiter);

    return ACM;
}