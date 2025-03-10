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
	word = malloc(sizeof(char) * (len + 1));
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

t_ast *create_leaf(char *s, t_ast *prev)
{
	t_ast *leaf = malloc(sizeof(t_ast));
	leaf->type = E_LEAF;
	if (!prev || (prev->type == E_OPE && prev->ope.type == E_PIPE))
	{
		leaf->leaf.type = E_FUNC;
		leaf->leaf.func.cmd = s;
		leaf->leaf.func.nb_args = 0;
		leaf->leaf.func.args = NULL;
	}
	else
	{
		leaf->leaf.type = E_FILENAME;
		leaf->leaf.filename = s;
	}
	return (leaf);
}

t_ast *create_ope(char *s)
{
	t_ast *ope = malloc(sizeof(t_ast));
	ope->type = E_OPE;
	ope->ope.type = string_to_ope_type(s);
	ope->ope.left = NULL;
	ope->ope.right = NULL;
	return (ope);
}

t_ast *create_ast(char *input, t_ast *prev)
{
	char *word = get_next_word(&input);
	if (!word || strlen(word) == 0)
		return (prev);
	if (string_to_ope_type(word) != E_OPE_TYPE_LIMIT)
	{
		t_ast *ope = create_ope(word);
		// Affecte la feuille gauche.
		ope->ope.left = prev;
		create_ast(input, ope);
		free(get_next_word(&input));
		// Création du noeud parent (s'il y en a un).
		return (create_ast(input, ope));
	}
	else
	{
		// si c'est un argument
		if (prev && prev->type == E_LEAF && prev->leaf.type == E_FUNC)
		{
			prev->leaf.func.nb_args++;
			prev->leaf.func.args = realloc(prev->leaf.func.args, prev->leaf.func.nb_args * sizeof(char *));
			prev->leaf.func.args[prev->leaf.func.nb_args - 1] = word;
			return (create_ast(input, prev));
		}
		else
		{
			t_ast *leaf = create_leaf(word, prev);
			if (!prev)
				return (create_ast(input, leaf));
			if (prev->ope.left && !prev->ope.right)
				prev->ope.right = leaf;
		}
		return (prev);
	}
}

// TODO
// > file -> créé un fichier