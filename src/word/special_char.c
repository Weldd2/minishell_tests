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

t_dir	explore_directory(void)
{
	t_list	*list = NULL;
	struct dirent *ent;
	struct stat st;
	int count = 0;

	DIR *rep = opendir(".");
	if (rep == NULL)
	{
		perror("Erreur lors de l'ouverture du répertoire");
		exit(EXIT_FAILURE);
	}
	while ((ent = readdir(rep)) != NULL)
	{

		if (ent->d_name[0] == '.' && (ent->d_name[1] == '\0' || (ent->d_name[1] == '.' && ent->d_name[2] == '\0')))
			continue;
		if (stat(ent->d_name, &st) == 0)
		{
			count++;
			lst_add_back(&list, ent->d_name);
		}
	}
	return ((t_dir) {.head = list, .nb_dir = count});
}

void	expand_wildcard(char **word)
{
	t_list  *current;
	size_t  index;
	char	*new_str;
	t_dir	dir;
	bool	expanding_single;
	bool	expanding_double;

	expanding_single = true;
	expanding_double = true;
	dir = explore_directory();
	index = 0;
	while ((*word)[index] && (*word)[index] != '*')
	{
		if ((*word)[index] == '\'')
			expanding_single = !expanding_single;
		if ((*word)[index] == '"')
			expanding_double = !expanding_double;
		index++;
	}
	if ((*word)[index] == '*' && expanding_single && expanding_double)
	{
		current = dir.head;
		new_str = strdup("");
		while (current)
		{
			new_str = ft_strjoin(new_str, current->content, true, false);
			if (current->next)
				new_str = ft_strjoin(new_str, " ", true, false);
			current = current->next;
		}
		strreplace(word, new_str, index, index + 1);
		free(new_str);
	}
}

void	special_char(char **word)
{
	expand_tilde(word);
	expand_wildcard(word);
}
