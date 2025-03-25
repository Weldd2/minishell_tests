#include "minishell.h"

static ssize_t	count_chars_until(char **input, ssize_t pos, char until)
{
	while ((*input)[pos] && (*input)[pos] != until)
		pos++;
	return (pos);
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

static ssize_t	get_word_length(char **input)
{
	ssize_t	len;

	len = 0;
	while ((*input)[len] && !isspace((*input)[len]))
	{
		if ((*input)[len] == '"')
			len = count_chars_until(input, len + 1, '"');
		else if ((*input)[len] == '\'')
			len = count_chars_until(input, len + 1, '\'');
		len++;
	}
	return (len);
}

static bool	is_variable_bracketed(char *word, int w_index)
{
	if (!word || word[w_index] != '$')
		return (false);
	w_index++;
	if (word[w_index] == '{')
	{
		w_index++;
		while (word[w_index] && word[w_index] != '}' && word[w_index] != ' ')
			w_index++;
	}
	return (word[w_index] == '}');
}

static char	*extract_variable_name(char **word, int w_index, bool *bracket)
{
	size_t	start;
	size_t	end;
	size_t	name_len;
	char	*var_name;

	*bracket = is_variable_bracketed(*word, w_index);
	start = w_index + 1 + *bracket;
	end = start;
	while ((*word)[end] && (*word)[end] != ' ' &&
			(*word)[end] != '}' && (*word)[end] != '{' &&
			(*word)[end] != '$' && (*word)[end] != '"')
		end++;
	name_len = end - start;
	var_name = malloc(sizeof(char) * (name_len + 1));
	if (!var_name)
		return (NULL);
	memcpy(var_name, &((*word)[start]), name_len);
	var_name[name_len] = '\0';
	return (var_name);
}

static size_t	compute_suffix_offset(int index, size_t var_name_len, bool bracketed)
{
	size_t	offset;

	offset = index + 1 + var_name_len;
	if (bracketed)
		offset = offset + 2;
	return (offset);
}

/*
 * Constructs a new word with the variable expanded.
 * It copies the prefix (up to the variable), appends the variable's value,
 * and then appends the suffix (the remainder of the word).
 */
static char *construct_new_word(char *old_word, int index, const char *var_value, size_t suffix_offset)
{
	size_t	prefix_length;
	size_t	var_value_length;
	size_t	suffix_length;
	size_t	new_length;
	char	*new_word;

	prefix_length = (size_t)index;
	var_value_length = strlen(var_value);
	suffix_length = strlen(old_word) - suffix_offset;
	new_length = prefix_length + var_value_length + suffix_length;
	new_word = malloc(new_length + 1);
	if (!new_word)
		return (NULL);
	strncpy(new_word, old_word, prefix_length);
	new_word[prefix_length] = '\0';
	strcat(new_word, var_value);
	strcat(new_word, old_word + suffix_offset);
	return (new_word);
}

/*
 * Expands the variable at the specified index in the word.
 * It extracts the variable name, obtains its value, computes the suffix offset,
 * builds the new word with the expanded variable, frees the old word, and returns
 * the length of the inserted variable value.
 */
// TODO NORM
static int	expand_variable(char **word, int index)
{
	bool	bracketed;
	char	*var_name;
	char	*var_value;
	char	*new_word;
	size_t	var_name_length;
	size_t	suffix_offset;

	bracketed = false;
	var_name = extract_variable_name(word, index, &bracketed);
	printf("var_name = %s\n", var_name);
	if (!var_name)
		return (0);
	var_value = get_var_value(var_name);
	printf("var_value = %s\n", var_value);
	var_name_length = strlen(var_name);
	suffix_offset = compute_suffix_offset(index, var_name_length, bracketed);
	new_word = construct_new_word(*word, index, var_value, suffix_offset);
	mgc_add_block(new_word);
	free(var_name);
	*word = new_word;
	return (int)strlen(var_value);
}


/*
 * Expands all variables in the word.
 * Respects single quotes by not expanding variables within them.
 * If an opening quote is not closed, prints an error message.
 */
// TODO check double quote
/*
	./minishell
	minishell echo "$HOME"
	Leaf -> type : func, name echo
	minishell ehco '$HOME'
	Leaf -> type : func, name ehco, args [1]: '$HOME' 
	minishell exit
*/
static void	expand_word(char **word)
{
	bool	expand;
	int		index;

	index = 0;
	expand = true;
	while ((*word)[index])
	{
		if ((*word)[index] == '\'')
			expand = !expand;
		if ((*word)[index] == '$' && expand && (index == 0 || (*word)[index - 1] != '\\'))
			index += expand_variable(word, index);
		else
			index++;
	}
	if (!expand)
		printf("ERROR PARSING -> \" not closed\n"); // Handle error appropriately
}

/*
 * Retrieves the next word from the input string.
 * It skips leading spaces, extracts a word, performs variable expansion,
 * removes quotes, and then returns the processed word.
 */
char	*get_next_word(char **input)
{
	char	*word;
	ssize_t	len;

	while (**input && isspace(**input))
		(*input)++;
	len = get_word_length(input);
	word = mgc_alloc(sizeof(char), (len + 1));
	if (!word)
		return (NULL);
	strncpy(word, *input, len);
	word[len] = '\0';
	*input += len;
	while (**input && isspace(**input))
		(*input)++;
	expand_word(&word);
	remove_quotes(word);
	return (word);
}
