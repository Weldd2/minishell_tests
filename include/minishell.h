#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
# include <libgen.h>
# include <limits.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "mgc.h"
# include "env.h"
# include "builtins.h"

typedef enum e_node_type
{
	E_OPE,
	E_LEAF
}	t_node_type;

typedef enum e_ope_type
{
	E_PIPE,
	E_REDIR_IN,
	E_HEREDOC,
	E_REDIR_OUT,
	E_APPEND,
	E_OPE_TYPE_LIMIT
}	t_ope_type;

typedef enum e_leaf_type
{
	E_FUNC,
	E_FILENAME,
}	t_leaf_type;

typedef struct s_args
{
	struct s_args	*next;
	char			*arg;
}	t_args;

typedef struct s_ast
{
	t_node_type	type;
	union
	{
		struct
		{
			t_leaf_type	type;
			union
			{
				struct
				{
					char	*cmd;
					t_args	*args;
					int		nb_args;
				}	s_func;
				char	*filename;
			};
		}	s_leaf;
		struct
		{
			t_ope_type		type;
			struct s_ast	*left;
			struct s_ast	*right;
		}	s_ope;
	};
}	t_ast;

typedef struct s_ast_data
{
	char	*input;
	t_ast	*prev;
	t_ast	*root;
	t_ast	*last_ope;
}	t_ast_data;

void		print_ast(t_ast *ast, int indent);
char		*get_next_word(char **input);
t_ast		*create_ast(t_ast_data *data);
t_ast		*handle_leaf(t_ast_data *data, char *word);
t_ast		*handle_ope(t_ast_data *data, char *word);
t_ope_type	string_to_ope_type(char *word);
const char	*ope_type_to_string(t_ope_type type);
bool		is_filename(t_ast *node);
char		*str_strvjoin(int nb_args, ...);
char	*set_var_value(char *var_name, char *var_value);

#endif