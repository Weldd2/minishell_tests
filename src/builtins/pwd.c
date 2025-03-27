#include "builtins.h"

int	ft_pwd(int argc, t_args *args)
{
	char		cwd[PATH_MAX];

	if (argc != 0)
		return (fprintf(stderr, "pwd: too many arguments\n"), 1);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';
	printf("%s\n", cwd);
	return (0);
}