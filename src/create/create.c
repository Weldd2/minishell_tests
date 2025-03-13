#include "minishell.h"

char *get_next_word(char **input)
{
	char	*word;
	ssize_t	len = 0;
	ssize_t	i;

	len = 0;
	while (**input && isspace(**input))
		(*input)++;
	while ((*input)[len] && !isspace((*input)[len]))
		len++;
	word = mgc_alloc(sizeof(char), (len + 1));
	if (!word)
		return (NULL);
	i = -1;
	while (++i < len)
		word[i] = (*input)[i];
	word[len] = '\0';
	*input += len;
	while (**input && isspace(**input))
		(*input)++;
	return (word);
}

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

// t_ast *create_ast(char *input, t_ast *prev)
// {
// 	char *word = get_next_word(&input);
// 	if (!word || strlen(word) == 0)
// 		return (prev);
// 	if (string_to_ope_type(word) != E_OPE_TYPE_LIMIT)
// 	{
// 		t_ast *ope = create_ope(word);
// 		// set prev comme parent de ope
// 		if (prev && prev->type == E_OPE && !prev->ope.right)
// 			prev->ope.right = ope;
// 		else
// 		{
// 			// set ope comme parent de prev
// 			if (prev)
// 				ope->ope.left = prev;
// 		}
// 		create_ast(input, ope);
// 		get_next_word(&input);
// 		// Création du noeud suivant (s'il y en a un).
// 		return (create_ast(input, ope));
// 	}
// 	else
// 	{
// 		// si c'est un argument
// 		if (prev && prev->type == E_LEAF && prev->leaf.type == E_FUNC)
// 		{
// 			add_arg(prev, word);
// 			return (create_ast(input, prev));
// 		}
// 		else
// 		{
// 			t_ast *leaf = create_leaf(word, prev);
// 			if (!prev)
// 				return (create_ast(input, leaf));
// 			if (prev->ope.left && !prev->ope.right)
// 				prev->ope.right = leaf;
// 			if (!prev->ope.left)
// 				prev->ope.left = leaf;
// 			create_ast(input, leaf);
// 		}
// 		return (prev);
// 	}
// }

// TODO
// cmd > file arg1