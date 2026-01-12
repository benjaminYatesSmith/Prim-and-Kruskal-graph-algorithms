#include <stdio.h>
#include <stdlib.h>
#include "tri_fusion.h"
#include "union_find.h"
#include "free.h"
#include "prim2.h"
#include <string.h>
// Ce fichier est destiné a accueillir 
// la fonction main du programme principal final acm
// Dans sa version fournie, il se contente 
// de réécrire dans le Terminal les arguments passés au programme
// sur la ligne de commande




int main(int argc, char * argv[]) {

    if (argc < 3 || argc > 4) {
        fprintf(stderr, "Usage: %s <filename> <0|1> [-v]\n", argv[0]);
        return 1;
    }

    int choix_algo = atoi(argv[2]);
    int verbeux = (argc == 4 && strcmp(argv[3], "-v") == 0);

    if (choix_algo != 0 && choix_algo != 1) {
        fprintf(stderr, "Le deuxieme argument doit être 0 (Kruskal) ou 1 (Prim)\n");
        return 1;
    }

    if (verbeux) {
        printf("Verbose mode is ON\n");
    }

    // Concaténer "graphes/" avec le nom de fichier
    char *repertoire = "graphes/";
    char *fichier = argv[1];

    // Allouer suffisamment de mémoire pour le chemin complet
    size_t longueur_chemin = strlen(repertoire) + strlen(fichier) + 1;
    char *chemin = malloc(longueur_chemin);
    if (!chemin) {
        fprintf(stderr, "Erreur: échec de l'allocation de mémoire\n");
        return 1;
    }

    // Construire le chemin complet
    strcpy(chemin, repertoire);
    strcat(chemin, fichier);

    // Lire le fichier pour construire le graphe
    graph_t graph = graph_read(chemin);

    // Exécuter l'algorithme choisi
    if (choix_algo == 1) {
        if (verbeux) {
            printf("Execution de Prim\n");
        }
        if(test_prim2(graph))
        printf("\nTests du fichier test_prim2.c passés avec succès\n");

    } 
    else {
        if (verbeux) {
            printf("Execution de Kruskal\n");
        }
        if(test_kruscal(graph))
        printf("\nTests du fichier test_kruscal.c passés avec succès\n");
    }

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
    //test_each_vertex_reached(acm, graph_toTest);//on test que chaque sommet a été atteint

    free_edge_list(acm);

    return 1;
}


int test_prim2(graph_t graph_toTest) {
    printf("\n\n Test de la fonction prim: \n");

    long int cout_totale = 0;
    //permet de commencer avec le sommet de départ de l'arête par lequel kruskal commencerait
    list_edge_t sorted_edges = sorted_ascending_graph_merge(graph_toTest);

    int starting_vertex = sorted_edges->val.id_departure;
    printf("\n\n l'ID de depart est %d\n", starting_vertex);

    list_edge_t acm = acm_prim2(starting_vertex, graph_toTest);

    printf("\n\nAretes de l'ACM:\n");
    list_edge_t current = acm;

    while (current != NULL) {
        printf("Edge de %ld a %ld avec cout %lf\n", current->val.id_departure, current->val.id_arrival, current->val.cost);
        cout_totale += current->val.cost;
        current = current->next;
    }

    printf("Le cout total de l'ACM = %ld\n", cout_totale);

    free_edge_list(acm);

    return 1;
}