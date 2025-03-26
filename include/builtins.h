#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void	echo(int nb_arg, ...);
int		cd(char *path);
int		pwd(void);

#endif