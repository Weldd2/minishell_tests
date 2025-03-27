#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void	ft_echo(int nb_arg, ...);
int		ft_cd(char *path);
int		ft_pwd(void);

#endif