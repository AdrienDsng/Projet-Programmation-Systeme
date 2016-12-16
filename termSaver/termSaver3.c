#include <stdio.h>
#include <stdlib.h>
#include "../utils.h"
#include <unistd.h>
#include <sys/wait.h>
#include <ncurses.h>
#include <termios.h>
#include <fcntl.h>

/**
 * Structure représentant des coordonnées
**/
typedef struct {
	int x, y;	/**< Coordonnées x et y */
} Pos;

/**
 * Structure représentant un pixel avec ses coordonnées
**/
typedef struct {
	Pos pos;			/**< Position du pixel */
	unsigned int on;	/**< 1 si allumé, 0 si éteint */
} Pixel;


Pixel avionUp[36];
Pixel avionDown[36];
Pixel avionLeft[36];
Pixel avionRight[36];


/**
 * Permet d'initialiser les images de l'avion
**/
void init();

/**
 * Transformer une chaîne de caractère en structure
 * @param str 		Chaîne de caractère à mettre en structure
 * @param pixels 	Structure dans laquelle on écrit
**/
void stringToPixel(char* str, Pixel* pixels);

/**
 * Transferer une structure dans une autre
 * @param actual 	Structure dans laquelle on écrit
 * @param new 		Stucture copié
**/
void setActualPlane(Pixel *actual, Pixel *new);
void checkCollission(Pixel *plane);
void renderPlane(Pixel *plane);
int kbhit();


int main(int argc, char* argv[]) {
	Pos startPos;
	char* str;
	Pixel actualPlane[36];
	pid_t pid;
	int running = 1;
	int descPipe[2];

	/************************/
	struct termios old_tio, new_tio;
	unsigned char c;

	tcgetattr(STDIN_FILENO, &old_tio);
	new_tio = old_tio;
	new_tio.c_lflag &= (~ICANON & ~ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

	/************************/


	system("clear");

	if(argc < 2) {
		printf("Error: Argument missing\n");
		exit(1);
	}

	//Start Position
	str = strtok(argv[1], "x");
	startPos.x = atoi(str);
	str = strtok(NULL, "");
	startPos.y = atoi(str);

	//Init actual plane
	int x = startPos.x, y = startPos.y;
	for(int i = 0; i < 36; i++) {
		x++;
		if(i % 6 == 0) {
			x = startPos.x;
			y++;
		}

		actualPlane[i].pos.x = x;
		actualPlane[i].pos.y = y;
		actualPlane[i].on = 0;
	}

	init();
	setActualPlane(actualPlane, avionRight);

	printf("Bonjour StarScream\n\n");
	printf("Bienvenue dans l'écran de veille interactif\n\n");
	printf("Appuyer sur n'importe quelle touche pour commencer");

	char dir;
	pipe(descPipe);
	pid = fork();

	while(running) {
		if(pid > 0) { //Père
			if(kbhit()) {
				dir = getchar();
				write(descPipe[1], &dir, sizeof(dir));
			}

			if(dir == 'q')
				running = 0;
		}
		else if(pid == 0) { // Fils
			read(descPipe[0], &dir, sizeof(dir));

			if(dir == 'h') {
				setActualPlane(actualPlane, avionUp);
				for(int i = 0; i < 36; i++)
					actualPlane[i].pos.y -= 1;
			}
			else if(dir == 'b') {
				setActualPlane(actualPlane, avionDown);
				for(int i = 0; i < 36; i++)
					actualPlane[i].pos.y += 1;
			}
			else if(dir == 'g') {
				setActualPlane(actualPlane, avionLeft);
				for(int i = 0; i < 36; i++)
					actualPlane[i].pos.x -= 1;
			}
			else if(dir == 'd') {
				setActualPlane(actualPlane, avionRight);
				for(int i = 0; i < 36; i++)
					actualPlane[i].pos.x += 1;
			}
			else if(dir == 'q') {
				running = 0;
			}

			checkCollission(actualPlane);

			renderPlane(actualPlane);

			wait(NULL);
		}
		else if(pid == -1) {
			printf("Oups! An error occured while creating a new processus\n");
			exit(1);
		}
	}

	close(descPipe[0]);
	close(descPipe[1]);

	tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

	return 0;
}

void init() {
	char up[1920];
	char down[1920];
	char left[1920];
	char right[1920];
	Taille taille;

	lirePBM("termSaver/3/up.pbm", up, &taille);
	lirePBM("termSaver/3/down.pbm", down, &taille);
	lirePBM("termSaver/3/left.pbm", left, &taille);
	lirePBM("termSaver/3/right.pbm", right, &taille);

	stringToPixel(up, avionUp);
	stringToPixel(down, avionDown);
	stringToPixel(left, avionLeft);
	stringToPixel(right, avionRight);
}

void stringToPixel(char* str, Pixel *pixels) {
	int x = 0, y = 0, cpt = 0;

	for(int i = 0; i < strlen(str); i++) {
		if(str[i] != '\n') {
			pixels[cpt].on = str[i] - '0';
			pixels[cpt].pos.x = x;
			pixels[cpt].pos.y = y;
			x++;
			cpt++;
		}
		else {
			y++;
			x = 0;
		}
	}
}

void setActualPlane(Pixel *actual, Pixel *new) {
	for(int i = 0; i < 36; i++) {
		actual[i].on = new[i].on;
	}
}

void checkCollission(Pixel *plane) {
	for(int i = 0; i < 36; i++) {
		if(plane[i].pos.x >= 80)
			plane[i].pos.x = 0;
		else if(plane[i].pos.x <= 0)
			plane[i].pos.x = 80;

		if(plane[i].pos.y >= 23)
			plane[i].pos.y = 0;
		else if(plane[i].pos.y <= 0)
			plane[i].pos.y = 23;
	}
}

void renderPlane(Pixel *plane) {
	system("clear");

	for(int i = 0; i < plane[0].pos.y; i++)
		printf("\n");

	for(int i = 0; i < 36; i++) {
		if(i % 6 == 0){
			printf("\n");
			for(int j = 0; j < plane[i].pos.x; j++)
				putchar(' ');
		}

		if(plane[i].on == 1)
			printf("%s", "\u2588");
		else
			printf(" ");
	}

	for(int i = 0; i < 23 - plane[30].pos.y; i++)
		printf("\n");
}

int kbhit() {
 	struct termios oldt, newt;
	int ch;
	int oldf;

  	tcgetattr(STDIN_FILENO, &oldt);
 	
 	newt = oldt;
 	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

 	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF) {
		ungetc(ch, stdin);

		return 1;
	}

  return 0;
}