#include "minishell.h"

static ssize_t	char_count_until(char **input, ssize_t len, char until)
{
	while ((*input)[len] != until)
		len++;
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
		if (*src == '\\' && *(src + 1) == '"')
		{
			*dst++ = '"';
			src += 2;
		}
		else if (*src == '"')
			src++;
		else
			*dst++ = *src++;
	}
	*dst = '\0';
}

static ssize_t	get_word_len(char **input)
{
	ssize_t	len;

	len = 0;
	while ((*input)[len] && !isspace((*input)[len]))
	{
		if ((*input)[len] == '"')
			len += char_count_until(input, len + 1, '"');
		if ((*input)[len] == '\'')
			len += char_count_until(input, len + 1, '\'');
		len++;
	}
	return (len);
}

char	*get_next_word(char **input)
{
	char	*word;
	ssize_t	len;

	while (**input && isspace(**input))
		(*input)++;
	len = get_word_len(input);
	word = mgc_alloc(sizeof(char), (len + 1));
	if (!word)
		return (NULL);
	strncpy(word, *input, len);
	word[len] = '\0';
	*input += len;
	while (**input && isspace(**input))
		(*input)++;
	remove_quotes(word);
	return (word);
}

// TODO
// valid : cmd|cmd cmd>file cmd<file
