#include "minishell.h"

char	*get_word(char *s)
{
	char	*word;
	ssize_t	len;
	ssize_t	index;

	len = 0;
	while (s[len] && s[len] != ' ')
		len++;
	word = malloc(sizeof(char) * (len + 1));
	index = 0;
	while (index < len)
	{
		word[index] = s[index];
		index++;
	}
	word[index] = '\0';
	return (word);
}

t_ast	*create_leaf(char *s)
{
	t_ast	*leaf = malloc(sizeof(t_ast));
	leaf->type = E_LEAF;
	leaf->leaf.cmd = s;
	return (leaf);
}

t_ast	*create_ope(void)
{
	t_ast	*ope = malloc(sizeof(t_ast));
	ope->type = E_OPE;
	ope->ope.left = NULL;
	ope->ope.right = NULL;
	return (ope);
}

t_ast	*create_ast(char *input, t_ast *prev)
{
	while (*input == ' ')
		input++;
	char *word = get_word(input);
	input += strlen(word);
	if (!word || strlen(word) == 0)
		return (prev);
	if (strcmp(word, "|") == 0)
	{
		t_ast	*ope;
		ope = create_ope();
		// set la leaf gauche
		ope->ope.left = prev;
		create_ast(input, ope);
		while (*input == ' ')
			input++;
		char *next_word = get_word(input);
		input += strlen(next_word);
		// creer le mot parent (si il y en a un)
		return (create_ast(input, ope));
	}
	else
	{
		t_ast *leaf;
		leaf = create_leaf(word);
		if (!prev)
			return (create_ast(input, leaf));
		if (prev && prev->type == E_OPE)
		{
			if (prev->ope.left && !prev->ope.right)
				prev->ope.right = leaf;
		}
		return (prev);
	}
}
