#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "mgc.h"

# ifdef DEBUG
#  include <assert.h>
#  define EX(fmt, ...) \
    do { \
        fprintf(stderr, "%s:%d, %s: " fmt "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
        abort(); \
    } while (0)
# endif

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
				} func;
				char *filename;
			};
		} leaf;
		struct
		{
			t_ope_type		type;
			struct s_ast	*left;
			struct s_ast	*right;
		} ope;
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
t_ast		*create_ast(t_ast_data *data);
t_ast		*handle_leaf(t_ast_data *data, char *word);
t_ast		*handle_ope(t_ast_data *data, char *word);
t_ope_type	string_to_ope_type(char *word);
const char	*ope_type_to_string(t_ope_type type);
bool		is_filename(t_ast *node);

#endif