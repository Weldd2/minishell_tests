#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2, bool free_s1, bool free_s2)
{
	size_t  len1;
	size_t  len2;
	char	*result;

	len1 = s1 ? strlen(s1) : 0;
	len2 = s2 ? strlen(s2) : 0;
	
	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
		return (NULL);
	if (s1)
		memcpy(result, s1, len1);
	if (s2)
		memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	if (free_s1 && s1)
		free(s1);
	if (free_s2 && s2)
		free(s2);
	return (result);
}
