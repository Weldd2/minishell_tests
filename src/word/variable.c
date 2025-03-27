#include "minishell.h"

static char	*locate(char *str, int *start, int *end)
{
	int		i;
	char	*var_name;
	bool	bracket;
	int		var_name_len;
	bool	expanding;

	i = 0;
	expanding = true;
	while (str[i] && str[i] != '$')
	{
		if (str[i] == '\'')
			expanding = !expanding;
		i++;
	}
	if (str[i] == '$' && expanding)
	{
		*start = i++;
		bracket = (str[i] == '{');
		while (str[i] && !isspace(str[i]) && str[i] != '}' && str[i] != '$'
			&& str[i] != '"' && str[i] != '/') // TODO HANDLE { i.e echo $H{OME}
			i++;
		bracket = (bracket && str[i] == '}');
		*end = i + bracket;
		var_name_len = (*end - *start) - 1 - (2 * bracket);
		var_name = mgc_alloc(sizeof(char), var_name_len + 1);
		strncpy(var_name, str + *start + 1 + bracket, var_name_len);
		var_name[var_name_len] = '\0';
		return (var_name);
	}
	return ("");
}

void	expand(char **word)
{
	char	*var_name;
	int		start;
	int		end;

	do
	{
		start = 0;
		end = 0;
		var_name = locate(*word, &start, &end);
		if (strlen(var_name) != 0)
		{
			char *var_value = get_var_value(var_name);
			printf("var_value = %s\n", var_value);
			strreplace(word, var_value, start, end);
		}
	} while (end != 0);
}
// TODO echo $HOME/workspace
// /root/workspace