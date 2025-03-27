#include "minishell.h"

static void	expand_tilde(char **word)
{
	char	*home;
	size_t	home_len;
	size_t	old_len;
	size_t	new_len;
	char	*new_word;

	if ((*word)[0] == '~' && ((*word)[1] == '\0' || (*word)[1] == '/'))
	{
		home = get_var_value("HOME");
		if (!home)
			return ;
		home_len = strlen(home);
		old_len = strlen(*word);
		new_len = home_len + (old_len - 1);
		new_word = malloc(new_len + 1);
		if (!new_word)
			return ;
		strcpy(new_word, home);
		strcat(new_word, *word + 1);
		free(*word);
		*word = new_word;
	}
}


void	special_char(char **word)
{
	expand_tilde(word);
}