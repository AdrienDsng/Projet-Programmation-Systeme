#include "stat.h"

void toStringStat(Stat stat, char str[255]) {
	char tmp[5];

	toStringDateTime(stat, str);

	strcat(str, ";");
	sprintf(tmp, "%d", stat.screenSaver);
	strcat(str, tmp);
	strcat(str, ";");
	strcat(str, stat.args);
}

void toStringDateTime(Stat stat, char str[255]) {
	char buf[255];
	char numtmp[255];

	sprintf(buf, "%d", stat.dateTime.tm_mday); //Ajout jour
	strcpy(str, buf);

	strcat(str, "/");

	sprintf(buf, "%d", stat.dateTime.tm_mon); //Ajout mois
	strcat(str, buf);

	strcat(str, "/");

	sprintf(buf, "%d", stat.dateTime.tm_year); //Ajout année
	strcat(str, buf);

	strcat(str, " ");

	sprintf(buf, "%d", stat.dateTime.tm_hour); //Ajout hour
	if(stat.dateTime.tm_hour < 10) { strcpy(numtmp, buf); strcpy(buf, "0"); strcat(buf, numtmp); }
	strcat(str, buf);

	strcat(str, ":");

	sprintf(buf, "%d", stat.dateTime.tm_min); //Ajout min
	if(stat.dateTime.tm_min < 10) { strcpy(numtmp, buf); strcpy(buf, "0"); strcat(buf, numtmp); }
	strcat(str, buf);

	strcat(str, ":");

	sprintf(buf, "%d", stat.dateTime.tm_sec); //Ajout seconde
	if(stat.dateTime.tm_sec < 10) { strcpy(numtmp, buf); strcpy(buf, "0"); strcat(buf, numtmp); }
	strcat(str, buf);
}

void writeInFileStat(char termSaver[2], char* args) {
	Stat stat;
	char line[255];
	FILE* file;

	time_t now = time(NULL);
	printf("%d\n", (int)now);
	system("clear");
	stat.dateTime = *localtime(&now);
	stat.dateTime.tm_year += 1900;
	stat.screenSaver = atoi(termSaver);
	strcpy(stat.args, args);

	toStringStat(stat, line);

	file = fopen("historique", "a");
	if(file == NULL) {
		printf("An error occured while opening the file \"historique\"\n");
		exit(0);
	}

	fprintf(file, "%s\n", line);
	fclose(file);
}

void showStats() {
	int choice;

	printf("Afficher par:\n");
	printf("1 - Date croissante\n");
	printf("2 - Date décroissante\n");
	printf("3 - Type\n");
	printf("\n");

	do {
		scanf("%d", &choice);
	} while(choice < 1 || choice > 3);

	system("clear");

	getContentStatFile();

	switch(choice) {
		case 1:
			sortDateIncreasing();
			break;

		case 2:
			sortDateDecreasing();
			break;

		case 3:
			sortType();
			break;
	}
}

void getContentStatFile() {
	char strTmp[70];
	int i = 0;

	pid_t pid = fork();															//Création processus fils pour lire fichier

	if(pid == 0) {																//Si le nouveau processus est le processus fils
		FILE *file;

		file = fopen("historique", "r");										//On ouvre le fichier historique

		if(file == NULL) {														//On vérifie que le fichier s'est bien ouvert
			printf("An errror occured while opening the statistic file\n");
			exit(1);
		}

		while(fgets(strTmp, 70, file) != NULL) {								//On lit le fichier jusqu'à la fin
			strcpy(strBuf[i], strTmp);
			i++;
		}
		printf("\n");

		fclose(file);															//On ferme le fichier
	}
	else if(pid > 0) {															//Sinon si le nouveau processus est supérieur à 0
		wait(NULL);																//On attends la fin du processus fils
	}
}

void parseLine() {
	char* str;

	for(int i = 0; i < SIZE_LOG; i++) {
		if(strcmp(strBuf[i], "") != 0) {
			str = strtok(strBuf[i], "/"); //Jour
			buf[i].dateTime.tm_mday = atoi(str);

			str = strtok(NULL, "/"); //Mois
			buf[i].dateTime.tm_mon = atoi(str);

			str = strtok(NULL, " "); //Année
			buf[i].dateTime.tm_year = atoi(str);

			str = strtok(NULL, ":"); //Heure
			buf[i].dateTime.tm_hour = atoi(str);

			str = strtok(NULL, ":"); //Minute
			buf[i].dateTime.tm_min = atoi(str);

			str = strtok(NULL, ";"); //Seconde
			buf[i].dateTime.tm_sec = atoi(str);

			str = strtok(NULL, ";"); //Type
			buf[i].screenSaver = atoi(str);

			str = strtok(NULL, "");
			strcpy(buf[i].args, str);
		}
	}
}

void sortDateIncreasing() {
	char str[255];

	parseLine();

	for(int i = 0; i < SIZE_LOG; i++) {
		if(strcmp(buf[i].args, "") != 0) {
			toStringStat(buf[i], str);
			printf("%s", str);
		}
	}
}

void sortDateDecreasing() {
	char str[255];

	parseLine();

	for(int i = 0; i < SIZE_LOG; i++) {
		if(strcmp(buf[SIZE_LOG - i].args, "") != 0) {
			toStringStat(buf[SIZE_LOG - i], str);
			printf("%s", str);
		}
	}
}

void sortType() { //TODO Improve sort with args
	Stat tmp;
	char str[255];

	parseLine();

	for(int i = 0; i < SIZE_LOG; i++) {
		for(int j = 0; j < i - 1; j++) {
			if(buf[j+1].screenSaver < buf[j].screenSaver) {
				tmp = buf[j];
				buf[j] = buf[j+1];
				buf[j+1] = tmp;
			}
		}
	}

	for(int i = 0; i < SIZE_LOG; i++) {
		if(strcmp(buf[i].args, "") != 0) {
			toStringStat(buf[i], str);
			printf("%s", str);
		}
	}
}