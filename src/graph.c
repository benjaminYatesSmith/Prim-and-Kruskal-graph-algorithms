#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

graph_t graph_new(){
    graph_t graph = calloc(1,sizeof(*graph));
    return graph;
}

int graph_is_empty(graph_t g) {
  return NULL == g;
}

graph_t graph_read(char* nom_fichier){
    FILE* f;
    graph_t graph = graph_new();
    long int nb_vertices, nb_edges;
    long int vertex_id;
    long int vertex_depart;
    long int vertex_arriv;
    double vertex_latitude, vertex_longitude ; // pour la position d’un sommet
    double cost;
    char vertex_name[512] ;
    char tmp_string[512] ;
    f = fopen( nom_fichier, "r");
    if (NULL == f) {
        fprintf(stderr, "Le fichier graphe n'a pu etre ouvert. Aborts.\n");
        exit(EXIT_FAILURE);
        }
// Lecture de la premiere ligne du fichier : nombre de sommets et nombre d’arcs
    fscanf(f,"%ld %ld", &nb_vertices, &nb_edges);
    graph->numOf_vertices = nb_vertices;
    graph->numOf_egdes = nb_edges;
// Avec fgets(), on lit la fin de la première ligne pour passer à la suivante,
// y compris le caractère de retour à la ligne backslash-n
    fgets(tmp_string, 511, f);
// Lecture de la 2ème ligne : texte "Sommets du graphe" qui ne sert a rien.
// On supprime le retour à la ligne et on vérifié que la ligne est correcte
    fgets(tmp_string,511,f);
    //allocation en mémoire des sommets
    graph->data = calloc(nb_vertices,sizeof(vertex_t));

    for(long int i = 0; i<nb_vertices ;i++){
    // On est prêt a lire le début de la troisieme ligne du fichier.
    // Lecture de la ligne de description du premier sommet :
    // On lit d’abord le numero du sommet, sa position et le nom de la ligne
        fscanf(f,"%ld %lf %lf ", &vertex_id, &vertex_latitude, &vertex_longitude);
    
        
    

    // vertex id contient alors l’entier numero du sommet,
    // vertex latitude et vertex longitude la position du sommet
    // Le nom du sommet peut contenir des separateurs comme l’espace.
    // => On utilise plutot fgets pour lire toute la fin de ligne, m^eme les espaces :
        fgets(vertex_name,511,f);
    // fgets a lu toute la ligne, y compris le retour a la ligne.
    // On supprime le retour `a la ligne ’backslash-n’
    // qui peut se trouver a la fin de la chaine vertex name
    // en le remplacant par le caract`ere de fin de cha^ıne ’backslash-0’
    // Remarque : 32 est le code ascii du caract`ere espace ’ ’
    // et tous les caract`eres valides on un code ascii >= 32.
        while ( vertex_name[ strlen(vertex_name) - 1 ] < 32) {
            vertex_name[ strlen(vertex_name) - 1 ] = '\0';
        }
        
    // vertex name contient d´esormais le nom du sommet, espaces ´eventuels inclus.
    
        fscanf(f,"%ld %lf %lf ", &vertex_id, &vertex_latitude, &vertex_longitude);
        
    // vertex name contient désormais le nom du sommet, espaces éventuels inclus.
    
    //allocation des arcs
        list_edge_t arcs = list_edge_new();
    //allocation des sommets
        graph->data[i]=sommet_new(vertex_name, vertex_id, -1, edge_new(-1,-1,-1), vertex_latitude, vertex_longitude, arcs);

    // affichage de ce qui a été lu :
        printf("Nb sommets %ld ; Nb arcs %ld\n", nb_vertices, nb_edges);
        printf("Sommet %ld : indice %ld ; position [%lf ; %lf] ; nom %s\n",i ,vertex_id, vertex_latitude, vertex_longitude, vertex_name);
    }
    //lecture de la ligne "arc du graphe : départ arrivée valeur"
    fgets(tmp_string, 511, f);

    for(int k = 0; k<nb_edges; k++){
            //lecture de l'edge et test condition
            fscanf(f, "%ld %ld %lf ", &vertex_depart, &vertex_arriv, &cost);
            
            //création de l'edge
            edge_t edge_n = edge_new(vertex_depart, vertex_arriv, cost);

            //ajout dans la liste des sommets du graphe
            graph->data[vertex_depart].edges = list_edge_add_first(graph->data[vertex_depart].edges, edge_n);
            printf("Arc ajouté : %ld vers %ld, son coût est %lf.\n", vertex_depart, vertex_arriv, cost);
        } 
    

// Ne pas oublier de fermer le fichier !
    fclose(f);
    return graph;
}