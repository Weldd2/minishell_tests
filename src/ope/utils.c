#include "minishell.h"

static const char	*g_ope_strings[E_OPE_TYPE_LIMIT] = {
	"|",
	"<",
	"<<",
	">",
	">>",
};

// TODO handle heredoc
bool	is_filename(t_ast *node)
{
	if (!node)
		return (false);
	if (node->type == E_OPE && node->s_ope.type != E_PIPE)
	{
		if (node->s_ope.left && node->s_ope.left->type == E_LEAF)
		{
			if (node->s_ope.left->s_leaf.type == E_FILENAME)
				return (false);
			return (true);
		}
		return (true);
	}
	return (false);
}

t_ope_type	string_to_ope_type(char *word)
{
	size_t		index;

	index = 0;
	while (index < E_OPE_TYPE_LIMIT)
	{
		if (strcmp(word, g_ope_strings[index]) == 0)
			return ((t_ope_type) index);
		index++;
	}
	return (E_OPE_TYPE_LIMIT);
}

const char	*ope_type_to_string(t_ope_type type)
{
	return (g_ope_strings[type]);
}
