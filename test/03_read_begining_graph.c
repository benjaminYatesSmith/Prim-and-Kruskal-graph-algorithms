#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // pour PATH_MAX
#include <assert.h>
#include <libgen.h>

#include <unistd.h>

// Cette fonction extrait le chemin vers la racine du dépot git
// et stocke ce chemin dans path_to_git_directory,
// qui doit être préalablement alloué à la taille size.
// PARAMS :
//    executable_path : chemin vers l'exécutable (typiquemet argv[0])
void compute_git_repository_path(char * executable_path, 
  char *path_to_git_directory, 
  int size) {
    
  char real_path[PATH_MAX];
  realpath(executable_path, real_path);
  char * path_to_directory;
  path_to_directory = dirname(real_path); // le repertoire test
  path_to_directory = dirname(path_to_directory); // le repertoire racine du dépôt
  
  if( strlen(path_to_git_directory) + 1 >= (unsigned int) size) {
    fprintf(stderr, "compute_git_repository_path : error - path is too long. Aborts.\n");
    exit(EXIT_FAILURE);
  }

  strcpy(path_to_git_directory, path_to_directory);
}

void test_read_begining_graph_file(char * graph_file_name, 
    // parametres pour tester que le nb de sommets et d'arcs
    // a été lu correctement
    int check_nb_vertices,
    int check_nb_edges,
    // parametres pour tester que les données du premier sommet
    // ont été lues correctement
    int    check_first_vertex_id,
    char * check_first_vertex_name,
    double check_first_vertex_latitude,
    double check_first_vertex_longitude) {
      
  FILE* f;

  int nb_vertices, nb_edges; 
  
  int vertex_id;
  double vertex_latitude, vertex_longitude ; // pour la position d'un sommet
  char vertex_name[512] ;
  
  char tmp_string[512] ;
  
  fprintf(stderr, "\n## Test du début de la lecture du fichier graphe %s\n", graph_file_name);

  f=fopen(graph_file_name, "r");
  if (NULL == f) { 
    fprintf(stderr, "Le fichier %s n'a pu être ouvert. Aborts.\n", graph_file_name); 
    exit(EXIT_FAILURE);
  }
  
  // Lecture de la premiere ligne du fichier : 
  // nombre de sommets et nombre d'aretes 
  fscanf(f,"%d %d", &nb_vertices, &nb_edges);
  
  fprintf(stderr, "<= Test : le nombre de sommets et d'arcs lu dans le fichier est correct\n");
  assert(nb_vertices == check_nb_vertices);
  assert(nb_edges == check_nb_edges);
  fprintf(stderr, "=> Test passé avec succès\n" );

  // On saute la fin de la première ligne,
  // y compris le caractère de retour à la ligne '\n',
  // en la lisant avec fgets :
  fgets(tmp_string, 511, f);
  
  // Lecture de la 2ème ligne : 
  // texte "Sommets du graphe" qui ne sert a rien.
  // ... mais il conviendrait de vérifier qu'elle est correcte...
  fgets(tmp_string,511,f); 

  // Pour finir, on lit une ligne de description d'un sommet :
  
  // On lit d'abord le numero du sommet, sa position et  le nom de la ligne
  fscanf(f,"%d %lf %lf ", &vertex_id, &vertex_latitude, &vertex_longitude);
  // vertex_id contient alors l'entier numero du sommet, 
  // vertex_latitude et vertex_longitude la position du sommet
  
  // Le nom du sommet peut contenir des separateurs comme l'espace. 
  // On utilise plutot fgets pour lire toute la fin de ligne :
  fgets(vertex_name,511,f); 
  
  // fgets a lu toute la ligne, y compris le retour a la ligne.
  // On supprime le caractere retour-à-la-ligne '\n'  
  // qui peut se trouver a la fin de la chaine vertex_name
  // en le remplacant par '\0'.
  // Remarque : 32 est le code ascii du caractère espace ' '
  // et tous les caractères valides on un code ascii >= 32.
  while ( vertex_name[ strlen(vertex_name) - 1 ] < 32) {
    vertex_name[ strlen(vertex_name) - 1 ] = '\0';
  }
  // vertex_name contient desormais le nom du sommet, espaces eventuels inclus.
  
  fprintf(stderr, "<= Test : les données lues pour le premier sommet sont correctes\n");
  assert(vertex_id        == check_first_vertex_id);
  assert(vertex_latitude  == check_first_vertex_latitude);
  assert(vertex_longitude == check_first_vertex_longitude);
  assert( strcmp(vertex_name, check_first_vertex_name) == 0 );
  fprintf(stderr, "=> Test passé avec succès\n" );

  // Ne pas oublier de fermer le fichier !
  fclose(f);
}


int main(int argc, char * argv[]) {
  char path_to_git_repository[4096];
  char graph_file_path[4096];
  
  // on récupère le chemin vers le fichier exécutable du test
  // ... comme cela, on pourra lancer ce programme de 
  // n'importe quel répertoire !
  compute_git_repository_path(argv[0], path_to_git_repository, 4096);
  // path_to_git_repository est 
  // le chemin vers le répertoire racine du dépot git 
  
  // Fichier graphe0.txt
  // Construction du chemin vers le fichier graphe0.txt
  sprintf(graph_file_path, "%s/%s", path_to_git_repository, "graphes/graphe0.txt");
  // Test de la lecture de ce fichier
  test_read_begining_graph_file(graph_file_path, 
      8,  // nb de sommets du graphe
      12, // nb d'arcs du graphe

      0,     // id du premier sommet dans le fichier
      "Aaa", // nom du premier sommet dans le fichier
      0.5,   // latitude du premier sommet dans le fichier
      0.95  // longitude du premier sommet dans le fichier
    );
    
  // Fichier graphe2.txt
  // Construction du chemin vers le fichier graphe0.txt
  sprintf(graph_file_path, "%s/%s", path_to_git_repository, "graphes/graphe2.txt");
  // Test de la lecture de ce fichier
  test_read_begining_graph_file(graph_file_path, 
      14,  // nb de sommets du graphe
      28, // nb d'arcs du graphe

      0,     // id du premier sommet dans le fichier
      "Sommet1", // nom du premier sommet dans le fichier
      0.05,   // latitude du premier sommet dans le fichier
      0.7  // longitude du premier sommet dans le fichier
    );
    
  fprintf(stderr, "Tests du fichier 03_read_begining_graph.c passés avec succès\n");

  return EXIT_SUCCESS;
}
