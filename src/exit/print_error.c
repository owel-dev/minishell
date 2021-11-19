#include "../minishell.h"

void	print_error(char *str, int error_num)
{
	printf("%s\n", str);
	exit(error_num);
}
