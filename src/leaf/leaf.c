#include "minishell.h"

static t_ast	*create_leaf(char *s, t_ast *prev)
{
	t_ast	*leaf;

	leaf = mgc_alloc(sizeof(t_ast), 1);
	leaf->type = E_LEAF;
	if (is_filename(prev))
	{
		leaf->s_leaf.type = E_FILENAME;
		leaf->s_leaf.filename = s;
	}
	else
	{
		leaf->s_leaf.type = E_FUNC;
		leaf->s_leaf.s_func.cmd = s;
		leaf->s_leaf.s_func.nb_args = 0;
		leaf->s_leaf.s_func.args = NULL;
	}
	return (leaf);
}

static t_ast	*add_arg(t_ast *prev, char *word)
{
	t_args	*current;

	prev->s_leaf.s_func.nb_args++;
	if (!prev->s_leaf.s_func.args)
	{
		prev->s_leaf.s_func.args = mgc_alloc(sizeof(t_args), 1);
		prev->s_leaf.s_func.args->next = NULL;
		prev->s_leaf.s_func.args->arg = word;
		return (prev);
	}
	current = prev->s_leaf.s_func.args;
	while (current->next)
		current = current->next;
	current->next = mgc_alloc(sizeof(t_args), 1);
	current->next->next = NULL;
	current->next->arg = word;
	return (prev);
}

static bool	is_arg(t_ast_data *data)
{
	return (data && data->prev && data->prev->type == E_LEAF
		&& data->prev->s_leaf.type == E_FUNC);
}

t_ast	*handle_leaf(t_ast_data *data, char *word)
{
	t_ast	*leaf;

	if (is_arg(data))
	{
		add_arg(data->prev, word);
		return (create_ast(data));
	}
	leaf = create_leaf(word, data->prev);
	if (data && !data->prev)
	{
		data->prev = leaf;
		data->root = leaf;
	}
	if (data->last_ope && !data->last_ope->s_ope.left)
		data->last_ope->s_ope.left = leaf;
	else if (data->last_ope && !data->last_ope->s_ope.right)
		data->last_ope->s_ope.right = leaf;
	data->prev = leaf;
	return (create_ast(data));
}
