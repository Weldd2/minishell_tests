#include "minishell.h"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell ");
		if (strcmp(input, "exit") == 0)
			exit(EXIT_SUCCESS);
		print_ast(create_ast(input, NULL), 0);
	}
	return (0);
}