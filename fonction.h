#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/ioctl.h> 
#include <unistd.h> 
#include <ncurses.h>
#include <curses.h>
#include <sys/wait.h>


typedef struct // structure pour la taille de l'image
{
	int width;
	int height;
} Taille;

void  lirePBM(char* nomDuFichier, char* chaine,Taille *taille);//fonction qui lit l'image et la transforme les données en chaîne de caractére nous renvoie également la taille de l'image 

void retirerLesBlancs(char chaines[],char copy[]); // fonction permettant de retirer les espaces dans une chaîne il a besoin de 2 chaîne de caractére pour copier l'une dans l'autre

char* affPBM(char* chaine); //fonction permmettant de changer les caractéres reçu en caractére ascii

void center (char* text,Taille *taille); //fonction permettant d'afficher l'image centrée 