
#include "lirePBM.h"
void retirerLesBlancs(char chaines[],char copy[])  
{
	int i = 0, l = 0, lg; 
	lg = strlen(chaines);	// on calcule la longeur de la chaine 
	while(i<lg)				// tant que on a pas atteint le dernier terme de la chaine on  écrit tout les caractéres qui ne sont pas des espaces.
	{
		if(chaines[i] !=  ' '  )  // cet boucle parcour la chaine et dés quelle rencontre un blanc elle le met dans une autre chaine
		{
			copy[l] = chaines[i];
			l++;
		}
		i++;
	}
	copy = '\0';				//on assimille tout les caractéres dans cette chaine a du vide on enléve donc tout les blancs
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
	//char* ker;

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
	while (fgets(copie, 70,file) != NULL)	//on lit l'intégralité de ce qui reste du fichier 
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
	
	taille->width = width; 				// on donne a la structure la valeur de la taille lu
	taille->height = height;			// on donne a la structure la valeur de la taille lu	
}
char* affPBM(char* chaine)
{

	FILE* chaines;

	int charTmp = 0;
	int i, j = 0, k = 0;

	
	charTmp = strlen(chaine);		// on calcule la taille de la chaine 
	for (i = 0;i != charTmp ;i++)	// on parcour la chaine grace a sa taille 
	{
		
		if (chaine[i] == '1')
		{
			//printf("%c",36);       // on remplace les caractéres 1 par le caractére ascii 36
			chaine[i] = 36;
		}
		if (chaine[i] == '\n')
		{
			chaine[i] = '\n' ;		// on modifie pas les caractéres \n 
		}
		if (chaine[i] == '0')
		{
			//printf("%c",32);	// on remplace les caractéres 0 par le caractére ascii 32
			chaine[i] = 32;
		} 
	}
}

	


void center (char* text, Taille* taille)
{
    struct winsize w;								//on appele une structure dans une librairie ainsi que des variable permettant d'avoir la taille de la console 
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int col = w.ws_col;
    int row = w.ws_row;

    int height = taille->width ;                     //variable de hauteur de l'image
    int width = taille->height;                        //variable de largeur de l'image 
    unsigned int i = 0;
    unsigned int n;
    unsigned int x;

    system("clear");

    for (n = 0; n < (row - height)/2; n++)			// on rajoute des blancs entre la différences de taille de la console et de l'image le tout diviser par deux (ici en haut)
    {
        putchar('\n');
    }

    for (int j = 0; j < (col - width) / 2; j++)   
    {
        putchar(' ');
    }

    for (int i = 0; i < strlen(text); i++)
    {
        printf("%c", text[i]);
        if(text[i] == '\n')
        {
            for (int j = 0; j < (col - width) / 2; j++) 
            	{
              	  putchar(' ');
           		}
        }
    }
    printf("\n");
    for (n = 0; n < (row - height)/2; n++)
    {
        putchar('\n');
    }
}


