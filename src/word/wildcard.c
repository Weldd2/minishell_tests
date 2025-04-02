#include "minishell.h"
#include <string.h>

static int	ascii_sort(void *a, void *b)
{
	const char	*str1;
	const char	*str2;

	str1 = (const char *)a;
	str2 = (const char *)b;
	return (strcmp(str1, str2));
}


t_list	*create_node(char *content)
{
	t_list	*r;

	r = mgc_alloc(sizeof(t_list), 1);
	r->content = content;
	r->next = NULL;
	return (r);
}

t_dir	explore_directory(void)
{
	t_list	*list;
	struct dirent *ent;
	struct stat st;
	int count = 0;

	list = NULL;
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
			lst_add_back(&list, create_node(strdup(ent->d_name)));
		}
	}
	closedir(rep);
	return ((t_dir) {.head = ft_qsort(list, ascii_sort), .nb_dir = count});
}

bool	match(const char *pattern, const char *str)
{
	if (*pattern == '\0')
		return *str == '\0';
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (*pattern == '\0')
			return (true);
		while (*str)
		{
			if (match(pattern, str))
				return (true);
			str++;
		}
		return (false);
	}
	else 
	{
		if (*pattern == *str)
			return (match(pattern + 1, str + 1));
		else
			return (false);
	}
}


char	*compute_pattern(char *pattern)
{
	t_dir	dir;
	t_list	*current;
	char	*file_n;
	char	*rep;

	dir = explore_directory();
	current = dir.head;
	rep = NULL;
	while (current)
	{
		file_n = current->content;
		if (pattern[0] != '.' && file_n[0] == '.')
		{
			current = current->next;
			continue;
		}
		if (match(pattern, file_n))
		{
			if (!rep)
				rep = file_n;
			else
				rep = strvjoin(3, rep, " ", file_n);
		}
		current = current->next;
	}
	return (rep);
}

void	expand_wildcard(char **word)
{
	size_t	index;
	
	index = 0;
	while ((*word)[index] && !isspace((*word)[index]) && (*word)[index] != '*')
		index++;
	if ((*word)[index] != '*')
		return ;
	index = 0;
	while ((*word)[index] && !isspace((*word)[index]))
		index++;
	char	*w;
	w = compute_pattern(*word);
	if (!w)
		w = "";
	strreplace(word, w, 0, index);
}
