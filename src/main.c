#include "minishell.h"

t_ast_data	*init_ast_data(char *input)
{
	t_ast_data	*ast_data;

	ast_data = mgc_alloc(sizeof(t_ast_data), 1);
	ast_data->input = input;
	ast_data->last_ope = NULL;
	ast_data->prev = NULL;
	ast_data->root = NULL;
	return (ast_data);
}

static inline char *readline_prompt(char *buf, size_t size)
{
	char		cwd[PATH_MAX];
	size_t		cwd_len;
	size_t		prefix_len;
	const char	*prefix;
	
	prefix = "minishell ";
	prefix_len = strlen(prefix);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';
	cwd_len = strlen(cwd);
	if (size < prefix_len + cwd_len + 2)
		return (NULL);
	memcpy(buf, prefix, prefix_len);
	memcpy(buf + prefix_len, cwd, cwd_len);
	memcpy(buf + prefix_len + cwd_len, "# ", 3);
	return (buf);
}

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv, char **envp)
{
	char		*input;
	t_ast_data	*ast_data;
	char		prompt[PATH_MAX + 20];

	ft_setenv(envp);
	mgc_init();
	while (1)
	{
		input = readline(readline_prompt(prompt, PATH_MAX + 20));
		if (input[0] != '\0')
			add_history(input);
		mgc_add_block(input);
		if (strcmp(input, "exit") == 0)
			break ;
		ast_data = init_ast_data(input);
		print_ast(create_ast(ast_data), 0);
	}
	rl_clear_history();
	mgc_free();
	return (0);
}
