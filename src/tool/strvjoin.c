#include "minishell.h"

char	*strvjoin(int nb_args, ...)
{
	va_list		args;
	size_t		total_length;
	int			i;
	const char	*str;
	char		*result;
	size_t		pos;

	va_start(args, nb_args);
	i = 0;
	total_length = 0;
	while (i < nb_args)
	{
		str = va_arg(args, const char*);
		if (str)
			total_length += strlen(str);
		i++;
	}
	va_end(args);
	result = malloc(total_length + 1);
	if (!result)
		return (NULL);
	pos = 0;
	va_start(args, nb_args);
	i = 0;
	while (i < nb_args)
	{
		str = va_arg(args, const char*);
		if (str)
		{
			size_t len = strlen(str);
			memcpy(result + pos, str, len);
			pos += len;
		}
		i++;
	}
	result[pos] = '\0';
	va_end(args);
	return (result);
}
