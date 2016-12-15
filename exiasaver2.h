#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

typedef struct {	//structure de chiffres ayant comme propriétés la taille et la chaine de caractère d'un fichier PBM
	Taille taille;
	char* image;
} Chiffre;

Chiffre* chiffres[10];	//création de 10 chiffres de type Chiffre

void chaine_h(char temps[8]);

void separateur(int tableau[3], int tab[6]);

void init(Chiffre *chiffres[]);

void checker(char *place, int tester);