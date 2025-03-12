#include "minishell.h"

static const char	*ope_strings[E_OPE_TYPE_LIMIT] = {
	"|",
	"<",
	"<<",
	">",
	">>",
};

bool	is_filename(t_ast *node)
{
	// une leaf est un filename si prev est une redir qui n'a pas de filename
	if (!node)
		return (false);
	// TODO handle heredoc
	if (node->type == E_OPE && node->ope.type != E_PIPE)
	{
		if (node->ope.left && node->ope.left->type == E_LEAF)
		{
			if (node->ope.left->leaf.type == E_FILENAME)
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
		if (strcmp(word, ope_strings[index]) == 0)
			return ((t_ope_type) index);
		index++;
	}
	return (E_OPE_TYPE_LIMIT);
}

const char	*ope_type_to_string(t_ope_type type)
{
	return (ope_strings[type]);
}
