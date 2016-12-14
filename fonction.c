
#include "fonction.h"
void retirerLesBlancs(char* chaines)  
{
	char copy[1920];
	char* token = NULL;
	token = strtok(chaines," ");
	strcpy(copy,token);
	
	while (token != NULL)
	{
	
		
		strcat(copy,token);
		token = strtok(NULL," ");
					
		
		

	}
	
	strcpy(chaines,copy);				//on assimille tout les caractéres dans cette chaine a du vide on enlève donc tout les blancs
}

 char* lirePBM(char* nomDuFichier, Taille *taille)
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
	char image [height*width + height];	
	char copie[height*width + height];
	int nbc = height*width + height;
	char* im = NULL;
	im = malloc(nbc*sizeof(char));

	while (fgets(copie, 70, file) != NULL)	//on lit l'intégralité de ce qui reste du fichier 
	{		
			if ( x < 1)						//on remplace une fois la chaine en paramétre par la chaine lu 
			{
				//printf("%s",copie);	
				retirerLesBlancs(copie);//on enléve les blancs dans cette chaîne
				//printf("%s",copie);
				strcpy(image,copie);
				//printf("%s",image); 
				
				x++;
			}
			else
			{		
			
				retirerLesBlancs(copie);	//on enléve les blancs dans cette chaîne
				//printf("%s",copie);
				strcat(image,copie);           	//ensuite on fusionne la chaine de caractére lu avec la chaine de caractére en paramétre 
				//printf("%s",image);
			}		
	}

	fclose(file);
	strcpy(im,image);
	taille->width = width; 				// on donne a la structure la valeur de la taille lu
	taille->height = height;			// on donne a la structure la valeur de la taille lu
	
	

	return im;
	free(im);
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

    for (int i = 1; i < strlen(text); i++)
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


