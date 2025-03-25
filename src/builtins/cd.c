#include "builtins.h"

void	cd(char *path) // TODO ongoing
{
	if (access(path, R_OK | X_OK) == -1)
		exit(EXIT_FAILURE);
	if (chdir(path) == -1)
		exit(EXIT_FAILURE);
	return ;
}