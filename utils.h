/**
 * Permet de vérifier si une variable d'environnement existe
 * @param varEnvName 	Nom de la variable d'environnement à vérifier
 * @param str 			Variable dans laquelle on écrit la valeur de la variable d'environnement
 * @param defaultValue	Valeur par défaut si la variable d'environnement n'existe pas
 * @return int			Retourne 1 si la variable d'environnement existe, 0 si elle n'existe pas
**/
int isDefEnv(char* varEnvName, char* str, char* defaultValue);
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

void  lirePBM(char* nomDuFichier, char* chaine,Taille *taille);
  
/**
*permet de retirer les espaces dans une chaîne 
*@param chaines 	phrase ou chaine de caractère
*@param copy 		chaine de caractére où on met les caractéres a modifier(ici les espaces)
*@return void 
**/

void retirerLesBlancs(char chaines[],char copy[]);

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
