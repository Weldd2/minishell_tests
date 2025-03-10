#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_node_type
{
	E_OPE,
	E_LEAF
}	t_node_type;

typedef enum e_ope
{
	PIPE,
	REDIR_IN,
	HEREDOC,
	REDIR_OUT,
	APPEND
}	t_ope;

typedef struct s_ast
{
	t_node_type	type;
	union
	{
		struct
		{
			char	*cmd;
			char	**args;
		} leaf;
		struct
		{
			t_ope			op;
			struct s_ast	*left;
			struct s_ast	*right;
		} ope;
	};
}	t_ast;


void print_ast(t_ast *ast, int indent);
t_ast	*create_ast(char *input, t_ast *prev);

#endif