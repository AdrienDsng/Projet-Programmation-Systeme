#include "lirePBM.h"

int main(int argc, char* argv[])
 {	
 	if (argc < 2) // on check si on a bien plus de 1 argument
 	{
 		printf("argument manquant");
 		exit(1);
 	}
 	char* nomDuFichier = argv[1];  //on assimile le 2éme argument au nom du fichier 	
 	Taille *taille;	
	taille = malloc(sizeof(Taille*)); // on alloue de la mémoire pour notre structure
	char image[1920];
	pid_t pid;
	pid = fork();

	if (pid == -1)
	{
		printf("Erreur 404");		//Erreur due au pid 
	}
	if(pid == 0)					//on passe en processus fils 
	{
		lirePBM(nomDuFichier, image, taille); // on utilise la fonction lirePBM on aura donc la lecture du nomdufichier en paramétre 				
	}
	if(pid<0) 						// on retourne en processus pére
	{
		wait(NULL);
		affPBM(image); 					 // transforme les caractéres binaire en caractére ascii
		center(image,taille);	 		// on utilise la fonction center pour centrer l'image 
		free(taille); 	
	}
					//on libére la mémoire de la structure
 	initscr();						//on initialise le mode curse pour pouvoir utiliser la fonction qui nous sera utile	
	getchar();						//fonction qui attend que l'utilisateur appuie sur une touche	
	endwin();						// on quitte le mode curse
	
	return 0;
}
