#include "minishell.h"

static t_ast	*create_ope(char *s)
{
	t_ast	*ope;

	ope = mgc_alloc(sizeof(t_ast), 1);
	ope->type = E_OPE;
	ope->s_ope.type = string_to_ope_type(s);
	ope->s_ope.left = NULL;
	ope->s_ope.right = NULL;
	return (ope);
}

t_ast	*handle_ope(t_ast_data *data, char *word)
{
	t_ast	*ope;

	ope = create_ope(word);
	if (data->prev && data->prev->type == E_LEAF)
		ope->s_ope.left = data->root;
	if (ope->s_ope.type == E_PIPE || !data->root || !data->last_ope
		|| data->root->type == E_LEAF || data->last_ope->s_ope.right)
		data->root = ope;
	if (data->prev && data->prev->type == E_OPE)
		data->prev->s_ope.right = ope;
	data->prev = ope;
	data->last_ope = ope;
	return (create_ast(data));
}
