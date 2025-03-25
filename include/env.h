#ifndef ENV_H
# define ENV_H

void	ft_setenv(void *e);
void	*ft_getenv(void);
char	*get_var(char *var_name);
char	*get_var_value(char *var_name);

#endif