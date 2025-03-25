#include "minishell.h"

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv, char **envp)
{
	char		*input;
	t_ast_data	*ast_data;

	ft_setenv(envp);
	mgc_init();
	while (1)
	{
		input = readline("minishell ");
		if (input[0] != '\0')
			add_history(input);
		mgc_add_block(input);
		if (strcmp(input, "exit") == 0)
			break ;
		ast_data = mgc_alloc(sizeof(t_ast_data), 1);
		ast_data->input = input;
		ast_data->last_ope = NULL;
		ast_data->prev = NULL;
		ast_data->root = NULL;
		print_ast(create_ast(ast_data), 0);
	}
	rl_clear_history();
	mgc_free();
	return (0);
}
