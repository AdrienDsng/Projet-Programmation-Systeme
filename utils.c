#include "utils.h"

int isDefEnv(char* varEnvName, char* str, char* defaultValue) {
	if(getenv(varEnvName) != NULL) {
		strcpy(str, getenv(varEnvName));

		return 1;
	}

	strcpy(str, defaultValue);

	return 0;
}