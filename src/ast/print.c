#include "minishell.h"

void print_ast(t_ast *ast, int indent)
{
	if (!ast)
	{
		printf("test");
		return ;
	}

	for (int i = 0; i < indent; i++)
		printf("  ");

	if (ast->type == E_LEAF)
		printf("Leaf: %s\n", ast->leaf.cmd);
	else if (ast->type == E_OPE)
	{
		printf("Operator: |\n");
		print_ast(ast->ope.left, indent + 1);
		print_ast(ast->ope.right, indent + 1);
	}
}
