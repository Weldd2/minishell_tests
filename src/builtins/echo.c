#include "builtins.h"

static void	print_args(char **args, bool nflag)
{
	int	i;

	if ((*args)[0] == '\0')
		return ;
	printf("%s", args[0]);
	i = 1;
	while (args[i] != NULL)
	{
		printf(" %s", args[i]);
		i++;
	}
	if (!nflag)
		printf("\n");
}

static char	**va_list_to_args(int nb_arg, va_list va_args, bool *nflag)
{
	int		i;
	int		j;
	char	*arg;
	char	**args;

	args = calloc(sizeof(char *), nb_arg + 1);
	if (!args)
		return (exit(EXIT_FAILURE), NULL);
	i = 0;
	j = 0;
	while (i < nb_arg)
	{
		arg = va_arg(va_args, char *);
		if (strcmp(arg, "-n") == 0)
			*nflag = true;
		else
		{
			args[j] = arg;
			j++;
		}
		i++;
	}
	return (args);
}

void	ft_echo(int nb_arg, ...)
{
	va_list	va_args;
	char	**args;
	bool	nflag;

	nflag = false;
	va_start(va_args, nb_arg);
	args = va_list_to_args(nb_arg, va_args, &nflag);
	if (args && *args)
		print_args(args, nflag);
	va_end(va_args);
}
