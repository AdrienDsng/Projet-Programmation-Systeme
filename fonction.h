#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/ioctl.h> 
#include <unistd.h> 
#include <sys/wait.h>

/**stucture
*taille de l'image
**/
typedef struct 
{
	int width; /*<largeur*/
	int height;/*<hauteur*/
} Taille;

/**
*fonction qui lit l'image  
*@param nomdufichier 	nom du fichier 
*@param chaine  	 	chaine où on va ecrire les données du fichier lu 
*@param Taille *taille  structure de int qui va récuperer la taille de l'image lue
*@return void
**/

char*  lirePBM(char* nomDuFichier,Taille *taille);
  
/**
*permet de retirer les espaces dans une chaîne 
*@param chaines 	phrase ou chaine de caractère
*@param copy 		chaine de caractére où on met les caractéres a modifier(ici les espaces)
*@return void 
**/

void retirerLesBlancs(char* chaines);

/**
permet de changer certain caractéres reçu en caractére ascii
*@param chaine  chaine de caractére qui sera modifier
*return void 	
**/
void affPBM(char* chaine); 
 /**
 *permet d'afficher l'image centrée
 *@param	text		l'image a centrée
 *@param	taille 		taille de l'image
 *@return void
 **/

void center (char* text,Taille *taille);