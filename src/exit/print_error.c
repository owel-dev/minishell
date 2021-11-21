#include "../minishell.h"

int	print_error(char *str, int error_num)
{
	printf("%s\n", str);
	return (error_num);
}
