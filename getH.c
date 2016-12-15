#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "exiasaver2.h"

void main()
{
	int i = 0;	//i et j compteurs
	int j = 0;
	int z = 0;
	int c=0, m=0, n=0, l=0, k=0, p=0, o=0, u=0;
	char actualisation[80] = "Cet écran sera actualisé dans quelques secondes";	//chaine de caractères à afficher en dessous de l'écran de veille
	char *varEnvN, *varEnvTaille;
	char *token;	//chaine de caractère permettant de stocker une chaine découpée
	int tableau[3];	//tableau de char à 3 cases 
	int tab[6];
	char chaine[8];
	char *dizaineH, *uniteH, *dizaineM, *uniteM, *dizaineS, *uniteS, *points, *affichage, *affichageResized;
	Chiffre* chiffres[10];

	//init(chiffres);

	points = "101011";//lirePBM("points.pbm", NULL);

	while (1)	//boucle infinie
	{
		chaine_h(chaine);
		
		/*token = strtok(chaine, ":");	//coupe de la chaine au caractère ":" et passage du morceau dans token
		
		
		for(i = 0; i < 3; i++)		//parcours à travers les autres morceaux et implémentations dans le tableau
		{

			tableau[i] = atoi(token);


			token = strtok(NULL, ":");

		}*/
		
		//separateur(tableau, tab);	//separation des int 2 par 2 de façon mathématique



				checker(dizaineH, tab[0]);	//placement de l'image du premier caractère dans une chaine de caractère prête à l'emplois

				checker(uniteH, tab[1]);	//de même pour les autres int du tableau

				checker(dizaineM, tab[2]);
	
				checker(uniteM, tab[3]);
	
				checker(dizaineS, tab[4]);

				checker(uniteS, tab[5]);

				free(Chiffre.chiffres[0]);
			
		
		
		for(c; c < strlen(dizaineH); c++)
		{
			if(&dizaineH[c] == "1")
			{
				strcat(affichage, "1");
			}
			else if(&dizaineH[c] == "0")
			{
				strcat(affichage, "0");
			}
			else
			{
				for(m ; m < strlen(uniteH);m++)
				{
					if(&uniteH[m] == "1")
					{
						strcat(affichage, "1");
					}
					else if(&uniteH[m] == "0")
					{
						strcat(affichage, "0");
					}
					else
					{
						for(n; n < strlen(points); n++)
						{
							if(&points[n] == "1")
							{
								strcat(affichage, "1");
							}
							else if(&points[n] == "0")
							{
								strcat(affichage, "0");
							}
							else
							{
								for(l; l < strlen(dizaineM); l++)
								{
									if(&dizaineM[l] == "1")
									{
										strcat(affichage, "1");
									}
									else if(&dizaineM[l] == "0")
									{
										strcat(affichage, "0");
									}
									else
									{
										for(k; k < strlen(uniteM); k++)
										{
											if(&uniteM[k] == "1")
											{
												strcat(affichage, "1");
											}
											else if(&uniteM[k] == "0")
											{
												strcat(affichage, "0");
											}
											else
											{
												for(p; p < strlen(points); p++)
												{
													if(&points[p] == "1")
													{
														strcat(affichage, "1");
													}
													else if(&points[p] == "0")
													{
														strcat(affichage, "0");
													}
													else
													{
														for(o; o < strlen(dizaineS); o++)
														{
															if(&dizaineS[o] == "1")
															{
																strcat(affichage, "1");
															}
															else if(&dizaineS[o] == "0")
															{
																strcat(affichage, "0");
															}
															else
															{
																for(u; u < strlen(uniteS); u++)
																{
																	if(&uniteS[u] == "1")
																	{
																		strcat(affichage, "1");
																	}
																	else if(&uniteS[u] == "0")
																	{
																		strcat(affichage, "0");
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		//affPBM(affichage);

		//center(affichage, NULL);
		// isDefEnv("EXIASAVER2_TAILLE", varEnvTaille, "5x3");

		// if(strcmp(varEnvTaille, "5x3") == 0)
		// {
		// 	center(affichage, NULL);
		// }
		// else
		// {
		// 	expand(affichage, affichageResized);

		// 	center(affichageResized, NULL);
		// }

		

		//isDefEnv("EXIASAVER2_SLEEP", varEnvN, "10");
		
		/*for(j; j < n; j++) 
		{ 
			strcat(actualisation, "."); 	//concaténation chaine de text et les "."

			printf("%s", actualisation);

			fflush(stdout); 	//déchargement du buffer pour forcer le printf

			printf("\x0d");		//retour au début de la ligne (permet de réécrire par dessus)

			sleep(1); 


		}*/
		
	}
}