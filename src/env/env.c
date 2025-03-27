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

char	*set_var_value(char *var_name, char *var_value)
{
	char	**env;
	char	*new_var;
	int		i;
	int		len;
	char **new_env;

	len = strlen(var_name);
	env = ft_getenv();
	new_var = str_strvjoin(3, var_name, "=", var_value);
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (env[i] = new_var, env[i]);
		i++;
	}
	new_env = mgc_alloc(sizeof(char *), (i + 2));
	memcpy(new_env, env, sizeof(char *) * i);
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	ft_setenv(new_env);
	return (new_env[i]);
}
