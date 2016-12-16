#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE_LOG 300

/**
 * Structure
 * Contient les stats
**/
typedef struct
{
	struct tm dateTime;	/**< Structure de temps */
	int screenSaver;	/**< Type d'écran de veille */
	char args[255];		/**< Arguments */
} Stat;

char strBuf[SIZE_LOG][70];
Stat buf[SIZE_LOG];

/**
 * Permet de créer les phrases a inscrire dans l'historique
 * @param		stat		statistique à mettre en chaine
 * @param		str[255]	chaine contenant les statistiques
 * @return 		void
**/
void toStringStat(Stat stat, char str[255]);

/**
 * Met l'heure sous forme de chaine de caractère
 * @param		stat		statistique à mettre en chaine
 * @param		str			chaine contenant les statistiques
 * @return 		void
**/
void toStringDateTime(Stat stat, char str[255]);


/**
 * Ecrit des chaînes de caractères dans le fichier historique
 * @param		termSaver		tableau de char contenant le type d'écran
 * @param		args			chaine de caractére	a mettre dans le fichier
 * return		void
**/
void writeInFileStat(char termSaver[2], char* args);


/**
 * Affiche un menu pour choisir les stats a afficher
 * @return	void
**/
void showStats();


/**
 * Recuperer les statistiques d'un fichier
 * @return	void
**/
void getContentStatFile();


/**
 * Associe chaque partie d'une ligne du fichier historique a un tableau 
 * @return void 
**/
void parseLine();


/**
 * Affiche les statistiques par date croissantes
 * @return	void
**/
void sortDateIncreasing();


/**
 * Affiche les statistiques par date décroissantes
 * @return	void
**/
void sortDateDecreasing();


/**
 * Affiche les statistiques par type 
 * @return	void
**/
void sortType();