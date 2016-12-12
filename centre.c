#include <sys/ioctl.h> 
#include <unistd.h> 
#include <stdio.h>
#include <math.h>
#include <string.h>

void center (char* image)
{
struct winsize w;
ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	int col = w.ws_col;
	int row =w.ws_row;
	
	int height = 2; 					//variable de hauteur de l'image
	int width = 5;						//variable de largeur de l'image 
	unsigned int i;
	unsigned int n;				

for (n = 0; n < (row - height)/2; n++)
	{
		putchar('\n');
	}
for (i = 0; i <(col - width)/2; i++)
	{
		putchar(' ');
	}
	printf ("%s", image);
for (n = 0; n < (row - height)/2; n++)
	{
		putchar('\n');
	}
}

int main ()
{
	center("test\n");
}
