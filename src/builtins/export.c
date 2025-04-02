#include "minishell.h"

void	ft_export(int argc,__attribute__((unused)) t_args *args)
{
	char	**env;
	char	*var_name;
	int		i;

	if (argc == 0)
	{
		env = ft_getenv();
		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
	}
	else if (argc > 0 && args)
	{
		i = 0;
		while (args->arg && args->arg[i] != '=')
			i++;
		var_name = mgc_alloc(sizeof(char), i + 1);
		var_name = strncpy(var_name, args->arg, i);
		var_name[i] = '\0';
		set_var_value(var_name, args->arg + i + 1);
	}
}
