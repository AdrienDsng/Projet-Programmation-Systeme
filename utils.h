/**
 * Permet de vérifier si une variable d'environnement existe
 * @param varEnvName 	Nom de la variable d'environnement à vérifier
 * @param str 			Variable dans laquelle on écrit la valeur de la variable d'environnement
 * @param defaultValue	Valeur par défaut si la variable d'environnement n'existe pas
 * @return int			Retourne 1 si la variable d'environnement existe, 0 si elle n'existe pas
**/
int isDefEnv(char* varEnvName, char* str, char* defaultValue);