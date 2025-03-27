#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void	ft_echo(int argc, t_args *args);
int		ft_cd(int argc, t_args *args);
int		ft_pwd(int argc, t_args *args);

#endif