#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE_LOG 300

typedef struct
{
	struct tm dateTime;
	int screenSaver;
	char args[255];
} Stat;

char strBuf[SIZE_LOG][70];
Stat buf[SIZE_LOG];


void toStringStat(Stat stat, char str[255]);
void toStringDateTime(Stat stat, char str[255]);
void writeInFileStat(char termSaver[2], char* args);
void showStats();
void showAdvancedStat();
void getContentStatFile();

void parseLine();
void sortDateIncreasing();
void sortDateDecreasing();
void sortType();