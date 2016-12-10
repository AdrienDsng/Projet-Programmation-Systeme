#include "tri.h"

void tri_nom(char* tableau[], int taille) {
  char *tmp;
  int i, j;

  for (i = 0; i < taille; i++) 
    for (j = 0; j < taille; j++)
      if(strcmp(tableau[i], tableau[j]) < 0) {
        strcpy(tmp, tableau[i]);
        strcpy(tableau[i], tableau[j]);
        strcpy(tableau[j], tmp);
      }
}