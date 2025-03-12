/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:38:09 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/12 14:36:30 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mgc.h"

static t_mgc	mgc_head(void)
{
	static t_mgc	mgc = NULL;

	if (!mgc)
	{
		mgc = malloc(sizeof(t_mgc_));
		if (!mgc)
			return (NULL);
		mgc->first = NULL;
		mgc->last = NULL;
	}
	return (mgc);
}

void	mgc_init(void)
{
	mgc_head();
}

void	*mgc_alloc(size_t size, size_t nb_elem)
{
	void	*block;

	block = malloc(size * nb_elem);
	if (!block)
		return (NULL);
	mgc_add_block(block);
	return (block);
}

void	mgc_add_block(void *block)
{
	t_mgc_block_list	*new_block;
	t_mgc				mgc;

	mgc = mgc_head();
	new_block = malloc(sizeof(t_mgc_block_list));
	if (!new_block)
		exit(EXIT_FAILURE);
	new_block->block = block;
	new_block->next = NULL;
	if (mgc->last)
		mgc->last->next = new_block;
	mgc->last = new_block;
	if (!mgc->first)
		mgc->first = new_block;
}

void	mgc_free(void)
{
	t_mgc_block_list	*current;
	t_mgc_block_list	*tmp;
	t_mgc				mgc;

	mgc = mgc_head();
	current = mgc->first;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->block);
		tmp->block = NULL;
		free(tmp);
		tmp = NULL;
	}
	free(mgc);
	mgc = NULL;
}
