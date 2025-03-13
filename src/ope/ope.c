/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:00:13 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/13 20:47:25 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*create_ope(char *s)
{
	t_ast	*ope;

	ope = mgc_alloc(sizeof(t_ast), 1);
	ope->type = E_OPE;
	ope->ope.type = string_to_ope_type(s);
	ope->ope.left = NULL;
	ope->ope.right = NULL;
	return (ope);
}

t_ast	*handle_ope(t_ast_data *data, char *word)
{
	t_ast	*ope;

	ope = create_ope(word);
	if (data->prev && data->prev->type == E_LEAF)
		ope->ope.left = data->root;
	if (ope->ope.type == E_PIPE || !data->root || !data->last_ope || data->root->type == E_LEAF || data->last_ope->ope.right)
		data->root = ope;
	if (data->prev && data->prev->type == E_OPE)
		data->prev->ope.right = ope;
	data->prev = ope;
	data->last_ope = ope;
	return (create_ast(data));
}
