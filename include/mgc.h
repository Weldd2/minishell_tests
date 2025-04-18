#ifndef MGC_H
# define MGC_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_mgc_block_list
{
	void					*block;
	struct s_mgc_block_list	*next;
}	t_mgc_block_list;

typedef struct s_mgc
{
	struct s_mgc_block_list	*first;
	struct s_mgc_block_list	*last;
}	t_mgc_;

typedef t_mgc_*	t_mgc;

void		mgc_init(void);
void		*mgc_alloc(size_t size, size_t nb_elem);
void		mgc_add_block(void *block);
void		mgc_free(void);

#endif