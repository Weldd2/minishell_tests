#include "minishell.h"

static ssize_t	count_chars_until(char *input, ssize_t pos, char until)
{
	while (input[pos] && input[pos] != until)
		pos++;
	if (input[pos] != until)
		return (-1);
	return (pos);
}

static ssize_t	get_word_len(char *input)
{
	ssize_t	len;
	ssize_t	tmp;
	char	c;

	len = 0;
	c = 0;
	while (input[len] && !isspace(input[len]))
	{
		if (input[len] == '"' || input[len] == '\'')
		{
			c = input[len];
			tmp = count_chars_until(input, len + 1, c);
			if (tmp == -1)
				return (fprintf(stderr, "%c is not closed\n", c), -1);
			len += tmp;
		}
		len++;
	}
	return (len);
}

static void	remove_quotes(char *str)
{
	char	*src;
	char	*dst;

	src = str;
	dst = str;
	while (*src)
	{
		if (*src == '"' || *src == '\'')
			src++;
		else
			*dst++ = *src++;
	}
	*dst = '\0';
}

char	*get_next_word(char **input)
{
	char	*word;
	int		len;

	while (**input && isspace(**input))
		(*input)++;
	len = get_word_len(*input);
	if (len < 0)
		return (NULL);
	word = mgc_alloc(sizeof(char), len + 1);
	strncpy(word, *input, len);
	*input += len;
	word[len] = '\0';
	if (strlen(word) == 0)
		return (word);
	expand(&word);
	special_char(&word);
	remove_quotes(word);
	return (word);
}
