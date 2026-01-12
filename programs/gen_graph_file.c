#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <string.h>


int main(int argc, char** argv) {
  int nbsom,degre,i,j, taille, graine=1;
  double seuil_distance;
  char filename[512];
  FILE* fp;

  taille=1000;

  printf("Generation d'un graphe aleatoire\n");
  if (argc!=6) {
    printf("Usage : %s graine_aleatoire seuil_distance Nombre_sommet Degre_sommet Nom_fichier\n",argv[0]);
    exit(EXIT_FAILURE);
  }
  if ( (graine=atoi(argv[1]))<0) {
    printf("Graine generateur aleatoire > 0\n");
    exit(EXIT_FAILURE);
  }
  srandom(graine);
  if ( (seuil_distance=atof(argv[2]))<0) {
    printf("0<seuil_distance < %d\n",taille);
    exit(EXIT_FAILURE);
  }
  if ( (nbsom=atoi(argv[3]))<0) {
    printf("Nombre de sommets > 0\n");
    exit(EXIT_FAILURE);
  }
  if ( (degre=atoi(argv[4]))<0 || degre>10) {
    printf("0< Degre des sommets < 10\n");
    exit(EXIT_FAILURE);
  }
  strcpy(filename,argv[5]);
  printf("de seuil_distance %lf, avec %d sommets et %d voisins dans le fichier %s\n",seuil_distance, nbsom, degre,filename);

  double* sommetsx=calloc(nbsom,sizeof(*sommetsx));
  double* sommetsy=calloc(nbsom,sizeof(*sommetsy));
  if (sommetsx==NULL|| sommetsy==NULL) { printf("Erreru allocation\n"); exit(EXIT_FAILURE); }
  fp=fopen(filename,"w");
  fprintf(fp,"%d %d\n",nbsom,degre*nbsom);
  fprintf(fp,"Sommets du graphe \n");
  for (i=0; i<nbsom; i++) {
    sommetsx[i]=random()/(double)INT_MAX*(double)taille;
    sommetsy[i]=random()/(double)INT_MAX*(double)taille;

    fprintf(fp,"%d %lf %lf sommet%d\n",i,sommetsx[i],sommetsy[i], i);
  }
  fprintf(fp,"arc du graphe : départ arrivée valeur\n");
  printf("Sommet %9d",0);
  for (i=0; i<nbsom;i++) { printf("\b\b\b\b\b\b\b\b\b%9d",i); fflush(stdout);
    for (j=0; j<degre; j++) { int k,l=0;
      for (l=0,k=random()%nbsom;l<nbsom && hypot(sommetsx[i]-sommetsx[k],sommetsy[i]-sommetsy[k])>seuil_distance*taille/sqrt(nbsom);l++,k=random()%nbsom );
      if (l!=nbsom) fprintf(fp,"%d %d %lf\n",i,k,hypot(sommetsx[i]-sommetsx[k],sommetsy[i]-sommetsy[k]));
    }
  }
  puts("");
  free(sommetsx); free(sommetsy);
  fclose(fp);
}
