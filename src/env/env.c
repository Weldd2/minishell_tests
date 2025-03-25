#include "minishell.h"
#include "env.h"

void	**env(void)
{
	static void	*env;

	return (&env);
}

inline void	*ft_getenv(void)
{
	return (*env());
}

inline void	ft_setenv(void *e)
{
	*env() = e;
}

char	*get_var(char *var_name)
{
	char	**env;
	int		len;

	env = ft_getenv();
	len = strlen(var_name);
	while (*env)
	{
		if (strncmp(*env, var_name, len) == 0 && (*env)[len] == '=')
			return (*env);
		env++;
	}
	return (NULL);
}

char	*get_var_value(char *var_name)
{
	char	*var_value;

	var_value = get_var(var_name);
	if (var_value)
		return (get_var(var_name) + strlen(var_name) + 1);
	return ("");
}

void	set_var_value(char *var_name, char *var_value) // TODO handle adding
{
	char	**env;
	char	*new_var;
	int		len;

	len = strlen(var_name);
	env = ft_getenv();
	new_var = str_strvjoin(3, var_name, "=", var_value);
	while (*env)
	{
		if (strncmp(*env, var_name, len) == 0 && (*env)[len] == '=')
			*env = new_var;
		env++;
	}
	return ;
}
