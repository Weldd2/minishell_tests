#include "builtins.h"


int	cd(char *path)
{
	struct stat	sb;
	char		cwd[PATH_MAX];

	if (!path || *path == '\0' || strlen(path) == 0)
		path = get_var_value("HOME");
	if (!path || *path == '\0' || strlen(path) == 0)
		return (0);
	if (strncmp(path, "-", 1) == 0 && strlen(path) == 1)
		path = get_var_value("OLDPWD");
	if (access(path, F_OK) != 0)
		return (perror("Le path n'existe pas"), 1);
	if (stat(path, &sb) != 0)
		return (perror("Erreur lors de l'obtention des informations"), 1);
	if (!S_ISDIR(sb.st_mode))
		return (fprintf(stderr, "Ce n'est pas un répertoire\n"), 1);
	if (access(path, X_OK) != 0)
		return (perror("Accès refusé au répertoire"), 1);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';
	set_var_value("OLDPWD", cwd);
	if (chdir(path) != 0)
		return (perror("Erreur lors du changement de répertoire"), 1);
	return (0);
}