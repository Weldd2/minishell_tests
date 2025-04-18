#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <ctype.h>
# include <sys/stat.h>
# include <libgen.h>
# include <limits.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "mgc.h"
# include "env.h"

typedef struct	s_list
{
	char	*content;
	struct s_list *next;
}	t_list;

typedef struct	s_dir
{
	int		nb_dir;
	t_list	*head;
}	t_dir;

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
char		*strvjoin(int nb_args, ...);
char		*set_var_value(char *var_name, char *var_value);
void		meta_char_interpreting(char **word);
int			expand_variable(char **word, int index);
void		expand(char **word);
void		strreplace(char **str, char *rep, int start, int end);
void		special_char(char **word);
char		*ft_strjoin(char *s1, char *s2);
void		lst_add_back(t_list **list, t_list *new_node);
char		*ft_itoa(int n);
t_list		*ft_qsort(t_list *list, int (*f)(void *, void *));
void		expand_wildcard(char **word);

void	ft_echo(int argc, t_args *args);
int		ft_cd(int argc, t_args *args);
int		ft_pwd(int argc, t_args *args);
void	ft_export(int argc, t_args *args);

#endif