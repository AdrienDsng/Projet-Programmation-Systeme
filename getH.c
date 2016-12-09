#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

void main()
{
	pid_t f;
	int i;
	int j;
	int n = 5;
	char actualisation[80] = "Cet écran sera actualisé dans quelques secondes";

	char n_secondes[59];

	time_t t=time(NULL);
	struct tm tm=*localtime(&t);	//structure des données temporelles de la machine

	if(tm.tm_sec < 10)
	{
		printf("il est %d:%d:0%d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
	}
	else
	{
		printf("il est %d:%d:%d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
	}
	
	/*for(i = 0; i < 5; i++)
	{
		f=fork();
	} 

	if(f = 0)	//processus fils (5)
	{

	}
	else
	{
		wait(&f);


			//récup structures de fichiers
			//mettre à la suite et afficher l'heure*/

	//n_secondes = getenv(SCREENSAVER2_N);

	//int n = n_secondes - '0';
	
	for(j; j < n; j++) 
	{ 
		strcat(actualisation, "."); 

		printf("%s", actualisation);

		fflush(stdout); 

		printf("\x0d");

		sleep(1); 


	}	
	printf("\n");
	//}
}