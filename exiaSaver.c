#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <dirent.h>

#define SIZE_LOG 20

typedef struct
{
	struct tm dateTime;
	int screenSaver;
	char args[255];
} Statttt;

void showStats();
void getContentStatFile();
void verifyEnv();
int isDefEnv(char* varEnvName, char* str, char* defaultValue);
void writeInFileStat(time_t dateTime, int termSaver, char* args);


char strBuf[SIZE_LOG][70];
int sort = 10;
int *sortPtr = &sort;


int main(int argc, char* argv[]) {
	//verifyEnv();

	char dirHome[255];
	char strTmp[255];
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

	isDefEnv("EXIASAVER_HOME", dirHome, "./");

	random = rand() % 3;
	random = 0;

	if(random == 0) { //TermSaver static
		char dirPbm[255];
		isDefEnv("EXIASAVER1_PBM", dirPbm, "./");

		strcpy(strTmp, dirHome);
		if(strcmp(strTmp, dirPbm) != 0)
			strcat(strTmp, dirPbm);

		DIR* dir = opendir(strTmp);
		struct dirent* file;
		int count = 0;

		if(dir == NULL) {
			printf("An error occured while searching for the termSaver static file.\n");
			printf("Tried to open %s\n", strTmp);
			exit(1);
		}

		while((file = readdir(dir)) != NULL) {
			if(strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0)
				count++;
		}
		closedir(dir);

		random = rand() % count + 1;

		dir = opendir(strTmp);
		if(dir == NULL) {
			printf("An error occured while searching for the termSaver static file.\n");
			printf("Tried to open %s\n", strTmp);
			exit(1);
		}

		count = 0;
		while(count != random) {
			file = readdir(dir);
			if(strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0)
				count++;
		}
		closedir(dir);

		Statttt statttt;
		//time_t now ;
		time_t now;
		now = time(NULL);
		//memcpy(&(statttt.dateTime), localtime(&now), sizeof(struct tm));
		statttt.dateTime = *localtime(&now);

		char* arguments[] = {"termSaver1", file->d_name, NULL};

		strcpy(strTmp, dirHome);
		execv(strcat(strTmp, "termSaver1"), arguments);
	}
	else if(random == 1) { //TermSaver dynamic
		char* arguments[] = {"termSaver2", NULL};

		char strTmp[255];
		strcpy(strTmp, dirHome);
		execv(strcat(strTmp, "termSaver2"), arguments);
	}
	else if(random == 2) { //TermSaver interactif
		int x, y;
		char tmp[3];
		char pos[6];

		x = rand() % 80;
		y = rand() % 23;
		sprintf(pos, "%d", x);
		sprintf(tmp, "%d", y);

		strcat(pos, "x");
		strcat(pos, tmp);

		char* arguments[] = {"termSaver3", pos, NULL};

		char strTmp[255];
		strcpy(strTmp, dirHome);
		execv(strcat(strTmp, "termSaver3"), arguments);;
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

		file = fopen("historique", "r");										//On ouvre le fichier historique

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

int isDefEnv(char* varEnvName, char* str, char* defaultValue) {
	if(getenv(varEnvName) != NULL) {
		strcpy(str, getenv(varEnvName));

		return 1;
	}

	strcpy(str, defaultValue);

	return 0;
}

void verifyEnv() {
	/*char* env[20] = {{"EXIASAVER_HOME"}, {"EXIASAVER1_PBM"}, {"EXIASAVER2_PBM"}, {"EXIASAVER2_TAILLE"}, {"EXIASAVER2_SLEEP"}, {"EXIASAVER3_PBM"}};

	for(int i = 0; env[i] != NULL; i++) {
		printf("%s\n", env[i]);
	}*/
}