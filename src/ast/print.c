#include "minishell.h"

static void	print_args(t_args *current)
{
	if (!current)
		return ;
	printf("%s ", current->arg);
	print_args(current->next);
}

static void	print_leaf(t_ast *ast)
{
	printf("Leaf -> ");
	if (ast->s_leaf.type == E_FILENAME)
		printf("type : filename, name %s", ast->s_leaf.filename);
	else
	{
		printf("type : func, name %s", ast->s_leaf.s_func.cmd);
		if (ast->s_leaf.s_func.nb_args != 0)
			printf(", args [%d]: ", ast->s_leaf.s_func.nb_args);
		print_args(ast->s_leaf.s_func.args);
	}
	printf("\n");
}

void	print_ast(t_ast *ast, int indent)
{
	int	i;

	if (!ast)
		return ;
	i = -1;
	while (++i < indent)
		printf("  ");
	if (ast->type == E_LEAF)
		print_leaf(ast);
	else if (ast->type == E_OPE)
	{
		printf("Operator: %s\n", ope_type_to_string(ast->s_ope.type));
		print_ast(ast->s_ope.left, indent + 1);
		print_ast(ast->s_ope.right, indent + 1);
	}
}
