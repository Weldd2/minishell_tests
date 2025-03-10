#include "minishell.h"

void print_ast(t_ast *ast, int indent)
{
	int	i;

	if (!ast)
		return ;
	i = -1;
	while (++i < indent)
		printf("  ");
	if (ast->type == E_LEAF)
		printf("Leaf: %s %s\n", ast->leaf.type == E_FILENAME ? "filename" : "command", ast->leaf.func.cmd);
	else if (ast->type == E_OPE)
	{
		printf("Operator: %s\n", ope_type_to_string(ast->ope.type));
		print_ast(ast->ope.left, indent + 1);
		print_ast(ast->ope.right, indent + 1);
	}
}
