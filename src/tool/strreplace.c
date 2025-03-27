#include "minishell.h"

void	strreplace(char **str, char *rep, int start, int end)
{
	int		new_word_l;
	char	*new_word;
	int		str_l;
	int		rep_l;

	rep_l = strlen(rep);
	str_l = strlen(*str);
	new_word_l = str_l - (end - start) + rep_l;
	new_word = malloc(sizeof(char) * new_word_l);
	strncpy(new_word, *str, start);
	strncpy(new_word + start, rep, rep_l);
	strncpy(new_word + start + rep_l, (*str) + end, str_l);
	*str = new_word;
}
