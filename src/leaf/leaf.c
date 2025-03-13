#include "minishell.h"

static t_ast *create_leaf(char *s, t_ast *prev)
{
	t_ast	*leaf;

	leaf = mgc_alloc(sizeof(t_ast), 1);
	leaf->type = E_LEAF;
	if (is_filename(prev))
	{
		leaf->leaf.type = E_FILENAME;
		leaf->leaf.filename = s;
	}
	else
	{
		leaf->leaf.type = E_FUNC;
		leaf->leaf.func.cmd = s;
		leaf->leaf.func.nb_args = 0;
		leaf->leaf.func.args = NULL;
	}
	return (leaf);
}

__attribute__((unused)) static t_ast	*add_arg(t_ast *prev, char *word)
{
	t_args	*current;

	prev->leaf.func.nb_args++;
	if (!prev->leaf.func.args)
	{
		prev->leaf.func.args = mgc_alloc(sizeof(t_args), 1);
		prev->leaf.func.args->next = NULL;
		prev->leaf.func.args->arg = word;
		return (prev);
	}
	current = prev->leaf.func.args;
	while (current->next)
		current = current->next;
	current->next = mgc_alloc(sizeof(t_args), 1);
	current->next->next = NULL;
	current->next->arg = word;
	return (prev);
}

t_ast	*handle_leaf(t_ast_data *data, char *word)
{
	t_ast	*leaf;

	// handle arg
	if (data->prev && data->prev->type == E_LEAF && data->prev->leaf.type == E_FUNC)
	{
		add_arg(data->prev, word);
		return (create_ast(data));
	}
	leaf = create_leaf(word, data->prev);
	if (!data->prev)
	{
		data->prev = leaf;
		data->root = leaf;
	}
	if (data->last_ope && !data->last_ope->ope.left)
		data->last_ope->ope.left = leaf;
	else if (data->last_ope && !data->last_ope->ope.right)
		data->last_ope->ope.right = leaf;
	data->prev = leaf;
	return (create_ast(data));
}
