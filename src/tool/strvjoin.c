#include "minishell.h"

static char	**va_list_to_args(int nb_arg, va_list va_args)
{
	int		i;
	char	**args;

	args = calloc(sizeof(char *), nb_arg + 1);
	if (!args)
		return (exit(EXIT_FAILURE), NULL);
	i = -1;
	while (++i < nb_arg)
		args[i] = va_arg(va_args, char *);
	return (args);
}

static int	get_new_str_size(char **args)
{
	int	r;

	r = 0;
	while (args && *args)
	{
		r += strlen(*args);
		args++;
	}
	return (r);
}

char	*str_strvjoin(int nb_args, ...)
{
	va_list	ap;
	char	**args;
	char	*r;
	int		index;

	va_start(ap, nb_args);
	args = va_list_to_args(nb_args, ap);
	r = mgc_alloc(sizeof(char), get_new_str_size(args) + 1);
	index = 0;
	int	r_index = 0;
	while (index < nb_args)
	{
		strncpy(r + r_index, args[index], strlen(args[index]));
		r_index += strlen(args[index]);
		index++;
	}
	r[r_index] = '\0';
	free(args);
	va_end(ap);
	return (r);
}
