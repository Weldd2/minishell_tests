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

static void expand_variable(char *word, int w_index)
{
	char	*var_name;
	char	*var_value;
	size_t	word_index;
	size_t	index = 0;

	word_index = w_index + 1; // pour le signe $
	while (word[word_index] && word[word_index] != ' ' && word[word_index != '}'])
		word_index++;
	var_name = malloc(sizeof(char) * word_index + 1);
	word_index = w_index + 1;
	word_index += word[1] == '{';
	while (word[word_index] && word[word_index] != ' ' && word[word_index] != '}')
	{
		var_name[index] = word[word_index];
		index++;
		word_index++;
	}
	var_name[index] = '\0';
	var_value = get_var_value(var_name);
	printf("%s=%s\n", var_name, var_value);
	free(var_name);
}

static void expand_word(char *word)
{
	bool	expand;
	int		len;

	expand = true;
	len = 0;
	while (word[len])
	{
		if (word[len] == '"')
			expand = !expand;
		if (word[len] == '$' && expand && (len > 0 || word[len - 1] != '\\'))
			expand_variable(word, len);
		len++;
	}
	if (!expand)
		printf("ERROR PARSING -> \" not closed\n"); // throw error
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
	expand_word(word);
	remove_quotes(word);
	return (word);
}
