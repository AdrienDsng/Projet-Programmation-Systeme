#include <unistd.h> 
#include <sys/ioctl.h> //librairie permettant d'avoir la largeur et la hauteur de la console
#include <string.h> //librairie permettant de manipuler des chaines de caractères
#include <stdlib.h> 
#include <stdio.h>


void center (char* text/*, Taille *taille*/) //fonctione permettant de centrer une chaine de caractère dans la console.
{
	struct winsize w; //structure de la librairie 
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); //appel système d'entrée-sortie 
	int largeurCsl = w.ws_col;	//variable du nombre de colonnes de la console, sa largeur
	int hauteurCsl = w.ws_row; //variable du nombre de lignes de la console, sa hauteur
	unsigned int n = 0, i = 0, j = 0;	// Variables utilisées dans les boucles for.

	int height = 5; //variable de hauteur de l'image
	int width = 5;	//variable de largeur de l'image 

	system("clear"); //vide la console

	for (n = 0; n < (hauteurCsl - height)/2; n++) //boucle permettant d'ajouter les \n nécessaires au dessus de l'image en fonction de la taille de la console et de l'image
	{
		putchar('\n');
	}

	for (int j = 0; j < (largeurCsl - width) / 2; j++)	//boucle ajoutant les espaces nécessaires pour la premiere ligne de la chaine de caractères
	{	
		putchar(' ');
	}

	for (i = 0; i < strlen(text); i++) //boucle parcourant toute la chaine de caractères qui affiche tous les caractères.
	{
		printf("%c", text[i]);
		if(text[i] == '\n')  //si le caractère rencontré est un \n
		{
			for (int j = 0; j < (largeurCsl - width) / 2; j++) //permet d'ajouter les espaces pour toutes les autres lignes 
			{
				putchar(' ');
			}
		}
	}
	printf("\n");
	for (n = 0; n < (hauteurCsl - height)/2; n++) 	//permet d'ajouter les \n nécessaires en dessous en fonction de la taille de la console et de l'image
	{										
		putchar('\n');
	}
}


int main () 
{
	center("test\ntest1\ntest2"); //Test de la fonction sur trois lignes.
}


