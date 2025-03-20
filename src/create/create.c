#include "minishell.h"

t_node_type	get_node_type(char *word)
{
	if (strcmp(word, "|") == 0)
		return (E_OPE);
	if (strcmp(word, ">") == 0)
		return (E_OPE);
	if (strcmp(word, ">>") == 0)
		return (E_OPE);
	if (strcmp(word, "<") == 0)
		return (E_OPE);
	if (strcmp(word, "<<") == 0)
		return (E_OPE);
	return (E_LEAF);
}

t_ast	*create_ast(t_ast_data *data)
{
	char		*word;
	t_node_type	node_type;

	word = get_next_word(&data->input);
	if (!word || strlen(word) == 0)
		return (data->root);
	node_type = get_node_type(word);
	if (node_type == E_LEAF)
		return (handle_leaf(data, word));
	if (node_type == E_OPE)
		return (handle_ope(data, word));
	return (NULL);
}
