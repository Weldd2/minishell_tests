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
	{
		printf("Leaf -> ");
		printf("type : %s, ", ast->leaf.type == E_FILENAME ? "filename" : "command");
		if (ast->leaf.type == E_FUNC)
		{
			printf("name : %s", ast->leaf.func.cmd);
			if (ast->leaf.func.nb_args != 0)
				printf(", args [%d]: ", ast->leaf.func.nb_args);
			for (int j = 0; j < ast->leaf.func.nb_args; j++)
				printf("%s ", ast->leaf.func.args[j]);
		}
		else
			printf("name : %s", ast->leaf.filename);
		printf("\n");
	}
	else if (ast->type == E_OPE)
	{
		printf("Operator: %s\n", ope_type_to_string(ast->ope.type));
		print_ast(ast->ope.left, indent + 1);
		print_ast(ast->ope.right, indent + 1);
	}
}
