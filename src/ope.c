#include "minishell.h"

static const char	*ope_strings[E_OPE_TYPE_LIMIT] = {
	"|",
	"<",
	"<<",
	">",
	">>",
};

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
