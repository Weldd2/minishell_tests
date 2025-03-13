#include "minishell.h"

int	main(void)
{
	char		*input;
	t_ast_data	*ast_data;

	mgc_init();
	while (1)
	{
		input = readline("minishell ");
		mgc_add_block(input);
		if (strcmp(input, "exit") == 0)
			break ;
		ast_data = mgc_alloc(sizeof(t_ast_data), 1);
		ast_data->input = input;
		ast_data->last_ope = NULL;
		print_ast(create_ast(ast_data), 0);
	}
	mgc_free();
	return (0);
}
