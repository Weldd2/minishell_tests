#include "minishell.h"

void	fixtures(void)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	ast->type = E_OPE;

	t_ast	*left = malloc(sizeof(t_ast));
	left->type = E_OPE;
	ast->ope.left = left;

	t_ast	*right = malloc(sizeof(t_ast));
	right->type = E_LEAF;
	right->leaf.cmd = "right";
	ast->ope.right = right;

	t_ast	*leftleft = malloc(sizeof(t_ast));
	leftleft->type = E_LEAF;
	leftleft->leaf.cmd = "left left";
	left->ope.left = leftleft;

	t_ast	*leftright = malloc(sizeof(t_ast));
	leftright->type = E_LEAF;
	leftright->leaf.cmd = "left right";
	left->ope.right = leftright;

	print_ast(ast, 0);
}

int	main(void)
{
	// fixtures();
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