#include "builtins.h"

void	ft_echo(int argc, t_args *args)
{
	bool	nflag;
	t_args	*current;

	nflag = false;
	if (!args || strlen(args->arg) == 0)
		return ;
	current = args;
	printf("%s", current->arg);
	while (current)
	{
		if (strncmp(current->arg, "-n", 2) == 0 && strlen(current->arg) == 2)
			nflag = true;
		else
			printf(" %s", current->arg);
	}
	if (!nflag)
		printf("\n");
}
