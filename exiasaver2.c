#include "exiasaver2.h"


void chaine_h(char temps[8])	//prend un tableau de caractère qu'il remplis
{

	char m[3], s[3];	//tableaux de caractères permettant de stocker temporairement une chaine
	
	time_t t=time(NULL);
	struct tm tm=*localtime(&t);	//structure des données temporelles de la machine

	if(tm.tm_hour < 10)
	{
		sprintf(temps, "0%d", tm.tm_hour);
	}
	else
	{
		sprintf(temps, "%d", tm.tm_hour);
	}
	if(tm.tm_min < 10)
	{
		sprintf(m, ":0%d", tm.tm_min);
		strcat(temps, m);
	}
	else										//système rajoutant les ":" à l'heure
	{
		sprintf(m, ":%d", tm.tm_min);
		strcat(temps, m);
	}

	if(tm.tm_sec < 10)
	{
		sprintf(s, ":0%d", tm.tm_sec);
		strcat(temps, s);
	}
	else
	{
		sprintf(s, ":%d", tm.tm_sec);
		strcat(temps, s);
	}

}

void separateur(int tableau[3], int tab[6])	//prend un tableau de 3 ou il sépare les chiffres et un tableau de 6 qu'il remplis 
{
	int variable, dizaines, unites;

	for(int i = 0; i < 3; i++)	//boucle de 3 itérations (pour parcourir tableau)
	{
		variable = tableau[i];	//variable prend la valeur de la i-ème case du tableau

		dizaines = variable/10;	//récupération du chiffre des dizaines
		unites = variable%10;	//récupération du chiffre des unités

		switch(i)				//switch testant i
		{
			case 0:				//cas ou c'est la première case de tableau les chiffres vont dans les 2 premières cases de tab	
			tab[0] = dizaines;
			tab[1] = unites;
			break;
		
			case 1:				//cas ou c'est la seconde case de tableau les chiffres vont dans les 3è et 4è cases de tab
			tab[2] = dizaines;
			tab[3] = unites;
			break;
		
			case 2:				//cas ou c'est la troisième case de tableau les chiffres vont dans les 5è et 6è cases de tab
			tab[4] = dizaines;
			tab[5] = unites;
			break;
		}
	}
}			

void init(Chiffre *chiffres[])
{
	char valeur[15];
	Taille taille;

	Chiffre *zero;
	zero = malloc(sizeof(Chiffre));	
	zero->taille = taille;
	zero->image = "110101010101";//lirePBM("zero.pbm", &taille);

	chiffres[0] = zero;

	Chiffre *un;
	un = malloc(sizeof(Chiffre));	
	un->taille = taille;
	un->image = "0101010110";//lirePBM("un.pbm", &taille);

	chiffres[1] = un;

	Chiffre *deux;
	deux = malloc(sizeof(Chiffre));	
	deux->taille = taille;
	deux->image = "110111001";//lirePBM("deux.pbm", &taille);

	chiffres[2] = deux;

	Chiffre *trois;
	trois = malloc(sizeof(Chiffre));	
	trois->taille = taille;
	trois->image = "11010001";//lirePBM("trois.pbm", &taille);

	chiffres[3] = trois;

	Chiffre *quatre;
	quatre = malloc(sizeof(Chiffre));	
	quatre->taille = taille;
	quatre->image = "01010110";//lirePBM("quatre.pbm", &taille);

	chiffres[4] = quatre;

	Chiffre *cinq;
	cinq = malloc(sizeof(Chiffre));	
	cinq->taille = taille;
	cinq->image = "01001001";//lirePBM("cinq.pbm", &taille);

	chiffres[5] = cinq;

	Chiffre *six;
	six = malloc(sizeof(Chiffre));	
	six->taille = taille;
	six->image = "001010101";//lirePBM("six.pbm", &taille);

	chiffres[6] = six;

	Chiffre *sept;
	sept = malloc(sizeof(Chiffre));	
	sept->taille = taille;
	sept->image = "01010100";//lirePBM("sept.pbm", &taille);

	chiffres[7] = sept;

	Chiffre *huit;
	huit = malloc(sizeof(Chiffre));	
	huit->taille = taille;
	huit->image = "101010101";//lirePBM("huit.pbm", &taille);

	chiffres[8] = huit;

	Chiffre *neuf;
	neuf = malloc(sizeof(Chiffre));	
	neuf->taille = taille;
	neuf->image = "1001010110";//lirePBM("neuf.pbm", &taille);

	chiffres[9] = neuf;
}

void checker(char *place, int tester)
{
	switch(tester)								//test du chiffre du tableau recu et renvoi de la bonne chaine de caractère dans place
				{
					case 0:
					place = chiffres[0]->image;

					break;
					case 1:
					place = chiffres[1]->image;

					break;
					case 2:
					place = chiffres[2]->image;

					break;
					case 3:
					place = chiffres[3]->image;

					break;
					case 4:
					place = chiffres[4]->image;

					break;
					case 5:
					place = chiffres[5]->image;

					break;
					case 6:
					place = chiffres[6]->image;

					break;
					case 7:
					place = chiffres[7]->image;

					break;
					case 8:
					place = chiffres[8]->image;

					break;
					case 9:
					place = chiffres[9]->image;

					break;
				}
}