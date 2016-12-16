#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <dirent.h>
#include "stat.h"
#include "utils.h"


void verifyEnv();


int main(int argc, char* argv[]) {
	//verifyEnv();

	char dirHome[255];
	char strTmp[255];
	unsigned int random;
	srand(time(NULL));

	system("clear");

	if(argc == 2) { 																	//Si le programme a été appelé avec une option
		if(strcmp(argv[1], "-stat") == 0) {											//Si l'option est égale à "-stat"
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

		writeInFileStat("1", file->d_name);

		char* arguments[] = {"termSaver1", file->d_name, NULL};

		strcpy(strTmp, dirHome);
		execv(strcat(strTmp, "termSaver1"), arguments);
	}
	else if(random == 1) { //TermSaver dynamic
		char str[6];
		isDefEnv("EXIASAVER2_TAILLE", str, "5x3");

		writeInFileStat("2", str);

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

		writeInFileStat("3", pos);

		char* arguments[] = {"termSaver3", pos, NULL};

		char strTmp[255];
		strcpy(strTmp, dirHome);
		execv(strcat(strTmp, "termSaver3"), arguments);;
	}

	return 0;
}

void verifyEnv() {
	/*char* env[20] = {{"EXIASAVER_HOME"}, {"EXIASAVER1_PBM"}, {"EXIASAVER2_PBM"}, {"EXIASAVER2_TAILLE"}, {"EXIASAVER2_SLEEP"}, {"EXIASAVER3_PBM"}};

	for(int i = 0; env[i] != NULL; i++) {
		printf("%s\n", env[i]);
	}*/
}