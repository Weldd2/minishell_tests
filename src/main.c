#include "minishell.h"

int	main(void)
{
	char	*input;

	mgc_init();
	while (1)
	{
		input = readline("minishell ");
		mgc_add_block(input);
		if (strcmp(input, "exit") == 0)
			break ;
		print_ast(create_ast(input, NULL), 0);
	}
	mgc_free();
	return (0);
}
