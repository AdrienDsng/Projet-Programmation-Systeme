#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <dirent.h>

#define SIZE_LOG 20

void showStats();
void getContentStatFile();
void verifyEnv();
void writeInFileStat(time_t dateTime, int termSaver, char* args);


char strBuf[SIZE_LOG][70];
int sort = 10;
int *sortPtr = &sort;


int main(int argc, char* argv[]) {
	//verifyEnv();

	char* dirHome;
	unsigned int random;
	srand(time(NULL));

	system("clear");

	if(argc == 2) { 																	//Si le programme a été appelé avec une option
		if(strcmp(argv[1], "-stats") == 0) {											//Si l'option est égale à "-stat"
			showStats();

			return 0;
		}
		else {																			//Sinon on affiche un message d'erreur comme quoi l'option n'existe pas
			printf("Param %s doesn't exist\n", argv[1]);
			return 0;
		}
	}

	/*if(getenv("EXIASAVER_HOME") != NULL)
		strcpy(dirHome, getenv("EXIASAVER_HOME"));
	else
		strcpy(dirHome, ".");*/

	random = rand() % 3;
	random = 0;

	if(random == 0) { //TermSaver static
		DIR* dir = opendir("termSaver/1");
		struct dirent* file;
		int count = 0;

		if(dir == NULL) {
			printf("An error occured while searching for the termSaver static\n");
			printf("Tried to open %s", "dir");
			exit(1);
		}

		while((file = readdir(dir)) != NULL) {
			if(strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0)
				count++;
		}
		closedir(dir);

		random = rand() % count + 1;

		dir = opendir("termSaver/1");
		if(dir == NULL) {
			printf("An error occured while searching for the termSaver static\n");
			printf("Tried to open %s\n", "dir");
			exit(1);
		}

		count = 0;
		while(count != random) {
			file = readdir(dir);
			if(strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0)
				count++;
		}
		closedir(dir);

		char* arguments[] = {"termSaver/termSaver1", file->d_name, NULL};

		execv("termSaver/termSaver1", arguments);
	}
	else if(random == 1) { //TermSaver dynamic
		char* arguments[] = {strcat(dirHome, "termSaver2"), NULL};

		execv("termSaver2", arguments);
	}
	else if(random == 2) { //TermSaver interactif
		char* arguments[] = {strcat(dirHome, "termSaver3"), "20x20", NULL};

		execv("termSaver3", arguments);;
	}

	return 0;
}

void showStats() {
	int choice;

	printf("Afficher par:\n");
	printf("1 - Date\n");
	printf("2 - Type\n");
	printf("3 - Nom\n");

	do {
		scanf("%d", &choice);
	} while(choice < 1 || choice > 3);

	system("clear");

	*sortPtr = choice;

	getContentStatFile();

	//Afficher les logs
	for(int i = 0; i < SIZE_LOG; i++)
		printf("%s", strBuf[i]);
	printf("\n");
}

void getContentStatFile() {
	printf("%d\n", *sortPtr);
	char strTmp[70];
	int i = 0;

	pid_t pid = fork();															//Création processus fils pour lire fichier

	if(pid == 0) {																//Si le nouveau processus est le processus fils
		FILE *file;

		file = fopen("log", "r");												//On ouvre le fichier log

		if(file == NULL) {														//On vérifie que le fichier c'est bien ouvert
			printf("An errror occured while opening the statistic file\n");
			exit(1);
		}

		while(fgets(strTmp, 70, file) != NULL) {								//On lit le fichier jusqu'à la fin
			strcpy(strBuf[i], strTmp);

			i++;
			if(i >= SIZE_LOG) {
				break;
			}
		}
		printf("\n");

		fclose(file);															//On ferme le fichier
	}
	else if(pid > 0) {															//Sinon si le nouveau processus est supérieur à 0
		wait(NULL);																//On attends la fin du processus fils
	}
}

void verifyEnv() {
	/*char* env[20] = {{"EXIASAVER_HOME"}, {"EXIASAVER1_PBM"}, {"EXIASAVER2_PBM"}, {"EXIASAVER2_TAILLE"}, {"EXIASAVER2_SLEEP"}, {"EXIASAVER3_PBM"}};

	for(int i = 0; env[i] != NULL; i++) {
		printf("%s\n", env[i]);
	}*/
}