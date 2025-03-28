#include "minishell.h"

void	lst_add_back(t_list **list, char *content)
{
	t_list	*new_node;
	t_list	*current;

	new_node = malloc(sizeof(t_list));
	new_node->content = content;
	new_node->next = NULL;
	if (!(*list))
		*list = new_node;
	else
	{
		current = *list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}
