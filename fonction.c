
#include "fonction.h"
void retirerLesBlancs(char chaines[],char copy[])  
{
	int i = 0, l = 0, lg; 
	lg = strlen(chaines);	// on calcule la longeur de la chaine 
	while(i<lg)				// tant que on a pas atteint le dernier terme de la chaine on  écrit tout les caractéres qui ne sont pas des espaces.
	{
		if(chaines[i] !=  ' '  )  // cette boucle parcour la chaine et dés quelle rencontre un blanc elle le met dans une autre chaine
		{
			copy[l] = chaines[i];
			l++;
		}
		i++;
	}
	copy = '\0';				//on assimille tout les caractéres dans cette chaine a du vide on enlève donc tout les blancs
}

void lirePBM(char* nomDuFichier, char* chaine, Taille *taille)
{
	FILE* file; 				
	char strTmp[70];
	char* token;
	int x = 0, y = 0, lg = 0;
	file = fopen(nomDuFichier, "r"); //on ouvre le fichier demander
	
	int height = 0;
	int width = 0;
	

	if (file == NULL)				//on verifie si on arrive a lire le fichier 
	{
		printf("Erreur de lecture du fichier %s", nomDuFichier);
		exit(1);
	} 


	fgets(strTmp, 70, file); // lecture du nombre magique 
	fgets(strTmp, 70, file); //ligne de commentaire
	fgets(strTmp, 70, file); // taille de l'image 


	token = strtok(strTmp, " \n");// on récupére la premiere taille le nombre de ligne
	width = atoi(token)  ;		//on met la taille dans un int en utilisant une fonction transformant un char en int 
	token = strtok(NULL, " \n");// on récupére la deuxieme taille 
	height = atoi(token)  ;			//on met la taille dans un int  (même procédés qu'aux dessus)
		
	char copy[1920];
	char copie[1920];
	while (fgets(copie, 70, file) != NULL)	//on lit l'intégralité de ce qui reste du fichier 
	{		
			if ( x < 1)						//on remplace une fois la chaine en paramétre par la chaine lu 
			{
				strcpy(chaine,copy);		
				retirerLesBlancs(copie,copy);//on enléve les blancs dans cette chaîne 
				x++;
			}
			else
			{			
			strcat(chaine,copy);           	//ensuite on fusionne la chaine de caractére lu avec la chaine de caractére en paramétre 
			retirerLesBlancs(copie,copy);	//on enléve les blancs dans cette chaîne
			}		
	}
	fclose(file);
	
	taille->width = width; 				// on donne a la structure la valeur de la taille lu
	taille->height = height;			// on donne a la structure la valeur de la taille lu	
}


void affPBM(char* chaine)
{

	//FILE* chaines;

	int charTmp = 0;
	int i, j = 0, k = 0;

	
	charTmp = strlen(chaine);		// on calcule la taille de la chaine 
	for (i = 0;i != charTmp ;i++)	// on parcour la chaine grace a sa taille 
	{
		
		if (chaine[i] == '1')
		{						      
			chaine[i] = 36;// on remplace les caractéres 1 par le caractére ascii 36
		}
		if (chaine[i] == '\n')
		{
			chaine[i] = '\n' ;		// on modifie pas les caractéres \n 
		}
		if (chaine[i] == '0')
		{	
			chaine[i] = 32;// on remplace les caractéres 0 par le caractére ascii 32
		} 
	}

}


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


