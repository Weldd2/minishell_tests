#include "minishell.h"

static inline bool	is_bracketed(char *str, int i, int vst)
{
	return (str[i] == '}' && str[vst + 1] == '{');
}

static bool	locate(char *str, int *vst, int *vnst, int *vnd, int *vnnd)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] != '$')
		return (false);
	*vst = i;
	i++;
	if (str[i] == '{')
		i++;
	*vnst = i;
	while (str[i] && (isalnum(str[i]) || (i != *vnst && str[i] == '_')))
		i++;
	if (i == *vnst && str[i] == '$')
		i++;
	*vnnd = i;
	*vnd = i + is_bracketed(str, i, *vst);
	if (*vnst == *vnnd && !is_bracketed(str, i, *vst))
		return (false);
	return (true);
}

// vst = variable start (start on $ sign)
// vnd = variable end
// vnst = variable name start (after the $ and the bracket)
// vnnd = variable name end
void	expand(char **word)
{
	char	*var_name;
	int	vst;
	int vnst;
	int vnd;
	int vnnd;

	vst = 0;
	vnst = 0;
	vnd = 0;
	vnnd = 0;
	while (locate(*word, &vst, &vnst, &vnd, &vnnd))
	{
		var_name = mgc_alloc(sizeof(char), ((vnnd - vnst) + 2));
		var_name = strncpy(var_name, (*word) + vnst, vnnd);
		var_name[((vnnd - vnst))] = '\0';
		strreplace(word, get_var_value(var_name), vst, vnd);
	}
}
