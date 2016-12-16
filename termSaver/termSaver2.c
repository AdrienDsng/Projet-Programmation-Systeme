#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "../utils.h"

/**
 * Permet d'initialiser les 10 images
**/
void init();

/**
 * Permet de récupérer l'heure de la machine sous forme de chaîne de caractère
 * @param str 	Chaîne de caractère dans laquelle on écrit l'heure
**/
void getTimeToString(char str[10]);

/**
 * Permet de réunir plusieurs chaînes de caractères en une
 * @param str 		Chaîne de caractère dans laquelle on écrit
 * @param heure		Heure sous forme de chaîne de caractère
**/
void reuniteNumber(char str[255], char heure[10]);

/**
 * Permet de dessiner
 * @param str Chaîne de caractère
**/
void draw(char str[255]);


char chiffres[10][1920];


int main(int argc, char* argv[]) {
	char heure[10];
	char strToShow[255];
	char point[60] = ".";
	int cpt = 0, n = 0;

	isDefEnv("EXIASAVER2_SLEEP", strToShow, "10");

	n = atoi(strToShow);
	cpt = n;

	init();

	while(1 == 1) {
		system("clear");
		
		if(cpt >= n) {
			getTimeToString(heure);
			reuniteNumber(strToShow, heure);
			cpt = 0;
			strcpy(point, ".");
		}

		draw(strToShow);

		printf("Cet écran sera actualisé dans quelquels secondes%s", point);
		strcat(point, ".");
		cpt++;

		fflush(stdout);

		sleep(1);
	}

	
	return 0;
}


void init() {
	char str[30];
	Taille taille;

	for(int i = 0; i < 10; i++) {
		sprintf(str, "termSaver/2/%d.pbm", i);
		lirePBM(str, chiffres[i], &taille);
	}

	system("clear");
}

void getTimeToString(char str[10]) {
	char tmp[100], buf[100];

	time_t t = time(NULL);
	struct tm heure = *localtime(&t);

	sprintf(tmp, "%d", heure.tm_hour);
	if(heure.tm_hour < 10) { strcpy(buf, tmp); strcpy(tmp, "0"); strcat(tmp, buf); }
	strcpy(str, tmp);

	strcat(str, ":");

	sprintf(tmp, "%d", heure.tm_min);
	if(heure.tm_min < 10) { strcpy(buf, tmp); strcpy(tmp, "0"); strcat(tmp, buf); }
	strcat(str, tmp);

	strcat(str, ":");

	sprintf(tmp, "%d", heure.tm_sec);
	if(heure.tm_sec < 10) { strcpy(buf, tmp); strcpy(tmp, "0"); strcat(tmp, buf); }
	strcat(str, tmp);
}

void reuniteNumber(char str[255], char heure[10]) {
	char buffer[255];
	char heureUn = heure[0], heureDeux = heure[1];
	char minUn = heure[3], minDeux = heure[4];
	char secUn = heure[6], secDeux = heure[7];
	int cpt = 0, cpt2, tmp;

	for(int j = 0; j < 5; j++) {
		tmp = heureUn - '0';					//Chiffre un des heures
		for(int i = 0; i < 3; i++) {
			cpt2 = i + j*4;
			buffer[cpt] = chiffres[tmp][cpt2];
			cpt++;
		}

		buffer[cpt] = '0';
		cpt++;

		tmp = heureDeux - '0';					//Chiffre deux des heures
		for(int i = 0; i < 3; i++) {
			cpt2 = i + j*4;
			buffer[cpt] = chiffres[tmp][cpt2];
			cpt++;
		}

		buffer[cpt] = '0';
		cpt++;

		if(j % 2 != 0) {						//Deux points
			buffer[cpt] = '0';
			cpt++;
			buffer[cpt] = '1';
			cpt++;
			buffer[cpt] = '0';
			cpt++;
		}
		else {
			for(int i = 0; i < 3; i++) {
				buffer[cpt] = '0';
				cpt++;
			}
		}

		buffer[cpt] = '0';
		cpt++;

		tmp = minUn - '0';						//Chiffre un des minutes
		for(int i = 0; i < 3; i++) {
			cpt2 = i + j*4;
			buffer[cpt] = chiffres[tmp][cpt2];
			cpt++;
		}

		buffer[cpt] = '0';
		cpt++;

		tmp = minDeux - '0';					//Chiffre deux des minutes
		for(int i = 0; i < 3; i++) {
			cpt2 = i + j*4;
			buffer[cpt] = chiffres[tmp][cpt2];
			cpt++;
		}

		buffer[cpt] = '0';
		cpt++;

		if(j % 2 != 0) {						//Deux points
			buffer[cpt] = '0';
			cpt++;
			buffer[cpt] = '1';
			cpt++;
			buffer[cpt] = '0';
			cpt++;
		}
		else {
			for(int i = 0; i < 3; i++) {
				buffer[cpt] = '0';
				cpt++;
			}
		}

		buffer[cpt] = '0';
		cpt++;

		tmp = secUn - '0';						//Chiffre un des secondes
		for(int i = 0; i < 3; i++) {
			cpt2 = i + j*4;
			buffer[cpt] = chiffres[tmp][cpt2];
			cpt++;
		}

		buffer[cpt] = '0';
		cpt++;

		tmp = secDeux - '0';					//Chiffre deux des secondes
		for(int i = 0; i < 3; i++) {
			cpt2 = i + j*4;
			buffer[cpt] = chiffres[tmp][cpt2];
			cpt++;
		}

		buffer[cpt] = '\n';
		cpt++;
	}


	strcpy(str, buffer);
}

void draw(char str[255]) {
	int cpt = 0;

	for(int i = 0; i < 255; i++) {
		if(str[i] == '\n') {
			cpt = i;
			break;
		}
	}

	for(int i = 0; i < (24 - 5) / 2; i++)
		printf("\n");
	for(int j = 0; j < (80 - cpt) / 2; j++)
		printf(" ");

	for(int i = 0; i < 255; i++) {
		if(str[i] == '1')
			printf("%s", "\u2588");
		else if(str[i] == '0')
			printf(" ");
		else if(str[i] == '\n') {
			printf("\n");

			for(int j = 0; j < (80 - cpt) / 2; j++)
				printf(" ");
		}
	}

	for(int i = 0; i < (24 - 5) / 2; i++)
		printf("\n");
}