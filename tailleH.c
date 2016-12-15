#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char *text = "0101\n1100\n"; 
	char buffer[2*strlen(text)];
	int bufPos = 0;
	int n = 0;	

	for (int i = 0; i < strlen(text); i++) //parcourt la chaine de caractère
	{
		if (text[i] == '1') //si le caractère rencontre un 1 il en ajoute deux dans la chaine buffer
		{
			buffer[bufPos] = '1'; //met un 1 dans la chaine buffer à la position de bufPos
			buffer[bufPos+1] = '1'; //même principe mais à la position bufPos+1
			bufPos = bufPos+2;
		}
		else if (text[i] == '0') //même principe que le if précédent mais avec les 0
		{
			buffer[bufPos] = '0';
			buffer[bufPos+1] = '0';
			bufPos = bufPos+2;
		}
		else if (text[i] == '\n') //si le caractère rencontré est un \n incrément n
		{
			n++; 
		}
	}

	int tmp = strlen(buffer) / n; 
	char bufferN[strlen(buffer)+8]; //chaine de caractère faisant 8 caractères de plus que la chaine buffer

	for(int j = 0; j < strlen(buffer); j++) //permet d'ajouter le bon nombre de \n à la fin de chaque ligne
	{
		bufferN[j] = buffer[j]; 
		if (j % tmp == 0)
		{
			buffer[j] = '\n'; 
		}
	}

	strcat (buffer, buffer); //permet de copier la chaine buffer
	printf ("%s", buffer); //afficher la chaine de caractère
}
