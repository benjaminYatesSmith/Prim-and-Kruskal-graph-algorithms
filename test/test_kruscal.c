#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "tri_fusion.h"
#include "union_find.h"
#include "free.h"


int main(){
    char *fichier = "graphes/graphe2.txt";
    graph_t graph = graph_read(fichier);
    if(test_kruscal(graph))
        printf("\nTests du fichier test_kruscal.c passés avec succès\n");

    
    return 0;
}


int test_kruscal(graph_t graph_toTest)
{
    printf("\n\n Test de la fonction kruscal: \n");

    long int cout_totale = 0;
    list_edge_t acm = kruskal(graph_toTest);

    printf("\n\nAretes de l'ACM:\n");
    list_edge_t current = acm;

    while (current != NULL){
        printf("(%ld, %ld) cout: %lf\n", current->val.id_departure, current->val.id_arrival, current->val.cost);
        cout_totale += current->val.cost;
        current = current->next;
    }

    printf("Le cout total de l'ACM = %ld\n", cout_totale);

    //test_sorted_ascending_graph(graph_toTest); //on test que la liste est bien triée par ordre croissant
    test_each_vertex_reached(acm, graph_toTest);//on test que chaque sommet a été atteint

    free_edge_list(acm);

    return 1;
}

void test_sorted_ascending_graph_fusion(graph_t graph_toTest){
    list_edge_t sorted_edges = sorted_ascending_graph_merge(graph_toTest);

    double last_cost = -1.0; // Je suppose que nous ne pouvons pas avoir de coût négatif
    list_edge_t current_list = sorted_edges;

    while (current_list != NULL)
    {
        assert(current_list->val.cost >= last_cost);
        last_cost = current_list->val.cost;
        current_list = current_list->next;
    }


    // Libérer la mémoire des arêtes triées si nécessaire
    /*
    while (sorted_edges != NULL) {
        list_edge_t temp = sorted_edges;
        sorted_edges = sorted_edges->next;
        free(temp);
    }
    */
}


void test_each_vertex_reached(list_edge_t acm, graph_t graph_toTest)
{

    // Je pars du dernier sommet pour trouver le représentant
    vertex_t* root = find_parent(&graph_toTest->data[graph_toTest->numOf_vertices - 1]);
    // Je teste si chaque ensemble a été atteint une fois
    printf("il y a %ld sommets dans l'ensemble et %ld sommets en totales\n", root->nb_sommet_dans_ensemble, graph_toTest->numOf_vertices);
    assert(root->nb_sommet_dans_ensemble == graph_toTest->numOf_vertices);
    
    printf("Ainsi chaque sommet a ete atteint\n");
    printf("Test each vertex reached reussi.\n");

    /* Libérer la mémoire des arêtes de l'ACM si nécessaire
    while (acm != NULL) {
        list_edge_t temp = acm;
        acm = acm->next;
        free(temp);
    }*/
}

void test_fusion_deux_ensembles(graph_t graph_toTest, long int id_vertex1, long int id_vertex2) {
    assert(graph_toTest != NULL);
    assert(id_vertex1 >= 0 && id_vertex1 < graph_toTest->numOf_vertices);
    assert(id_vertex2 >= 0 && id_vertex2 < graph_toTest->numOf_vertices);

    vertex_t* vertex1 = &graph_toTest->data[id_vertex1];
    vertex_t* vertex2 = &graph_toTest->data[id_vertex2];
    vertex_t* parent1 = find_parent(vertex1);
    vertex_t* parent2 = find_parent(vertex2);

    if (parent1 == parent2) {
        printf("Les deux sommets avaient déjà les mêmes parents\n");
        return;
    }

    long int set_size1 = parent1->nb_sommet_dans_ensemble;
    long int set_size2 = parent2->nb_sommet_dans_ensemble;

    vertex1->parent = vertex1;
    vertex2->parent = vertex2;

    long int new_set_size = fusion_deux_ensembles(parent1, parent2);

    assert(new_set_size == (set_size1 + set_size2));
    assert(find_parent(vertex1) == find_parent(vertex2));

    printf("Test fusion_deux_ensembles réussi.\n");
}


/*void test_reproducibility_kruscal(graph_t graph) {
    list_edge_t acm1 = kruskal(graph);
    list_edge_t acm2 = kruskal(graph);

    // Comparez les deux ACM pour s'assurer qu'ils sont identiques
    list_edge_t current1 = acm1;
    list_edge_t current2 = acm2;

    while (current1 != NULL && current2 != NULL) {
        assert(current1->val.id_departure == current2->val.id_departure);
        assert(current1->val.id_arrival == current2->val.id_arrival);
        assert(current1->val.cost == current2->val.cost);
        current1 = current1->next;
        current2 = current2->next;
    }

    assert(current1 == NULL && current2 == NULL);

    free_edge_list(acm1);
    free_edge_list(acm2);

    printf("Test de la consistance des résultats réussi.\n");
}*/
