#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void showStats();

int main(int argc, char* argv[]) {

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

	//Executer les termSaver

	return 0;
}

void showStats() {
	int choice;

	printf("Afficher par:\n");
	printf("1 - Date\n");
	printf("2 - Type\n");

	do {
		scanf("%d", &choice);
	} while(choice < 1 || choice > 2);

	switch(choice) {
		case 1:
			break;

		case 2:
			break;
	}

	system("clear");

	getContentStatFile();
}

char** getContentStatFile() {
	char* strBuf[20];
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
			strBuf[i] = strTmp;
			i++;
		}
		printf("\n");

		fclose(file);															//On ferme le fichier
	}
	else if(pid > 0) {															//Sinon si le nouveau processus est supérieur à 0
		wait(NULL);																//On attends la fin du processus fils
	}
}