#include "builtins.h"

bool	check_permissions(char *path)
{
	struct stat	sb;

	return (
		(access(path, F_OK || X_OK) != 0
		|| stat(path, &sb) != 0
		|| !S_ISDIR(sb.st_mode))
	);
}

bool	handle_char(char **path, char *test, char *var_name)
{
	int	path_len;
	int	test_len;

	path_len = strlen(*path);
	test_len = strlen(test);
	if (strncmp(*path, test, test_len) == 0 && path_len == test_len)
		*path = get_var_value(var_name);
	if (!*path || **path == '\0' || strlen(*path) == 0)
		return (false);
	return (true);
}

int	ft_cd(int argc, ...)
{
	char		cwd[PATH_MAX];
	va_list		va_args;
	char		*path;

	if (argc == 0)
		path = get_var_value("HOME");
	if (argc > 1)
		fprintf(stderr, "cd: too many arguments\n");
	va_start(va_args, argc);
	path = va_arg(va_args, char *);
	va_end(va_args);
	if (!path || *path == '\0' || strlen(path) == 0)
		return (0);
	if (!handle_char(&path, "--", "HOME"))
		return (fprintf(stderr, "cd: HOME not set\n"), 1);
	if (!handle_char(&path, "-", "OLDPWD"))
		return (fprintf(stderr, "cd: OLDPWD not set\n"), 1);
	if (check_permissions(path))
		return (perror("cd"), 1);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';
	set_var_value("OLDPWD", cwd);
	if (chdir(path) != 0)
		return (perror("Erreur lors du changement de répertoire"), 1);
	return (0);
}
