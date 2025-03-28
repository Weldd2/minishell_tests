#include "minishell.h"

void	strreplace(char **str, char *rep, int start, int end)
{
	char	*old_str;
	char	*new_word;
	size_t  str_l;
	size_t  rep_l;
	size_t  new_word_l;

	old_str = *str;
	rep_l = strlen(rep);
	str_l = strlen(old_str);
	new_word_l = str_l - (end - start) + rep_l;
	new_word = malloc(sizeof(char) * (new_word_l + 1));
	if (!new_word)
		return;
	memcpy(new_word, old_str, start);
	memcpy(new_word + start, rep, rep_l);
	memcpy(new_word + start + rep_l, old_str + end, str_l - end);
	new_word[new_word_l] = '\0';
	free(old_str);
	*str = new_word;
}
