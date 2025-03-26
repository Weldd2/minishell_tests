#include "builtins.h"


int	cd(char *path)
{
	struct stat	sb;

	if (access(path, F_OK) != 0)
		return (perror("Le path n'existe pas"), 1);
	if (stat(path, &sb) != 0)
		return (perror("Erreur lors de l'obtention des informations"), 1);
	if (!S_ISDIR(sb.st_mode))
		return (fprintf(stderr, "Ce n'est pas un répertoire\n"), 1);
	if (access(path, X_OK) != 0)
		return (perror("Accès refusé au répertoire"), 1);
	if (chdir(path) != 0)
		return (perror("Erreur lors du changement de répertoire"), 1);
	
	return (0);
}