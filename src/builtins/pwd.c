#include "builtins.h"

int	ft_pwd(void)
{
	char		cwd[PATH_MAX];
	
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';
	printf("%s\n", cwd);
	return (0);
}