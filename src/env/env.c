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

	env = ft_getenv();
	while (*env)
	{
		if (strncmp(*env, var_name, strlen(var_name)) == 0)
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
